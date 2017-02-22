//╔═╗┌─┐┬ ┬─┐ ┬┌┬┐┌─┐┌─┐┬ ┬┌─┐┌─┐
//╠╣ ├─┤│ │┌┴┬┘ │ │ │└─┐├─┤│ │├─┘
//╚  ┴ ┴└─┘┴ └─ ┴ └─┘└─┘┴ ┴└─┘┴


// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"

using namespace std;


static bool     openImageFromFilename(GBufferedImage &img, string filename);
static bool 	saveImageToFilename(const GBufferedImage &img, string filename);
static void     getMouseClickLocation(int &row, int &col);
void ImageBlurFilter(GBufferedImage &img, GWindow &gw, int &r, int &g, int &b);
void rgbSum(int &r , int &g , int &b , int hex);

int main(){
    int r = 0 , g = 0 , b = 0;
    GWindow gw;
    GBufferedImage img;
    gw.setTitle("Fauxtoshop");



    openImageFromFilename(img, "kitten.jpg");

    //gw.setSize(img.getWidth(), img.getHeight());
   // gw.add(&img,0,0);


    ImageBlurFilter(img , gw , r , g , b);

    return 0;
}


static bool openImageFromFilename(GBufferedImage &img, string filename) {

    if(filename.length() == 0) {
        cout << "Exit" << endl;
        return false;
    }

    try {
        img.load(filename);
    }
    catch (exception e) {
        cout << filename << " didn't found. Please provide a valid image name." << endl;

        cout << "Image file name: " ;

        string newImageName = getLine();

        openImageFromFilename(img , newImageName);

        return false;
    }
    return true;
}
static bool saveImageToFilename(const GBufferedImage &img, string filename) {
    try {
        img.save(filename);
    } catch (...) {
        return false;
    }
    return true;
}




void rgbSum(int &r , int &g , int &b , int hex){
    int red , green , blue;
    GBufferedImage::getRedGreenBlue(hex, red,green,blue);

    r += red;
    g += green;
    b += blue;
}




int avgRgb(int &r , int &g , int &b){
    int red = r/9;
    int green = g/9;
    int blue = g/9;


    return GBufferedImage::createRgbPixel(red,green,blue);
}


void ImageBlurFilter(GBufferedImage &img , GWindow &gw ,int &r ,int &g ,int &b){

    // convert image to grid
    Grid<int > imgGrid = img.toGrid();
    //GBufferedImage::getRedGreenBlue(pixel, r,g,b);

    int imgGridCols = imgGrid.numCols(); // num of total columns
    int imgGridRows = imgGrid.numRows();

    for(int row = 0 ; row < imgGridRows - 1 ; row++){
           for(int col = 0 ; col < imgGridCols - 1 ; col++){
               try{

                   for(int r = row-1 ; r <= row+1 ; r++){
                        for(int c = col-1 ; c <= col+1 ; c++){
                            int pixel = imgGrid[r][c];
                            rgbSum(pixel , r , g , b);
                        }
                   }
                   imgGrid[row][col] = avgRgb(r,g,b);
               }catch(exception e){

               }
           }
    }
    img.fromGrid(imgGrid); // grid to image

    gw.setSize(img.getWidth(), img.getHeight());

    gw.add(&img,0,0); // show image to window

}
