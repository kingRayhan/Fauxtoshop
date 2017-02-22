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

//static const int    WHITE = 0xFFFFFF;
//static const int    BLACK = 0x000000;
//static const int    GREEN = 0x00FF00;

static bool     openImageFromFilename(GBufferedImage &img, string filename);
static bool 	saveImageToFilename(const GBufferedImage &img, string filename);
static void     getMouseClickLocation(int &row, int &col);
void ImageBlurFilter(GBufferedImage &img, GWindow gw);
void chosenImageFilter(GBufferedImage &img , GWindow gw);


int main(){
    GWindow gw;
    GBufferedImage img;
    gw.setTitle("Fauxtoshop");




    cout << "Enter the namer of the image file to open (or blank to quit) : ";
    string imageName = getLine(); // ask image file name from user

    openImageFromFilename(img, imageName);

    gw.setSize(img.getWidth(), img.getHeight());
//    gw.add(&img,0,0);




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





void ImageBlurFilter(GBufferedImage &img , GWindow gw){


    Grid<int> imgGrid = img.toGrid();


    int imgGridCols = imgGrid.numCols();
    int imgGridRows = imgGrid.numRows();


    for(int row = 0 ; row < imgGridRows - 1 ; row++){
        for(int col = 0 ; col < imgGridCols - 1 ; col++){
            try{


                // Upper Portion
                int UpLeftCell  = imgGrid[row+1][col-1];
                int UptMiffleCell  = imgGrid[row+1][col];
                int UpRightCell = imgGrid[row+1][col+1];

                // Middle Portion
                int leftCell    = imgGrid[row][col-1];
                int currentCell = imgGrid[row][col];
                int rightCell   = imgGrid[row][col+1];


                // Down Portion
                int DowntLeftCell   =  imgGrid[row-1][col-1];
                int DowntMiddleCell =  imgGrid[row-1][col];
                int DowntRightCell  =  imgGrid[row-1][col+1];

                int sumCel;
                int
                        red1,
                        red2,
                        red3,
                        red4,
                        red5,
                        red6,
                        red7,
                        red8,
                        red9,

                        green1,
                        green2,
                        green3,
                        green4,
                        green5,
                        green6,
                        green7,
                        green8,
                        green9,

                        blue1,
                        blue2,
                        blue3,
                        blue4,
                        blue5,
                        blue6,
                        blue7,
                        blue8,
                        blue9;

                GBufferedImage::getRedGreenBlue(UpLeftCell, red1, green1, blue1);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red2, green2, blue2);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red3, green3, blue3);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red4, green4, blue4);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red5, green5, blue5);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red6, green6, blue6);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red7, green7, blue7);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red8, green8, blue8);
                GBufferedImage::getRedGreenBlue(UpLeftCell, red9, green9, blue9);


                int red, green, blue;

                red =
                        red1
                        +red2
                        +red3
                        +red4
                        +red5
                        +red6
                        +red7
                        +red8
                        +red9;
                red = red/9;

                green =
                        green1
                        +green2
                        +green3
                        +green4
                        +green5
                        +green6
                        +green7
                        +green8
                        +green9;
                green = green/9;

                blue =
                       blue1
                        +blue2
                        +blue3
                        +blue4
                        +blue5
                        +blue6
                        +blue7
                        +blue8
                        +blue9;
                blue = blue/9;

                string Hex = ""+red+green+blue;
                int newHex = stringToInteger(Hex);


//                sumCel =
//                          UpLeftCell
//                        * UptMiffleCell
//                        * UpRightCell
//                        * leftCell
//                        * currentCell
//                        * DowntLeftCell
//                        * rightCell
//                        * DowntMiddleCell
//                        * DowntRightCell  ;
//                int sumCellAvg = sumCel/9;


cout << red;
            }catch(exception e){

            }
        }
    }



    img.fromGrid(imgGrid); // grid to image

    gw.setSize(img.getWidth(), img.getHeight());

    gw.add(&img,0,0); // show image to window
}
void chosenImageFilter(GBufferedImage &img , GWindow gw){
//    cout << "Which image filter would you like to apply?" << endl;
//    cout << "\t\t\t\t\t 1 - BLUR" << endl;
//    cout << "Your choice: ";

    //int choseFilter = getInteger();


   //ImageBlurFilter(img,gw);
//    if(choseFilter == 1){
//        ImageBlurFilter(img,gw);
//    }else{
//        int choseFilter = getInteger();
//        chosenImageFilter(img,gw);
//    }


}
