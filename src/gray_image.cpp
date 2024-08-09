#include "gray_image.h"

GrayImage::GrayImage() : Image(0, 0){
    pixels = nullptr;
}

GrayImage::GrayImage(int w, int h, int **p) : Image(w, h){
    pixels = p;
}

GrayImage::~GrayImage(){
    for(int i = 0; i < height; i++){
        delete[] pixels[i];
    }
    delete[] pixels;
}

bool GrayImage::load_image(string filename){
    int **p = loader.Load_Gray(filename, &width, &height);
    if(p == nullptr){
        return false;
    }
    pixels = p;
    return true;
}

void GrayImage::dump_image(string filename){
    if(pixels == nullptr){
        return;
    }
    loader.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::display_x_server(){
    if(pixels == nullptr){
        return;
    }
    loader.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::display_ascii(){
    if(pixels == nullptr){
        return;
    }
    loader.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::display_cmd(){
    if(pixels == nullptr){
        return;
    }
    const char* filename = "temp_gray.jpg";
    loader.Dump_Gray(width, height, pixels, filename);
    loader.Display_Gray_CMD(filename);
    std::remove(filename);
}