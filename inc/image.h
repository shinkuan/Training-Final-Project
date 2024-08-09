#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"

using namespace std;

class Image{
protected:
    int width;
    int height;
    static Data_Loader loader; 

public:
    Image(int w, int h);
    ~Image();
    virtual bool load_image(string filename) = 0;
    virtual void dump_image(string filename) = 0;
    virtual void display_x_server() = 0;
    virtual void display_ascii() = 0;
    virtual void display_cmd() = 0;
    virtual void resize(int w, int h) = 0;
    int get_width();
    int get_height();

};

#endif