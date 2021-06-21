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


using namespace cv;
using namespace std;

Mat T = (Mat_<double>(3, 3) <<
    1, 0, 0,
    0, 1, 0,
    0, 0, 1);

int main(int argc, char *argv[])

{   struct_deger values;
    forester subaru;


    QCoreApplication a(argc, argv);
    QString filename="I4.txt";
    QString filename1="I5.txt";

    int count = 0;
    int Sizerow, Sizecol;
    IplImage *ipl;
    Mat *ptrref, *ptrreceived, matref, matreceived, matcombined,matcombined1, homography, newhomography, homographytemp;
    ptrref = &matref;
    ptrreceived = &matreceived;

    RobustMatcher rmatcher;
    rmatcher.setConfidenceLevel(0.98);
    rmatcher.setMinDistanceToEpipolar(1.0);
    rmatcher.setRatio(0.65f);
    cv::Ptr<cv::FeatureDetector> pfd= new cv::SurfFeatureDetector(10);
    rmatcher.setFeatureDetector(pfd);
    Mat z_values;
    Mat z_d = Mat::zeros(960,1280,CV_64F);




    max_min mm,mm1;

    CvCapture* capture = cvCreateCameraCapture(0);

    while(capture && count < 1000)
    {
         ipl = cvQueryFrame(capture);

         Mat frame = cvarrToMat(ipl);


         imshow("video frame",frame);

         char ch =  cvWaitKey(25);
         if(ch==27) break;



        if(count == 0 && ch=='s')
        {
            matref = frame.clone();

            values = Cfar::run_cfar(matref);

            z_d = Panaroma::z_degerleri(values,matref,z_d);

            count++;
        }



        else if(count == 1 && ch=='s')
        {
            matreceived = frame.clone();

            //imshow("matreceicdsasd",matreceived);
            //
            //imshow("Z2",z_degerleri);

            homographytemp = Panaroma::hmgImage(matref,matreceived,rmatcher);

            if(homographytemp.at<double>(0,0) == T.at<double>(0,0) && homographytemp.at<double>(1,1) == T.at<double>(1,1))
            {
                cout<< Panaroma::get_glhf() << "NOT ENOUGH INPUTS!" << endl;
            }

            else
            {

                mm = Panaroma::multiply(homographytemp,matreceived);

                newhomography = Panaroma::nhomog(mm,homographytemp);

                subaru = Panaroma::auto_size(matreceived, mm);
                cout<<subaru.row<<"  "<<subaru.colmn<<"  \_/"<<endl;
                warpPerspective(matreceived,matcombined,newhomography,Size(subaru.row,subaru.colmn));

                cout << "New Homography ->" << newhomography << endl;




                //warpPerspective(z_degerleri,z_toplam,newhomography,Size(Sizecol,Sizerow));
                //imshow("z_toplam",z_toplam);


                Mat abc;

                abc = Panaroma::trans(matref,mm);
                matref = abc.clone();
                abc = Panaroma::trans(z_d,mm);
                z_d = abc.clone();

                //imshow("z_values",z_d);
               // z_d = Panaroma::z_degerleri(values,matreceived,z_d);
                //imshow("z_values1",z_d);


                matcombined = Panaroma::copy(matref,matcombined);

                imshow("wrap", matcombined);
                imwrite( "matcombined.jpg", matcombined );
                values = Cfar::run_cfar(matreceived);
                z_values = Panaroma::z_degerleri(newhomography,values,matreceived,z_d);
                imshow("Panaroma",z_d);

                cout<<matcombined.cols<<"combined size"<<matcombined.rows;

                matref = matreceived;
                count++;
            }



        }


        else if(count != 0 && count != 1 && ch=='s')
        {
            matreceived = frame.clone();
            values = Cfar::run_cfar(matreceived);
            homographytemp = Panaroma::hmgImage(matref,matreceived,rmatcher);

            if(homographytemp.at<double>(0,0) == T.at<double>(0,0) && homographytemp.at<double>(1,1) == T.at<double>(1,1))
            {
                cout<< Panaroma::get_glhf() << "NOT ENOUGH INPUTS!" << endl;
            }
            else
            {
                cout<< Panaroma::get_glhf() <<"**********************************"<< endl;
                mm = Panaroma::multiply(homographytemp,matreceived);
                newhomography *= Panaroma::nhomog(mm,homographytemp );
                mm1 = Panaroma::multiply(newhomography,matreceived);

                subaru = Panaroma::auto_size(matcombined, mm);
                cout<<subaru.row<<"  "<<subaru.colmn<<"  \_/"<<endl;

                cout<<matcombined.cols<<"combined size"<<matcombined.rows;

                warpPerspective(matreceived,matcombined1,newhomography,Size(subaru.row, subaru.colmn));
                matcombined1 = Panaroma::trans(matcombined1,mm1);

                matcombined = Panaroma::trans(matcombined,mm);

                z_d = Panaroma::trans(z_d,mm);


                //imshow("trans2",matcombined);
                matcombined = Panaroma::copy(matcombined,matcombined1);
                imshow("wrap", matcombined);
                z_values = Panaroma::z_degerleri(newhomography,values,matreceived,z_d);
                imshow("Panaroma",z_d);
                matref = matreceived;
                //imshow("4", matref);
                count++;
            }



        }



    }








    return a.exec();
}
