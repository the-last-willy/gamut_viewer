#pragma once

template<typename T>
auto remap(T a, T b, T x, T c, T d) -> T {
    return (x - a) / (b - a) * (d - c) + c;
}
