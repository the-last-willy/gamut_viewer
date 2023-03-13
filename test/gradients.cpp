#include <gamut_viewer/color.hpp>
#include <gamut_viewer/common.hpp>
#include <gamut_viewer/image.hpp>
#include <gamut_viewer/opengl_context.hpp>

#include <catch2/catch_test_macros.hpp>
#include <glad/glad.h>

TEST_CASE("Linear RGB grayscale") {
    auto context = StandaloneOpenGL_Context();
    context.makeCurrent();

    auto image = Image(256, 1);

    for (std::size_t i = 0; i < image.width(); ++i) {
        auto &rgb = image.at(i, 0);
        auto x = remap(0.f, float(image.width() - 1),
                                       float(i),
                                       0.f, 1.f);
        x = (x);
        auto v = static_cast<unsigned char>(x * 255.f);
        rgb = RGB{v, v, v};
    }

    saveAsPNG(image, "tmp/linear_rgb_grayscale.png");
}

TEST_CASE("sRGB grayscale") {
    auto context = StandaloneOpenGL_Context();
    context.makeCurrent();

    auto image = Image(256, 1);

    for (std::size_t i = 0; i < image.width(); ++i) {
        auto &rgb = image.at(i, 0);
        auto x = remap(0.f, float(image.width() - 1),
                       float(i),
                       0.f, 1.f);
        x = linear_RGB_to_sRGB(x);
        auto v = static_cast<unsigned char>(x * 255.f);
        rgb = RGB{v, v, v};
    }

    saveAsPNG(image, "tmp/srgb_grayscale.png");
}
