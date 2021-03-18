#include "cor.h"

Cor::Cor(GLfloat r, GLfloat g, GLfloat b)
{
    this->R = r;
    this->G = g;
    this->B = b;
}


GLfloat Cor::getR(){
    return this->R;
};
GLfloat Cor::getG(){
    return this->G;
};
GLfloat Cor::getB(){
    return this->B;
};


void Cor::setR(GLfloat r){
    this->R = r;
};
void Cor::setG(GLfloat g){
    this->G = g;
};
void Cor::setB(GLfloat b){
    this->B = b;
};