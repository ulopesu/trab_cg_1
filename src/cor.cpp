#include "cor.h"

Cor::Cor(GLfloat r, GLfloat g, GLfloat b)
{
    this->R = r;
    this->G = g;
    this->B = b;
}
Cor::Cor(string nameCor)
{
    if (nameCor == "red")
    {
        this->R = 1;
        this->G = 0;
        this->B = 0;
    }
    else if (nameCor == "green")
    {
        this->R = 0;
        this->G = 1;
        this->B = 0;
    }
    else if (nameCor == "blue")
    {
        this->R = 0;
        this->G = 0;
        this->B = 1;
    } else {
        this->R = 1;
        this->G = 1;
        this->B = 1;
    }
}

GLfloat Cor::getR()
{
    return this->R;
};
GLfloat Cor::getG()
{
    return this->G;
};
GLfloat Cor::getB()
{
    return this->B;
};

void Cor::setR(GLfloat r)
{
    this->R = r;
};
void Cor::setG(GLfloat g)
{
    this->G = g;
};
void Cor::setB(GLfloat b)
{
    this->B = b;
};