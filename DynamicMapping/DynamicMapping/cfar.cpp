#include "cfar.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <opencv2/opencv.hpp>
#include <QTextStream>
#include <QtCore/QFile>

//#include <opencv/cv.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include  <opencv2/legacy/legacy.hpp>
#include <iomanip>
#include <vector>
#include <opencv2/features2d/features2d.hpp>
#include <iterator>

using namespace std;
using namespace cv;

struct_deger Cfar::run_cfar(cv::Mat img1)
{

    struct_deger c;

Mat imgArr3, imgArr4;

imgArr3 = img1.clone();
imgArr4 = img1.clone();

    double deger[480][6];

    int maxx;
    int maxy;
    int minx = 0;
    int miny = 0;
    int bs,by,bs1,by1;
    double slope1 = 0;
    double slope2 = 0;
    double ks,ksk;
    double offset = 10;
    double kat_sayi = 1.2;
    double kat_sayi2 = 0.02;
    double filter_lenght = 15;


    for(int i = 0; i < img1.rows; i++)
    {
        double sum =  0;// kullanıldı
        double sum1 = 0;// kullanıldı
        double sum2 = 0;// kullanıldı
        double sum3 = 0;
        double sum4 = 0;
        int count = 0;
        int count2 = 0;
        int start = 0;
        int start2 = 0;


        for(int j = 0; j< img1.cols; j++)
        {
            if(j == 0)
            {   double po = 0;
                double p;
                for( int k = 1; k <= filter_lenght; k++)
                {
                    p = img1.at<Vec3b>(i,k)[2];
                    po = po + p ;
                    sum = po;

                }
                sum = sum / filter_lenght;
                if(img1.at<Vec3b>(i,j)[2] > kat_sayi * sum + offset)
                {
                    imgArr3.at<Vec3b>(i,j) = {0,0,255};
                    if (i == 0 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs = i;
                        by = j;
                    }
                    count++;
                    if (count == 1)
                    {
                        start = j;
                    }
                    if(count+start-1 != j)
                    {
                        count= count-1;
                        if(count2==0)
                        {
                           start2 = j;
                        }
                        count2++;

                    }
                }
                else
                {
                    imgArr3.at<Vec3b>(i,j) = {0,0,0};
                }


                sum = ((sum* filter_lenght) +img1.at<Vec3b>(i,j)[2]) / (filter_lenght+1);

                if(img1.at<Vec3b>(i,j)[2] > (kat_sayi2+1) * sum)
                {
                   imgArr4.at<Vec3b>(i,j) = {0,0,255};
                }
                else if(img1.at<Vec3b>(i,j)[2] < (1-kat_sayi2) * sum)
                {
                    imgArr4.at<Vec3b>(i,j) = {0,0,0};
                }
                else
                {
                    imgArr4.at<Vec3b>(i,j) = {255,255,255};
                }
              }
             else if(j > 0 && j < filter_lenght)
             {
                double p1 = 0;
                double p2 = 0;
                 for(int kk = 0; kk < j; kk++)
                 {
                     double p1x = img1.at<Vec3b>(i,kk)[2];
                     p1 = p1+ p1x;



                 }
                 for(int kkk = j+1; kkk <= j+filter_lenght; kkk++)
                 {
                     double p2x = img1.at<Vec3b>(i,kkk)[2];
                     p2  = p2+ p2x;

                 }
                 sum1 = (p1+ p2)/((j-1)+filter_lenght);
                if(img1.at<Vec3b>(i,j)[2] > kat_sayi *sum1 + offset)
                {
                    imgArr3.at<Vec3b>(i,j) = { 0,0,255};
                    if (i == 0 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs = i;
                        by = j;
                    }
                    count++;
                    if (count == 1)
                    {
                        start = j;
                    }
                    if(count+start-1 != j)
                    {
                        count= count-1;
                        if(count2==0)
                        {
                           start2 = j;
                           imgArr3.at<Vec3b>(i,j) = {255,0,0};
                        }
                        count2++;

                    }

                }
                else
                {
                    imgArr3.at<Vec3b>(i,j) = {0,0,0};
                }
                sum1 = ((sum1* ((j-1)+filter_lenght)) +img1.at<Vec3b>(i,j)[2]) / ((j)+filter_lenght);

                if(img1.at<Vec3b>(i,j)[2] > (kat_sayi2+1) * sum1)
                {
                   imgArr4.at<Vec3b>(i,j) = {0,0,255};
                }
                else if(img1.at<Vec3b>(i,j)[2] < (1-kat_sayi2) * sum1)
                {
                    imgArr4.at<Vec3b>(i,j) = {0,0,0};
                }
                else
                {
                    imgArr4.at<Vec3b>(i,j) = {255,255,255};
                }
             }
             else if (j < 639 && j > (639-filter_lenght) )
            {
                double p3 = 0;
                double p4 = 0;
                 for(int k4 = j+1; k4 < img1.cols; k4++ )
                {
                     double p3x = img1.at<Vec3b>(i,k4)[2];

                     p3  = p3+ p3x;


                }
                for (int k5 = j-15; k5 < j; k5++)
                {
                     double p4x = img1.at<Vec3b>(i,k5)[2];

                     p4  = p4 + p4x;


                }
                sum2 = (p3+p4)/((639-j)+filter_lenght);
                if(img1.at<Vec3b>(i,j)[2] > kat_sayi *sum2+ offset)
                {
                    imgArr3.at<Vec3b>(i,j) = { 0,0,255};
                    if (i == 0 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs = i;
                        by = j;
                    }
                    count++;
                    if (count == 1)
                    {
                        start = j;
                    }
                    if(count+start-1 != j)
                    {
                        count= count-1;
                        if(count2==0)
                        {
                           start2 = j;
                           imgArr3.at<Vec3b>(i,j) = {255,0,0};
                        }
                        count2++;

                    }

                }
                else
                {
                    imgArr3.at<Vec3b>(i,j) = {0,0,0};
                }
                sum2 = ((sum2* ((639-j)+filter_lenght)) +img1.at<Vec3b>(i,j)[2]) / ((640-j)+filter_lenght);

                if(img1.at<Vec3b>(i,j)[2] > (kat_sayi2+1) * sum2)
                {
                   imgArr4.at<Vec3b>(i,j) = {0,0,255};
                }
                else if(img1.at<Vec3b>(i,j)[2] < (1-kat_sayi2) * sum2)
                {
                    imgArr4.at<Vec3b>(i,j) = {0,0,0};
                }
                else
                {
                    imgArr4.at<Vec3b>(i,j) = {255,255,255};
                }
            }
            else if (j == 639)
            {
                double p5 = 0;
                for(int k6 = 639-filter_lenght ; k6 < 639 ; k6++ )
                {
                    double p5x = img1.at<Vec3b>(i,k6)[2];
                    p5  = p5 + p5x;

                }
                sum3 = p5 / filter_lenght;
                if(img1.at<Vec3b>(i,j)[2] > kat_sayi * sum3 + offset)
                {
                    imgArr3.at<Vec3b>(i,j) = { 0,0,255};
                    if (i == 0 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs = i;
                        by = j;
                    }

                    count++;
                    if (count == 1)
                    {
                        start = j;
                    }
                    if(count+start-1 != j)
                    {
                        count= count-1;
                        if(count2==0)
                        {
                           start2 = j;
                           imgArr3.at<Vec3b>(i,j) = {255,0,0};
                        }
                        count2++;

                    }

                }
                else
                {
                    imgArr3.at<Vec3b>(i,j) = {0,0,0};
                }
                sum3 = ((sum3* filter_lenght) +img1.at<Vec3b>(i,j)[2]) / (filter_lenght+1);

                if(img1.at<Vec3b>(i,j)[2] > (kat_sayi2+1) * sum3)
                {
                   imgArr4.at<Vec3b>(i,j) = {0,0,255};
                }
                else if(img1.at<Vec3b>(i,j)[2] < (1-kat_sayi2) * sum3)
                {
                    imgArr4.at<Vec3b>(i,j) = {0,0,0};
                }
                else
                {
                    imgArr4.at<Vec3b>(i,j) = {255,255,255};
                }



            }
            else
            {
                double p6 = 0;
                double p7 = 0;
                for(int k7 = j-filter_lenght; k7 < j; k7++)
                {
                    double p6x= img1.at<Vec3b>(i,k7)[2];


                    p6  = p6 + p6x;
                }
                for(int k8 = j+1; k8 < j+filter_lenght+1 ; k8++)
                {
                    double p7x= img1.at<Vec3b>(i,k8)[2];

                    p7  = p7+ p7x;

                }
                sum4 = (p6+p7)/(2*filter_lenght);




                if(img1.at<Vec3b>(i,j)[2] > kat_sayi *sum4 + offset)
                {

                    imgArr3.at<Vec3b>(i,j) = { 0,0,255};
                    if (i == 0 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs = j;
                        by = i;
                    }
                    if (i == 479 && count == 0)
                    {
                        imgArr3.at<Vec3b>(i,j) = {0,255,0};
                        bs1 = j;
                        by1 = i;
                    }
                    count++;
                    if (count == 1)
                    {
                        start = j;
                    }
                    if(count+start-1 != j)
                    {
                        count= count-1;
                        if(count2==0)
                        {
                           start2 = j;
                           imgArr3.at<Vec3b>(i,j) = {255,0,0};
                        }
                        count2++;

                    }

                }
                else
                {
                    imgArr3.at<Vec3b>(i,j) ={0,0,0};
                }
                sum4 = ((sum4* (2*filter_lenght)) +img1.at<Vec3b>(i,j)[2]) / ((2*filter_lenght)+1);

                if(img1.at<Vec3b>(i,j)[2] > (kat_sayi2+1) * sum4)
                {
                   imgArr4.at<Vec3b>(i,j) = {0,0,255};
                }
                else if(img1.at<Vec3b>(i,j)[2] < (1-kat_sayi2) * sum4)
                {
                    imgArr4.at<Vec3b>(i,j) = {0,0,0};
                }
                else
                {
                    imgArr4.at<Vec3b>(i,j) = {255,255,255};
                }


            }


        }// CFAR column bitimi

        deger[i][0] = i;//y
        deger[i][1] = start;// x
        deger[i][2] = count;
        deger[i][3] = start2;
        deger[i][4] = count2;


        if ( i == 0)
        {
            deger[0][3] = 0;
        }
        else
        {
            deger[i][3] = deger[i][1]- deger[i-1][1];
        }


    } // Cfar row bitimi

    cout << deger[2][1]<< "---"<< endl;

    for(int i=0; i<480; i++)
    {
        for(int j=0; j<5; j++)
        {
            c.deger1[i][j] = deger[i][j];
        }
    }
    cout << c.deger1[2][1]<< "-mı--"<< endl;

     //imshow("Cfar laser", imgArr3);
     //imshow("Cfar laser2", imgArr4);

return c;

}
