#ifndef DATA_H_HEADER_GUARD
#define DATA_H_HEADER_GUARD

#include "image.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_WIDTH 28
#define IMAGE_HEIGHT 28
const int MAX_LINE_SIZE = 5000;

typedef struct LabeledImage {
  uint8_t label;

  Image *image;
} LabeledImage;

LabeledImage *readData(char *dataPath, int rows) {
  FILE *file = fopen(dataPath, "r");

  if (!file) {
    perror("Failed to open data file");
    exit(EXIT_FAILURE);
  }

  LabeledImage *images = malloc(sizeof(LabeledImage) * rows);
  for (int i = 0; i < rows; i++) {
    images[i].image = newEmptyImage(28, 28, 1);
  }

  int lineNumber = 0;
  char line[MAX_LINE_SIZE];
  while (fgets(line, sizeof(line), file) && lineNumber < rows) {
    // Removes any newlines or carrige returns from the line
    line[strcspn(line, "\r\n")] = 0;

    // Tokenize the line
    char *token = strtok(line, ",");

    // The first token is the label
    images[lineNumber].label = atoi(token);

    int row = 0;
    int col = 0;
    token = strtok(NULL, ","); // Hops to next token

    while (token != NULL) {
      int pixel = atoi(token);
      images[lineNumber].image->channels[0]->pixels[row][col] = pixel;
      col++;
      if (col == IMAGE_WIDTH) {
        col = 0;
        row++;

        // Handle invalid data (partially)
        if (row > IMAGE_HEIGHT) {
          fprintf(stderr, "Too many pixel values on line %d\n", lineNumber + 1);
          exit(EXIT_FAILURE);
        }
      }
      token = strtok(NULL, ",");
    }

    lineNumber++;
  }

  if (lineNumber != rows) {
    printf("Rows does not match row count. Actual %d", lineNumber);
  }

  return images;
}

#endif
