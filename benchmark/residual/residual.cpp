/*
    y - Ax
    y - einsum("ij,j -> i", A,x)
*/
#define DIM_I 4


float y[DIM_I];
float x[DIM_I];
float A[DIM_I][DIM_I];
float output[DIM_I];


void kernel(float y[], float A[][DIM_I], float x[],float output[]);


int main(){

    kernel(y,A,x, output);
    return 0;

}

void kernel(float y[], float A[][DIM_I], float x[], float output[]){
    int i = 0, j = 0;
    

    for(i = 0; i < DIM_I; i++){
        output[i] = 0.0;
    }
    
    for(i = 0; i < DIM_I; i++){

        for(j = 0; j < DIM_I; j++){
            output[i] += A[i][j] * x[j]; 
        }

        output[i] = y[i] - output[i];
    }
}