/* Basic sacalr multiplication and vector addition*/


#define NTAPS 32


float output[NTAPS];
float alpha = -1.5;
float X[NTAPS] = {0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
    0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
    0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
    0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};

float Y[NTAPS] = {0.35, -1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
        0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
        0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
        0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};

void kernel(float X[], float Y[], float alpha, float output[]);

int main()
{

//  input_dsp (input, NTAPS, 0);
float a = 3.9;
  kernel(X, Y, a, output);

//  output_dsp (input, NTAPS, 0);
//  output_dsp (coefficients, NTAPS, 0);
//  output_dsp (output, NTAPS, 0);
  return 0;
}

void kernel(float X[], float Y[], float alpha, float output[])
/*
scalar multiplication of alpha * X followed by vector addition of Y.
*/
{
int i;

for (i = 0; i < NTAPS; ++i) {
output[i] = alpha * X[i] + Y[i];
}

}