#include <gamut_viewer/conventions.hpp>

auto upDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(0.f, +1.f, 0.f);
    return dir;
}

auto bottomDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(0.f, -1.f, 0.f);
    return dir;
}

auto forwardDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(0.f, 0.f, -1.f);
    return dir;
}

auto backwardDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(0.f, 0.f, +1.f);
    return dir;
}

auto leftDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(-1.f, 0.f, 0.f);
    return dir;
}

auto rightDir() -> const glm::vec3 & {
    static auto dir = glm::vec3(+1.f, 0.f, 0.f);
    return dir;
}
