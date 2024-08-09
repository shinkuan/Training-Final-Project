#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

using namespace std;

class RGBImage : public Image{
private:
    int ***pixels;

public:
    RGBImage();
    RGBImage(int w, int h, int ***p);
    ~RGBImage();
    bool load_image(string filename);
    void dump_image(string filename);
    void display_x_server();
    void display_ascii();
    void display_cmd();
    void resize(int w, int h);
    RGBImage *create_resized(int w, int h);
    int *get_average_pixel();
    int *get_pixel(int x, int y);

};

#endif