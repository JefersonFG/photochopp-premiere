#pragma once

#include <opencv2/opencv.hpp>

namespace premiere {

/**
 * Class for managing which filters should be applied and effectively
 * applying the filters on each frame captured
 */
class FilterManager
{
public:
  /**
   * Initializes filter values
   */
  FilterManager();

  /**
   * Processes the user input and applies filters to the input frame
   * Saves the frame with the filters applied on video_output skipping
   * filters that change the image size
   */
  cv::Mat ApplyFilters(cv::Mat input_frame, char user_input, cv::VideoWriter& output_video);

private:
  /**
   * Resets the state of each filter indicator
   */
  void ResetFilters();

  /**
   * Updates current filters based on user input
   */
  void UpdateFilters(char user_input);

  int blur_size_;
  bool blur_trackpad_on_;
  bool detect_edges_;
  bool get_gradient_;
  int brightness_adjust_value_;
  bool brightness_trackbar_on_;
  int contrast_adjust_value_;
  bool contrast_trackbar_on_;
  bool show_negative_;
  bool convert_grayscale_;
  int resize_half_;
  int rotate_by_90_degrees_;
  bool mirror_horizontally_;
  bool mirror_vertically_;
};

} // namespace premiere
