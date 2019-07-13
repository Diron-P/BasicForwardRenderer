#pragma once



namespace Oblivion {
namespace Math {
    class Mat3x3 {
    public:
        float m[3][3];

        inline Mat3x3()
        {
            memset(m, 0, sizeof(m[0][0]) * 3 * 3);
        }

        inline Mat3x3(const float diagonal)
        {
            memset(m, 0, sizeof(m[0][0]) * 3 * 3);
            m[0][0] = m[1][1] = m[2][2] = diagonal;
        }

        inline Mat3x3(const float& num1, const float& num2, const float& num3, const float& num4, const float& num5, const float& num6, const float& num7, const float& num8, const float& num9)
        {
            m[0][0] = num1;
            m[0][1] = num2;
            m[0][2] = num3;
            m[1][0] = num4;
            m[1][1] = num5;
            m[1][2] = num6;
            m[2][0] = num7;
            m[2][1] = num8;
            m[2][2] = num9;
        }

        inline Mat3x3(const Vector3D& vx, const Vector3D& vy, const Vector3D& vz)
        {
            m[0][0] = vx.x;
            m[0][1] = vx.y;
            m[0][2] = vx.z;
            m[1][0] = vy.x;
            m[1][1] = vy.y;
            m[1][2] = vy.z;
            m[2][0] = vz.x;
            m[2][1] = vz.y;
            m[2][2] = vz.z;
        }

        inline Mat3x3& MakeZero()
        {
            memset(m, 0, sizeof(m[0][0]) * 3 * 3);
            return *this;
        }

        inline Mat3x3& SetIdentity()
        {
            memset(m, 0, sizeof(m[0][0]) * 3 * 3);
            m[0][0] = m[1][1] = m[2][2] = 1.0f;
            return *this;
        }

        const float& operator()(uint8_t i, uint8_t j) const
        {
            return m[i][j];
        }

        float& operator()(uint8_t i, uint8_t j)
        {
            return m[i][j];
        }

		/*const Vector3D& operator[](uint8_t i) const
        {
            return (*reinterpret_cast<Vector3D*>(m[i]));  
        }*/

        Vector3D& operator[](uint8_t i)
        {
            return (*reinterpret_cast<Vector3D *>(m[i])); 
        }

        inline Mat3x3& operator*=(const Mat3x3& m1)
        {
            //Row 1
            Vector3D tmp(m[0][0], m[0][1], m[0][2]);
            m[0][0] = tmp.x * m1(0, 0) + tmp.y * m1(1, 0) + tmp.z * m1(2, 0);
            m[0][1] = tmp.x * m1(0, 1) + tmp.y * m1(1, 1) + tmp.z * m1(2, 1);
            m[0][2] = tmp.x * m1(0, 2) + tmp.y * m1(1, 2) + tmp.z * m1(2, 2);

            //Row 2
            tmp.x = m[1][0];
            tmp.y = m[1][1];
            tmp.z = m[1][2];
            m[1][0] = tmp.x * m1(0, 0) + tmp.y * m1(1, 0) + tmp.z * m1(2, 0);
            m[1][1] = tmp.x * m1(0, 1) + tmp.y * m1(1, 1) + tmp.z * m1(2, 1);
            m[1][2] = tmp.x * m1(0, 2) + tmp.y * m1(1, 2) + tmp.z * m1(2, 2);

            //Row 3
            tmp.x = m[2][0];
            tmp.y = m[2][1];
            tmp.z = m[2][2];
            m[2][0] = tmp.x * m1(0, 0) + tmp.y * m1(1, 0) + tmp.z * m1(2, 0);
            m[2][1] = tmp.x * m1(0, 1) + tmp.y * m1(1, 1) + tmp.z * m1(2, 1);
            m[2][2] = tmp.x * m1(0, 2) + tmp.y * m1(1, 2) + tmp.z * m1(2, 2);

            return *this;
        }

        inline Mat3x3 operator*(const float& scalar) const
        {
            return Mat3x3(
                scalar * m[0][0], scalar * m[0][1], scalar * m[0][2],
                scalar * m[1][0], scalar * m[1][1], scalar * m[1][2],
                scalar * m[2][0], scalar * m[2][1], scalar * m[2][2]);
        }

        inline Mat3x3 operator*(const Mat3x3& m1) const
        {
            return Mat3x3(
                m[0][0] * m1(0, 0) + m[0][1] * m1(1, 0) + m[0][2] * m1(2, 0),
                m[0][0] * m1(0, 1) + m[0][1] * m1(1, 1) + m[0][2] * m1(2, 1),
                m[0][0] * m1(0, 2) + m[0][1] * m1(1, 2) + m[0][2] * m1(2, 2),
                m[1][0] * m1(0, 0) + m[1][1] * m1(1, 0) + m[1][2] * m1(2, 0),
                m[1][0] * m1(0, 1) + m[1][1] * m1(1, 1) + m[1][2] * m1(2, 1),
                m[1][0] * m1(0, 2) + m[1][1] * m1(1, 2) + m[1][2] * m1(2, 2),
                m[2][0] * m1(0, 0) + m[2][1] * m1(1, 0) + m[2][2] * m1(2, 0),
                m[2][0] * m1(0, 1) + m[2][1] * m1(1, 1) + m[2][2] * m1(2, 1),
                m[2][0] * m1(0, 2) + m[2][1] * m1(1, 2) + m[2][2] * m1(2, 2));
        }

        inline Vector3D operator*(const Vector3D& v) const
        {
            return Vector3D(
                v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
                v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
                v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]);
        }

        inline bool operator==(const Mat3x3& m1) const
        {
            return (m[0][0] == m1(0, 0))
				&& (m[0][1] == m1(0, 1))
				&& (m[0][2] == m1(0, 2))
				&& (m[1][0] == m1(1, 0))
				&& (m[1][1] == m1(1, 1))
				&& (m[1][2] == m1(1, 2))
				&& (m[2][0] == m1(2, 0))
				&& (m[2][1] == m1(2, 1))
				&& (m[2][2] == m1(2, 2));
        }

        inline bool operator!=(const Mat3x3& m1) const
        {
            return (m[0][0] != m1(0, 0))
				|| (m[0][1] != m1(0, 1))
				|| (m[0][2] != m1(0, 2))
				|| (m[1][0] != m1(1, 0))
				|| (m[1][1] != m1(1, 1))
				|| (m[1][2] != m1(1, 2))
				|| (m[2][0] != m1(2, 0))
				|| (m[2][1] != m1(2, 1))
				|| (m[2][2] != m1(2, 2));
        }

        inline Mat3x3 Transpose() const
        {
            return Mat3x3(
                Vector3D(m[0][0], m[1][0], m[2][0]),
                Vector3D(m[0][1], m[1][1], m[2][1]),
                Vector3D(m[0][2], m[1][2], m[2][2]));
        }

        inline float Determinant() const
        {
            return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
				- m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1])
				+ m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
        }

        inline Mat3x3 Inverse()
        {
            float determinant = Determinant();

            if (determinant == 0.0f) {
                return SetIdentity(); // Return an identity matrix if the current matrix is singular.
            }

            float inversedDet = 1.0f / determinant;

            // Transposed inverse matrix
            return Mat3x3(
                (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * inversedDet,
                -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * inversedDet,
                (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inversedDet,
                -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * inversedDet,
                (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inversedDet,
                -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * inversedDet,
                (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * inversedDet,
                -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * inversedDet,
                (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inversedDet);
        }
    };
} // end namespace Math
} // end namespace Oblivion