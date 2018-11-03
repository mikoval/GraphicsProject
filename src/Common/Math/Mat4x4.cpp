#include <Math/Mat4x4.h>   

Mat4x4::Mat4x4(){
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0;
}

Mat4x4::Mat4x4(float input[4][4]){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			m[i][j] = input[i][j];
		}
	}
}

void Mat4x4::print() const {
	cout << "| " << m[0][0] << " " <<  m[0][1] << " " << m[0][2] << " " << m[0][3] << " |" << endl;
	cout << "| " << m[1][0] << " " <<  m[1][1] << " " << m[1][2] << " " << m[1][3] << " |" << endl;
	cout << "| " << m[2][0] << " " <<  m[2][1] << " " << m[2][2] << " " << m[2][3] << " |" << endl;
	cout << "| " << m[3][0] << " " <<  m[3][1] << " " << m[3][2] << " " << m[3][3] << " |" << endl;
}

Mat4x4 Mat4x4::operator*(const Mat4x4 &m2) {
	return Mult(*this, m2);
}

Vec3<float> Mat4x4::operator*(const Vec3<float> &v) {
	float x = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * 1;
	float y = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * 1;
	float z = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * 1;
	float w = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * 1;

//	cout << "3,2: " << v[2] << endl;
//	cout << "w: " << w << endl;
	return Vec3<float>(x, y, z) / w;
}

Mat4x4 Mat4x4::transpose() const {
	float mtrans[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mtrans[j][i] = m[i][j];
		}
	}
	return Mat4x4(mtrans);
}

Mat4x4 Mat4x4::inverse() const {
    int indxc[4], indxr[4];
    int ipiv[4] = {0, 0, 0, 0};
    float minv[4][4];
    memcpy(minv, m, 4 * 4 * sizeof(float));
    for (int i = 0; i < 4; i++) {
        int irow = 0, icol = 0;
        float big = 0.f;
        // Choose pivot
        for (int j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (abs(minv[j][k]) >= big) {
                            big = float(abs(minv[j][k]));
                            irow = j;
                            icol = k;
                        }
                    }
                }
            }
        }
        ++ipiv[icol];
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol) {
            for (int k = 0; k < 4; ++k) std::swap(minv[irow][k], minv[icol][k]);
        }
        indxr[i] = irow;
        indxc[i] = icol;

        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        float pivinv = 1. / minv[icol][icol];
        minv[icol][icol] = 1.;
        for (int j = 0; j < 4; j++) minv[icol][j] *= pivinv;

        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++) {
            if (j != icol) {
                float save = minv[j][icol];
                minv[j][icol] = 0;
                for (int k = 0; k < 4; k++) minv[j][k] -= minv[icol][k] * save;
            }
        }
    }
    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; k++)
                std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
        }
    }
    return Mat4x4(minv);
}

Mat4x4 Mult(const Mat4x4 &m1, const Mat4x4 &m2) {
	Mat4x4 m = Mat4x4();

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			m.m[j][i] = (m1.m[j][0] * m2.m[0][i]) + (m1.m[j][1] * m2.m[1][i]) + 
						(m1.m[j][2] * m2.m[2][i]) + (m1.m[j][3] * m2.m[3][i]); 
		}	
	}
	return m;
}



Mat4x4 Translation(float x, float y, float z) {
	Mat4x4 m = Mat4x4();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return m;
}

Mat4x4 Translation(Vec3f v) {
	return Translation(v.x, v.y, v.z);
}

Mat4x4 Scale(float x, float y, float z) {
	Mat4x4 m = Mat4x4();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return m;
}

Mat4x4 Scale(Vec3f v) {
	return Scale(v.x, v.y, v.z);
}

Mat4x4 RotateX(float theta) {
	Mat4x4 m = Mat4x4();
	m.m[1][1] = cos(theta);
	m.m[1][2] = -sin(theta);
	m.m[2][1] = sin(theta);
	m.m[2][2] = cos(theta);
	return m;
}

Mat4x4 RotateY(float theta) {
	Mat4x4 m = Mat4x4();
	m.m[0][0] = cos(theta);
	m.m[0][2] = sin(theta);
	m.m[2][0] = -sin(theta);
	m.m[2][2] = cos(theta);
	return m;
}

Mat4x4 RotateZ(float theta) {
	Mat4x4 m = Mat4x4();
	m.m[0][0] = cos(theta);
	m.m[0][1] = -sin(theta);
	m.m[1][0] = sin(theta);
	m.m[1][1] = cos(theta);
	return m;
}

Mat4x4 Rotate(Vec3f dir, float angle) {
	Mat4x4 m = Mat4x4();



	return m;
}

Mat4x4 Rotate(Vec3<float> direction, Vec3<float> origin, float theta) {
	Mat4x4 m = Mat4x4();
	Vec3<float> dir = direction.norm();
	
	float u = dir.x;
	float v = dir.y;
	float w = dir.z;
	float a = origin.x;
	float b = origin.y;
	float c = origin.z;

	m.m[0][0] = u * u + (v * v + w * w) * cos(theta);
	m.m[0][1] = u * v * (1 - cos(theta)) - w * sin(theta);
	m.m[0][2] = u * w * (1 - cos(theta)) + v * sin(theta);
	m.m[0][3] = (a * (v * v + w * w) - u * (b * v + c * w) ) * (1 - cos(theta))
				+ (b * w - c * v) * sin(theta);

	m.m[1][0] = u * v * (1 - cos(theta)) + w * sin(theta);
	m.m[1][1] = v * v + (u * u + w * w) * cos(theta);
	m.m[1][2] = v * w * (1 - cos(theta)) - u * sin(theta);
	m.m[1][3] = (b * (u * u + w * w) - v * (a * u + c * w) ) * (1 - cos(theta))
				+ (c * u - a * w) * sin(theta);

	m.m[2][0] = u * w * (1 - cos(theta)) - v * sin(theta);
	m.m[2][1] = v * w * (1 - cos(theta)) + u * sin(theta);
	m.m[2][2] = w * w + (u * u + v * v) * cos(theta);
	m.m[2][3] = (c * (u * u + v * v) - w * (a * u + b * v) ) * (1 - cos(theta))
				+ (a * v - b * u) * sin(theta);

	return m;
}

Mat4x4 PerspectiveProjection(float fov, float near, float far, float aspect){
	float v = 1.0 / tan( radians(fov) /2.0);
	Mat4x4 m = Mat4x4();
	m.m[0][0] = v * aspect;
	m.m[1][1] = v;
	m.m[2][2] = (near - far)/(near - far);
	m.m[2][3] = (2*near*far)/(near-far);
	m.m[3][2] = 1.0;
	m.m[3][3] = 0.0;

	return m;
}

Mat4x4 OrthographicProjection(float left, float right, float top, float bottom, float near, float far){
	Mat4x4 m = Mat4x4();

	m.m[0][0] = 2.0 / (right - left);
	m.m[1][1] = 2.0 / (top - bottom);
	m.m[2][2] = 2.0 / (far - near);

	m.m[0][3] = -(right + left)/(right - left);
	m.m[1][3] = -(top + bottom)/(top - bottom);
	m.m[2][3] = -(far + near)/(far - near);

	return m;
}

Mat4x4 LookAt(Vec3f pos, Vec3f target, Vec3f worldUp){
	Mat4x4 m = Mat4x4();

	Vec3f dir = (target - pos).norm();
	Vec3f right = cross(worldUp, dir).norm();
	Vec3f up = cross(dir, right).norm();

	m.m[0][0] = right.x;
	m.m[1][0] = right.y;
	m.m[2][0] = right.z;

	m.m[0][1] = up.x;
	m.m[1][1] = up.y;
	m.m[2][1] = up.z;

	m.m[0][2] = dir.x;
	m.m[1][2] = dir.y;
	m.m[2][2] = dir.z;

	m.m[0][3] = pos.x;
	m.m[1][3] = pos.y;
	m.m[2][3] = pos.z;

	return m;
}

