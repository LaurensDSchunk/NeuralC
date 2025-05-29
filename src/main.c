#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

const int MAX_LINE_LEN = 5000;

int main(void) {
  readData("resources/mnist_train.csv", 60000);
  return 0;
}
