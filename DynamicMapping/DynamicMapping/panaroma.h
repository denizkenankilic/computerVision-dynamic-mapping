#ifndef PANAROMA_H
#define PANAROMA_H

#endif // PANAROMA_H

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
#include "cfar.h"

using namespace std;
using namespace cv;

struct max_min{
    double max_x,max_y,min_x,min_y,clear_matches;
};

struct forester{
    int row, colmn;
};


class Panaroma
{

public:

    static Mat z_degerleri( struct_deger variables, Mat image,Mat z_d);
    static Mat z_degerleri(Mat,struct_deger,Mat,Mat);
    static max_min multiply(Mat,Mat);
    static Mat copy(Mat src, Mat dst);
    static Mat nhomog (max_min,Mat);
    static Mat trans(Mat,max_min);
    static Mat hmgImage(Mat,Mat,RobustMatcher);
    static int get_glhf();
    static forester auto_size(Mat, max_min);


};
