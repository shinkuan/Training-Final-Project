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
    Image();
    ~Image();
    virtual bool load_image(string filename);
    virtual bool dump_image(string filename);
    virtual void display_x_server();
    virtual void display_ascii();
    virtual void display_cmd();
    int get_width();
    int get_height();

};

#endif