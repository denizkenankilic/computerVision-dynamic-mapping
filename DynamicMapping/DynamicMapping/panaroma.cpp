
#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"

#include "vector"

#include "matcher.h"
#include "panaroma.h"
#include "cfar.h"

using namespace std;
using namespace cv;

static int glhf;



forester Panaroma::auto_size(Mat combined, max_min mm)
{
    forester subaru;

    cout<<"girdi"<<endl;
    if(mm.min_x < 0 && mm.min_y < 0 && mm.max_x < combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = abs(mm.min_y) + combined.rows;
        subaru.colmn = abs(mm.min_x) + combined.cols;
    }


    else if(mm.min_x >= 0 && mm.min_y < 0 && mm.max_x < combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = abs(mm.min_y) + combined.rows;
        subaru.colmn = combined.cols;
    }

    else if(mm.min_x < 0 && mm.min_y >= 0 && mm.max_x < combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = combined.rows;
        subaru.colmn = abs(mm.min_x) + combined.cols;
    }

    else if(mm.min_x >= 0 && mm.min_y >= 0 && mm.max_x < combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = combined.rows;
        subaru.colmn = combined.cols;
    }

    else if(mm.min_x < 0 && mm.min_y < 0 && mm.max_x >= combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = abs(mm.min_y) + combined.rows;
        subaru.colmn = abs(mm.min_x) + mm.max_x;
    }

    else if(mm.min_x >= 0 && mm.min_y < 0 && mm.max_x >= combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = abs(mm.min_y) + combined.rows;
        subaru.colmn = mm.max_x;
    }

    else if(mm.min_x < 0 && mm.min_y >= 0 && mm.max_x >= combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = combined.rows;
        subaru.colmn = abs(mm.min_x) + mm.max_x;
    }

    else if(mm.min_x >= 0 && mm.min_y >= 0 && mm.max_x >= combined.cols && mm. max_y < combined.rows)
    {
        subaru.row = combined.rows;
        subaru.colmn = mm.max_x;
    }

    else if(mm.min_x < 0 && mm.min_y < 0 && mm.max_x < combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = abs(mm.min_y) + mm.max_y;
        subaru.colmn = abs(mm.min_x) + combined.cols;
    }

    else if(mm.min_x >= 0 && mm.min_y < 0 && mm.max_x < combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = abs(mm.min_y) + mm.max_y;
        subaru.colmn = combined.cols;
    }

    else if(mm.min_x < 0 && mm.min_y >= 0 && mm.max_x < combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = mm.max_y;
        subaru.colmn = abs(mm.min_x) + combined.cols;
    }

    else if(mm.min_x >= 0 && mm.min_y >= 0 && mm.max_x < combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = mm.max_y;
        subaru.colmn = combined.cols;
    }

    else if(mm.min_x < 0 && mm.min_y < 0 && mm.max_x >= combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = abs(mm.min_y) + mm.max_y;
        subaru.colmn = abs(mm.min_x) + mm.max_x;
    }

    else if(mm.min_x >= 0 && mm.min_y < 0 && mm.max_x >= combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = abs(mm.min_y) + mm.max_y;
        subaru.colmn = mm.max_x;
    }

    else if(mm.min_x < 0 && mm.min_y >= 0 && mm.max_x >= combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = mm.max_y;
        subaru.colmn = abs(mm.min_x) + mm.max_x;
    }

    else if(mm.min_x >= 0 && mm.min_y >= 0 && mm.max_x >= combined.cols && mm. max_y >= combined.rows)
    {
        subaru.row = mm.max_y;
        subaru.colmn = mm.max_x;
    }

    cout<<"çıktı"<<endl;
    cout<<subaru.row<<"    row&column   "<<subaru.colmn<<endl;
    return subaru;

}

Mat Panaroma::z_degerleri(Mat H, struct_deger variables, Mat image,Mat z_d)
{

    // Homography matrix ile laser noktalarının çarpımından elde ediliyor
    Mat index; Mat hafiza;
    int a = 0.1;
    int b = 0.2;
    int c = 8;
    int z;

    for(int i= 0; i < image.rows; i++)
    {


            double x;
            double y;

            //float z;
            index = (Mat_<double>(3, 1) <<
                variables.deger1[i][1],
                variables.deger1[i][0],
                1);// z buraya gelecek




             hafiza = H*index;

             if(hafiza.at<double>(2,0) < 1)
             {
                 hafiza.at<double>(2,0) = 1;
             }
             else
             {
                 hafiza.at<double>(2,0)= hafiza.at<double>(2,0);
             }

             x =  hafiza.at<double>(0,0)/hafiza.at<double>(2,0);
             y =  hafiza.at<double>(1,0)/hafiza.at<double>(2,0);
             //z =  c.deger1[i][5];

              z_d.at<double>(y,x) = 150; //(a*i)+(b*variables.deger1[i][1])+c;

    }
    return z_d;
}

Mat Panaroma::z_degerleri( struct_deger variables, Mat image,Mat z_d)
{


    //Mat index;

    float a = 0.1;
    float b = 0.2;
    float c = 8;
    for(int i= 0; i < image.rows; i++)
    {
            float x;
            float y;

            x =  variables.deger1[i][1];
            y =  variables.deger1[i][0];
            z_d.at<double>(y,x) = 150;//(a*i)+(b*variables.deger1[i][1])+c;

    }

        return z_d;
}




Mat Panaroma::copy(Mat src, Mat dst)
{

    for (int i = 0; i < src.rows ; i++)
    {
        for(int j = 0 ; j < src.cols; j++)
        {
            if (src.at<Vec3b>(i,j)[0] != 0 &&
                    src.at<Vec3b>(i,j)[1] != 0 &&
                    src.at<Vec3b>(i,j)[2] != 0 &&
                    dst.at<Vec3b>(i,j)[0] == 0 &&
                    dst.at<Vec3b>(i,j)[1] == 0 &&
                    dst.at<Vec3b>(i,j)[2] == 0)
            {
                dst.at<Vec3b>(i,j) = src.at<Vec3b>(i,j);
            }

          else if(src.at<Vec3b>(i,j)[0] != 0 &&
                    src.at<Vec3b>(i,j)[1] != 0 &&
                    src.at<Vec3b>(i,j)[2] != 0 &&
                    dst.at<Vec3b>(i,j)[0] != 0 &&
                    dst.at<Vec3b>(i,j)[1] != 0 &&
                    dst.at<Vec3b>(i,j)[2] != 0)
            {
               dst.at<Vec3b>(i,j)[0] = dst.at<Vec3b>(i,j)[0] / 2 + src.at<Vec3b>(i,j)[0] / 2;
               dst.at<Vec3b>(i,j)[1] = dst.at<Vec3b>(i,j)[1] / 2 + src.at<Vec3b>(i,j)[1] / 2;
               dst.at<Vec3b>(i,j)[2] = dst.at<Vec3b>(i,j)[2] / 2 + src.at<Vec3b>(i,j)[2] / 2;
            }
        }
    }

    return dst;



}

Mat Panaroma::hmgImage(Mat img1, Mat img2, RobustMatcher rmatcher)
{
    std::vector<cv::DMatch> matches;
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat fundemental= rmatcher.match(img1,img2,matches, keypoints1, keypoints2);

    glhf = rmatcher.lazim();

    // draw the matches
    cv::Mat imageMatches;
    cv::drawMatches(img1,keypoints1,  // 1st image and its keypoints
                        img2,keypoints2,  // 2nd image and its keypoints
                                    matches,                        // the matches
                                    imageMatches,           // the image produced
                                    cv::Scalar(255,255,255)); // color of the lines
   // cv::namedWindow("Matches");
    //cv::imshow("Matches",imageMatches);

    std::vector<cv::Point2f> points1, points2;
    for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
             it!= matches.end(); ++it) {

                     // Get the position of left keypoints
                     float x= keypoints1[it->queryIdx].pt.x;
                     float y= keypoints1[it->queryIdx].pt.y;
                     points1.push_back(cv::Point2f(x,y));
                     // Get the position of right keypoints
                     x= keypoints2[it->trainIdx].pt.x;
                     y= keypoints2[it->trainIdx].pt.y;
                     points2.push_back(cv::Point2f(x,y));



    }

    cv::Mat hmgrphy;
    if(points2.size() > 30 && points1.size() > 30)
    {

    std::vector<uchar> inliers(points1.size(),0);
     hmgrphy= cv::findHomography(
            cv::Mat(points2),cv::Mat(points1), // corresponding points
            inliers,        // outputed inliers matches
            CV_RANSAC,      // RANSAC method
            5.);        // max distance to reprojection point
    }
    else
    {
        cv::Mat T = (cv::Mat_<double>(3, 3) <<
            1, 0, 0,
            0, 1, 0,
            0, 0, 1);
        std::cout<<"birim matris"<<std::endl;

        hmgrphy = T;
    }


    return hmgrphy;


}

int Panaroma::get_glhf()
{
    return glhf;
}

max_min Panaroma::multiply(Mat H, Mat img)
{

    double a [2] = {0,img.cols};
    double b [2] = {0,img.rows};


    double max_y= 0;
    double max_x= 0;
    double min_y= 0;
    double min_x= 0;
    Mat index;
    Mat c;
    for(int i= 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            float x;
            float y;
            //float z;
            index = (Mat_<double>(3, 1) <<
                a[i],
                b[j],
                1);

             c = H*index;



             if(c.at<double>(2,0) < 1)
             {
                 x = c.at<double>(0,0);
             }
             else
             {
                 x =  c.at<double>(0,0)/c.at<double>(2,0);
             }


              if( x < min_x)
              {
                  min_x = x;
              }
              else
              {
                  min_x= min_x;
              }
              if( x > max_x)
              {
                  max_x = x;
              }
              else
              {
                  max_x= max_x;
              }

              if(c.at<double>(2,0) < 1)
              {
                  y = c.at<double>(1,0);
              }
              else
              {
                  y =  c.at<double>(1,0)/c.at<double>(2,0);
              }

              if( y < min_y)
              {
                  min_y = y;
              }
              else
              {
                  min_y= min_y;
              }
              if( y > max_y)
              {
                  max_y = y;
              }
              else
              {
                  max_y= max_y;
              }
              //z = c.at<double>(2,0);



            //yeni.at<Vec3b>(i,j)[2]   = z;
        }
    }

           max_min ccc;


           Point minLoc;
           Point maxLoc;

          //minMaxLoc(yeni_x,  &minVal, &maxVal, &minLoc, &maxLoc );
/* cout << "yeni_x "<<yeni_x.at<float>(0,0) << endl;
        cout << "yeni_y "<<yeni_y.at<float>(0,0) << endl;
        cout << "max-x val: " << maxVal << endl;
        cout << "min-x val: " << minVal << endl;*/

        ccc.max_x = max_x;
        ccc.min_x = min_x;
       // minMaxLoc(yeni_y,  &minVal, &maxVal, &minLoc, &maxLoc );
        //cout << "max-y val: " << maxVal << endl;
        cout << "min-x val: " << min_x << endl;
        ccc.max_y = max_y;
        ccc.min_y = min_y;

        return ccc;


}

Mat Panaroma::nhomog(max_min values, Mat Hmgrphy)
{

    double x_ofset;
    if(values.min_x < 0)
    {
        x_ofset = abs(values.min_x);
    }
    else
    {
        x_ofset = 0;
    }

    double y_ofset;

    if(values.min_y < 0)
    {
        y_ofset = abs(values.min_y);
    }
    else
    {
        y_ofset = 0;
    }
    Mat T = (Mat_<double>(3, 3) <<
        0, 0, x_ofset,
        0, 0, y_ofset,
        0, 0, 0);

    cout << values.min_y <<"->"<< y_ofset << endl;
    cout << values.min_x <<"->"<< x_ofset << endl;

    Mat H = Hmgrphy+T;



    return H;



}



Mat Panaroma::trans(Mat src, max_min H1)
{

    float x_ofset = 0;
    if(H1.min_x < 0)
    {
        x_ofset = abs(H1.min_x);

    }



    float y_ofset = 0;

    if(H1.min_y< 0)
    {
        y_ofset =(abs(H1.min_y));

    }


    Mat dst;
    Mat T = (Mat_<double>(3, 3) <<
        1, 0, x_ofset,
        0, 1, y_ofset,
        0, 0, 1);


    warpPerspective(src,
                    dst,
                    T,
                    Size(x_ofset+src.cols,y_ofset+src.rows ));



    return dst;


}
