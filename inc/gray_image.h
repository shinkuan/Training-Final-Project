#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;

public:
    GrayImage();
    GrayImage(int w, int h, int **p);
    ~GrayImage();
    bool load_image(string filename);
    bool dump_image(string filename);
    void display_x_server();
    void display_ascii();
    void display_cmd();

};

#endif