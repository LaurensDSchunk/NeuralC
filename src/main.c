#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data.h"
#include "filter.h"
#include "image.h"

int main(void) {
  srand(time(NULL));

  LabeledImage *data = readData("resources/mnist_train.csv", 60000);

  Filter *filter1 = newFilter(3, 3, 1);
  Filter *filter2 = newFilter(3, 3, 1);
  Filter *filter3 = newFilter(3, 3, 1);

  Image *img = data[45].image;

  Image *out = newEmptyImage(28, 28, 3);

  out->channels[0] = applyFilter(img, filter1);
  out->channels[1] = applyFilter(img, filter2);
  out->channels[2] = applyFilter(img, filter3);

  printFilter(filter1);
  printImageChannel(out, 0);
  printFilter(filter2);
  printImageChannel(out, 1);
  printFilter(filter3);
  printImageChannel(out, 2);

  return EXIT_SUCCESS;
}
