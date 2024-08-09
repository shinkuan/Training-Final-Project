#include "image.h"

Image::Image(int w, int h){
    width = w;
    height = h;
}

Image::~Image(){
    // Free the pixels at inherited classes, not here
}

Data_Loader Image::loader = Data_Loader();

int Image::get_width(){
    return width;
}

int Image::get_height(){
    return height;
}