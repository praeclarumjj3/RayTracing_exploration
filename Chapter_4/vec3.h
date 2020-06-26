#include <math.h>
#include <iostream>

using std::sqrt;

class vec3{
    public:
      vec3() {}
      vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

      inline float x() const {return e[0]; }
      inline float y() const {return e[1]; }
      inline float z() const {return e[2]; }
      inline float r() const {return e[0]; }
      inline float g() const {return e[1]; }
      inline float b() const {return e[2]; }

      inline const vec3& operator+() const { return *this; }
      inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
      inline float operator[](int i) const { return e[i]; }
      inline float& operator[](int i){ return e[i]; }

      inline vec3& operator+=(const vec3 &v2);
      inline vec3& operator-=(const vec3 &v2);
      inline vec3& operator*=(const vec3 &v2);
      inline vec3& operator/=(const vec3 &v2);
      inline vec3& operator*=(const float t);
      inline vec3& operator/= (const float t);

      inline float length() const {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }

      inline float length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

      inline void make_unit_vector();

      float e[3];
};

// vec3 Utility Functions

inline void vec3::make_unit_vector(){
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *=k; e[2] *=k;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, float t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3& vec3::operator*=(const vec3 &v) {
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            e[2] *= v.e[2];
            return *this;
        }

inline vec3& vec3::operator/=(const vec3 &v) {
            e[0] /= v.e[0];
            e[1] /= v.e[1];
            e[2] /= v.e[2];
            return *this;
        }

inline vec3& vec3::operator-=(const vec3 &v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
            return *this;
        }
inline vec3& vec3::operator*=(const float t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

inline vec3& vec3::operator/=(const float k) {
            float t = 1.0/k;

            e[0] /= t;
            e[1] /= t;
            e[2] /= t;
            return *this;
        }

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}
