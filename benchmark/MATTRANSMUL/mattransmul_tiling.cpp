#define DIM_I 16
#define DIM_J 16
#define TI 2  // tile size for i
#define TJ 2  // tile size for j

float output[DIM_I];
float A[DIM_J][DIM_I];
float x[DIM_J];
float z[DIM_I];

void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[]);

void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[])
{
    int i, j, ii, jj;

    // Initialization (not tiled)
    for(i = 0; i < DIM_I; i++) {
        output[i] = beta * z[i];
    }

    // Tiled matrix-vector multiplication
    for (ii = 0; ii < DIM_I; ii += TI) {
        for (jj = 0; jj < DIM_J; jj += TJ) {
            for (i = ii; i < ii + TI && i < DIM_I; i++) {
                for (j = jj; j < jj + TJ && j < DIM_J; j++) {
                    output[i] += alpha * A[j][i] * x[j];
                }
            }
        }
    }
}
