#include "FilterManager.hpp"

namespace premiere {

FilterManager::FilterManager()
{
  ResetFilters();
}

void FilterManager::ResetFilters()
{
  blur_size_ = 0;
  detect_edges_ = false;
  get_gradient_ = false;
  adjust_brightness_ = 0;
  adjust_contrast_ = 0;
  show_negative_ = false;
  convert_grayscale_ = false;
  resize_half_ = 0;
  rotate_by_90_degrees_ = 0;
  mirror_horizontally_ = false;
  mirror_vertically_ = false;
}

cv::Mat FilterManager::ApplyFilters(cv::Mat input_frame, char user_input)
{
  UpdateFilters(user_input);

  // TODO(jfguimaraes) Process frame
  return input_frame;
}

void FilterManager::UpdateFilters(char user_input)
{
  // TODO(jfguimaraes) Update filters
}

} // namespace premiere
