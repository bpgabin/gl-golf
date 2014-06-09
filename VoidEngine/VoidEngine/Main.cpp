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
#include "Putter.hpp"

using namespace std;

glm::vec3 calculateNormal(vector<glm::vec3>);



class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader *shader;

private:
    std::vector<Level*> levels;

	Camera* camera;
    Putter* putter;

    FreeLookCamera freeLookCamera;
	TopDownCamera topDownCamera;
	ThirdPersonCamera* thirdPersonCamera;
    const int numberOfObjects = 6;
    GLuint vao[6], buffers[18], elementCounts[6];
    std::vector<glm::vec4> diffuseColors, ambientColors;
    std::vector<glm::mat4> mMatrices;

    unsigned timeSinceStart;
    unsigned currentLevel = 0;
    float cameraAngle;
    float cameraRadius;
	
    float physicsLagTime = 0.0f;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	const float rotateX = 30.f;
    const float fixedUpdateTime = 1.0f / 60.0f;
	int par;
    int stroke = 0;
	bool mouseDown = false;
	std::vector<char> keysPressed;
	int mouse_x, mouse_y;
	FileHandling file;

public:
    myWindow(string inputFilename)
    {
        // Load Level
	
        levels = file.ReadFile(inputFilename);
        thirdPersonCamera = new ThirdPersonCamera(levels[currentLevel]->getGolfBall());
		
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
		char string[64];
		char string2[64];
		char string3[64];
        char string4[64];
		
		stroke = putter->getStroke();
        sprintf_s(string4, "Player: %d", levels[currentLevel]->getCurrentPlayer());
		sprintf_s(string, " Hole: %d", currentLevel + 1);
		sprintf_s(string2, " Par: %d", par);
		sprintf_s(string3, " Stroke: %d", stroke);
        printText(40, 100, string4);
        printText(50, 100, string);
		printText(60, 100, string2);
		printText(70, 100, string3);

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
            Physics::fixedUpdate(*levels[currentLevel], fixedUpdateTime);
        }

        // Call Update
        Update(deltaTime);

        // Update Model Matrices
        mMatrices[2] = levels[currentLevel]->getGolfBall()->getModelMatrix();

        // Render
        glutPostRedisplay();
    }

    void Update(float deltaTime)
    {
        // Update Camera
        camera->updateCamera(deltaTime);

        // Move Putter to Ball
        putter->setPosition(levels[currentLevel]->getGolfBall()->getPosition());
        mMatrices[5] = putter->getModelMatrix();

        // Handle Input
        if (keysPressed.size() != 0)
        {
            for (char keyPressed : keysPressed)
            {
                camera->handleKeyboard(keyPressed, deltaTime);
                putter->handleKeyboard(keyPressed, deltaTime);
            }
        }

        // Check if level complete
        if (levels[currentLevel]->getComplete())
        {
            currentLevel++;
            LoadLevelData(currentLevel);
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

    void LoadLevelData(unsigned level)
    {
        // Get Level Data
        std::vector<glm::vec3> levelVerts = levels[currentLevel]->getTilesVertices();
        std::vector<glm::vec3> levelNormals = levels[currentLevel]->getTilesNormals();
        std::vector<GLuint> levelElements = levels[currentLevel]->getTilesIndices();
        elementCounts[0] = levelElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.0, 0.5, 0.0, 1.0));
        ambientColors.push_back(glm::vec4(0.0, 0.2, 0.0, 1.0));

        // Get Wall Data
        std::vector<glm::vec3> wallVerts = levels[currentLevel]->getWallsVertices();
        std::vector<glm::vec3> wallNormals = levels[currentLevel]->getWallsNormals();
        std::vector<GLuint> wallElements = levels[currentLevel]->getWallsIndices();
        elementCounts[1] = wallElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.5, 0.0, 0.0, 1.0));
        ambientColors.push_back(glm::vec4(0.2, 0.0, 0.0, 1.0));

        // Get Ball Data
        GolfBall* golfBall = levels[currentLevel]->getGolfBall();
        std::vector<glm::vec3> ballVerts = golfBall->getVertices();
        std::vector<glm::vec3> ballNormals = golfBall->getNormals();
        std::vector<GLuint> ballElements = golfBall->getIndices();
        elementCounts[2] = ballElements.size();
        mMatrices.push_back(levels[currentLevel]->getGolfBall()->getModelMatrix());
        diffuseColors.push_back(glm::vec4(0.5, 0.5, 0.5, 1.0));
        ambientColors.push_back(glm::vec4(0.2, 0.2, 0.2, 1.0));

        // Get Tee Data
        std::vector<glm::vec3> teeVerts = levels[currentLevel]->getTeeVertices();
        std::vector<glm::vec3> teeNormals = levels[currentLevel]->getTeeNormals();
        std::vector<GLuint> teeElements = levels[currentLevel]->getTeeIndices();
        elementCounts[3] = teeElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.0, 0.0, 0.5, 1.0));
        ambientColors.push_back(glm::vec4(0.0, 0.0, 0.2, 1.0));

        // Get Cup Data
        std::vector<glm::vec3> cupVerts = levels[currentLevel]->getCupVertices();
        std::vector<glm::vec3> cupNormals = levels[currentLevel]->getCupNormals();
        std::vector<GLuint> cupElements = levels[currentLevel]->getCupIndices();
        elementCounts[4] = cupElements.size();
        mMatrices.push_back(glm::mat4());
        diffuseColors.push_back(glm::vec4(0.01, 0.01, 0.01, 1.0));
        ambientColors.push_back(glm::vec4(0.01, 0.01, 0.01, 1.0));

        //Putter
        putter = levels[currentLevel]->getPutter();
        std::vector<glm::vec3> puttVerts = putter->getVertices();
        std::vector<glm::vec3> puttNormals = putter->getNormals();
        std::vector<GLuint> puttElements = putter->getIndices();
        elementCounts[5] = puttElements.size();
        mMatrices.push_back(levels[currentLevel]->getPutter()->getModelMatrix());
        diffuseColors.push_back(glm::vec4(0.5, 0.0, 0.0, 1.0));
        ambientColors.push_back(glm::vec4(0.2, 0.0, 0.0, 1.0));

		//Par
		 par = levels[currentLevel]->getParNum();

        // Configure Buffers
        SetupBuffer(vao[0], 0, levelVerts, levelNormals, levelElements);
        SetupBuffer(vao[1], 3, wallVerts, wallNormals, wallElements);
        SetupBuffer(vao[2], 6, ballVerts, ballNormals, ballElements);
        SetupBuffer(vao[3], 9, teeVerts, teeNormals, teeElements);
        SetupBuffer(vao[4], 12, cupVerts, cupNormals, cupElements);
        SetupBuffer(vao[5], 15, puttVerts, puttNormals, puttElements);
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
        {
            std::cout << "Error Loading, compiling or linking shader\n";
        }

        // Generate Buffers
        glGenVertexArrays(numberOfObjects, vao);
        glGenBuffers(numberOfObjects * 3, buffers);

        LoadLevelData(currentLevel);
    }
	void printText(int x, int y, string String)
	{
		//(x,y) is from the bottom left of the window
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, GLUT_WINDOW_WIDTH, 0, GLUT_WINDOW_HEIGHT, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glRasterPos2i(x, y);
		for (unsigned i = 0; i < String.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
		}
		glPopAttrib();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
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
		else if (cAscii == 'p') // 3
		{
            if (currentLevel < levels.size() - 1)
            {
                currentLevel += 1;
                LoadLevelData(currentLevel);
            }
		}
		else if (cAscii == 'o') // 3
		{
            if (currentLevel > 0)
            {
                currentLevel -= 1;
				LoadLevelData(currentLevel);
            }
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