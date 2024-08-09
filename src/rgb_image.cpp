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

void RGBImage::resize(int w, int h){
    if(pixels == nullptr){
        return;
    }
    RGBImage *new_img = create_resized(w, h);
    if(new_img == nullptr){
        return;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            delete[] pixels[i][j];
        }
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = new_img->pixels;
    width = w;
    height = h;
    new_img->pixels = nullptr;
    delete new_img;
}

RGBImage *RGBImage::create_resized(int w, int h){
    if(pixels == nullptr){
        return nullptr;
    }
    int ***new_pixels = new int**[h];
    for(int i = 0; i < h; i++){
        new_pixels[i] = new int*[w];
        for(int j = 0; j < w; j++){
            new_pixels[i][j] = new int[3];
        }
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
            int valr = 0;
            int valg = 0;
            int valb = 0;
            int count = 0;
            for(int y = (int)(i * y_scale); y < (int)((i + 1) * y_scale); y++){
                for(int x = (int)(j * x_scale); x < (int)((j + 1) * x_scale); x++){
                    valr += pixels[y][x][0];
                    valg += pixels[y][x][1];
                    valb += pixels[y][x][2];
                    count++;
                }
            }
            new_pixels[i][j][0] = valr / count;
        }
    }

    RGBImage *new_img = new RGBImage(w, h, new_pixels);
    return new_img;
}
    

int *RGBImage::get_average_pixel(){
    if(pixels == nullptr){
        return nullptr;
    }
    int *avg = new int[3];
    avg[0] = 0;
    avg[1] = 0;
    avg[2] = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            avg[0] += pixels[i][j][0];
            avg[1] += pixels[i][j][1];
            avg[2] += pixels[i][j][2];
        }
    }
    avg[0] /= (width * height);
    avg[1] /= (width * height);
    avg[2] /= (width * height);
    return avg;
}

int *RGBImage::get_pixel(int x, int y){
    if(pixels == nullptr || x < 0 || x >= width || y < 0 || y >= height){
        return nullptr;
    }
    int *pixel = new int[3];
    pixel[0] = pixels[y][x][0];
    pixel[1] = pixels[y][x][1];
    pixel[2] = pixels[y][x][2];
    return pixel;
}