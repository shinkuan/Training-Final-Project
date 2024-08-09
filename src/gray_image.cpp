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
    GrayImage *new_img = create_resized(w, h);
    if(new_img == nullptr){
        return;
    }
    for(int i = 0; i < height; i++){
        delete[] pixels[i];
    }
    delete[] pixels;
    width = w;
    height = h;
    pixels = new_img->pixels;
    new_img->pixels = nullptr;
    delete new_img;
}

GrayImage *GrayImage::create_resized(int w, int h){
    if(pixels == nullptr){
        return nullptr;
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
        return nullptr;
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

    GrayImage *new_img = new GrayImage(w, h, new_pixels);
    return new_img;
}

int GrayImage::get_average_pixel(){
    if(pixels == nullptr){
        return -1;
    }
    int sum = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            sum += pixels[i][j];
        }
    }
    return sum / (width * height);
}

int GrayImage::get_pixel(int x, int y){
    if(pixels == nullptr || x < 0 || x >= width || y < 0 || y >= height){
        return -1;
    }
    return pixels[y][x];
}