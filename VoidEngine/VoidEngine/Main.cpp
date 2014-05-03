#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include "glsl.h"
#include "glutwindow.h"
#include "glApplication.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "FileHandling.h"

using namespace std;

class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader *shader;

private:
    string filename;
    Level level;
    GLuint triangleVBO;

public:
    myWindow(string inputFilename)
    {
        filename = inputFilename;
    }

    virtual void OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glutSwapBuffers();
    }

    virtual void OnIdle() {}

    virtual void OnInit()
    {
        // Load Level
        level = FileHandling::ReadFile(filename);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
        if (shader == 0)
            std::cout << "Error Loading, compiling or linking shader\n";

        // Get Level Data
        vector<Tile> tiles = level.getTiles();
        vector<glm::vec3> verts;
        for (Tile tile : tiles)
        {
            vector<glm::vec3> points = tile.getVertices();
            verts.insert(verts.end(), points.begin(), points.end());
        }

        // 
        GLuint shaderAttribute = 0;

        // Create and Manage Buffers
        // Create a new VBO and use the variable id to store the VBO id
        glGenBuffers(1, &triangleVBO);

        // Make the new VBO active
        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

        // Upload vertex data to the video device
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verts.size(), &verts[0], GL_STATIC_DRAW);

        // Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex
        glVertexAttribPointer(shaderAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Enable attribute index 0(shaderAttribute) as being used
        glEnableVertexAttribArray(shaderAttribute);

        // Make the new VBO active.
        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    }

    virtual void OnResize(int w, int h) {}
    virtual void OnClose() {}
    virtual void OnMouseDown(int button, int x, int y) {}
    virtual void OnMouseUp(int button, int x, int y) {}
    virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

    virtual void OnKeyDown(int nKey, char cAscii)
    {
        if (cAscii == 27) // 0x1b = ESC
        {
            this->Close(); // Close Window!
        }
    }

    virtual void OnKeyUp(int nKey, char cAscii)
    {
        if (cAscii == 'f')
        {
            SetFullscreen(true);
        }
        else if (cAscii == 'w')
        {
            SetFullscreen(false);
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

//void displayObject();
//void drawString(float, float, float, char*);
//void handleMenu(int);
//void handleMotion(int, int);
//void handleMouse(int, int, int, int);
//glm::vec3 calculateNormal(vector<glm::vec3> verts);
//
//typedef enum
//{
//    TRANSLATE,
//    ROTATE_X,
//    ROTATE_Y,
//    ROTATE_Z
//} mode;
//
//int		btn[3] = { 0 };				// Current button state
//mode	cur_mode = TRANSLATE;		// Current mouse mode
//float	translate[3] = { 0 };		// Current translation values
//float	rotateVal[3] = { 0 };		// Current rotation values
//int		mouse_x, mouse_y;			// Current mouse position
//Level*	level;						// Level to be rendered
//
//int main(int argc, TCHAR* argv[])
//{
//	// Read in file name
//	string inFile;
//	inFile = argv[1];
//
//	// Parse file into level
//	Level loadedLevel = FileHandling::ReadFile(inFile);
//	level = &loadedLevel;
//
//
//    glutInit(&argc, (char **)argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutCreateWindow("VOID Engine");
//
//    glutDisplayFunc(displayObject);	// Setup GLUT callbacks
//    glutMotionFunc(handleMotion);
//    glutMouseFunc(handleMouse);
//
//    glutCreateMenu(handleMenu);	// Setup GLUT popup menu
//    glutAddMenuEntry("Translate", 0);
//    glutAddMenuEntry("Rotate X", 1);
//    glutAddMenuEntry("Rotate Y", 2);
//    glutAddMenuEntry("Rotate Z", 3);
//    glutAddMenuEntry("Quit", 4);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//    glMatrixMode(GL_PROJECTION);	// Setup perspective projection
//    glLoadIdentity();
//    gluPerspective(70, 1, 1, 40);
//
//    glMatrixMode(GL_MODELVIEW);		// Setup model transformations
//    glLoadIdentity();
//    gluLookAt(0, 0, 5, 0, 0, -1, 0, 1, 0);
//
//    glShadeModel(GL_SMOOTH);
//
//    glClearDepth(1.0);			// Setup background colour
//    glClearColor(0, 0, 0, 0);
//    glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//    glutMainLoop();
//
//    return EXIT_SUCCESS;
//}
//
//void displayObject()
//{
//	glMatrixMode(GL_MODELVIEW);		// Setup model transformations
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glPushMatrix();
//	glTranslatef(translate[0], translate[1], translate[2]);
//	glRotatef(rotateVal[0], 1, 0, 0);
//	glRotatef(rotateVal[1], 0, 1, 0);
//	glRotatef(rotateVal[2], 0, 0, 1);
//
//    glm::vec4 lightPos(1.0, 2.0, 1.0, 1.0);
//    glLightfv(GL_LIGHT0, GL_POSITION, &lightPos[0]);
//
//    glm::vec3 green(0, 1, 0);
//    glm::vec3 red(1, 0, 0);
//    glm::vec3 black(0, 0, 0);
//    glm::vec3 blue(0, 0, 1);
//
//	// Draw Level
//	// Iterate through and draw tiles
//	vector<Tile> tiles = level->getTiles();
//	for (unsigned i = 0; i < tiles.size(); i++)
//	{
//        // Draw floor of tile
//		vector<glm::vec3> verts = tiles[i].getVertices();
//		glm::vec3 normals = calculateNormal(verts);
//		glBegin(GL_TRIANGLE_FAN);
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &green[0]);
//		glNormal3fv(&normals[0]);
//		for (unsigned j = 0; j < verts.size(); j++)
//		{
//			glVertex3fv(&verts[j][0]);
//		}
//		glEnd();
//
//        // Draw walls
//        vector<int> neighbors = tiles[i].getNeighbors();
//        // Search through neighbors
//        for (unsigned j = 0; j < neighbors.size(); j++)
//        {
//            // If there is no neighbor draw a wall
//            if (neighbors[j] == 0)
//            {
//                vector<glm::vec3> wall;
//                // Get ground points
//                wall.push_back(verts[j]);
//                if (j + 1 == neighbors.size())
//                {
//                    wall.push_back(verts[0]);
//                    wall.push_back(verts[0] + glm::vec3(0.0, 0.25, 0.0));
//                }
//                else
//                {
//                    wall.push_back(verts[j + 1]);
//                    wall.push_back(verts[j + 1] + glm::vec3(0.0, 0.25, 0.0));
//                }
//                wall.push_back(verts[j] + glm::vec3(0, 0.25, 0));
//
//                //Calculate normal
//                glm::vec3 normal = calculateNormal(wall);
//                normal = -normal;
//
//                // Draw Wall
//                glm::vec3 red(1, 0, 0);
//                glBegin(GL_TRIANGLE_FAN);
//                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &red[0]);
//                glNormal3fv(&normal[0]);
//                glVertex3fv(&wall[0][0]);
//                glVertex3fv(&wall[1][0]);
//                glVertex3fv(&wall[2][0]);
//                glVertex3fv(&wall[3][0]);
//                glEnd();
//            }
//        }
//	}
//
//    // Draw Cup
//    vector<glm::vec3> cupPoints;
//    Level::LevelObject cup = level->getCup();
//    cupPoints.push_back(cup.position + glm::vec3(0.0, 0.01, 0.0));
//    // Create Vertices
//    for (int i = 0; i < 10; i++)
//    {
//        float x = sin((6.28 / 10.0) * i) * 0.1;
//        float z = cos((6.28 / 10.0) * i) * 0.1;
//        glm::vec3 point(x + cup.position.x, cup.position.y + 0.01, z + cup.position.z);
//        cupPoints.push_back(point);
//    }
//    float x = sin(0) * 0.1;
//    float z = cos(0) * 0.1;
//    glm::vec3 point(x + cup.position.x, cup.position.y + 0.01, z + cup.position.z);
//    cupPoints.push_back(point);
//
//    glm::vec3 cupNormal = calculateNormal(cupPoints);
//    glBegin(GL_TRIANGLE_FAN);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &black[0]);
//    glNormal3fv(&cupNormal[0]);
//    for (unsigned i = 0; i < cupPoints.size(); i++)
//    {
//        glVertex3fv(&cupPoints[i][0]);
//    }
//    glEnd();
//
//    // Draw Tee
//    vector<glm::vec3> teePoints;
//    Level::LevelObject tee = level->getTee();
//    // Create Vertices
//    glm::vec3 t1 = tee.position - glm::vec3(-0.1, -0.01, -0.1);
//    glm::vec3 t2 = tee.position - glm::vec3( 0.1, -0.01, -0.1);
//    glm::vec3 t3 = tee.position - glm::vec3( 0.1, -0.01,  0.1);
//    glm::vec3 t4 = tee.position - glm::vec3(-0.1, -0.01,  0.1);
//    teePoints.push_back(t1);
//    teePoints.push_back(t2);
//    teePoints.push_back(t3);
//    teePoints.push_back(t4);
//    glm::vec3 teeNormal = calculateNormal(teePoints);
//    glBegin(GL_TRIANGLE_FAN);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &blue[0]);
//    glNormal3fv(&teeNormal[0]);
//    glVertex3fv(&teePoints[0][0]);
//    glVertex3fv(&teePoints[1][0]);
//    glVertex3fv(&teePoints[2][0]);
//    glVertex3fv(&teePoints[3][0]);
//    glEnd();
//
//    glPopMatrix();
//    glFlush();				// Flush OpenGL queue
//    glutSwapBuffers();			// Display back buffer
//}
//
//// Calculates the normal vector using the first three verts from input
//glm::vec3 calculateNormal(vector<glm::vec3> verts)
//{
//	glm::vec3 p1 = verts[0];
//	glm::vec3 p2 = verts[1];
//	glm::vec3 p3 = verts[2];
//
//	glm::vec3 v = p2 - p1;
//	glm::vec3 w = p3 - p1;
//
//	float nx = (v.y * w.z) - (v.z * w.y);
//	float ny = (v.z * w.x) - (v.x * w.z);
//	float nz = (v.x * w.y) - (v.y * w.x);
//
//	glm::vec3 normals(nx, ny, nz);
//	return normals;
//}
//
//void drawString(float x, float y, float z, char *txt)
//
////  This routine draws the text string at the given (x,y,z) position
////
////  x,y,z:  Raster position for text
////  txt:    String to draw
//{
//    glRasterPos3f(x, y, z);
//    while (*txt != '\0')
//    {
//        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *txt);
//        txt++;
//    }
//}					// End routine draw_string
//
//void handleMenu(int ID)
//
////  This routine handles popup menu selections
////
////  ID:  Menu entry ID
//{
//    switch (ID)
//    {
//    case 0:				// XY translation
//        cur_mode = TRANSLATE;
//        break;
//    case 1:				// X rotation
//        cur_mode = ROTATE_X;
//        break;
//    case 2:				// Y rotation
//        cur_mode = ROTATE_Y;
//        break;
//    case 3:				// Z rotation
//        cur_mode = ROTATE_Z;
//        break;
//    case 4:				// Quit
//        exit(0);
//    }
//}					// End routine handle_menu
//
//void handleMotion(int x, int y)
//
////  This routine acts as a callback for GLUT mouse motion events
////
////  x, y:  Cursor position
//{
//    float	 x_ratchet;			// X ratchet value
//    float	 y_ratchet;			// Y ratchet value
//
//
//    if (!btn[0])
//    {			// Left button not depressed?
//        return;
//    }
//
//    x_ratchet = glutGet(GLUT_WINDOW_WIDTH) / 10.0;
//    y_ratchet = glutGet(GLUT_WINDOW_HEIGHT) / 10.0;
//
//    //  Windows XP has y = 0 at top, GL has y = 0 at bottom, so reverse y
//
//    y = glutGet(GLUT_WINDOW_HEIGHT) - y;
//
//    switch (cur_mode)
//    {
//    case TRANSLATE:			// XY translation
//        translate[0] += (float)(x - mouse_x) / x_ratchet;
//        translate[1] += (float)(y - mouse_y) / y_ratchet;
//        break;
//    case ROTATE_X:			// X rotation
//        x_ratchet /= 10.0;
//        rotateVal[0] += (float)(x - mouse_x) / x_ratchet;
//        break;
//    case ROTATE_Y:			// Y rotation
//        x_ratchet /= 10.0;
//        rotateVal[1] += (float)(x - mouse_x) / x_ratchet;
//        break;
//    case ROTATE_Z:			// Z rotation
//        x_ratchet /= 10.0;
//        rotateVal[2] += (float)(x - mouse_x) / x_ratchet;
//        break;
//    }
//
//    mouse_x = x;				// Update cursor position
//    mouse_y = y;
//
//    glutPostRedisplay();
//}					// End routine handle_motion
//
//
//void handleMouse(int b, int s, int x, int y)
//
////  This routine acts as a callback for GLUT mouse events
////
////  b:     Mouse button (left, middle, or right)
////  s:     State (button down or button up)
////  x, y:  Cursor position
//{
//    if (s == GLUT_DOWN)
//    {		// Store button state if mouse down
//        btn[b] = 1;
//    }
//    else
//    {
//        btn[b] = 0;
//    }
//
//    mouse_x = x;
//    mouse_y = glutGet(GLUT_WINDOW_HEIGHT) - y;
//}					// End routine handle_mouse