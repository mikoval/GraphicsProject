#ifndef Vec3_H
#define Vec3_H

#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

template <typename T> class Vec3
{
    
public:
    T x, y, z;
    Vec3() { x = 0; y = 0; z = 0; }
    Vec3(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }
    
    T dot(Vec3& v) {
        return x * v.x + y * v.y + z * v.z;
    }


    T length() const {
        return sqrt(x * x + y * y + z * z);
    }

    T length2() const {
        return x * x + y * y + z * z;
    }
    T min() const {
        return std::min(std::min(x, y),z);
    }
    T max() const {
        return std::max(std::max(x, y),z);
    }


    Vec3<T> norm () const {
        float l = length();
        return *this / l;
    }

    void normalize () {
        float l = length();
        *this /= l;
    }

    void print() const{
        cout << "x: " << x << ", y: " << y <<  ", z: " << z << endl;
    }
    Vec3<T> operator+ (const Vec3<T>& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3<T> operator- (const Vec3<T>& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    Vec3<T> operator* (const Vec3<T>& v) const {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }
    Vec3<T> operator/ (const Vec3<T>& v) const {
        return Vec3(x / v.x, y / v.y, z / v.z);
    }
    Vec3<T> operator+= (const Vec3<T>& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    Vec3<T> operator-= (const Vec3<T>& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    Vec3<T> operator*= (const Vec3<T>& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    Vec3<T> operator/= (const Vec3<T>& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    Vec3<T> operator+ (T v) const {
        return Vec3(x + v, y + v, z + v);
    }
    Vec3<T> operator- (T v) const {
        return Vec3(x - v, y - v, z - v);
    }
    Vec3<T> operator* (T v) const {
        return Vec3(x * v, y * v, z * v);
    }
    Vec3<T> operator/ (T v) const {
        return Vec3(x / v, y / v, z / v);
    }

    Vec3<T> operator+= (T v) {
        this->x += v;
        this->y += v;
        this->z += v;
        return *this;
    }
    Vec3<T> operator-= (T v) {
        this->x -= v;
        this->y -= v;
        this->z -= v;
        return *this;
    }
    Vec3<T> operator*= (T v) {
        this->x *= v;
        this->y *= v;
        this->z *= v;
        return *this;
    }
    Vec3<T> operator/= (T v) {
        this->x /= v;
        this->y /= v;
        this->z /= v;
        return *this;
    }

    Vec3<T> operator- () const {
        return Vec3<T>(-x, -y, -z);
    }
    T operator[] (int i) const {
        assert(i >= 0 && i < 3);
        if(i == 0) { return x; }
        else if (i == 1) { return y; }
        else { return z; }
    }

    bool operator== (const Vec3<T>& v) {
        if(this->x != v.x || this->y != v.y || this->z != v.z) {
            return false;
        }

        return true;
    }
    bool operator!= (const Vec3<T>& v) {
        return !(*this == v);
    }
};



template <typename T> inline Vec3<T> operator+(const float v , const Vec3<T> &vec) {
    return vec + v;
}

template <typename T> inline Vec3<T> operator-(const float v , const Vec3<T> &vec) {
    return -vec + v;
}

template <typename T> inline Vec3<T> operator*(const float v , const Vec3<T> &vec) {
    return vec * v;
}

template <typename T> inline Vec3<T> operator/(const float v , const Vec3<T> &vec) {
    return Vec3<T>(v, v, v) / vec;
}

inline Vec3<float> cross(const Vec3<float> &vec1, const Vec3<float> &vec2){
    float x = vec1.y * vec2.z - vec1.z * vec2.y;
    float y = vec1.z * vec2.x - vec1.x * vec2.z;
    float z = vec1.x * vec2.y - vec1.y * vec2.x;
    Vec3<float> f= Vec3<float>(x, y, z);
    return f;
}

inline Vec3<float> norm(const Vec3<float> &vec1){
    float l = vec1.length();
    return vec1/l;
}

inline float dist(const Vec3<float> &vec1, const Vec3<float> &vec2){
    return (vec1 + vec2).length();
}
inline float dist2(const Vec3<float> &vec1, const Vec3<float> &vec2){
    return (vec1 + vec2).length2();
}

#endif
