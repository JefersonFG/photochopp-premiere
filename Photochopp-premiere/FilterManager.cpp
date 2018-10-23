#include "FilterManager.hpp"

#include "Constants.hpp"

namespace premiere {

FilterManager::FilterManager()
{
  blur_trackpad_on_ = false;
  ResetFilters();
}

void FilterManager::ResetFilters()
{
  if (blur_trackpad_on_)
    cv::destroyWindow(window_name);

  blur_size_ = 0;
  blur_trackpad_on_ = false;
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

  cv::Mat output_frame;
  input_frame.copyTo(output_frame);

  if (blur_trackpad_on_) {
    auto kernel_size = blur_size_ * 2 + 1;
    cv::GaussianBlur(input_frame, output_frame, cv::Size(kernel_size, kernel_size), 0, 0);
    output_frame.copyTo(input_frame);
  }

  if (detect_edges_) {
    cv::Canny(input_frame, output_frame, 75, 225);
    output_frame.copyTo(input_frame);
  }

  return output_frame;
}

void FilterManager::UpdateFilters(char user_input)
{
  switch (user_input) {
  case 'd':
    ResetFilters();
    break;
  case 'b':
    if (blur_trackpad_on_)
      cv::destroyWindow(window_name);
    else
      cv::createTrackbar("Blur", window_name, &blur_size_, 12);
    blur_trackpad_on_ = !blur_trackpad_on_;
    break;
  case 'e':
    detect_edges_ = !detect_edges_;
    break;
  case 'g':
    get_gradient_ = !get_gradient_;
    break;
  case 'i':
    // TODO(jfguimaraes) Get new brightness value
    adjust_brightness_ = 0;
    break;
  case 'c':
    // TODO(jfguimaraes) Get new brightness value
    adjust_contrast_ = 0;
    break;
  case 'n':
    show_negative_ = !show_negative_;
    break;
  case 'a':
    convert_grayscale_ = !convert_grayscale_;
    break;
  case 'z':
    resize_half_++;
    break;
  case 'r':
    rotate_by_90_degrees_ = ++rotate_by_90_degrees_ > 3 ? 0 : rotate_by_90_degrees_;
    break;
  case 'h':
    mirror_horizontally_ = !mirror_horizontally_;
  case 'v':
    mirror_vertically_ = !mirror_vertically_;
  }

  resize_half_ = 0;
  rotate_by_90_degrees_ = 0;
  mirror_horizontally_ = false;
  mirror_vertically_ = false;
}

} // namespace premiere
