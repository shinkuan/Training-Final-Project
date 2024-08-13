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
    int width = img->get_width();
    int height = img->get_height();

    // Find min and max pixel values for each channel
    int min_r = 255, max_r = 0;
    int min_g = 255, max_g = 0;
    int min_b = 255, max_b = 0;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int *pixel = img->get_pixel(x, y);
            min_r = std::min(min_r, pixel[0]);
            max_r = std::max(max_r, pixel[0]);
            min_g = std::min(min_g, pixel[1]);
            max_g = std::max(max_g, pixel[1]);
            min_b = std::min(min_b, pixel[2]);
            max_b = std::max(max_b, pixel[2]);
        }
    }

    // Apply contrast stretching
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int *pixel = img->get_pixel(x, y);

            pixel[0] = (pixel[0] - min_r) * 255 / (max_r - min_r);
            pixel[1] = (pixel[1] - min_g) * 255 / (max_g - min_g);
            pixel[2] = (pixel[2] - min_b) * 255 / (max_b - min_b);

            img->set_pixel(x, y, pixel[0], pixel[1], pixel[2]);
        }
    }
}

void Filter::apply_contrast_stretching_filter(GrayImage *img){
    // Apply the contrast stretching filter to the gray image
    int width = img->get_width();
    int height = img->get_height();

    // Find min and max pixel values
    int min_val = 255, max_val = 0;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int pixel = img->get_pixel(x, y);
            min_val = std::min(min_val, pixel);
            max_val = std::max(max_val, pixel);
        }
    }

    // Apply contrast stretching
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int pixel = img->get_pixel(x, y);
            int stretched_pixel = (pixel - min_val) * 255 / (max_val - min_val);
            img->set_pixel(x, y, stretched_pixel);
        }
    }
}

void Filter::apply_mosaic_filter(RGBImage *img){
    // Apply the mosaic filter to the RGB image
    int width = img->get_width();
    int height = img->get_height();
    int block_size = 6;  // define the size of mosaic

    for(int y = 0; y < height; y += block_size) {
        for(int x = 0; x < width; x += block_size) {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int pixel_count = 0;

            // calculate the sum of pixel
            for(int ky = 0; ky < block_size; ky++) {
                for(int kx = 0; kx < block_size; kx++) {
                    if(y + ky < height && x + kx < width) {
                        int *pixel = img->get_pixel(x + kx, y + ky);
                        red_sum += pixel[0];
                        green_sum += pixel[1];
                        blue_sum += pixel[2];
                        pixel_count++;
                    }
                }
            }

            // calculate the average
            int red_avg = red_sum / pixel_count;
            int green_avg = green_sum / pixel_count;
            int blue_avg = blue_sum / pixel_count;

            // apply to the pixel
            for(int ky = 0; ky < block_size; ky++) {
                for(int kx = 0; kx < block_size; kx++) {
                    if(y + ky < height && x + kx < width) {
                        img->set_pixel(x + kx, y + ky, red_avg, green_avg, blue_avg);
                    }
                }
            }
        }
    }
}

void Filter::apply_mosaic_filter(GrayImage *img){
    // Apply the mosaic filter to the gray image
    int width = img->get_width();
    int height = img->get_height();
    int block_size = 6;  

    for(int y = 0; y < height; y += block_size) {
        for(int x = 0; x < width; x += block_size) {
            int pixel_sum = 0;
            int pixel_count = 0;

            for(int ky = 0; ky < block_size; ky++) {
                for(int kx = 0; kx < block_size; kx++) {
                    if(y + ky < height && x + kx < width) {
                        pixel_sum += img->get_pixel(x + kx, y + ky);
                        pixel_count++;
                    }
                }
            }

            int pixel_avg = pixel_sum / pixel_count;

            for(int ky = 0; ky < block_size; ky++) {
                for(int kx = 0; kx < block_size; kx++) {
                    if(y + ky < height && x + kx < width) {
                        img->set_pixel(x + kx, y + ky, pixel_avg);
                    }
                }
            }
        }
    }
}

