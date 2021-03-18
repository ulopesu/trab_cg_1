#include "matrix.h"


void imprimeMatrix(GLfloat** mtx, int N) {
    int i, j;

    for (j = 0; j < N; j++)
    {
        printf("    %d    ", j);
    }

    printf("\n");

    for (i = 0; i < N; i++)
    {   
        printf("%d", i);
        for (j = 0; j < N; j++)
        {
            printf("    %f    ", mtx[i][j]);
        }
        printf("\n");
    }
}


GLfloat** identityMatrix(int N) {
    int i, j;
    GLfloat **result = (GLfloat **)calloc(N * N, sizeof(GLfloat));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if(i==j){
                result[i][j] = 1;
            }
        }
    }
    return result;
}


void multiMatrix(GLfloat **m1, GLfloat **m2, int N)
{
    int i, j, k;
    GLfloat **result = (GLfloat **)calloc(N * N, sizeof(GLfloat));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                result[i][j] += m1[i][k] + m2[k][j];
            }
        }
    }
    free(m1);
    m1 = result;
}


void rotateMatrix(GLfloat **m1, GLfloat a, GLfloat b, GLfloat c, int N)
{
    if (N < 3)
    {
        return;
    }

    int i, j, k;
    GLfloat **result = identityMatrix(N);

    a *= toRad;
    b *= toRad;
    c *= toRad;

    result[0][0] = cos(a) * cos(c) - sin(a) * cos(b) * sin(c);
    result[0][1] = sin(a) * cos(c) + cos(a) * cos(b) * sin(c);
    result[0][2] = sin(b) * sin(c);

    result[1][0] = -cos(a) * sin(c) - sin(a) * cos(b) * cos(c);
    result[1][1] = -sin(a) * sin(c) + cos(a) * cos(b) * cos(c);
    result[1][2] = sin(b) * cos(c);

    result[2][0] = sin(a) * sin(b);
    result[2][1] = -cos(a) * sin(b);
    result[2][2] = cos(b);

    multiMatrix(m1, result, N);
}