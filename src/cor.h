#ifndef COR_H
#define COR_H
#include <GL/gl.h>

class Cor
{   
private:
    GLfloat R;
    GLfloat G;
    GLfloat B;

public:
    Cor(GLfloat r, GLfloat g, GLfloat b);
    GLfloat getR();
    GLfloat getG();
    GLfloat getB();
    void setR(GLfloat R);
    void setG(GLfloat G);
    void setB(GLfloat B);
};

#endif /* COR_H */