#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->load_image("Image-Folder/mnist/img_100.jpg");
    img1->dump_image("img1.jpg");
    // img1->display_x_server();
    // img1->display_cmd();
    

    Image *img2 = new RGBImage();
    img2->load_image("Image-Folder/lena.jpg");
    img2->dump_image("img2.jpg");
    // img2->display_x_server();
    // img2->display_cmd();

    // some bit field filter design driven code here
    RGBImage *rgbImg = new RGBImage();
    rgbImg->load_image("Image-Folder/lena.jpg");

    GrayImage *grayImg = new GrayImage();
    grayImg->load_image("Image-Folder/mnist/img_100.jpg");

    // Other filter
    Filter filter;

    int choose=2;
    if(choose==1){
        // Box Filter
        filter.set_option(FILTER_BOX);
        filter.apply(rgbImg);
        //rgbImg->dump_image("out_Image/rgb_box_filtered.jpg");

        //filter.set_option(FILTER_BOX);
        filter.apply(grayImg);
        grayImg->dump_image("out_Image/gray_box_filtered.jpg");
    }
    else if(choose==2){
        // Sobel Gradient Filter
        filter.set_option(FILTER_SOBEL_GRADIENT);
        filter.apply(rgbImg);
        rgbImg->dump_image("out_Image/rgb_sobel_filtered.jpg");

        //filter.set_option(FILTER_SOBEL_GRADIENT);
        filter.apply(grayImg);
        grayImg->dump_image("out_Image/gray_sobel_filtered.jpg");
    }
    else if(choose==3){
        // Contrast Stretching Filter
        filter.set_option(FILTER_CONTRAST_STRETCHING);
        filter.apply(rgbImg);
        rgbImg->dump_image("out_Image/rgb_contrast_stretched.jpg");    

        //filter.set_option(FILTER_CONTRAST_STRETCHING);
        filter.apply(grayImg);
        grayImg->dump_image("out_Image/gray_contrast_stretched.jpg");
    }
    else{
        // Mosaic Filter
        filter.set_option(FILTER_MOSAIC);
        filter.apply(rgbImg);
        rgbImg->dump_image("out_Image/rgb_mosaic_filtered.jpg");

        //filter.set_option(FILTER_MOSAIC);
        filter.apply(grayImg);
        grayImg->dump_image("out_Image/gray_mosaic_filtered.jpg");
    }

    // TODO: ./Image_Processing <target> <tiles_folder> <output> [--filter]
    // Photo Mosaic
    PhotoMosaic *pm = new PhotoMosaic();
    pm->set_target("Image-Folder/girl_2x.png");     
    pm->set_tiles("Image-Folder/cifar10");
    RGBImage *mosaic = pm->create_mosaic(64, 64);
    mosaic->dump_image("mosaic.jpg");
    RGBImage *original = new RGBImage();
    original->load_image("Image-Folder/girl_2x.png");
    RGBImage *resized = original->create_resized(64, 64);
    resized->dump_image("resized.jpg");

    // more ...
    return 0;
}
