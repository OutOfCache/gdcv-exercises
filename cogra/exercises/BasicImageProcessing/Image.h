#pragma once
#include <cogra/types.h>
#include <memory>
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

using namespace cogra;

namespace GdCV
{
template<class T>
class Image
{
public:
  /// <summary>
  /// Creates an empty image.
  /// </summary>
  Image()
    : m_width(0)
    , m_height(0)
  { }

  /// <summary>
  /// Copies an image from another image.
  /// </summary> 
  Image(const Image<T>& other)    
    // Assignment 1
      : m_width(other.m_width)
      , m_height(other.m_height)
      , m_data(std::make_unique<T[]>(m_width* m_height))
  {    
    // Assignment 1
      std::memcpy(m_data.get(), other.m_data.get(), m_width * m_height * sizeof(T));
  }

  /// <summary>
  /// Moves an image from another image.
  /// </summary>
  Image(Image<T>&& other) noexcept
    // Assignment 1
      : m_width(std::exchange(other.m_width, 0))
      , m_height(std::exchange(other.m_height, 0))
      , m_data(std::exchange(other.m_data, nullptr))
  {    
    // Assignment 1 


  }

  /// <summary>
  /// Copies an image from onther image.
  /// </summary>
  Image& operator=(const Image<T>& other)
  {
      //if (this == &other) return *this;
      //std::size_t n{std::strlen(other.)}
    
      Image tmp(other);

      std::swap(m_width, tmp.m_width);
      std::swap(m_height, tmp.m_height);
      std::swap(m_data, tmp.m_data);

    // Assignment 1    
    return *this;
  }

  /// <summary>
  /// Moves an image from another image.
  /// </summary>
  Image& operator=(Image<T>&& other) noexcept
  {
      std::swap(m_height, other.m_height);
      std::swap(m_width, other.m_width);
      std::swap(m_data, other.m_data);
    // Assignment 1
    return *this;
  }

  /// <summary>
  /// Creates an image with the provide number of pixels in x and y direction.
  /// </summary>
  /// <param name="width">Number of pixels in x (horizontal) direction.</param>
  /// <param name="height">Number of pixels in y (vertical) direction.</param>
  Image(uint32 width, uint32 height)
      : m_data(std::make_unique<T[]>(width* height))
      , m_width(width)
      , m_height(height)
  { 
  }

  /// <summary>
  /// Loads an image from file.
  /// </summary>
  Image(const std::string& pathToFileName)
  {
    const int numberOfChannels = sizeof(T) / sizeof(uint8);

    int x, y, c;

    auto stbImage = std::unique_ptr<T, void(*)(T*)>(
      reinterpret_cast<T*>(stbi_load(pathToFileName.c_str(), &x, &y, &c, numberOfChannels)),
      [](T* image) { stbi_image_free(image); });

    m_width = x;
    m_height = y;
    m_data = std::make_unique<T[]>(m_width * m_height);

    for(size_t i = 0; i < nPixels(); i++)
    {
      m_data[i] = stbImage.get()[i];
    }
  }

  /// <summary>
  /// Saves an image as png file.
  /// </summary>
  void saveAsPNG(const std::string& pathToFileName) const
  {
    const int numberOfChannels = sizeof(T) / sizeof(uint8);
    stbi_write_png(pathToFileName.c_str(), m_width, m_height, numberOfChannels, m_data.get(),
                   m_width * sizeof(T));
  }

  /// <summary>
  /// Returns a const pointer to the image data.
  /// The image is presented row major with line or pixel padding.
  /// </summary>
  const T* const data()  const
  {
    // Assignment 1
    return m_data.get();
  }

  /// <summary>
  /// Returns a pointer to the image data.
  /// The image is presented row major with line or pixel padding.
  /// </summary>
  T* data()
  {
    // Assignment 1
    return m_data.get();
  }

  /// <summary>
  /// Returns the offset (or address) in pixels (not in bytes) to the pixel with the provided coordinate.
  /// </summary>
  uint32 offset(uint32 x, uint32 y) const
  {
    // Assignment 1
    return y * m_width + x;
  }

  /// <summary>
  /// Computes the x coordinate from an offset in pixels (not in bytes).
  /// </summary>
  uint32 offsetToXCoord(uint32 offset)  const
  {
    // Assignment 1
    return offset % m_width;
  }

  /// /// <summary>
  /// Computes the y coordinate from an offset in pixels (not in bytes).
  /// </summary>
  uint32 offsetToYCoord(uint32 offset) const
  {
    // Assignment 1
    return offset / m_width;
  }

  /// <summary>
  /// Returns the color at the pixel location x, y for reading.
  /// </summary>
  const T operator()(uint32 x, uint32 y) const
  {
    // Assignment 1
      return m_data[offset(x, y)];
  }

  /// <summary>
  /// Returns the color at the pixel location x, y for writing.
  /// </summary>
  T& operator()(uint32 x, uint32 y)
  {
    // Assignment 1
      return m_data[offset(x, y)];
  }

  /// <summary>
  /// Returns the color at the pixel location offset for reading.
  /// </summary>
  const T operator()(uint32 offset) const
  {
    // Assignment 1
    return m_data[offset];
  }

  /// <summary>
  /// Returns the color at the pixel location offset for writing.
  /// </summary>
  T& operator()(uint32 offset)
  {
    // Assignment 1
    return m_data[offset];
  }

  /// <summary>
  /// Returns the total number of pixels.
  /// </summary>
  uint32 nPixels() const
  {
    // Assignment 1
    return m_width * m_height;
  }

  /// <summary>
  /// Returns the width of the image in pixels.
  /// </summary>  
  uint32 width() const
  {
    // Assignment 1
    return m_width;
  }

  /// <summary>
  /// Returns the height of the image in pixels.
  /// </summary>
  uint32 height() const
  {
    // Assignment 1
    return m_height;
  }

  /// <summary>
  /// Returns the number of bytes the image consumes in main memory.
  /// </summary>  
  size_t sizeInBytes() const
  {
    // Assignment 1
    return sizeof(m_data);
  }

private:
  std::unique_ptr<T[]>        m_data;

  uint32                      m_width;

  uint32                      m_height;
};

// Assignment 1
// TODO typedef templates


typedef Image<uint8> ImageG8;
typedef Image<ui8vec3> ImageRGB8;
}