#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#define toRad (M_PI / 180)

void imprimeMatrix(GLfloat** mtx, int N);
GLfloat** identityMatrix(int N);
void multiMatrix(GLfloat **m1, GLfloat **m2, int N);
void rotateMatrix(GLfloat **m1, GLfloat a, GLfloat b, GLfloat c, int N);