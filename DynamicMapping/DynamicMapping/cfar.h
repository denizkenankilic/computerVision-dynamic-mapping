#ifndef CFAR_H
#define CFAR_H

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
#include <opencv2/legacy/legacy.hpp>
#include <iomanip>
#include <vector>
#include <opencv2/features2d/features2d.hpp>
#include <iterator>

struct struct_deger
{
    double deger1[480][6];
};

class Cfar
{
public:
      static struct_deger run_cfar(cv::Mat);
};

#endif // CFAR_H
