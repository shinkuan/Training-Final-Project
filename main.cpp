#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->load_image("Image-Folder/mnist/img_100.jpg");
    img1->dump_image("img1.jpg");
    img1->display_x_server();
    img1->display_cmd();
    

    Image *img2 = new RGBImage();
    img2->load_image("Image-Folder/lena.jpg");
    img2->dump_image("img2.jpg");
    img2->display_x_server();
    img2->display_cmd();

    // some bit field filter design driven code here

    // some photo mosaic driven code here

    // more ...
    return 0;
}
