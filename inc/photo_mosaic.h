#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include <future>
#include <vector>
#include <chrono>
#include <map>
#include "image.h"
#include "rgb_image.h"
#include "gray_image.h"
#include "filter.h"

// Todo: Dynamic tile width and height
#define TILE_WIDTH  32
#define TILE_HEIGHT 32

using namespace std;

struct Tile{
    int avg_r;
    int avg_g;
    int avg_b;
    RGBImage *img;
};

class PhotoMosaic{
public:
    PhotoMosaic();
    PhotoMosaic(string target_filename, string tile_folder);
    ~PhotoMosaic();
    void set_target(string target_filename);
    void set_tiles(string tile_folder);
    RGBImage *create_mosaic(int tile_width, int tile_height);

private:
    RGBImage *target;
    std::vector<Tile> tiles;

};

double color_distance(int r1, int g1, int b1, int r2, int g2, int b2);
Tile *find_closest_tile(int r, int g, int b, vector<Tile> &tiles);

#endif