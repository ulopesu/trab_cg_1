#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include <stdio.h>
#include "lutador.h"
#include "matrix.h"

#define INC_KEY 2
#define INC_KEYIDLE 1

#define INC_MOUSE 2
#define INC_MOUSE_DRAG 1

#define N_MTX 4

bool onDrag = false;
GLfloat mouseX=0;
GLfloat mouseY=0;

int keyStatus[256];

const GLint Width = 700;
const GLint Height = 700;

const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

//Componentes do mundo virtual sendo modelado
bool soco = false;
Lutador *lutador1 = new Lutador(0, 0, new Cor(0.2, 0.2, 1), 0, 50);

void drag(int _x, int _y)
{
    if (onDrag)
    {   
        _y = ViewingHeight-_y;
        GLfloat x = (GLfloat)_x / (GLfloat)ViewingWidth;
        GLfloat y = (GLfloat)_y / (GLfloat)ViewingHeight;
        mouseX = x;
        mouseY = y;

        GLfloat xLut, yLut, dirLut;

        lutador1->getPosXY(xLut, yLut, dirLut);

        GLfloat **mtxMouse = identityMatrix(N_MTX);
        mtxMouse[0][0]=mouseX-xLut;
        mtxMouse[0][1]=mouseY-yLut;

        imprimeMatrix(mtxMouse, N_MTX);

        rotateMatrix(mtxMouse, 0,0, dirLut, N_MTX);

        if(mtxMouse[0][0] > 0){
            lutador1->darSoco(INC_MOUSE_DRAG, 0);
        } else {
            lutador1->darSoco(INC_MOUSE_DRAG, 1);
        }

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int _x, int _y)
{
    _y = ViewingHeight-_y;
    GLfloat x = (GLfloat)_x / (GLfloat)ViewingWidth;
    GLfloat y = (GLfloat)_y / (GLfloat)ViewingHeight;
    if (!state)
    {
        onDrag = true;
        mouseX = x;
        mouseY = y;
    }
    else
    {
        onDrag = false;
        mouseX = x;
        mouseY = y;
    }
    //printf("\nX: %f.Y: %f.", x, y);
    //printf("\nSTATE: %d.", state);
    glutPostRedisplay();
}

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    lutador1->Desenha();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1;
        break;
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1;
        break;
    case 'w':
    case 'W':
        keyStatus[(int)('w')] = 1;
        break;
    case 's':
    case 'S':
        keyStatus[(int)('s')] = 1;
        break;
    case ' ':
        if (!soco)
            lutador1->darSoco(1, 0);
        lutador1->darSoco(1, 1);
        break;
    case 27:
        free(lutador1);
        exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

void init(void)
{
    ResetKeyStatus();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-(ViewingWidth / 2),
            (ViewingWidth / 2),
            -(ViewingHeight / 2),
            (ViewingHeight / 2),
            -100,
            100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle(void)
{
    double inc = INC_KEYIDLE;

    if (keyStatus[(int)('a')])
    {
        lutador1->Move(0, inc);
    }
    if (keyStatus[(int)('d')])
    {
        lutador1->Move(0, -inc);
    }
    if (keyStatus[(int)('w')])
    {
        lutador1->Move(inc, 0);
    }
    if (keyStatus[(int)('s')])
    {
        lutador1->Move(-inc, 0);
    }

    if (soco)
    {
        /*
        tiro->Move();

        if (alvo.Atingido(tiro))
        {
            alvo.Recria(rand() % 500 - 250, 200);
        }

        if (!tiro->Valido())
        {
            delete tiro;
            tiro = NULL;
        }
        */
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Tranformations 2D");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(drag);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}
