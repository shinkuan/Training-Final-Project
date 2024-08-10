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

template<typename ImageType>
void Filter::apply(ImageType *img){
    // Apply the filter to the RGB image
    if (option & FILTER_BOX){
        // Apply the box filter
        apply_box_filter(img);
    }
    if (option & FILTER_SOBEL_GRADIENT){
        // Apply the Sobel gradient filter
        apply_sobel_gradient_filter(img);
    }
    if (option & FILTER_CONTRAST_STRETCHING){
        // Apply the contrast stretching filter
        apply_contrast_stretching_filter(img);
    }
    if (option & FILTER_MOSAIC){
        // Apply the mosaic filter
        apply_mosaic_filter(img);
    }
}

void Filter::set_option(int8_t opt){
    option = opt;
}

void Filter::apply(RGBImage *img){
    apply<RGBImage>(img);
}

void Filter::apply(GrayImage *img){
    apply<GrayImage>(img);
}

void Filter::apply_box_filter(RGBImage *img){
    // Apply the box filter to the RGB image
    //模糊處理
    
}

void Filter::apply_box_filter(GrayImage *img){
    // Apply the box filter to the gray image
}

void Filter::apply_sobel_gradient_filter(RGBImage *img){
    // Apply the Sobel gradient filter to the RGB image
    //垂直和水平的線條
    
}

void Filter::apply_sobel_gradient_filter(GrayImage *img){
    // Apply the Sobel gradient filter to the gray image
}

void Filter::apply_contrast_stretching_filter(RGBImage *img){
    // Apply the contrast stretching filter to the RGB image
}

void Filter::apply_contrast_stretching_filter(GrayImage *img){
    // Apply the contrast stretching filter to the gray image
}

void Filter::apply_mosaic_filter(RGBImage *img){
    // Apply the mosaic filter to the RGB image
}

void Filter::apply_mosaic_filter(GrayImage *img){
    // Apply the mosaic filter to the gray image
}

