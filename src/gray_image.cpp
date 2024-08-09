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

void GrayImage::resize(int w, int h){
    if(pixels == nullptr){
        return;
    }
    int **new_pixels = new int*[h];
    for(int i = 0; i < h; i++){
        new_pixels[i] = new int[w];
    }

    // Downscaling
    // For each pixel in the new image, take average of the corresponding pixels in the old image
    float x_scale = (float)width / w;
    float y_scale = (float)height / h;
    if(x_scale < 1 || y_scale < 1){
        std::cerr << "Cannot upscale image" << std::endl;
        return;
    }
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int val = 0;
            int count = 0;
            for(int y = (int)(i * y_scale); y < (int)((i + 1) * y_scale); y++){
                for(int x = (int)(j * x_scale); x < (int)((j + 1) * x_scale); x++){
                    val += pixels[y][x];
                    count++;
                }
            }
            new_pixels[i][j] = val / count;
        }
    }

    for(int i = 0; i < height; i++){
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = new_pixels;
    width = w;
    height = h;

    return;
}