#include "color.hpp"

#include <cmath>

auto sRGB_gammaCompression(float x) -> float {
    return x <= 0.0031308f
           ? x * 12.92f
           : std::pow(x, 1.0f / 2.4f) * 1.055f - 0.055f;
}

auto sRGB_gammaExpansion(float x) -> float {
    return x <= 0.04045f
           ? x / 12.92f
           : std::pow((x + 0.055f) / 1.055f, 2.4f);
}

auto sRGB_to_linear_RGB(float sRGB) -> float {
    return sRGB_gammaCompression(sRGB);
}

auto linear_RGB_to_sRGB(float sRGB) -> float {
    return sRGB_gammaExpansion(sRGB);
}
