#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "image.hpp"

#include <stb_image_write.h>

Image::Image(std::size_t width, std::size_t height)
        : height_(height), width_(width),
          RGB_values_(std::make_unique<RGB[]>(width * height)) {}

auto Image::height() const -> std::size_t {
    return height_;
}

auto Image::width() const -> std::size_t {
    return width_;
}

auto Image::data() const -> const RGB * {
    return RGB_values_.get();
}

auto Image::data() -> RGB * {
    return RGB_values_.get();
}

auto Image::at(std::size_t i, std::size_t j) -> RGB & {
    return RGB_values_[j * width() + i];
}

void saveAsPNG(const Image &image, const char *filepath) {
    auto w = static_cast<int>(image.width());
    auto h = static_cast<int>(image.height());
    stbi_write_png(filepath, w, h, 3, image.data(), 0);
}
