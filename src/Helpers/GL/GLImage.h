#pragma once
#include "Helpers/GL/GLHelper.h"

#include <string>

class GLImage {

public:
  GLuint m_texture = 0;
  std::string m_name;
  std::string m_image_source;
  int m_width;
  int m_height;

public:
  GLImage(int width, int height, std::string name);

  GLImage() = default;
  ~GLImage() = default;

  void loadFromImage(std::string path, bool flipImage = false);
  void resize(int width, int height);
};