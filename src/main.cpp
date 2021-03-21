#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<sys/time.h>

#include <stdio.h>
#include "lutador.h"
#include "matrix.h"

#define INC_KEY 2
#define INC_KEYIDLE 1

#define N_MTX 4
#define TIME_SOCO 1000  // TEMPO PARA PONTUAR SOCO EM MILISSEGUNDOS

long long timeMS(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

bool onDrag = false;
GLfloat mouseINIT_X = 0;
GLfloat mouseINIT_Y = 0;
GLfloat mouseX = 0;
GLfloat mouseY = 0;
int mouseState;
bool ladoMouse;

int keyStatus[256];

const GLint Width = 700;
const GLint Height = 700;

bool click = false;

//Componentes do mundo virtual sendo modelado
bool soco = false;
Lutador *lutador1 = new Lutador(-200, 0, new Cor(0.2, 0.2, 1), 0, 50, Width, Height);
Lutador *lutador2 = new Lutador(200, 0, new Cor(1, 0.2, 0.2), 0, 50, Width, Height);

void atualizaLadoMouse()
{   
    GLfloat xLut, yLut, dirLut;
    lutador1->getPosXY(xLut, yLut, dirLut);
    ladoMouse = (mouseX > 0);
}

void drag(int _x, int _y)
{   
    mouseX = (GLfloat)_x - (Width / 2);
    _y = Height - _y;
    mouseY = (GLfloat)_y - (Height / 2);
    atualizaLadoMouse();

    if (!mouseState && ladoMouse)
    {   
        lutador1->controleSoco(mouseX, DIREITA);
    }
    else if (!mouseState && !ladoMouse)
    {
        lutador1->controleSoco(-mouseX, ESQUERDA);
    }
    lutador1->darSoco();

    glutPostRedisplay();
}

void mouse(int button, int state, int _x, int _y)
{   
    mouseX = (GLfloat)_x - (Width / 2);
    _y = Height - _y;
    mouseY = (GLfloat)_y - (Height / 2);

    mouseState = state;
    atualizaLadoMouse();
    if (!mouseState && ladoMouse)
    {   
        lutador1->controleSoco(mouseX/Width, DIREITA);
    }
    else if (!mouseState && !ladoMouse)
    {
        lutador1->controleSoco(-mouseX/Width, ESQUERDA);
    }

    click=true;
    //printf("\nX: %f.Y: %f.", x, y);
    //printf("\nSTATE: %d.", state);
    glutPostRedisplay();
}

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    lutador1->Desenha();
    lutador2->Desenha();
    //lutador1->acerto();
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
    glOrtho(-(Width / 2), (Width / 2),   //     X
            -(Height / 2), (Height / 2), //     Y
            -100, 100);                                //     Z
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lutador1->setOponente(lutador2);
    lutador2->setOponente(lutador1);
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
    if(mouseState){
        lutador1->controleSoco(1, TODOS);
        lutador1->darSoco();
    }

    if  (   lutador1->acerto() && 
            lutador1->getSocoStatus() &&
            click
        )
    {   

        lutador1->addPontos(1);
        int pts;
        lutador1->getPontos(pts);
        printf("\npts: %d\n\n", pts);

        click = false;
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
