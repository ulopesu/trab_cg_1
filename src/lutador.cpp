#include "lutador.h"
#include "soco.h"
#include "circulo.h"
#include "retangulo.h"

Lutador::Lutador(GLfloat _gX, GLfloat _gY, Cor* _cor, GLfloat _theta, GLfloat _tam)
{   

    // PRESET LOCALIZAÇÃO E DIREÇÃO
    gTheta=_theta;
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
    rCabeca = _tam*4;
    rNariz = _tam;
    tamBracos = _tam*6;
    rLuvas = _tam*1.5;
    rColisao = rCabeca*3;
};

void Lutador::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat tamBracos, GLfloat rLuvas){
    Cor* cor = new Cor(0.2, 1, 0.2);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);

    Retangulo *ret = new Retangulo(tamBracos/6, tamBracos, 0, 0);
    ret->desenha(cor);

    glTranslatef(0, tamBracos, 0);

    glRotatef(theta2, 0, 0, 1);
    ret->desenha(cor);
    
    glTranslatef(0, tamBracos, 0);

    Circulo *circ = new Circulo(rLuvas, 20, 0, 0);
    circ->desenhaComBorda(new Cor(1,0.2,0.2));
    
    glPopMatrix();

    free(ret);
    free(circ);
}


void Lutador::DesenhaNariz(GLfloat x, GLfloat y, Cor* _cor, GLfloat rNariz){
    Circulo *circ = new Circulo(rNariz, 100, x, y);
    circ->desenhaComBorda(_cor);
    free(circ);
}

void Lutador::DesenhaCabeca(GLfloat x, GLfloat y, Cor* _cor, GLfloat rCabeca){
    Circulo *circ = new Circulo(rCabeca, 100, x, y);
    circ->desenhaComBorda(_cor);
    free(circ);
}

void Lutador::DesenhaRaioColisao(GLfloat x, GLfloat y, Cor* _cor, GLfloat rClsao){
    Circulo *circ = new Circulo(rClsao, 100, x, y);
    circ->desenhaPontos(3, _cor);
    free(circ);
}

void Lutador::DesenhaLutador(   GLfloat x, GLfloat y, Cor* cor, GLfloat theta, 
                                GLfloat theta1_R, GLfloat theta2_R, 
                                GLfloat theta1_L, GLfloat theta2_L, 
                                GLfloat rCab, GLfloat tBracos, 
                                GLfloat rLvs, GLfloat rClsao){

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(gTheta, 0, 0, 1);
    DesenhaRaioColisao(0, 0, new Cor(1,1,1), rClsao);
    DesenhaNariz(0, rCabeca+(rNariz/2), cor, rNariz);
    DesenhaBraco(rCabeca, 0, (-90+theta1_R), theta2_R, tamBracos, rLuvas);  // DIREITA
    DesenhaBraco(-rCabeca, 0, 90-theta1_L, -theta2_L, tamBracos, rLuvas);   // ESQUERDA
    DesenhaCabeca(0, 0, cor, rCabeca);
    
    
    
    glPopMatrix();
}


void Lutador::Move(GLfloat dY, GLfloat dTheta) {
    //GLfloat toRad = M_PI / 180;
    
    if(dY){
        gX-=dY*sin(gTheta*toRad);
        gY+=dY*cos(gTheta*toRad);
    } else {
        gTheta+=dTheta;
    }

    //printf("GX: %.2f GY: %.2f\n", cos(dTheta), sin(dTheta));
}


Lutador* Lutador::darSoco(GLfloat dSoco, bool mao){
    dSoco*=5; //VELOCIDADE DO SOCO
    if(!mao){ //MAO DIREITA
        if (gTheta1_R > LIM_INF_THETA_1 && gTheta1_R < LIM_SUP_THETA_1)
        {
            gTheta1_R+=dSoco;
        }

        if (gTheta2_R>LIM_SUP_THETA_2 && gTheta2_R<LIM_INF_THETA_2)
        {
            gTheta2_R-=dSoco;
        }
    } else { //MAO ESQUERDA
        if (gTheta1_L > LIM_INF_THETA_1 && gTheta1_L < LIM_SUP_THETA_1)
        {
            gTheta1_L+=dSoco;
        }

        if (gTheta2_L<LIM_INF_THETA_2 && gTheta2_L>LIM_SUP_THETA_2)
        {
            gTheta2_L-=dSoco;
        }
    }
    return this;
}

