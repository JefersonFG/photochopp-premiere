#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
  cv::VideoCapture cap;

  if (!cap.open(0)) {
    std::cerr << "Couldn't open capture\n";
    return -1;
  }

  char input = 0;
  
  // Loop until ESC pressed
  do {
    cv::Mat input_frame;
    cv::Mat output_frame;
    cap >> input_frame;

    // End of video stream
    if (input_frame.empty())
      break;

    imshow("Capture", input_frame);

    input = cv::waitKey(10);
  } while (input != 27);

  cap.release();
  return 0;
}
