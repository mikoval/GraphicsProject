#ifndef Vec2_H
#define Vec2_H

#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

template <typename T> class Vec2
{
    
public:
    T x, y;
    Vec2() { x = 0; y = 0; }
    Vec2(T x, T y) { this->x = x; this->y = y; }
    
    T dot(Vec2& v) {
        return x * v.x + y * v.y;
    }

    T length() {
        return sqrt(x * x + y * y);
    }

    T length2() {
        return x * x + y * y;
    }

    void print() {
        cout << "x: " << x << ", y: " << y << endl;
    }
    Vec2<T> operator+ (const Vec2<T>& v) {
        return Vec2(x + v.x, y + v.y);
    }
    Vec2<T> operator- (const Vec2<T>& v) {
        return Vec2(x - v.x, y - v.y);
    }
    Vec2<T> operator* (const Vec2<T>& v) {
        return Vec2(x * v.x, y * v.y);
    }
    Vec2<T> operator/ (const Vec2<T>& v) {
        return Vec2(x / v.x, y / v.y);
    }
    Vec2<T> operator+= (const Vec2<T>& v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    Vec2<T> operator-= (const Vec2<T>& v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    Vec2<T> operator*= (const Vec2<T>& v) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    Vec2<T> operator/= (const Vec2<T>& v) {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    Vec2<T> operator+ (T v) const {
        return Vec2(x + v, y + v);
    }
    Vec2<T> operator- (T v) const {
        return Vec2(x - v, y - v);
    }
    Vec2<T> operator* (T v) const {
        return Vec2(x * v, y * v);
    }
    Vec2<T> operator/ (T v) const {
        return Vec2(x / v, y / v);
    }

    Vec2<T> operator+= (T v) {
        this->x += v;
        this->y += v;
        return *this;
    }
    Vec2<T> operator-= (T v) {
        this->x -= v;
        this->y -= v;
        return *this;
    }
    Vec2<T> operator*= (T v) {
        this->x *= v;
        this->y *= v;
        return *this;
    }
    Vec2<T> operator/= (T v) {
        this->x /= v;
        this->y /= v;
        return *this;
    }

    Vec2<T> operator- () const {
        return Vec2<T>(-x, -y);
    }
    T operator[] (int i) const {
        assert(i >= 0 && i < 2);
        if(i == 0) { return x; }
        else { return y; }
    }
};

template <typename T> inline Vec2<T> operator+(const float v , const Vec2<T> &vec) {
    return vec + v;
}

template <typename T> inline Vec2<T> operator-(const float v , const Vec2<T> &vec) {
    return -vec + v;
}

template <typename T> inline Vec2<T> operator*(const float v , const Vec2<T> &vec) {
    return vec * v;
}

template <typename T> inline Vec2<T> operator/(const float v , const Vec2<T> &vec) {
    return Vec2<T>(v, v) / vec;
}

#endif