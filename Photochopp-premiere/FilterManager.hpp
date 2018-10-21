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
   */
  cv::Mat ApplyFilters(cv::Mat input_frame, char user_input);

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
  bool detect_edges_;
  bool get_gradient_;
  int adjust_brightness_;
  int adjust_contrast_;
  bool show_negative_;
  bool convert_grayscale_;
  int resize_half_;
  int rotate_by_90_degrees_;
  bool mirror_horizontally_;
  bool mirror_vertically_;
};

} // namespace premiere
