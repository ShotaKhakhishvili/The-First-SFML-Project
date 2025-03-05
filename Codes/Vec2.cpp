#include "Vec2.h"

Vec2::Vec2()
    : x(0.0f)
    , y(0.0f)
{
}

Vec2::Vec2(float xin, float yin)
    : x(xin)
    , y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}

bool Vec2::operator!=(const Vec2& rhs) const
{
    return !(*this == rhs);
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
    // No checks for division-by-zero here, but you could add them.
    return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator+(const float value) const
{
    return Vec2(x + value, y + value);
}

Vec2 Vec2::operator-(const float value) const
{
    return Vec2(x - value, y - value);
}

Vec2 Vec2::operator*(const float value) const
{
    return Vec2(x * value, y * value);
}

Vec2 Vec2::operator/(const float value) const
{
    // Again, you could check for `value == 0.0f`
    return Vec2(x / value, y / value);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::operator*=(const Vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

Vec2& Vec2::operator/=(const Vec2& rhs)
{
    x /= rhs.x; // no zero-check
    y /= rhs.y; // no zero-check
    return *this;
}

Vec2& Vec2::operator+=(const float value)
{
    x += value;
    y += value;
    return *this;
}

Vec2& Vec2::operator-=(const float value)
{
    x -= value;
    y -= value;
    return *this;
}

Vec2& Vec2::operator*=(const float value)
{
    x *= value;
    y *= value;
    return *this;
}

Vec2& Vec2::operator/=(const float value)
{
    x /= value; // no zero-check
    y /= value; // no zero-check
    return *this;
}

Vec2& Vec2::operator=(const float value)
{
    x = value;
    y = value;
    return *this;
}

Vec2& Vec2::operator=(const Vec2& rhs)
{
    // Guard self assignment if you like:
    if (this == &rhs) return *this;
    x = rhs.x;
    y = rhs.y;
    return *this;
}

float Vec2::dist(const Vec2& other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

float Vec2::distSqr(const Vec2& other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return dx * dx + dy * dy;
}

float Vec2::length() const
{
    return std::sqrt(x * x + y * y);
}

float Vec2::dot(const Vec2& other) const
{
    return x * other.x + y * other.y;
}

Vec2 Vec2::normalized() const
{
    Vec2 ans;
    float len = length();
    if (len != 0.0f)
    {
        ans.x /= len;
        ans.y /= len;
    }
    return ans;
}

Vec2& Vec2::normalize()
{
    float len = length();
    if (len != 0.0f)
    {
        x /= len;
        y /= len;
    }
    return *this;
}

Vec2 Vec2::rotated(float degree) const
{
    float radians = degree * (M_PI / 180.f);
    float cosine = std::cos(radians);
    float sine = std::sin(radians);

    return Vec2(x * cosine - y * sine,
        x * sine + y * cosine);
}

Vec2& Vec2::rotate(float degree)
{
    float radians = degree * (M_PI / 180.f);
    float cosine = std::cos(radians);
    float sine = std::sin(radians);

    x = x * cosine - y * sine;
    y = x * sine + y * cosine;

    return *this;
}
