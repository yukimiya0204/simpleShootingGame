#pragma once

#include <cmath> 

struct Vector2 {
    float x, y;

    // コンストラクタ
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float px, float py) : x(px), y(py) {}

    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    float length() const {
        return std::sqrt(x * x + y * y);
    }
    Vector2 normalized() const {
        float len = length();
        if (len == 0.0f) return Vector2(0.0f, 0.0f);
        return Vector2(x / len, y / len);
    }
};