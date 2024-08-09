#include "filter.h"

Filter::Filter(){
    option = FILTER_NONE;
}

Filter::Filter(int8_t opt){
    option = opt;
}

Filter::~Filter(){
    // Nothing to do
}

void Filter::apply(RGBImage *img){
    // Apply the filter to the RGB image
    if (option & FILTER_BOX){
        // Apply the box filter
    }
    if (option & FILTER_SOBEL_GRADIENT){
        // Apply the Sobel gradient filter
    }
    if (option & FILTER_CONTRAST_STRETCHING){
        // Apply the contrast stretching filter
    }
    if (option & FILTER_MOSAIC){
        // Apply the mosaic filter
    }
}

void Filter::apply(GrayImage *img){
    // Apply the filter to the gray image
    if (option & FILTER_BOX){
        // Apply the box filter
    }
    if (option & FILTER_SOBEL_GRADIENT){
        // Apply the Sobel gradient filter
    }
    if (option & FILTER_CONTRAST_STRETCHING){
        // Apply the contrast stretching filter
    }
    if (option & FILTER_MOSAIC){
        // Apply the mosaic filter
    }
}

void Filter::set_option(int8_t opt){
    option = opt;
}