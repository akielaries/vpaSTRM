#include <math.h>
#include <stdio.h>
 
// Function to calculate the inverse
// discrete fourier transformation
void calculate_IDFT(int len) {
    int x[len];
    float Xr[len];
    float Xi[len];
    int i, k, n, N = 0;
    for (i = 0; i < len; i++) {
        printf(
            "Enter the real and "
            "imaginary bits of X(%d): ",
            i);
        scanf("%f %f", &Xr[i], &Xi[i]);
    }
 
    printf("Enter the number of "
           "points in the IDFT: ");
    scanf("%d", &N);
 
    for (n = 0; n < N; n++) {
        x[n] = 0;
        for (k = 0; k < N; k++) {
            int theta = (2 * 3.141592 * k * n) / N;
            x[n] = x[n] + Xr[k] * cos(theta)
                   + Xi[k] * sin(theta);
        }
        x[n] = x[n] / N;
        printf("\n x[%d] = %d\n", n,
               x[n]);
    }
 
    printf("\n-----------x[n]------------\n\n");
}
 
int main() {
    int len = 0;
    printf("Enter the length of "
           "the sequence: ");
    scanf("%d", &len);
    calculate_IDFT(len);
 
    return 0;
}

