#pragma once

#include "MathFunctions.h"

namespace Oblivion {
namespace Math {
    class Mat4x4;

    class Quaternion {
    public:
        float w;
        Vector3D v;

        /**********************************************************************
		****************Quaternion constructor definitions*****************
		**********************************************************************/

        Quaternion()
            : w(0.0f)
        {
        }

        Quaternion(const float& w, const Vector3D& v)
            : w(w)
            , v(v)
        {
        }

        Quaternion(const Vector4D& v)
            : w(v.w)
            , v(v.x, v.y, v.z)
        {
        }

        Quaternion(const Quaternion& q)
            : w(q.w)
            , v(q.v)
        {
        }

        /**********************************************************************
		****************Quaternion inline function definitions*****************
		**********************************************************************/

        inline Quaternion& SetIdentity()
        {
            w = 1.0f;
            v.x = v.y = v.z = 0.0f;
            return *this;
        }

        inline Quaternion& operator+=(const Quaternion& q)
        {
            this->w += q.w;
            this->v += q.v;
            return *this;
        }

        inline Quaternion& operator-=(const Quaternion& q)
        {
            this->w -= q.w;
            this->v -= q.v;
            return *this;
        }

        inline Quaternion& operator*=(const Quaternion& q)
        {
            *this = *this * q;
            return *this;
        }
		
		inline Quaternion& operator*=(const float& scalar)
        {
            *this = *this * scalar;
            return *this;
        }

        inline Quaternion operator+(const Quaternion& q) const
        {
            return Quaternion(w + q.w, v + q.v);
        }

        inline Quaternion operator-(const Quaternion& q) const
        {
            return Quaternion(w - q.w, v - q.v);
        }

        inline Quaternion operator*(const Quaternion& q2) const
        {
            return Quaternion(
                w * q2.w - v.x * q2.v.x - v.y * q2.v.y - v.z * q2.v.z,
                Vector3D(w * q2.v.x + v.x * q2.w + v.y * q2.v.z - v.z * q2.v.y,
                    w * q2.v.y + v.y * q2.w + v.z * q2.v.x - v.x * q2.v.z,
                    w * q2.v.z + v.z * q2.w + v.x * q2.v.y - v.y * q2.v.x));
        }

        inline Quaternion operator*(const float& scalar) const
        {
            return Quaternion(w * scalar, v * scalar);
        }

        inline bool operator==(const Quaternion& q) const
        {
            return w == q.w && v == q.v;
        }

        inline bool operator!=(const Quaternion& q) const
        {
            return w != q.w || v != q.v;
        }

        inline float Magnitude() const
        {
            return sqrt(w * w) + v.Magnitude();
        }

        // Can be further optimized
        /*inline Quaternion& Normalize()
        {
            float magnitude = Magnitude();

            if (magnitude > 0.0f) {
                float inverseMag = 1.0f / Magnitude();
                this =* inverseMag;
				return *this;
            } else {
                assert(false);
                SetIdentity();
            }
        }*/

        // Can be further optimized
        inline Quaternion Inverse() const
        {
            Quaternion conjugate(w, Vector3D(-(v.x), -(v.y), -(v.z)));

            float inverseMag = 1.0f / Magnitude();

            return Quaternion(conjugate * inverseMag);
        }

        inline Quaternion& Conjugated()
        {
            v.x = -v.x;
            v.y = -v.y;
            v.z = -v.z;
            return *this;
        }

        inline float DotProduct(const Quaternion& q1, const Quaternion& q2) const
        {
            return q1.w * q2.w + q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z;
        }

        inline Quaternion& Exp(const float scalar)
        {
            if (fabs(w) < .9999f) {
                float alpha = ACos(w);
                float newAlpha = scalar * alpha;
                float mult = Sin(newAlpha) / Sin(alpha);

                Quaternion result;

                result.w = Cos(newAlpha);
                result.v.x = v.x * mult;
                result.v.y = v.y * mult;
                result.v.z = v.z * mult;

                return result;
            }

            return *this;
        }

        inline Quaternion& Slerp(Quaternion& q1, float injectParam)
        {
            // If interpolation parameter/injectParam is out of bounds, return edge points.
            if (injectParam <= 0.0f)
                return *this;
            if (injectParam >= 1.0f)
                return q1;

            float cosAngle = DotProduct(*this, q1);

            if (cosAngle < 0.0f) {
                q1.w = -q1.w;
                q1.v.x = -q1.v.x;
                q1.v.y = -q1.v.y;
                q1.v.z = -q1.v.z;
                cosAngle = -cosAngle;
            }

            float k0, k1 = 0.0f;
            if (cosAngle > 0.9999f) {
                k0 = 1.0f - injectParam;
                k1 = injectParam;
            } else {
                float sinAngle = sqrt(1.0f - cosAngle * cosAngle);
                float angle = atan2(sinAngle, cosAngle);
                float invSinAngle = 1.0f / sinAngle;

                k0 = Sin((1.0f - injectParam) * angle) * invSinAngle;
                k1 = Sin(injectParam * angle) * invSinAngle;
            }

            // Interpolate
            Quaternion result;
            result.w = w * k0 + q1.w * k1;
            result.v.x = v.x * k0 + q1.v.x * k1;
            result.v.y = v.y * k0 + q1.v.y * k1;
            result.v.z = v.z * k0 + q1.v.z * k1;

            return result;
        }

        inline Quaternion MatToQuat(const Mat4x4& m)
        {
            float wAbsVal = m(0, 0) + m(1, 1) + m(2, 2);
            float xAbsVal = m(0, 0) - m(1, 1) - m(2, 2);
            float yAbsVal = -m(0, 0) + m(1, 1) - m(2, 2);
            float zAbsVal = -m(0, 0) - m(1, 1) + m(2, 2);

            int biggestComp = 0;
            float biggestAbsVal = wAbsVal;
            if (xAbsVal > biggestAbsVal) {
                biggestAbsVal = xAbsVal;
                biggestComp   = 1;
            }
            if (yAbsVal > biggestAbsVal) {
                biggestAbsVal = yAbsVal;
                biggestComp   = 2;
            }
            if (zAbsVal > biggestAbsVal) {
                biggestAbsVal = zAbsVal;
                biggestComp   = 3;
            }

            float biggestVal = sqrt(biggestAbsVal + 1.0f) * 0.5f;
            float multComp   = 0.25f / biggestVal;

            Quaternion result;

            switch (biggestComp) {
            case 0:
                result.w   = biggestVal;
                result.v.x = m(1, 2) - m(2, 1) * multComp;
                result.v.y = m(2, 0) - m(0, 2) * multComp;
                result.v.z = m(0, 1) - m(1, 0) * multComp;
                break;
            case 1:
                result.v.x = biggestVal;
                result.w   = m(1, 2) - m(2, 1) * multComp;
                result.v.y = m(0, 1) + m(1, 0) * multComp;
                result.v.z = m(2, 0) + m(0, 2) * multComp;
                break;
            case 2:
                result.v.y = biggestVal;
                result.w   = m(2, 0) - m(0, 2) * multComp;
                result.v.x = m(0, 1) + m(1, 0) * multComp;
                result.v.z = m(1, 2) + m(2, 1) * multComp;
                break;
            case 3:
                result.v.z = biggestVal;
                result.w   = m(0, 1) - m(1, 0) * multComp;
                result.v.x = m(2, 0) + m(0, 2) * multComp;
                result.v.y = m(1, 2) + m(2, 1) * multComp;
                break;
            }

            return result;

			//Alternative method
			//This code was adapted from a Euclideanspace article.
			//See more: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
            /*float trace = m[0][0] + m[1][1] + m[2][2];
            if (trace > 0.0f) {
                float s = 0.5f / sqrtf(trace + 1.0f);
                q.w = 0.25f / s;
                q.x = (m[2][1] - m[1][2]) * s;
                q.y = (m[0][2] - m[2][0]) * s;
                q.z = (m[1][0] - m[0][1]) * s;
            } else {
                if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
                    float s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
                    q.w = (m[2][1] - m[1][2]) / s;
                    q.x = 0.25f * s;
                    q.y = (m[0][1] + m[1][0]) / s;
                    q.z = (m[0][2] + m[2][0]) / s;
                } else if (m[1][1] > m[2][2]) {
                    float s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
                    q.w = (m[0][2] - m[2][0]) / s;
                    q.x = (m[0][1] + m[1][0]) / s;
                    q.y = 0.25f * s;
                    q.z = (m[1][2] + m[2][1]) / s;
                } else {
                    float s = 2.0f * sqrtf(1.0f + m[2][2] - m[0][0] - m[1][1]);
                    q.w = (m[1][0] - m[0][1]) / s;
                    q.x = (m[0][2] + m[2][0]) / s;
                    q.y = (m[1][2] + m[2][1]) / s;
                    q.z = 0.25f * s;
                }
            }*/
        }
    };
} // end namespace Math
} // end namespace Oblivion