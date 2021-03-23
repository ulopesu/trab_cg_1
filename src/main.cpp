#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "lutador.h"
#include "matrix.h"
#include "tinyxml/tinyxml.h"



#define INC_KEY 2
#define INC_KEYIDLE 1

#define N_MTX 4

#define TOTAL_PONTOS_WIN 10
// TEMPO PARA PONTUAR SOCO DO BOOT EM MILISSEGUNDOS
#define TIME_SOCO 1000

long long timeMS(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}


// SVG CONFIG

GLfloat arenaX, arenaY, arenaWidth, arenaHeight;
Cor* arenaCor, *lut1cor, *lut2cor;
GLfloat lut1x, lut1y, lut1rCabeca;
GLfloat lut2x, lut2y, lut2rCabeca;





bool onDrag = false;
GLfloat mouseClick_X = 0;
GLfloat mouseClick_Y = 0;
GLfloat mouseX = 0;
GLfloat mouseY = 0;
int mouseState;
bool ladoMouse;

int keyStatus[256];

// CONFIG DA JANEA
const GLint Width = 700;
const GLint Height = 700;

// CONTROLE DE SOCO
bool click = false;
long long tSocoBoot = 0;
bool soco = false;

int FIM = false;
//Componentes do mundo virtual sendo modelado
string nome1("PLAYER 1");
string nome2("PLAYER 2");

Lutador *lutador1 = new Lutador(nome1, -200, 0, new Cor(0.6, 0.2, 0.6), 0, 50, Width, Height);
Lutador *lutador2 = new Lutador(nome2, 200, 0, new Cor(0.2, 0.6, 0.6), 90, 50, Width, Height);

static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;

void ImprimePlacar(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    int ptsLut1, ptsLut2;
    ptsLut1 = lutador1->getPontos();
    ptsLut2 = lutador2->getPontos();

    sprintf(str, "| Player 1:  %d    |    Player 2:  %d |", ptsLut1, ptsLut2);

    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while (*tmpStr)
    {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void ImprimeVitoria(Lutador *lut)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;

    sprintf(str, "| %s !!! WIN !!! |", lut->getNome().c_str());

    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(-100, (Height / 2) - 50);
    //Imprime um caractere por vez
    tmpStr = str;
    while (*tmpStr)
    {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
    FIM = true;
}

void atualizaLadoMouse()
{
    GLfloat xLut, yLut, dirLut;
    lutador1->getPosXY(xLut, yLut, dirLut);
    ladoMouse = (mouseX > mouseClick_X);
}

void drag(int _x, int _y)
{
    mouseX = (GLfloat)_x - (Width / 2);
    _y = Height - _y;
    mouseY = (GLfloat)_y - (Height / 2);
    atualizaLadoMouse();

    if (!mouseState && ladoMouse)
    {   
        
        lutador1->controleSoco(fabs(mouseX-mouseClick_X), DIREITA);
    }
    else if (!mouseState && !ladoMouse)
    {
        lutador1->controleSoco(fabs(mouseX-mouseClick_X), ESQUERDA);
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
        mouseClick_X = mouseX;
    }
    else if (!mouseState && !ladoMouse)
    {
        mouseClick_X = mouseX;
    }

    click = true;
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
    ImprimePlacar(-150, (Height / 2) - 20);

    if (lutador1->getPontos() >= TOTAL_PONTOS_WIN)
    {
        ImprimeVitoria(lutador1);
    }
    else if (lutador2->getPontos() >= TOTAL_PONTOS_WIN)
    {
        ImprimeVitoria(lutador2);
    }

    glutSwapBuffers(); // Desenha the new frame of the game.
    if (FIM)
    {
        sleep(1000);
    }
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
        if (lutador2->ehBoot())
        {
            lutador2->setEhBoot(false);
        }
        else
        {
            lutador2->setEhBoot(true);
        }
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
            -100, 100);                  //     Z
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lutador1->setOponente(lutador2);
    lutador2->setOponente(lutador1);
    lutador1->dirOponente();
}

void idle(void)
{

    double inc = INC_KEYIDLE;
    long long diffTime;

    // CONFIGURACAO DO SOCO DO BOOT;
    int dSoco;
    LadoSoco lSoco;

    //MOVIMENTO DO BOOT
    if (lutador2->ehBoot())
    {
        lutador2->moveBoot();

        srand(timeMS());
        lSoco = (LadoSoco)(rand() % 3);

        if (lSoco == TODOS)
        {
            lutador2->controleSoco(1, TODOS);
        }
        else
        {
            srand(timeMS());
            dSoco = rand() % (Height * 2);
            lutador2->controleSoco(dSoco, lSoco);
        }
    }

    // PONTUACAO DO LUTADOR 1
    if (lutador1->acerto() &&
        lutador1->getSocoStatus() &&
        click)
    {

        lutador1->addPontos(1);
        click = false;
    }

    // PONTUACAO DO BOOT
    diffTime = timeMS() - tSocoBoot;
    if (lutador2->acerto() &&
        lutador2->getSocoStatus() && diffTime > TIME_SOCO)
    {
        lutador2->addPontos(1);
        tSocoBoot = timeMS();
    }

    // CONTROLE DE TECLAS
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
    if (mouseState)
    {
        lutador1->controleSoco(1, TODOS);
        lutador1->darSoco();
    }

    if (lutador2->ehBoot())
    {
        lutador2->darSoco();
    }

    glutPostRedisplay();
}

void lerXml(const char* fileName){

    TiXmlDocument doc(fileName);

	if (doc.LoadFile())
	{
		printf("\nLeitura do arquivo: %s -> OK!\n", fileName);
	}
	else
	{
		printf("Failed to load file: \"%s\"\n\n", fileName);
        exit(EXIT_FAILURE);
	}

    TiXmlElement* raiz = doc.RootElement();

    TiXmlElement* arena = raiz->FirstChildElement("rect");

    arena->QueryFloatAttribute("x",&arenaX); 

    printf("\n\nARENA X: %f\"\n\n", arenaX);

}

int main(int argc, char *argv[])
{   
    if(argc == 2){
        printf("\nDIR -> OK!  \n",argv[1]);
    }
    else{
        printf("\nSem diretorio.\n\n");
        return 1;
    }

    lerXml(argv[1]);


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
