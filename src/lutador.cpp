#include "lutador.h"
#include "soco.h"
#include "circulo.h"
#include "retangulo.h"

Lutador::Lutador(GLfloat _gX, GLfloat _gY, Cor *_cor,
                 GLfloat _theta, GLfloat _tam,
                 int TA_X, int TA_Y)
{

    // PRESET LOCALIZAÇÃO E DIREÇÃO
    TAM_ARENA_X = TA_X;
    TAM_ARENA_Y = TA_Y;

    gTheta = _theta;
    gTheta1_R = LIM_INF_THETA_1;
    gTheta2_R = LIM_INF_THETA_2;

    gTheta1_L = LIM_INF_THETA_1;
    gTheta2_L = LIM_INF_THETA_2;

    GLfloat dir[1][4];

    // PRESET DE TAMANHOS E ESCALAS E CORES
    _tam /= 9;
    gX = _gX;
    gY = _gY;
    cor = _cor;
    rCabeca = _tam * 4;
    rNariz = _tam;
    tamBracos = _tam * 8;
    rLuvas = _tam * 1.5;
    rColisao = rCabeca * 3;

    // PRESET DE SOCO
    gSocoStatus = false;
    gLadoSoco = DIREITA;
    gdSoco = 0;
};

void Lutador::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat tamBracos, GLfloat rLuvas)
{
    Cor *cor = new Cor(0.2, 1, 0.2);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);

    Retangulo *ret = new Retangulo(tamBracos / 6, tamBracos, 0, 0);
    ret->desenha(cor);

    glTranslatef(0, tamBracos, 0);

    glRotatef(theta2, 0, 0, 1);
    ret->desenha(cor);

    glTranslatef(0, tamBracos, 0);

    Circulo *circ = new Circulo(rLuvas, 20, 0, 0);
    circ->desenhaComBorda(new Cor(1, 0.2, 0.2));

    glPopMatrix();

    free(ret);
    free(circ);
}

void Lutador::DesenhaNariz(GLfloat x, GLfloat y, Cor *_cor, GLfloat rNariz)
{
    Circulo *circ = new Circulo(rNariz, 100, x, y);
    circ->desenhaComBorda(_cor);
    free(circ);
}

void Lutador::DesenhaCabeca(GLfloat x, GLfloat y, Cor *_cor, GLfloat rCabeca)
{
    Circulo *circ = new Circulo(rCabeca, 100, x, y);
    circ->desenhaComBorda(_cor);
    free(circ);
}

void Lutador::DesenhaRaioColisao(GLfloat x, GLfloat y, Cor *_cor, GLfloat rClsao)
{
    Circulo *circ = new Circulo(rClsao, 100, x, y);
    circ->desenhaPontos(3, _cor);
    free(circ);
}

void Lutador::DesenhaLutador(GLfloat x, GLfloat y, Cor *cor, GLfloat theta,
                             GLfloat theta1_R, GLfloat theta2_R,
                             GLfloat theta1_L, GLfloat theta2_L,
                             GLfloat rCab, GLfloat tBracos,
                             GLfloat rLvs, GLfloat rClsao)
{

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(gTheta, 0, 0, 1);
    DesenhaRaioColisao(0, 0, new Cor(1, 1, 1), rClsao);
    DesenhaNariz(0, rCabeca + (rNariz / 2), cor, rNariz);
    DesenhaBraco(rCabeca, 0, (-90 + theta1_R), theta2_R, tamBracos, rLuvas); // DIREITA
    DesenhaBraco(-rCabeca, 0, 90 - theta1_L, -theta2_L, tamBracos, rLuvas);  // ESQUERDA
    DesenhaCabeca(0, 0, cor, rCabeca);

    glPopMatrix();
}

bool Lutador::colisaoTelaX(GLfloat dXY)
{
    bool colisaoTela;
    GLfloat tam = -dXY * sin(gTheta * toRad);
    if (gX > 0)
    {
        tam += gX + rColisao;
    }
    else
    {
        tam += gX - rColisao;
    }
    return abs(tam) > (TAM_ARENA_X / 2) ? true : false;
}

bool Lutador::colisaoTelaY(GLfloat dXY)
{
    GLfloat tam = dXY * cos(gTheta * toRad);
    if (gY > 0)
    {
        tam += gY + rColisao;
    }
    else
    {
        tam += gY - rColisao;
    }
    return abs(tam) >= (TAM_ARENA_X / 2) ? true : false;
}

bool Lutador::colisaoLut(GLfloat dXY)
{   
    GLfloat dX = -dXY * sin(gTheta * toRad);
    GLfloat dY = dXY * cos(gTheta * toRad);
    GLfloat xOp, yOp, dirOp;
    gOponente->getPosXY(xOp, yOp, dirOp);

    dX = gX+dX-xOp;
    dY = gY+dY-yOp;

    GLfloat dist = sqrt(pow(dX,2)+pow(dY,2));

    return dist <= (rColisao+rCabeca) ? true : false;
}


bool Lutador::colisaoX(GLfloat dXY)
{
    return colisaoTelaX(dXY);
}

bool Lutador::colisaoY(GLfloat dXY)
{
    return colisaoTelaY(dXY);
}

void Lutador::Move(GLfloat dXY, GLfloat dTheta, Lutador *Op)
{
    //GLfloat toRad = M_PI / 180;
    gOponente = Op;
    dXY *= VEL_MOVE;
    dTheta *= VEL_GIRO;
    gTheta += dTheta;

    if (dXY)
    {
        if (!colisaoX(dXY) && !colisaoLut(dXY))
        {
            gX -= dXY * sin(gTheta * toRad);
        }

        if (!colisaoY(dXY) && !colisaoLut(dXY))
        {
            gY += dXY * cos(gTheta * toRad);
        }
    }
    else
    {
        if (gTheta > 360 || gTheta < -360)
        {
            gTheta = fmod(gTheta, 360);
        }
    }

    //printf("GX: %.2f GY: %.2f\n", cos(dTheta), sin(dTheta));
}

void Lutador::controleSoco(GLfloat dSoco, LadoSoco ladoSoco)
{
    gdSoco = dSoco;

    if (dSoco != 0)
    {
        gSocoStatus = true;
    }
    else
    {
        gSocoStatus = false;
        return;
    }

    gLadoSoco = ladoSoco;
}

void Lutador::darSocoRL(GLfloat dSoco)
{

    GLfloat p1 = ((LIM_SUP_THETA_1 - LIM_INF_THETA_1) * dSoco) + LIM_INF_THETA_1;

    GLfloat p2 = ((LIM_INF_THETA_2 - LIM_SUP_THETA_2) * dSoco);
    p2 *= (-1);
    p2 += LIM_INF_THETA_2;

    if (p1 > LIM_INF_THETA_1 && p1 < LIM_SUP_THETA_1)
    {
        switch (gLadoSoco)
        {
        case ESQUERDA:
            gTheta1_L = p1;
            break;

        case DIREITA:
            gTheta1_R = p1;
            break;
        }
    }

    if (p2 > LIM_SUP_THETA_2 && p2 < LIM_INF_THETA_2)
    {
        switch (gLadoSoco)
        {
        case ESQUERDA:
            gTheta2_L = p2;
            break;

        case DIREITA:
            gTheta2_R = p2;
            break;
        }
    }
}

void Lutador::voltarSoco(GLfloat dSoco)
{
    if ((gTheta1_R - dSoco) > LIM_INF_THETA_1 && (gTheta1_R - dSoco) < LIM_SUP_THETA_1)
    {
        gTheta1_R -= dSoco;
    }

    if ((gTheta1_L - dSoco) > LIM_INF_THETA_1 && (gTheta1_L - dSoco) < LIM_SUP_THETA_1)
    {
        gTheta1_L -= dSoco;
    }

    if ((gTheta2_R + dSoco) > LIM_SUP_THETA_2 && (gTheta2_R + dSoco) < LIM_INF_THETA_2)
    {
        gTheta2_R += dSoco;
    }

    if ((gTheta2_L + dSoco) > LIM_SUP_THETA_2 && (gTheta2_L + dSoco) < LIM_INF_THETA_2)
    {
        gTheta2_L += dSoco;
    }
}

void Lutador::darSoco()
{

    if (!gSocoStatus)
    {
        return;
    }

    GLfloat theta1, theta2;
    switch (gLadoSoco)
    {
    case TODOS:
        voltarSoco(gdSoco * VEL_VOLTAR_SOCO);
        break;

    default:
        darSocoRL(gdSoco * VEL_DAR_SOCO);
        break;
    }
}