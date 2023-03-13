#pragma once

/// \file color.hpp

/// \name Linear RGB
/// \{

/// \returns sRGB value in [0, 1].
/// \param linear_RGB value in [0, 1].
/// \see http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_RGB.html
auto linear_RGB_to_sRGB(float sRGB) -> float;

/// \}

/// \name sRGB
/// \{

/// \returns Value in [0, 1].
/// \param x in [0, 1].
/// \see http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_RGB.html
auto sRGB_gammaCompression(float x) -> float;

/// \returns Value in [0, 1].
/// \param x in [0, 1].
/// \see http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
auto sRGB_gammaExpansion(float x) -> float;

/// \returns Linear RGB value in [0, 1].
/// \param sRGB value in [0, 1].
/// \see http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
auto sRGB_to_linear_RGB(float sRGB) -> float;

/// \}
