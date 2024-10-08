#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

using namespace std;

class GrayImage : public Image{
private:
    int **pixels;

public:
    GrayImage();
    GrayImage(int w, int h, int **p);
    ~GrayImage();
    bool load_image(string filename);
    void dump_image(string filename);
    void display_x_server();
    void display_ascii();
    void display_cmd();
    void resize(int w, int h);
    GrayImage *create_resized(int w, int h);
    int get_average_pixel();
    int get_pixel(int x, int y);

    void set_pixel(int x, int y, int value);

};

#endif