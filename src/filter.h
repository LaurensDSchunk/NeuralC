#ifndef FILTER_H_HEADER_GUARD
#define FILTER_H_HEADER_GUARD

#include "image.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Filter {
  uint8_t width;
  uint8_t height;
  uint8_t kernelCount;

  float ***kernels;
  float bias;
} Filter;

Filter *newFilter(uint8_t width, uint8_t height, uint8_t kernelCount) {
  Filter *filter = malloc(sizeof(Filter));

  filter->width = width;
  filter->height = height;
  filter->kernelCount = kernelCount;
  filter->bias = ((float)rand() / RAND_MAX) * 2 - 1;

  // Create and fill kernels
  filter->kernels = malloc(sizeof(float **) * kernelCount);
  float **rows = malloc(sizeof(float *) * height * kernelCount);
  float *contArr = malloc(sizeof(float) * kernelCount * width * height);

  for (int i = 0; i < kernelCount; i++) {
    filter->kernels[i] = rows + i * height;
    for (int j = 0; j < height; j++) {
      filter->kernels[i][j] = contArr + (i * height * width) + (j * width);
      for (int k = 0; k < width; k++) {
        filter->kernels[i][j][k] = ((float)rand() / RAND_MAX) * 2 - 1;
      }
    }
  }

  return filter;
}

void deleteFilter(Filter *filter) {
  free(filter->kernels[0][0]); // Deletes contiguous float array
  free(filter->kernels[0]);    // Deletes contiguous row array
  free(filter->kernels);       // Deletes base array
  free(filter);
}

void printFilter(Filter *filter) {
  for (int i = 0; i < filter->kernelCount; i++) {
    printFloatImage(filter->kernels[i], filter->width, filter->height);
  }
}

Channel *applyFilter(Image *inputImage, Filter *filter) {
  if (inputImage->channelCount != filter->kernelCount) {
    fprintf(stderr,
            "Image channel count does not match filter kernel count.\n");
    exit(EXIT_FAILURE);
  }

  Channel *output = newChannel(inputImage->width, inputImage->height);

  for (int row = 0; row < inputImage->height; row++) {
    for (int col = 0; col < inputImage->width; col++) {

      output->pixels[row][col] = filter->bias;
      for (int filterRow = 0; filterRow < filter->height; filterRow++) {
        for (int filterCol = 0; filterCol < filter->width; filterCol++) {
          int imageRow = row + filterRow - filter->height / 2;
          int imageCol = col + filterCol - filter->width / 2;

          // Out-of-bounds pixels are 0
          if ((imageRow < 0 || imageRow >= inputImage->height) ||
              (imageCol < 0 || imageCol >= inputImage->width))
            continue;

          // Loop over channels, and sum up each dotproduct
          for (int channel = 0; channel < inputImage->channelCount; channel++) {
            output->pixels[row][col] +=
                inputImage->channels[channel]->pixels[imageRow][imageCol] *
                filter->kernels[channel][filterRow][filterCol];
          }
        }
      }
    }
  }

  return output;
}

#endif
