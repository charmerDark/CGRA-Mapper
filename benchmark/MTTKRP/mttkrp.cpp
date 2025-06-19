/*
Matricized tensor times Khatri-Rao product (MTTKRP)
        A(i,k,l) * B(l,j) * C(k,j)     

*/

#define DIM_I  2
#define DIM_J  2
#define DIM_K  2
#define DIM_L 2

float A[DIM_I][DIM_K][DIM_L];
float B[DIM_L][DIM_J];
float C[DIM_K][DIM_J];
float output[DIM_I][DIM_J];

void kernel(float A[][DIM_K][DIM_L], float B[][DIM_J], float C[][DIM_J], float output[][DIM_J]);

int main()
{

  kernel(A, B, C, output);

  return 0;
}

void kernel(float A[][DIM_K][DIM_L], float B[][DIM_J], float C[][DIM_J], float output[][DIM_J])
/*

*/
{
        int i = 0, j =0 , k = 0, l = 0;

        for(i = 0; i < DIM_I; i++){
                for(j =0; j< DIM_J; j++){
                        for(k = 0 ; k<DIM_K; k++){
                                for(l = 0 ; l<DIM_L; l++){
                                        output[i][j]+= A[i][k][l] * B[l][j] * C[k][j];
                                }
                        }
                }
        }
}
