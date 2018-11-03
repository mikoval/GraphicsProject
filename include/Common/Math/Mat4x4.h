#ifndef MAT4X4_H
#define MAT4X4_H

#include <iostream>
#include <assert.h>
#include <math.h>
#include <Math/MathTools.h>

using namespace std;

struct Mat4x4 {
    float m[4][4];
    Mat4x4();
    Mat4x4(float mat[4][4]);
    Mat4x4(float t00, float t01, float t02, float t03, float t10, float t11,
              float t12, float t13, float t20, float t21, float t22, float t23,
              float t30, float t31, float t32, float t33);

    void print() const;

    bool operator==(const Mat4x4 &m2);
    bool operator!=(const Mat4x4 &m2);

    Mat4x4 operator*(const Mat4x4 &m2);
    Vec3<float> operator*(const Vec3<float> &v);

    Mat4x4 inverse() const;
    Mat4x4 transpose() const;
};

Mat4x4 Mult(const Mat4x4 &m1, const Mat4x4 &m2);

Mat4x4 Translation(float x, float y, float z);
Mat4x4 Translation(Vec3<float> v);

Mat4x4 Scale(float x, float y, float z);
Mat4x4 Scale(Vec3<float> v);

Mat4x4 RotateX(float theta);
Mat4x4 RotateY(float theta);
Mat4x4 RotateZ(float theta);

Mat4x4 Rotate(Vec3<float> dir, float theta);
Mat4x4 Rotate(Vec3<float> dir, Vec3<float> origin, float theta);

Mat4x4 PerspectiveProjection(float fov, float near, float far, float aspect);

Mat4x4 OrthographicProjection(float left, float right, float top, float bottom, float near, float far);

Mat4x4 LookAt(Vec3<float> position, Vec3<float> target, Vec3<float> up);

#endif
