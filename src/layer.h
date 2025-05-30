#ifndef LAYER_H_HEADER_GUARD
#define LAYER_H_HEADER_GUARD

#include "filter.h"
#include <stdint.h>

typedef struct FilterLayer {
  Filter **filters;
  uint8_t filterCount;
} FilterLayer;

FilterLayer *newFilterLayer(uint8_t width, uint8_t height, uint8_t channelCount,
                            uint8_t filterCount) {
  FilterLayer *filterLayer = malloc(sizeof(FilterLayer));
  filterLayer->filters = malloc(sizeof(Filter *) * filterCount);

  for (int i = 0; i < filterCount; i++) {
    filterLayer->filters[i] = newFilter(width, height, inputChannelCount)
  }
}

Image *applyFilterLayer(Image *image, FilterLayer *layer) {}

typedef struct ReluLayer {

} ReluLayer;

typedef struct PoolLayer {

} PoolLayer;

#endif
