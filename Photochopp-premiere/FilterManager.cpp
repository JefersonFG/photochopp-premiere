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
  if (blur_trackpad_on_ || brightness_trackbar_on_ || contrast_trackbar_on_)
    cv::destroyWindow(window_name);

  blur_size_ = 0;
  blur_trackpad_on_ = false;
  detect_edges_ = false;
  get_gradient_ = false;
  brightness_adjust_value_ = 0;
  brightness_trackbar_on_ = false;
  contrast_adjust_value_ = 0;
  contrast_trackbar_on_ = false;
  show_negative_ = false;
  convert_grayscale_ = false;
  resize_half_ = 0;
  rotate_by_90_degrees_ = 0;
  mirror_horizontally_ = false;
  mirror_vertically_ = false;
}

cv::Mat FilterManager::ApplyFilters(cv::Mat input_frame, char user_input, cv::VideoWriter& output_video)
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
    cv::cvtColor(output_frame, output_frame, cv::COLOR_GRAY2BGR);
    output_frame.copyTo(input_frame);
  }

  if (get_gradient_) {
    cv::Mat grad_x;
    cv::Mat grad_y;
    cv::Mat abs_grad_x;
    cv::Mat abs_grad_y;

    cv::Sobel(input_frame, grad_x, CV_32F, 1, 0);
    cv::Sobel(input_frame, grad_y, CV_32F, 0, 1);

    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, output_frame);

    output_frame.copyTo(input_frame);
  }

  if (brightness_trackbar_on_) {
    input_frame.convertTo(output_frame, -1, 1, brightness_adjust_value_ - 50);
    output_frame.copyTo(input_frame);
  }

  if (contrast_trackbar_on_) {
    input_frame.convertTo(output_frame, -1, contrast_adjust_value_ + 1, 0);
    output_frame.copyTo(input_frame);
  }

  if (show_negative_) {
    cv::bitwise_not(input_frame, output_frame);
    output_frame.copyTo(input_frame);
  }

  if (convert_grayscale_) {
    cv::cvtColor(input_frame, output_frame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(output_frame, output_frame, cv::COLOR_GRAY2BGR);
    output_frame.copyTo(input_frame);
  }

  if (mirror_horizontally_) {
    cv::flip(input_frame, output_frame, 1);
    output_frame.copyTo(input_frame);
  }

  if (mirror_vertically_) {
    cv::flip(input_frame, output_frame, 0);
    output_frame.copyTo(input_frame);
  }

  output_video.write(output_frame);

  if (resize_half_ > 0) {
    double new_size_proportion = 1.0 / (resize_half_ + 1);
    cv::resize(input_frame, output_frame, cv::Size(), new_size_proportion, new_size_proportion, CV_INTER_AREA);
    output_frame.copyTo(input_frame);
  }

  if (rotate_by_90_degrees_ > 0) {
    auto angle = rotate_by_90_degrees_ * 90;
    cv::Point2f input_frame_center(input_frame.cols / 2.0F, input_frame.rows / 2.0F);
    cv::Mat rotation_matrix = getRotationMatrix2D(input_frame_center, angle, 1.0);
    cv::warpAffine(input_frame, output_frame, rotation_matrix, input_frame.size());
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
    blur_trackpad_on_ = !blur_trackpad_on_;
    break;
  case 'e':
    detect_edges_ = !detect_edges_;
    break;
  case 'g':
    get_gradient_ = !get_gradient_;
    break;
  case 'i':
    if (brightness_trackbar_on_)
      cv::destroyWindow(window_name);
    brightness_trackbar_on_ = !brightness_trackbar_on_;
    break;
  case 'c':
    if (contrast_trackbar_on_)
      cv::destroyWindow(window_name);
    contrast_trackbar_on_ = !contrast_trackbar_on_;
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
    break;
  case 'v':
    mirror_vertically_ = !mirror_vertically_;
    break;
  }

  if (blur_trackpad_on_)
    cv::createTrackbar("Blur", window_name, &blur_size_, 12);
  if (brightness_trackbar_on_)
    cv::createTrackbar("Brightness", window_name, &brightness_adjust_value_, 100);
  if (contrast_trackbar_on_)
    cv::createTrackbar("Contrast", window_name, &contrast_adjust_value_, 12);
}

} // namespace premiere
