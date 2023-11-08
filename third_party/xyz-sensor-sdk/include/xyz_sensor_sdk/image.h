/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Jiaji Zhou <jiaji.zhou@xyzrobotics.ai>, 2022/10/19
 *         Frank lee <frank.lee@xyzrobotics.ai>, 2022/11/19
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>
#include <memory>
#include <fstream>
#include <iomanip>
#include <string>

namespace xyz::sensor {

template <typename T, int C>
struct Image {
  std::shared_ptr<T> data;
  int width, height;
  T *ptr;
  Image() : data(nullptr), width(0), height(0), ptr(nullptr) {}
  Image(int width, int height)
      : data(new T[width * height * C], arr_d()), width(width), height(height) {
    ptr = data.get();
  }
  Image(int width, int height, T d) : Image(width, height) {
    std::fill(ptr, ptr + width * height * C, d);
  }
  Image(int width, int height, T *d) : data(d, null_d()), width(width), height(height), ptr(d) {}

  struct null_d {
    void operator()(T const *p) {}
  };
  struct arr_d {
    void operator()(T const *p) { delete[] p; }
  };
  int size() const { return width * height; }
  bool empty() const { return ptr == nullptr; }
  int sizebytes() const { return width * height * C * sizeof(T); }
  T &operator()(int i) { return ptr[i]; }
  const T &operator()(int i) const { return ptr[i]; }
  T &operator()(int y, int x) { return ptr[y * width + x]; }
  const T &operator()(int y, int x) const { return ptr[y * width + x]; }
  T &operator()(int y, int x, int c) { return ptr[C * (y * width + x) + c]; }
  const T &operator()(int y, int x, int c) const { return ptr[C * (y * width + x) + c]; }

  inline T sample(const float x, const float y, const int chan) {
    auto pix_x = [this](float x) {
      return static_cast<int>(std::clamp(0.0f, static_cast<float>(width - 1), std::round(x)));
    };
    auto pix_y = [this](float y) {
      return static_cast<int>(std::clamp(0.0f, static_cast<float>(height - 1), std::round(y)));
    };

    auto xm = pix_x(x - 0.5f);
    auto xp = pix_x(x + 0.5f);
    auto ym = pix_y(y - 0.5f);
    auto yp = pix_y(y + 0.5f);
    auto ptr = data.get();

    auto tl = ptr[C * (ym * width + xm) + chan];
    auto tr = ptr[C * (ym * width + xp) + chan];
    auto bl = ptr[C * (yp * width + xm) + chan];
    auto br = ptr[C * (yp * width + xp) + chan];

    float dx = x - xm;
    float dy = y - ym;

    auto sample =
        tl * (1.f - dx) * (1.f - dy) + tr * dx * (1.f - dy) + bl * (1.f - dx) * dy + br * dx * dy;
    return (T)sample;
  }
  Image<T, C> copy() const {
    Image<T, C> res(width, height);
    memcpy(res.data.get(), this->data.get(), width * height * sizeof(T) * C);
    res.ptr = res.data.get();
    return res;
  }
};

}  // namespace xyz::sensor
