#ifndef UTILS_H_HEADER_GUARD
#define UTILS_H_HEADER_GUARD

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFloatImage(float **image, const int width, const int height) {
  // Get the min and max
  float min = image[0][0];
  float max = image[0][0];
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (image[row][col] < min) {
        min = image[row][col];
      }
      if (image[row][col] > max) {
        max = image[row][col];
      }
    }
  }

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      float pixel = image[row][col];

      int r = 0, g = 0, b = 0;

      // Positive is red, negative is blue
      if (pixel >= 0 && max != 0) {
        float norm = pixel / max;
        r = (int)(norm * 255);
      } else if (min != 0) {
        float norm = pixel / min; // min is negative, so norm is positive
        b = (int)(norm * 255);
      }

      printf("\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
    }
    printf("\n");
  }
}

#endif
