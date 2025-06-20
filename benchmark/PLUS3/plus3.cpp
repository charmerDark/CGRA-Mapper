/*
        A+ B + C
*/


#define DIM_I  3
#define DIM_J  3


float A[DIM_I][DIM_J];
float B[DIM_I][DIM_J];
float C[DIM_I][DIM_J];
float output[DIM_I][DIM_J];

void kernel(float A[][DIM_J], float B[][DIM_J], float C[][DIM_J], float output[][DIM_J]);

int main()
{

  kernel(A, B, C, output);

  return 0;
}

void kernel(float A[][DIM_J], float B[][DIM_J], float C[][DIM_J], float output[][DIM_J])
/*

*/
{
        int i = 0, j =0 , k = 0, l = 0;

        for(i = 0; i < DIM_I; i++){
                for(j =0; j< DIM_J; j++){
                        output[i][j]+= A[i][j] + B[i][j] * C[i][j];
                }
        }
}
