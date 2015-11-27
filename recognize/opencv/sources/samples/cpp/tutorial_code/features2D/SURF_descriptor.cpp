/**
 * @file SURF_descriptor
 * @brief SURF detector + descritpor + BruteForce Matcher + drawing matches with OpenCV functions
 * @author A. Huaman
 */

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

void readme();

/**
 * @function main
 * @brief Main function
 */
int main( int argc, char** argv )
{
  if( argc != 3 )
  { return -1; }

  Mat img_1 = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_2 = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );

  if( !img_1.data || !img_2.data )
  { return -1; }
  //显示两个图片
  Mat img_3 = imread( argv[1], CV_LOAD_IMAGE_COLOR );
  Mat img_4 = imread( argv[2], CV_LOAD_IMAGE_COLOR );
  imshow("图像一", img_3);
  imshow("图像二", img_4);
  

  //-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 400;

  SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints_1, keypoints_2;

  detector.detect( img_1, keypoints_1 );
  detector.detect( img_2, keypoints_2 );

  //-- Step 2: Calculate descriptors (feature vectors)
  SurfDescriptorExtractor extractor;

  Mat descriptors_1, descriptors_2;

  extractor.compute( img_1, keypoints_1, descriptors_1 );
  extractor.compute( img_2, keypoints_2, descriptors_2 );

  //-- Step 3: Matching descriptor vectors with a brute force matcher
  BFMatcher matcher(NORM_L2);
  std::vector< DMatch > matches;
  matcher.match( descriptors_1, descriptors_2, matches );
  // create by me 2015.11.07  ---begin---
  // 选择了25个配准点
  std::nth_element(matches.begin(),matches.begin()+24,matches.end());
  matches.erase(matches.begin()+25,matches.end());
  // create by me  ---end---

  //-- Draw matches。画出配准的特征点连线。
  Mat img_matches;
  drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_matches );

  //-- Show detected matches，显示配准的结果
  imshow("特征点和配准", img_matches );

  waitKey(0);

  return 0;
}

/**
 * @function readme
 */
void readme()
{ std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl; }
