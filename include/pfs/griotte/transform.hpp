////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Notes:
//      Based on Transform implementation from https://github.com/sammycage/lunasvg
//
// Changelog:
//      2024.07.23 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include <utility>

namespace griotte {

template <typename Float>
class transform
{
private:
    constexpr static Float static_pi = Float(3.14159265358979323846);

private:
    Float _m00 {1};
    Float _m10 {0};
    Float _m01 {0};
    Float _m11 {1};
    Float _m02 {0};
    Float _m12 {0};

private:
    transform (Float m00, Float m10, Float m01, Float m11, Float m02, Float m12)
        : _m00(m00), _m10(m10), _m01(m01), _m11(m11), _m02(m02), _m12(m12)
    {}

public:
    transform () = default;

    transform inverted () const
    {
        Float det = (_m00 * _m11 - _m10 * _m01);

        if(det == 0.0)
            return transform{};

        Float inv_det = 1.0 / det;
        Float m00 = _m00 * inv_det;
        Float m10 = _m10 * inv_det;
        Float m01 = _m01 * inv_det;
        Float m11 = _m11 * inv_det;
        Float m02 = (_m01 * _m12 - _m11 * _m02) * inv_det;
        Float m12 = (_m10 * _m02 - _m00 * _m12) * inv_det;

        return transform{m11, -m10, -m01, m00, m02, m12};
    }

    transform operator * (transform const & rhs) const
    {
        transform result;

        result._m00 = _m00 * rhs._m00 + _m10 * rhs._m01;
        result._m10 = _m00 * rhs._m10 + _m10 * rhs._m11;
        result._m01 = _m01 * rhs._m00 + _m11 * rhs._m01;
        result._m11 = _m01 * rhs._m10 + _m11 * rhs._m11;
        result._m02 = _m02 * rhs._m00 + _m12 * rhs._m01 + rhs._m02;
        result._m12 = _m02 * rhs._m10 + _m12 * rhs._m11 + rhs._m12;

        return result;
    }

    transform & rotate (Float angle)
    {
        auto c = std::cos(angle * static_pi / Float{180});
        auto s = std::sin(angle * static_pi / Float{180});

        *this = transform{c, s, -s, c, 0, 0} * *this;

        return *this;
    }

    transform & rotate (Float angle, Float cx, Float cy)
    {
        auto c = std::cos(angle * static_pi / Float{180});
        auto s = std::sin(angle * static_pi / Float{180});

        auto x = cx * (1 - c) + cy * s;
        auto y = cy * (1 - c) - cx * s;

        *this = transform{c, s, -s, c, x, y} * *this;

        return *this;
    }

    transform & scale (Float factor_x, Float factor_y)
    {
        *this = transform{factor_x, 0, 0, factor_y, 0, 0} * *this;
        return *this;
    }

    transform & scale (Float factor)
    {
        *this = transform{factor, 0, 0, factor, 0, 0} * *this;
        return *this;
    }

    transform & shear (Float shx, Float shy)
    {
        auto x = std::tan(shx * static_pi / Float{180});
        auto y = std::tan(shy * static_pi / Float{180});

        *this = transform{1, y, x, 1, 0, 0} * *this;

        return *this;
    }

    transform & translate (Float tx, Float ty)
    {
        *this = transform{1, 0, 0, 1, tx, ty} * *this;
        return *this;
    }

    template <typename U>
    void map (U x, U y, U * px, U * py) const
    {
        *px = x * _m00 + y * _m01 + _m02;
        *py = x * _m10 + y * _m11 + _m12;
    }

    template <typename U>
    void map (U x, U y, U w, U h, U * px, U * py, U * pw, U * ph) const
    {
        auto x1 = x;
        auto y1 = y;
        auto x2 = x + w;
        auto y2 = y + h;

        U p[8];

        map(x1, y1, & p[0], & p[1]);
        map(x2, y1, & p[2], & p[3]);
        map(x2, y2, & p[4], & p[5]);
        map(x1, y2, & p[6], & p[7]);

        auto l = p[0];
        auto t = p[1];
        auto r = p[0];
        auto b = p[1];

        for (int i = 2; i < 8; i += 2) {
            if (p[i] < l)
                l = p[i];

            if (p[i] > r)
                r = p[i];

            if (p[i + 1] < t)
                t = p[i + 1];

            if (p[i + 1] > b)
                b = p[i + 1];
        }

        *px = l;
        *py = t;
        *pw = r - l;
        *ph = b - t;
    }
};

using transform_t = transform<float>;

} // namespace griotte
