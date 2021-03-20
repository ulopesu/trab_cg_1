#include "matrix.h"

void imprimeMatrix(GLfloat **mtx, int N)
{
    int i, j;

    printf("\n\n");
    printf("MATRIX\n\n");
    for (j = 0; j < N; j++)
    {
        printf("      %d      ", j);
    }

    printf("\n\n");

    for (i = 0; i < N; i++)
    {
        printf("%d", i);
        for (j = 0; j < N; j++)
        {
            printf("    %.2f    ", mtx[i][j]);
        }
        printf("\n");
    }
}

GLfloat **zeroMatrix(int N)
{
    int i, j;
    GLfloat **result = (GLfloat **)calloc(N, sizeof(GLfloat *));
    for (i = 0; i < N; i++)
    {
        result[i] = (GLfloat *)calloc(N, sizeof(GLfloat));
    }
    return result;
}

GLfloat **identityMatrix(int N)
{
    int i, j;
    GLfloat **result = (GLfloat **)calloc(N, sizeof(GLfloat *));
    for (i = 0; i < N; i++)
    {
        result[i] = (GLfloat *)calloc(N, sizeof(GLfloat));
        for (j = 0; j < N; j++)
        {
            if (i == j)
            {
                result[i][j] = 1;
            }
        }
    }
    return result;
}

GLfloat **transposedMatrix(GLfloat **mtx, int N)
{
    int i, j;
    GLfloat **result = zeroMatrix(N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            result[i][j] = mtx[j][i];
        }
    }
    return result;
}

GLfloat **multiMatrix(GLfloat **m1, GLfloat **m2, int N)
{
    int i, j, k;
    GLfloat **result = zeroMatrix(N);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}
/*
GLfloat** rotateZmatrix(GLfloat **m1, GLfloat c,  int N) {
    GLfloat **mtx_rotate = identityMatrix(N);

    c *= toRad;

    mtx_rotate[0][0] = cos(c);
    mtx_rotate[0][1] = -sin(c);

    mtx_rotate[1][0] = sin(c);
    mtx_rotate[1][1] = cos(c);

    return multiMatrix(m1, mtx_rotate, N);
}

GLfloat** rotateYmatrix(GLfloat **m1, GLfloat b,  int N) {
    GLfloat **mtx_rotate = identityMatrix(N);

    mtx_rotate[0][0] = cos(b);
    mtx_rotate[0][2] = sin(b);

    mtx_rotate[2][0] = -sin(b);
    mtx_rotate[2][2] = cos(b);

    return multiMatrix(m1, mtx_rotate, N);
}

GLfloat** rotateXmatrix(GLfloat **m1, GLfloat a,  int N) {
    GLfloat **mtx_rotate = identityMatrix(N);

    mtx_rotate[1][1] = cos(a);
    mtx_rotate[1][2] = -sin(a);

    mtx_rotate[2][1] = sin(a);
    mtx_rotate[2][2] = cos(a);

    return multiMatrix(m1, mtx_rotate, N);
}
*/
GLfloat **rotateMatrix(GLfloat **m1, GLfloat a, GLfloat b, GLfloat c, int N)
{
    GLfloat **mtx_rotate = identityMatrix(N);

    a *= toRad;
    b *= toRad;
    c *= toRad;

    mtx_rotate[0][0] = cos(b) * cos(c);
    mtx_rotate[0][1] = -(cos(b) * sin(c));
    mtx_rotate[0][2] = sin(b);

    mtx_rotate[1][0] = (sin(a) * sin(b) * cos(c)) + (cos(a) * sin(c));
    mtx_rotate[1][1] = -(sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c));
    mtx_rotate[1][2] = -(sin(a) * cos(b));

    mtx_rotate[2][0] = -(cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c));
    mtx_rotate[2][1] = (cos(a) * sin(b) * sin(c)) + (sin(a) * cos(c));
    mtx_rotate[2][2] = cos(a) * cos(b);

    return multiMatrix(m1, mtx_rotate, N);
}

GLfloat **translateMatrix(GLfloat **m1, GLfloat dx, GLfloat dy, GLfloat dz, int N)
{

    GLfloat **mtxTL = identityMatrix(N);
    mtxTL[3][0] = dx;
    mtxTL[3][1] = dy;
    mtxTL[3][2] = dz;

    m1[0][3] = 1;
    m1[1][3] = 1;
    m1[2][3] = 1;

    return multiMatrix(m1, mtxTL, N);
}

GLfloat **scaleMatrix(GLfloat **m1, GLfloat sx, GLfloat sy, GLfloat sz, int N)
{

    GLfloat **mtxS = identityMatrix(N);
    mtxS[0][2] = sx;
    mtxS[1][2] = sy;
    mtxS[2][2] = sz;

    return multiMatrix(m1, mtxS, N);
}

GLfloat dist(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    return sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}