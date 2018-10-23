#include <iostream>

#include <opencv2/opencv.hpp>

#include "Constants.hpp"
#include "FilterManager.hpp"

int main(int argc, char** argv)
{
  cv::VideoCapture cap;

  if (!cap.open(0)) {
    std::cerr << "Couldn't open capture\n";
    return -1;
  }

  char user_input = 0;
  premiere::FilterManager filter_manager;
  
  // Loop until ESC pressed
  do {
    cv::Mat input_frame;
    cap >> input_frame;

    // End of video stream
    if (input_frame.empty())
      break;

    auto output_frame = filter_manager.ApplyFilters(input_frame, user_input);

    imshow(premiere::window_name, output_frame);

    user_input = cv::waitKey(10);

    if (user_input == 's') {
      // TODO(jfguimaraes) Save video
    }
  } while (user_input != 27);

  cap.release();
  return 0;
}
