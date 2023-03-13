#pragma once

#include <array>
#include <cstdlib>
#include <memory>
#include <string_view>

using RGB = std::array<unsigned char, 3>;

class Image {
public:
    Image() = default;

    Image(std::size_t width, std::size_t height);

    auto height() const -> std::size_t;

    auto width() const -> std::size_t;

    auto at(std::size_t i, std::size_t j) -> RGB &;

    auto data() const -> const RGB *;

    auto data() -> RGB *;

private:
    std::size_t height_ = 0;
    std::size_t width_ = 0;

    std::unique_ptr<RGB[]> RGB_values_;
};

void saveAsPNG(const Image &, const char *filepath);
