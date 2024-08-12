#include "filter.h"

Filter::Filter(){
    option = FILTER_NONE;
}

Filter::Filter(int8_t opt){
    option = opt;
}

Filter::~Filter(){
    // Nothing to do
}

template<typename ImageType>
void Filter::apply(ImageType *img){
    // Apply the filter to the RGB image
    if (option & FILTER_BOX){
        // Apply the box filter
        apply_box_filter(img);
    }
    if (option & FILTER_SOBEL_GRADIENT){
        // Apply the Sobel gradient filter
        apply_sobel_gradient_filter(img);
    }
    if (option & FILTER_CONTRAST_STRETCHING){
        // Apply the contrast stretching filter
        apply_contrast_stretching_filter(img);
    }
    if (option & FILTER_MOSAIC){
        // Apply the mosaic filter
        apply_mosaic_filter(img);
    }
}

void Filter::set_option(int8_t opt){
    option = opt;
}

void Filter::apply(RGBImage *img){
    apply<RGBImage>(img);
}

void Filter::apply(GrayImage *img){
    apply<GrayImage>(img);
}

void Filter::apply_box_filter(RGBImage *img){
    // Apply the box filter to the RGB image
    // blurring
    int width = img->get_width();
    int height = img->get_height();
    
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int *pixel = img->get_pixel(x + kx, y + ky);
                    red_sum += pixel[0];
                    green_sum += pixel[1];
                    blue_sum += pixel[2];
                }
            }
            int red_avg = red_sum / 9;
            int green_avg = green_sum / 9;
            int blue_avg = blue_sum / 9;
            img->set_pixel(x, y, red_avg, green_avg, blue_avg);
        }
    }
}

void Filter::apply_box_filter(GrayImage *img){
    // Apply the box filter to the gray image
    int width = img->get_width();
    int height = img->get_height();

    // using a temp array
    std::vector<std::vector<int>> new_pixels(height, std::vector<int>(width, 0));

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sum = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sum += img->get_pixel(x + kx, y + ky); 
                }
            }
            new_pixels[y][x] = sum / 9;
        }
    }

    // update to original image
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            img->set_pixel(x, y, new_pixels[y][x]);
        }
    }
}

void Filter::apply_sobel_gradient_filter(RGBImage *img){
    // Apply the Sobel gradient filter to the RGB image
    //vertical line and horizental line
    int width = img->get_width();
    int height = img->get_height();
    
    // Define Sobel filters
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int red_Gx = 0, red_Gy = 0;
            int green_Gx = 0, green_Gy = 0;
            int blue_Gx = 0, blue_Gy = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int *pixel = img->get_pixel(x + kx, y + ky);
                    red_Gx += pixel[0] * Gx[ky + 1][kx + 1];
                    red_Gy += pixel[0] * Gy[ky + 1][kx + 1];
                    green_Gx += pixel[1] * Gx[ky + 1][kx + 1];
                    green_Gy += pixel[1] * Gy[ky + 1][kx + 1];
                    blue_Gx += pixel[2] * Gx[ky + 1][kx + 1];
                    blue_Gy += pixel[2] * Gy[ky + 1][kx + 1];
                }
            }

            int red_gradient = std::min(255, std::max(0, static_cast<int>(sqrt(red_Gx * red_Gx + red_Gy * red_Gy))));
            int green_gradient = std::min(255, std::max(0, static_cast<int>(sqrt(green_Gx * green_Gx + green_Gy * green_Gy))));
            int blue_gradient = std::min(255, std::max(0, static_cast<int>(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy))));

            img->set_pixel(x, y, red_gradient, green_gradient, blue_gradient);
        }
    }
}

void Filter::apply_sobel_gradient_filter(GrayImage *img){
    // Apply the Sobel gradient filter to the gray image
    int width = img->get_width();
    int height = img->get_height();
    
    // Define Sobel filters
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int Gx_value = 0, Gy_value = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixel = img->get_pixel(x + kx, y + ky);
                    Gx_value += pixel * Gx[ky + 1][kx + 1];
                    Gy_value += pixel * Gy[ky + 1][kx + 1];
                }
            }

            int gradient = std::min(255, std::max(0, static_cast<int>(sqrt(Gx_value * Gx_value + Gy_value * Gy_value))));

            img->set_pixel(x, y, gradient);
        }
    }
}

void Filter::apply_contrast_stretching_filter(RGBImage *img){
    // Apply the contrast stretching filter to the RGB image
    // Edge crispening
    
}

void Filter::apply_contrast_stretching_filter(GrayImage *img){
    // Apply the contrast stretching filter to the gray image
}

void Filter::apply_mosaic_filter(RGBImage *img){
    // Apply the mosaic filter to the RGB image
}

void Filter::apply_mosaic_filter(GrayImage *img){
    // Apply the mosaic filter to the gray image
}

