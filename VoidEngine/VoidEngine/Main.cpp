#include <cstdlib>
#include <GL/freeglut.h>

int main(int argc, TCHAR* argv[])
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("GLUT Demo");

    glutMainLoop();

    return EXIT_SUCCESS;
}