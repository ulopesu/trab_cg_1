#ifndef LUTADOR_H
#define LUTADOR_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "cor.h"
#include "matrix.h"

enum LadoSoco
{
    DIREITA,
    ESQUERDA,
    TODOS,
};

#define N_MTX 4

#define toRad (M_PI / 180)

#define LIM_INF_THETA_1 -50
#define LIM_INF_THETA_2 140

#define LIM_SUP_THETA_1 85
#define LIM_SUP_THETA_2 15

#define VEL_MOVE 5
#define VEL_GIRO 2
#define VEL_DAR_SOCO 2/350
#define VEL_VOLTAR_SOCO 10

class Lutador
{   
    int TAM_ARENA_X;
    int TAM_ARENA_Y;

    GLfloat gX;
    GLfloat gY;

    Cor *cor;

    GLfloat gTheta;

    GLfloat gTheta1_R; // ANGULO DO BRACO DIREITO
    GLfloat gTheta2_R; // ANGULO DO ANTEBRACO DIREITO

    GLfloat gTheta1_L; // ANGULO DO BRACO ESQUERDO
    GLfloat gTheta2_L; // ANGULO DO ANTEBRACO ESQUERDO

    GLfloat rCabeca;
    GLfloat rNariz;
    GLfloat tamBracos;
    GLfloat rLuvas;
    GLfloat rColisao;

    bool gSocoStatus;
    LadoSoco gLadoSoco;
    GLfloat gdSoco;

    Lutador* gOponente;
    int gPontos;

    GLfloat gTheta1_R_Ant;
    GLfloat gdiffTheta1_R;

    GLfloat gTheta1_L_Ant;
    GLfloat gdiffTheta1_L;
    
private:
    void getPosLuvaR(GLfloat &xL,GLfloat &yL);
    void getPosLuvaL(GLfloat &xL,GLfloat &yL);
    bool colisaoLut(GLfloat dXY);
    bool colisaoTelaX(GLfloat dXY);
    bool colisaoTelaY(GLfloat dXY);
    bool colisaoX(GLfloat dXY);
    bool colisaoY(GLfloat dXY);
    void darSocoRL(GLfloat dSoco);
    void voltarSoco(GLfloat dSoco);
    void DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2,
                      GLfloat tamBracos, GLfloat rLuvas);

    void DesenhaNariz(GLfloat x, GLfloat y, Cor *_cor, GLfloat rNariz);

    void DesenhaCabeca(GLfloat x, GLfloat y, Cor *_cor, GLfloat rCabeca);

    void DesenhaRaioColisao(GLfloat x, GLfloat y, Cor *_cor, GLfloat rClsao);

    void DesenhaLutador(GLfloat x, GLfloat y, Cor *cor,
                        GLfloat theta, GLfloat theta1_R, GLfloat theta2_R,
                        GLfloat theta1_L, GLfloat theta2_L, GLfloat rCab,
                        GLfloat tBracos, GLfloat rLvs, GLfloat rClsao);

public:
    Lutador(    GLfloat _gX, GLfloat _gY, Cor *_cor, 
                GLfloat _theta, GLfloat _tam, int TA_X, int TA_Y);

    void setOponente(Lutador* Op){
        gOponente = Op;
    }

    void addPontos(int pontos){
        gPontos+=pontos;
    }

    void getPontos(int &pontos){
        pontos = gPontos;
    }

    void Desenha()
    {
        DesenhaLutador(gX, gY, cor, gTheta,
                       gTheta1_R, gTheta2_R,
                       gTheta1_L, gTheta2_L,
                       rCabeca, tamBracos,
                       rLuvas, rColisao);
    };
    void darSoco();
    void Move(GLfloat dY, GLfloat dTheta);
    void controleSoco(GLfloat dSoco, LadoSoco ladoSoco);

    void getPosXY(GLfloat &x, GLfloat &y, GLfloat &dir)
    {
        x = gX;
        y = gY;
        dir = gTheta;
    }

    bool getSocoStatus()
    {
        return gSocoStatus;
    }

    bool acerto();

    void getPosNariz(GLfloat &xL,GLfloat &yL);

};

#endif /* LUTADOR_H */