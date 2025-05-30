#ifndef IMAGE_H_HEADER_GUARD
#define IMAGE_H_HEADER_GUARD

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Channel {
  float **pixels;
} Channel;

Channel *newChannel(uint8_t width, uint8_t height) {
  Channel *channel = malloc(sizeof(Channel));

  channel->pixels = malloc(sizeof(float *) * height);
  float *data = malloc(sizeof(float) * width * height);

  for (int i = 0; i < height; i++) {
    channel->pixels[i] = data + i * width;
  }

  return channel;
}

void deleteChannel(Channel *channel) {
  free(channel->pixels[0]);
  free(channel->pixels);
  free(channel);
}

typedef struct Image {
  uint8_t width;
  uint8_t height;

  Channel **channels;
  uint8_t channelCount;
} Image;

Image *newImage(uint8_t width, uint8_t height, Channel **channels,
                uint8_t channelCount) {
  Image *image = malloc(sizeof(Image));

  image->width = width;
  image->height = height;
  image->channels = channels;
  image->channelCount = channelCount;

  return image;
}

Image *newEmptyImage(uint8_t width, uint8_t height, uint8_t channelCount) {
  Channel **channels = malloc(sizeof(Channel *) * channelCount);
  for (int i = 0; i < channelCount; i++) {
    channels[i] = newChannel(width, height);
  }

  return newImage(width, height, channels, channelCount);
}

void deleteImage(Image *image) {
  for (int i = 0; i < image->channelCount; i++) {
    deleteChannel(image->channels[i]);
  }
  free(image->channels);
  free(image);
}

void printChannel(Channel *channel, uint8_t width, uint8_t height) {
  printFloatImage(channel->pixels, width, height);
}

void printImageChannel(Image *image, uint8_t channelIndex) {
  Channel *channel = image->channels[channelIndex];
  const int width = image->width;
  const int height = image->height;

  printChannel(channel, width, height);
}

#endif
