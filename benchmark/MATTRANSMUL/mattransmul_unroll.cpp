#define DIM_I 16
#define DIM_J 16
#define UNROLL 2

float output[DIM_I];
float A[DIM_J][DIM_I];
float x[DIM_J];
float z[DIM_I];

void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[]);

void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[])
{
    int i, j;

    // Initialization
    for(i = 0; i < DIM_I; i++) {
        output[i] = beta * z[i];
    }

    // Unrolled matrix-vector multiplication
    for(i = 0; i < DIM_I; i++) {
        for(j = 0; j + UNROLL - 1 < DIM_J; j += UNROLL) {
            // Unroll body
            #if UNROLL > 0
            output[i] += alpha * A[j][i] * x[j];
            #endif
            #if UNROLL > 1
            output[i] += alpha * A[j+1][i] * x[j+1];
            #endif
            #if UNROLL > 2
            output[i] += alpha * A[j+2][i] * x[j+1];
            #endif
            #if UNROLL > 3
            output[i] += alpha * A[j+3][i] * x[j+1];
            #endif

        }
        // Handle remainder
        for(; j < DIM_J; j++) {
            output[i] += alpha * A[j][i] * x[j];
        }
    }
}
