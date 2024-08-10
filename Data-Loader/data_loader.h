#ifndef _DATA_LOADER_H_
#define _DATA_LOADER_H_

#define cimg_use_jpeg
#define cimg_use_png
//#include "CImg.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <fstream>

// for luminance formula: Y = 0.2126R + 0.7152G + 0.0722B
#define R_FACTOR 0.2126
#define G_FACTOR 0.7152
#define B_FACTOR 0.0722

using namespace std;
using namespace cimg_library;

class Data_Loader{

public:
    Data_Loader();
    ~Data_Loader();
    int **Load_Gray(string filename, int *w, int *h);   //用指標將圖傳進來並讀入長寬，灰階圖片是二維陣列
    int ***Load_RGB(string filename, int *w, int *h);   //彩色圖片是三維陣列
    void Dump_Gray(int w, int h, int **pixels, string filename);    //輸出成jpg或png
    void Dump_RGB(int w, int h, int ***pixels, string filename);
    void Display_Gray_X_Server(int w, int h, int **pixels);     //串接X-Server來顯示圖片
    void Display_RGB_X_Server(int w, int h, int ***pixels);
    void Display_Gray_ASCII(int w, int h, int **pixels);
    void Display_RGB_ASCII(int w, int h, int ***pixels);
    void Display_Gray_CMD(string filename);
    void Display_RGB_CMD(string filename);
    static bool List_Directory(string directoryPath, vector<string> &filenames);    //小圖的檔名

private:
    bool File_Exists(const string &filename);
};

#endif