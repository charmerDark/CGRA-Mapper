#define DIM_I  4
#define DIM_J  4
#define DIM_K  4

//Tile sizes for i j k
#define TI 2 
#define TK 2 
#define TJ 2  

float A[DIM_I][DIM_J];
float B[DIM_J][DIM_K];
float C[DIM_I][DIM_K];
float output[DIM_I][DIM_K];

void kernel(float A[][DIM_J], float B[][DIM_K], float C[][DIM_K], float alpha, float beta, float output[][DIM_K]);

int main()
{
  float alpha = 1.0, beta = -0.5;
  kernel(A, B, C, alpha, beta, output);

  return 0;
}

void kernel(float A[][DIM_J], float B[][DIM_K], float C[][DIM_K], float alpha, float beta, float output[][DIM_K]){
  int i, j, k;
  int ii, jj, kk;

  // Initialization (not tiled, as it's simple)
  for(i = 0; i < DIM_I; i++){
      for(k = 0; k < DIM_K; k++){
          output[i][k] = beta * C[i][k];
      }
  }

  // Tiled matrix multiplication
  for (ii = 0; ii < DIM_I; ii += TI) {
    for (kk = 0; kk < DIM_K; kk += TK) {
      for (jj = 0; jj < DIM_J; jj += TJ) {
        for (i = ii; i < ii + TI && i < DIM_I; i++) {
          for (k = kk; k < kk + TK && k < DIM_K; k++) {
            for (j = jj; j < jj + TJ && j < DIM_J; j++) {
              output[i][k] += alpha * A[i][j] * B[j][k];
            }
          }
        }
      }
    }
  }
}