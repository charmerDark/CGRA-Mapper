/*
Tensor times vector
einsum(ijk,k-> ij, A,B)
*/

#define DIM_I  2
#define DIM_J  2
#define DIM_K  2
#define DIM_L 2

float A[DIM_I][DIM_J][DIM_K];
float B[DIM_K];
float output[DIM_I][DIM_J];

void kernel(float A[][DIM_J][DIM_K], float B[DIM_K], float output[][DIM_J]);

int main()
{

  kernel(A, B, output);

  return 0;
}

void kernel(float A[][DIM_J][DIM_K], float B[DIM_K], float output[][DIM_J])
/*

*/
{
    int i = 0, j =0 , k = 0;

    for(i = 0; i < DIM_I; i++){
            for(j =0; j< DIM_J; j++){
                    for(k = 0 ; k<DIM_K; k++){
                                output[i][j]+= A[i][j][k] * B[k];
                    }
            }
    }
}
