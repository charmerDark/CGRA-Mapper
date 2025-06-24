/*
alpha * transpose(A) * x + beta * z
alpha * einsum("ji,j ->i"A,x) + beta * z
*/

#define DIM_I 3
#define DIM_J 3

float output[DIM_I];
float A[DIM_J][DIM_I];
float x[DIM_J];  
float z[DIM_I];

void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[]);

int main()
{
    float alpha = 3.9, beta = 0.05;
    kernel(A, x, z, alpha, beta, output);
    return 0;
}
void kernel(float A[][DIM_I], float x[], float z[], float alpha, float beta, float output[])
{
    int i, j;
    
    for(i = 0; i < DIM_I; i++) {
        output[i] = beta * z[i];
    }
    
    for(i = 0; i < DIM_I; i++) {
        for(j = 0; j < DIM_J; j++) {
            output[i] += alpha * A[j][i] * x[j];
        }
    }
}