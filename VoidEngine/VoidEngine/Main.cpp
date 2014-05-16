#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <cmath>

#include "glsl.h"
#include "glutwindow.h"
#include "glApplication.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "FileHandling.hpp"
#include "FreeLookCamera.hpp"
#include "TopDownCamera.hpp"
#include "ThirdPersonCamera.hpp"
#include "Physics.hpp"

using namespace std;

glm::vec3 calculateNormal(vector<glm::vec3>);

class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader *shader;

private:
    Level* level;

	Camera* camera;
    FreeLookCamera freeLookCamera;
	TopDownCamera topDownCamera;
	ThirdPersonCamera* thirdPersonCamera;
    const int numberOfObjects = 5;
    GLuint vao[5], buffers[15], elementCounts[5];
    std::vector<glm::vec4> diffuseColors, ambientColors;
    std::vector<glm::mat4> mMatrices;

    unsigned timeSinceStart;
    float cameraAngle;
    float cameraRadius;
	
    float physicsLagTime = 0.0f;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	const float rotateX = 30.f;
    const float fixedUpdateTime = 1.0f / 60.0f;

	bool mouseDown = false;
	std::vector<char> keysPressed;
	int mouse_x, mouse_y;

public:
    myWindow(string inputFilename)
    {
        // Load Level
        level = FileHandling::ReadFile(inputFilename);
        thirdPersonCamera = new ThirdPersonCamera(level->getGolfBall());
    }

    virtual void OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->begin();
        
        glm::mat4 projectionMatrix = camera->getProjectionMatrix();
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::vec3 lightPosition = glm::vec3(7.0f, 2.0f, 7.0f);
        
        shader->setUniformMatrix4fv("pMatrix", 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        shader->setUniformMatrix4fv("vMatrix", 1, GL_FALSE, glm::value_ptr(viewMatrix));
        shader->setUniform3fv("lightPosition", 1, &lightPosition[0]);

        for (int i = 0; i < numberOfObjects; i++)
        {
            shader->setUniformMatrix4fv("mMatrix", 1, GL_FALSE, glm::value_ptr(mMatrices[i]));
            shader->setUniform4fv("diffuseMaterialColor", 1, &diffuseColors[i][0]);
            shader->setUniform4fv("ambientMaterialColor", 1, &ambientColors[i][0]);
            glBindVertexArray(vao[i]);
            glDrawElements(GL_TRIANGLES, elementCounts[i], GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);
        }

	
        shader->end();

        glutSwapBuffers();
    }

    virtual void OnIdle()
    {
		// Get deltaTime
		unsigned oldTimeSinceStart = timeSinceStart;
		timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		float deltaTime = (float)(timeSinceStart - oldTimeSinceStart) / 1000.0f;
        
        // Fixed Physics Time Step
        physicsLagTime += deltaTime;
        while (physicsLagTime > fixedUpdateTime)
        {
            physicsLagTime -= fixedUpdateTime;
            Physics::fixedUpdate(*level, fixedUpdateTime);
        }

        // Call Update
        Update(deltaTime);

        // Update Model Matrices
        mMatrices[2] = level->getGolfBall()->getModelMatrix();

        // Render
        glutPostRedisplay();
    }

    void Update(float deltaTime)
    {
        // Update Camera
        camera->updateCamera(deltaTime);

        // Handle Input
        if (keysPressed.size() != 0)
        {
            for (char keyPressed : keysPressed)
            {
                camera->handleKeyboard(keyPressed, deltaTime);
            }
        }
    }

    void SetupBuffer(GLuint vao, int bufferStart, const std::vector<glm::vec3> &verts, const std::vector<glm::vec3> &normals, const std::vector<GLuint> &elements)
    {
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferStart]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verts.size(), verts.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferStart + 1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[bufferStart + 2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* elements.size(), elements.data(), GL_STATIC_DRAW);

        GLuint vPosition = glGetAttribLocation(shader->GetProgramObject(), "in_Position");
        GLuint vNormal = glGetAttribLocation(shader->GetProgramObject(), "in_Normal");
        glEnableVertexAttribArray(vPosition);
        glEnableVertexAttribArray(vNormal);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferStart]);
        glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferStart + 1]);
        glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
    }

    virtual void OnInit()
    {
		// Set-up Cameras
		camera = &freeLookCamera;
        topDownCamera.setPosition(glm::vec3(0.0f, 100.0f, 0.0f));

        // Get Time
        timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
        cameraAngle = 0;
        cameraRadius = 5.0f;

        // Setup openGL
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        // Load Shader
        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
        if (shader == 0)
            std::cout << "Error Loading, compiling or linking shader\n";

        // Get Level Data
        std::vector<glm::vec3> levelVerts = level->getTilesVertices();
        std::vector<glm::vec3> levelNormals = level->getTilesNormals();
        std::vector<GLuint> levelElements = level->getTilesIndices();
        elementCounts[0] = levelElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.0, 0.5, 0.0, 1.0));
        ambientColors.push_back(glm::vec4(0.0, 0.2, 0.0, 1.0));

        // Get Wall Data
        std::vector<glm::vec3> wallVerts = level->getWallsVertices();
        std::vector<glm::vec3> wallNormals = level->getWallsNormals();
        std::vector<GLuint> wallElements = level->getWallsIndices();
        elementCounts[1] = wallElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.5, 0.0, 0.0, 1.0));
        ambientColors.push_back(glm::vec4(0.2, 0.0, 0.0, 1.0));

        // Get Ball Data
        GolfBall* golfBall = level->getGolfBall();
        std::vector<glm::vec3> ballVerts = golfBall->getVertices();
        std::vector<glm::vec3> ballNormals = golfBall->getNormals();
        std::vector<GLuint> ballElements = golfBall->getIndices();
        elementCounts[2] = ballElements.size();
        mMatrices.push_back(level->getGolfBall()->getModelMatrix());
        diffuseColors.push_back(glm::vec4(0.5, 0.5, 0.5, 1.0));
        ambientColors.push_back(glm::vec4(0.2, 0.2, 0.2, 1.0));

        // Get Tee Data
        std::vector<glm::vec3> teeVerts = level->getTeeVertices();
        std::vector<glm::vec3> teeNormals = level->getTeeNormals();
        std::vector<GLuint> teeElements = level->getTeeIndices();
        elementCounts[3] = teeElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.0, 0.0, 0.5, 1.0));
        ambientColors.push_back(glm::vec4(0.0, 0.0, 0.2, 1.0));

        // Get Cup Data
        std::vector<glm::vec3> cupVerts = level->getCupVertices();
        std::vector<glm::vec3> cupNormals = level->getCupNormals();
        std::vector<GLuint> cupElements = level->getCupIndices();
        elementCounts[4] = cupElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.01, 0.01, 0.01, 1.0));
        ambientColors.push_back(glm::vec4(0.01, 0.01, 0.01, 1.0));

        // Generate Buffers
        glGenVertexArrays(numberOfObjects, vao);
        glGenBuffers(numberOfObjects * 3, buffers);

        // Configure Buffers
        SetupBuffer(vao[0], 0, levelVerts, levelNormals, levelElements);
        SetupBuffer(vao[1], 3, wallVerts, wallNormals, wallElements);
        SetupBuffer(vao[2], 6, ballVerts, ballNormals, ballElements);
        SetupBuffer(vao[3], 9, teeVerts, teeNormals, teeElements);
        SetupBuffer(vao[4], 12, cupVerts, cupNormals, cupElements);
    }

    virtual void OnResize(int w, int h)
    {
        glViewport(0, 0, w, h);
        if (camera != nullptr)
        {
            if (camera->getProjectionMode() == Camera::perspective)
            {
                float aspect = (float)w / h;
                camera->setPerspectiveMatrix(60.0f, aspect, 0.3f, 100.0f);
            }
        }
        glutPostRedisplay();
    }
    
    virtual void OnClose() {}
    virtual void OnMouseDown(int button, int x, int y) 
	{
		mouseDown = true;
		mouse_x = x;
		mouse_y = y;
	}
	
	virtual void OnMouseMove(int x, int y) {
		if (mouseDown)
		{
			float x_ratchet = glutGet(GLUT_WINDOW_WIDTH) / 100.0f;
			float y_ratchet = glutGet(GLUT_WINDOW_HEIGHT) / 100.0f;
			float dx = (x - mouse_x) / x_ratchet;
			float dy = (y - mouse_y) / y_ratchet;
			mouse_x = x;
			mouse_y = y;
			camera->handleMouseMovement(dx, dy);
			glutPostRedisplay();
		}
	}
	
	
    virtual void OnMouseUp(int button, int x, int y)
	{
        float x_ratchet = glutGet(GLUT_WINDOW_WIDTH) / 100.0f;
        float y_ratchet = glutGet(GLUT_WINDOW_HEIGHT) / 100.0f;
        float dx = (x - mouse_x) / x_ratchet;
        float dy = (y - mouse_y) / y_ratchet;
		mouse_x = x;
		mouse_y = y;
		camera->handleMouseMovement(dx, dy);
		mouseDown = false;
        glutPostRedisplay();
    }
    
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) 
	{
		camera->handleMouseWheel(nWheelNumber, nDirection);
	}

    virtual void OnKeyDown(int nKey, char cAscii)
    {
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}
		else if (cAscii == '1') // 1
		{
			camera = &freeLookCamera;
			glutPostRedisplay();
		}
		else if (cAscii == '2') // 2
		{
			camera = &topDownCamera;
			glutPostRedisplay();
		}
		else if (cAscii == '3') // 3
		{
			camera = thirdPersonCamera;
			glutPostRedisplay();
		}
		else
		{
			bool keyFound = false;
			for (std::vector<char>::iterator c = keysPressed.begin(); c != keysPressed.end(); c++)
			{
				if (*c == cAscii)
				{
					keyFound = true;
					break;
				}
			}
			if (!keyFound)
			{
				keysPressed.push_back(cAscii);
			}
		}

    }
	
	
	
    virtual void OnKeyUp(int nKey, char cAscii)
    {	
        if (cAscii == 'f')
        {
            SetFullscreen(true);
        }
        else if (cAscii == 'g')
        {
            SetFullscreen(false);
        }
		else
		{
			for (std::vector<char>::iterator c = keysPressed.begin(); c != keysPressed.end(); c++)
			{
				if (*c == cAscii)
				{
					keysPressed.erase(c);
					break;
				}
			}
		}
    };
};

class myApplication : public cwc::glApplication
{
};

int main(int argc, char** argv)
{
    string filename = argv[1];

    myApplication* pApp = new myApplication();
    myWindow* myWin = new myWindow(filename);


    pApp->run();
    delete pApp;
    return EXIT_SUCCESS;
}