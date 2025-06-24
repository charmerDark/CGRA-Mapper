/*
Tensor times Matrix multiplication
einsum("ijl,kl -> ijk",A,B)
*/

#define DIM_I  2
#define DIM_J  2
#define DIM_K  2
#define DIM_L 2

float A[DIM_I][DIM_J][DIM_L];
float B[DIM_K][DIM_L];
float output[DIM_I][DIM_J][DIM_K];

void kernel(float A[][DIM_J][DIM_L], float B[][DIM_L], float output[][DIM_J][DIM_K]);

int main()
{

  kernel(A, B, output);

  return 0;
}

void kernel(float A[][DIM_J][DIM_L], float B[][DIM_L], float output[][DIM_J][DIM_K])
/*

*/
{
        int i = 0, j =0 , k = 0, l = 0;

        for(i = 0; i < DIM_I; i++){
                for(j =0; j< DIM_J; j++){
                        for(k = 0 ; k<DIM_K; k++){
                                for(l = 0 ; l<DIM_L; l++){
                                        output[i][j][k]+= A[i][j][l] * B[k][l];
                                }
                        }
                }
        }
}
