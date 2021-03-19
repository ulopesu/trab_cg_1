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

#define toRad (M_PI / 180)

#define LIM_INF_THETA_1 -50
#define LIM_INF_THETA_2 140

#define LIM_SUP_THETA_1 85
#define LIM_SUP_THETA_2 15

#define VEL_MOVE 1
#define VEL_SOCO 2/350

class Lutador
{
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

private:
    void darSocoDireita();
    void darSocoEsquerda();
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
    Lutador(GLfloat _gX, GLfloat _gY, Cor *_cor, GLfloat _theta, GLfloat _tam);
    void Desenha()
    {
        DesenhaLutador(gX, gY, cor, gTheta,
                       gTheta1_R, gTheta2_R,
                       gTheta1_L, gTheta2_L,
                       rCabeca, tamBracos,
                       rLuvas, rColisao);
    };
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
    void darSoco();
};

#endif /* LUTADOR_H */