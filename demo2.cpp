// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image [SIZE][SIZE];

void loadImage ();
void saveImage ();
void Enlarge_filter();
void skew();
void shuffle();

int main()
{
  loadImage();
   //Enlarge_filter();
    //skew();
    shuffle();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

void Enlarge_filter()
{
    unsigned char New_image [SIZE][SIZE];

    int choice ;
    cout <<"Choose which quarter of the image you want to enlarge: ";
    cin >> choice ;

switch (choice)
 {
 case 1:
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            New_image[i][j] =  image[i/2][j/2];
    break;

 case 2:
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            New_image[i][j] =  image[i/2][j/2 + 128];
    break;

case 3:
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            New_image[i][j] =  image[i/2 + 128][j/2];
    break;


 case 4:
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            New_image[i][j] =  image[i/2 + 128 ][j/2 + 128];
    break;

 default:
    break;
 }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            image[i][j] = New_image[i][j];

}

void skew()
{
    unsigned char shrinkimage[SIZE][SIZE]  ;
    double rad ;
    cout << "choose the angle at which you want the image to be skewed: ";
    cin >> rad ;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    double mov = tan(rad) * 256 ;
    double step = mov / SIZE ; // عدد الخطوات
    unsigned char img_in[SIZE][SIZE+(int)mov]  ;

    int x = (265 / (1 + tan(rad)));

    for(int i=0;i<SIZE;i++)
        for(int j=0; j<SIZE;j++)
           shrinkimage[i][j] = 255;

    for(int i=0;i<SIZE;i++)
        for(int j=0; j<SIZE;j++)
            shrinkimage[ i ][ (j*x) / 256]=image[i][j];

    for ( int i = 0 ; i < SIZE ; i++ )
        for ( int j = 0 ; j < SIZE ; j++ )
            img_in[i][j] = 255 ;

    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_in[i][j+(int)mov] = shrinkimage[i][j] ;
        }
        mov -= step ;
    }


    for ( int i = 0 ; i < SIZE ; i++ )
        for ( int j = 0 ; j < SIZE; j++ )
            image[i][j] = img_in[i][j] ;
}


void shuffle() {

unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char image4[SIZE][SIZE];

    int quarters[4];
    cout << "enter the order of quarters: ";
    for (int i = 0; i < 4; i++)
        cin >> quarters[i];

    for (int i = 0; i < SIZE / 2; i++)
        for (int j = 0; j < SIZE / 2; j++)
            image1[i][j] = image[i][j];


    for (int i = 0; i < SIZE / 2; i++)
        for (int j = 128, y = 0; j < SIZE; y++, j++)
            image2[i][y] = image[i][j];

    for (int i = 128, x = 0; i < SIZE; x++, i++)
        for (int j = 0; j < SIZE / 2; j++)
            image3[x][j] = image[i][j];

    for (int i = 128, x = 0; i < SIZE; x++, i++)
        for (int j = 128, y = 0; j < SIZE; y++, j++)
            image4[x][y] = image[i][j];


    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {

            switch (quarters[0]) {
                case 1 :
                    image[i][j] = image1[i][j];
                    break;
                case 2:
                    image[i][j] = image2[i][j];
                    break;
                case 3:
                    image[i][j] = image3[i][j];
                    break;
                case 4:
                    image[i][j] = image4[i][j];
                    break;

            }
        }
    }
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 128, y = 0; j < SIZE; y++, j++) {

            switch (quarters[1]) {
                case 1 :
                    image[i][j] = image1[i][y];
                    break;
                case 2:
                    image[i][j] = image2[i][y];
                    break;
                case 3:
                    image[i][j] = image3[i][y];
                    break;
                case 4:
                    image[i][j] = image4[i][y];
                    break;

            }

        }
    }

    for (int i = 128, x = 0; i < SIZE; x++, i++) {
        for (int j = 0; j < SIZE / 2; j++) {

            switch (quarters[2]) {
                case 1 :
                    image[i][j] = image1[x][j];
                    break;
                case 2:
                    image[i][j] = image2[x][j];
                    break;
                case 3:
                    image[i][j] = image3[x][j];
                    break;
                case 4:
                    image[i][j] = image4[x][j];
                    break;

            }

        }

        for (int i = 128, x = 0; i < SIZE; x++, i++) {
            for (int j = 128, y = 0; j < SIZE; y++, j++) {

                switch (quarters[3]) {
                    case 1 :
                        image[i][j] = image1[x][y];
                        break;
                    case 2:
                        image[i][j] = image2[x][y];
                        break;
                    case 3:
                        image[i][j] = image3[x][y];
                        break;
                    case 4:
                        image[i][j] = image4[x][y];
                        break;

                }

            }
        }


    }

}
