#ifndef _FILTER_H_
#define _FILTER_H_

#include "gray_image.h"
#include "rgb_image.h"

#define FILTER_NONE                 0b00000000
#define FILTER_BOX                  0b00000001
#define FILTER_SOBEL_GRADIENT       0b00000010
#define FILTER_CONTRAST_STRETCHING  0b00000100
#define FILTER_MOSAIC               0b00001000

class Filter{
public:
    Filter();
    Filter(int8_t opt);
    ~Filter();
    void apply(RGBImage *img);
    void apply(GrayImage *img);
    void set_option(int8_t opt);

private:
    int8_t option;

};

#endif