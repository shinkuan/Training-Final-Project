#include "rgb_image.h"

RGBImage::RGBImage() : Image(0, 0){
    pixels = nullptr;
}

RGBImage::RGBImage(int w, int h, int ***p) : Image(w, h){
    pixels = p;
}

RGBImage::~RGBImage(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            delete[] pixels[i][j];
        }
        delete[] pixels[i];
    }
    delete[] pixels;
}

bool RGBImage::load_image(string filename){
    int ***p = loader.Load_RGB(filename, &width, &height);
    if(p == nullptr){
        return false;
    }
    pixels = p;
    return true;
}

void RGBImage::dump_image(string filename){
    if(pixels == nullptr){
        return;
    }
    loader.Dump_RGB(width, height, pixels, filename);
}

void RGBImage::display_x_server(){
    if(pixels == nullptr){
        return;
    }
    loader.Display_RGB_X_Server(width, height, pixels);
}

void RGBImage::display_ascii(){
    if(pixels == nullptr){
        return;
    }
    loader.Display_RGB_ASCII(width, height, pixels);
}

void RGBImage::display_cmd(){
    if(pixels == nullptr){
        return;
    }
    const char* filename = "temp_rgb.jpg";
    loader.Dump_RGB(width, height, pixels, filename);
    loader.Display_RGB_CMD(filename);
    std::remove(filename);
}