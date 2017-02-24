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


static bool openImageFromFilename(GBufferedImage &img, string filename);
static bool saveImageToFilename(const GBufferedImage &img, string filename);
static void getMouseClickLocation(int &row, int &col);
       void ImageBlurFilter(GBufferedImage &img, GWindow &gw);
       void ImageRedNoiseFilter(GBufferedImage &img , GWindow &gw);
       bool selectFilter(GBufferedImage &img , GWindow &gw);



int main(){
    GWindow gw;
    GBufferedImage img;
    gw.setTitle("Fauxtoshop");

    openImageFromFilename(img, "no_image.gif");
    gw.setSize(img.getWidth() , img.getHeight());
    gw.add(&img,0,0);

    cout << "Wellcome to FAUXTOSHOP" << endl;

    cout << "Enter the name of the image file to open (or blank to quit): ";
    string fileName = getLine();

    openImageFromFilename(img, fileName);


    gw.setSize(img.getWidth(),img.getHeight());
    gw.add(&img,0,0);



    cout << "which image filter would you like to apply?" << endl;
    cout << "\t\t 1 - Blur" << endl;


    cout << "Your choice: ";
    bool done = selectFilter(img,gw);

    if(done){
        cout << "\n\n\n Done processing :) " << endl;
    }
    cout << "Enter filename to save (or blank to skip saving): ";

    string newFileName = getLine();

    bool saved = saveImageToFilename(img,newFileName);

    if(saved)   cout << "Successfully saved your image as " << newFileName << endl;

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
    } catch (exception e) {
        return false;
    }
    return true;
}



void ImageBlurFilter(GBufferedImage &img , GWindow &gw){


    Grid<int> imgGrid = img.toGrid();


    int imgGridCols = imgGrid.numCols();
    int imgGridRows = imgGrid.numRows();


    for(int row = 0 ; row < imgGridRows - 1 ; row++){
        for(int col = 0 ; col < imgGridCols - 1 ; col++){
            try{

                // Upper Portion
                int UpLeftCell  = imgGrid[row+1][col-1];
                int UptMiddleCell  = imgGrid[row+1][col];
                int UpRightCell = imgGrid[row+1][col+1];

                // Middle Portion
                int leftCell    = imgGrid[row][col-1];
                int currentCell = imgGrid[row][col];
                int rightCell   = imgGrid[row][col+1];


                // Down Portion
                int DowntLeftCell   =  imgGrid[row-1][col-1];
                int DowntMiddleCell =  imgGrid[row-1][col];
                int DowntRightCell  =  imgGrid[row-1][col+1];


                int red1, red2,red3,red4,red5,red6,red7,red8, red9, // all red
                    green1,green2,green3,green4,green5,green6,green7,green8,green9, // all green
                    blue1, blue2, blue3,blue4,blue5,blue6,blue7,blue8,blue9; // all blue


                GBufferedImage::getRedGreenBlue(UpLeftCell, red1, green1, blue1);
                GBufferedImage::getRedGreenBlue(UptMiddleCell, red2, green2, blue2);
                GBufferedImage::getRedGreenBlue(UpRightCell, red3, green3, blue3);
                GBufferedImage::getRedGreenBlue(leftCell, red4, green4, blue4);
                GBufferedImage::getRedGreenBlue(currentCell, red5, green5, blue5);
                GBufferedImage::getRedGreenBlue(rightCell, red6, green6, blue6);
                GBufferedImage::getRedGreenBlue(DowntLeftCell, red7, green7, blue7);
                GBufferedImage::getRedGreenBlue(DowntMiddleCell, red8, green8, blue8);
                GBufferedImage::getRedGreenBlue(DowntRightCell, red9, green9, blue9);

                int red   = (red1+red2+red3+red4+red5+red6+red7+red8+red9)/9;
                int green = (green1+green2+green3+green4+green5+green6+green7+green8+green9)/9;
                int blue  = (blue1+blue2+blue3+blue4+blue5+blue6+blue7+blue8+blue9)/9;

                int newHex = GBufferedImage::createRgbPixel(red,green,blue);

                imgGrid[row][col] = newHex;


            }catch(exception e){

            }
        }
    }



    img.fromGrid(imgGrid); // grid to image

    gw.setSize(img.getWidth(), img.getHeight());

    gw.add(&img,0,0); // show image to window
}


bool selectFilter(GBufferedImage &img , GWindow &gw){
    while(true){
        int choseFilter = getInteger();
        if(choseFilter == 1){
            ImageBlurFilter(img , gw);
            return true;
        }else{
            cout << "Invalid selection. try again" << endl;
            cout << "Your choice: ";
            continue;
        }
    }
    return false;
}
