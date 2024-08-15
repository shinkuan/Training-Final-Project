#include "photo_mosaic.h"

PhotoMosaic::PhotoMosaic(){
    target = nullptr;
    tiles.clear();
}

PhotoMosaic::PhotoMosaic(string target_filename, string tile_folder){
    target = nullptr;
    tiles.clear();
    set_target(target_filename);
    set_tiles(tile_folder);
}

PhotoMosaic::~PhotoMosaic(){
    if(target != nullptr){
        delete target;
    }
    for(int i = 0; i < tiles.size(); i++){
        delete tiles[i].img;
    }
}

void PhotoMosaic::set_target(string target_filename){
    if(target != nullptr){
        delete target;
    }
    target = new RGBImage();
    target->load_image(target_filename);
}

void PhotoMosaic::set_tiles(string tile_folder){
    tiles.clear();
    vector<string> filenames;
    Data_Loader::List_Directory(tile_folder, filenames);
    for(int i = 0; i < filenames.size(); i++){
        Tile t;
        t.img = new RGBImage();
        t.img->load_image(filenames[i]);
        int *avg = t.img->get_average_pixel();
        t.avg_r = avg[0];
        t.avg_g = avg[1];
        t.avg_b = avg[2];
        delete []avg;
        tiles.push_back(t);
    }
}

RGBImage *PhotoMosaic::create_mosaic(int mosaic_w, int mosaic_h){
    if(target == nullptr || tiles.size() == 0){
        return nullptr;
    }
    RGBImage *resized = target->create_resized(mosaic_w, mosaic_h);
    if(resized == nullptr){
        return nullptr;
    }
    int ***pixels = new int**[TILE_HEIGHT*mosaic_h];
    for(int i = 0; i < TILE_HEIGHT*mosaic_h; ++i) {
        pixels[i] = new int*[TILE_WIDTH*mosaic_w];
        for(int j = 0; j < TILE_WIDTH*mosaic_w; ++j) {
            pixels[i][j] = new int[3];
        }
    }
    // TODO: Parallelize this loop
    for(int i = 0; i < mosaic_h; i++){
        for(int j = 0; j < mosaic_w; j++){
            int *color = resized->get_pixel(j, i);
            Tile *t = find_closest_tile(
                color[0], color[1], color[2], tiles
            );
            for(int y = 0; y < TILE_HEIGHT; y++){
                for(int x = 0; x < TILE_WIDTH; x++){
                    int *tile_pixel = t->img->get_pixel(x, y);
                    pixels[i*TILE_HEIGHT + y][j*TILE_WIDTH + x][0] = 
                        tile_pixel[0];
                    pixels[i*TILE_HEIGHT + y][j*TILE_WIDTH + x][1] =
                        tile_pixel[1];
                    pixels[i*TILE_HEIGHT + y][j*TILE_WIDTH + x][2] =
                        tile_pixel[2];
                    delete []tile_pixel;
                }
            }
            delete []color;
        }
    }
    delete resized;

    RGBImage *mosaic = new RGBImage(TILE_WIDTH*mosaic_w, TILE_HEIGHT*mosaic_h, pixels);
    return mosaic;
}

double color_distance(int r1, int g1, int b1, int r2, int g2, int b2){
    int dr = r1 - r2;
    int dg = g1 - g2;
    int db = b1 - b2;
    return dr*dr + dg*dg + db*db;
}

Tile *find_closest_tile(int r, int g, int b, vector<Tile> &tiles){
    double min_dist = color_distance(r, g, b, tiles[0].avg_r, tiles[0].avg_g, tiles[0].avg_b);
    Tile *closest = &tiles[0];
    for(int i = 1; i < tiles.size(); i++){
        double dist = color_distance(r, g, b, tiles[i].avg_r, tiles[i].avg_g, tiles[i].avg_b);
        if(dist < min_dist){
            min_dist = dist;
            closest = &tiles[i];
        }
    }
    return closest;
}