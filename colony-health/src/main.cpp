/**
 * @Author: Nick Steele <nichlock>
 * @Date:   18:41 Sep 13 2020
 * @Last modified by:   Nick Steele
 * @Last modified time: 20:34 Sep 24 2020
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const std::string default_test_image = "/images/original.jpg";

bool loadImage(int argc, char const *argv[]);

Mat imageIn;
Mat imageHsv;

std::string window_image = "Image";
std::string window_live = "Living";
std::string window_dead = "Dead";
std::string window_contour_live = "Contours - Live";
std::string window_contour_dead = "Contours - Dead";

bool trackbarsChanged = true; // For OpenCV trackbar usage

int main(int argc, char const *argv[]) {
  if (!loadImage(argc, argv)) return EXIT_FAILURE;

  resize(imageIn, imageIn, Size(500, 500), 0, 0, INTER_AREA);
  cvtColor(imageIn, imageHsv, COLOR_BGR2HSV);

  int grayscale_type = CV_8UC1;
  int mask_types = grayscale_type; // imageHsv.type();

  Mat live_lut[3];
  Mat dead_lut[3];

  Mat live_mask[3];
  Mat live_mask_final(imageHsv.rows, imageHsv.cols, mask_types);
  Mat dead_mask[3];
  Mat dead_mask_final(imageHsv.rows, imageHsv.cols, mask_types);

  // Initialize image matrices
  for (int i = 0; i < 3; i++) {
    live_lut[i] = Mat(1, 256, grayscale_type);
    dead_lut[i] = Mat(1, 256, grayscale_type);
    live_mask[i] = Mat(imageHsv.rows, imageHsv.cols, mask_types);
    dead_mask[i] = Mat(imageHsv.rows, imageHsv.cols, mask_types);
  }

  Mat imgChannels[3];
  split(imageHsv, imgChannels);

// Live LUTs
  for (int ch = 0; ch < 3; ch++) {
    for (int color = 0; color < 256; color++) {
      switch (ch) {
      case 0: // HUE
        if (abs(color - 150) < 50) live_lut[ch].at <uchar> (0, color) = 255;
        else live_lut[ch].at <uchar> (0, color) = 0;
        break;
      case 1: // SAT
        if (color > 100) live_lut[ch].at <uchar> (0, color) = 255;
        else live_lut[ch].at <uchar> (0, color) = 0;
        break;
      case 2: // VAL
        live_lut[ch].at <uchar> (0, color) = 255;
        break;
      default:
        assert(ch < 3);
        break; // No other cases needed, only color
      } // switch
    }
  }

// Dead LUTs
  for (int ch = 0; ch < 3; ch++) {
    for (int color = 0; color < 256; color++) {
      switch (ch) {
      case 0: // HUE
        dead_lut[ch].at <uchar> (0, color) = 255;
        break;
      case 1: // SAT
        // Dead 1
        if (color < 50) dead_lut[ch].at <uchar> (0, color) = 255;
        else dead_lut[ch].at <uchar> (0, color) = 0;
        break;
      case 2: // VAL
        // Dead 2
        if (color > 200) dead_lut[ch].at <uchar> (0, color) = 255;
        else dead_lut[ch].at <uchar> (0, color) = 0;
        break;
      default:
        assert(ch < 3);
        break; // No other cases needed, only color
      } // switch
    }
  }

  // Run all three channel-specific LUTs on the input image channels.
  // Creates live and dead masks
  for (int i = 0; i < 3; i++) {
    LUT(imgChannels[i], live_lut[i], live_mask[i]);
    LUT(imgChannels[i], dead_lut[i], dead_mask[i]);
  }
  // Binary AND for the binary masks of each channel to block out noise from that channel
  dead_mask_final = dead_mask[0] & dead_mask[1] & dead_mask[2];
  live_mask_final = live_mask[0] & live_mask[1] & live_mask[2];

  double threshold1 = 100.0;
  double threshold2 = 200.0;
  int apertureSize = 3;
  bool L2gradient = false;
  Mat dead_edges, live_edges;
  Canny(dead_mask_final,
        dead_edges,
        threshold1,
        threshold2,
        apertureSize,
        L2gradient);
  Canny(live_mask_final,
        live_edges,
        threshold1,
        threshold2,
        apertureSize,
        L2gradient);

  vector <vector <Point> > dead_contours, live_contours;
  int mode = CV_RETR_TREE;
  int method = CV_CHAIN_APPROX_TC89_KCOS;
  findContours(dead_edges,
               dead_contours,
               mode,
               method);
  findContours(live_edges,
               live_contours,
               mode,
               method);

  RNG rng(12345); // any random number
  Mat dead_result(dead_edges.size(), CV_8UC3, Scalar(0));
  Mat live_result(live_edges.size(), CV_8UC3, Scalar(0));
  int thickness = 2;
  for (int i = 0; i < live_contours.size(); i++) {
    Scalar color = Scalar(rng.uniform(0, 255),
                          rng.uniform(0, 255),
                          rng.uniform(0, 255));
    drawContours(live_result,
                 live_contours,
                 i,
                 color,
                 thickness);
  }
  for (int i = 0; i < dead_contours.size(); i++) {
    Scalar color = Scalar(rng.uniform(0, 255),
                          rng.uniform(0, 255),
                          rng.uniform(0, 255));
    drawContours(dead_result,
                 dead_contours,
                 i,
                 color,
                 thickness);
  }

  // trackbarSetup();

  while (true) {
    waitKey(1);
    // Wait for trackbar changes, only update when they are changed.
    // Trackbars are an openCV feature which can change a variable value while
    // the program is running. They are also a little sketchy, so make sure that
    // the only code they have is to update a value and set trackbarsChanged = true,
    // Or the program will begin to lag.
    if (!trackbarsChanged) { continue;}
    trackbarsChanged = false;

    // Show results
    imshow(window_image, imageIn);
    imshow(window_live, live_mask_final);
    imshow(window_dead, dead_mask_final);
    imshow("living canny edges", live_edges);
    imshow("dead canny edges", dead_edges);
    imshow(window_contour_live, live_result);
    imshow(window_contour_dead, dead_result);

    waitKey(1); // MUST BE HERE for images to actually show.
  }

  return EXIT_SUCCESS;
} // main

bool loadImage(int argc, char const *argv[]) {
  if (argc > 1) {
    cout << "Loading image: " << argv[1] << "\n";
    imageIn = imread(argv[1]);
  } else {
    cout << "No image argument given. Loading default image " <<
      default_test_image << "\n";
    imageIn = imread(default_test_image);
  }
  if (imageIn.empty()) {
    cout << "Empty input image!\n";
    return false;
  }
  return true;
} // loadImage
