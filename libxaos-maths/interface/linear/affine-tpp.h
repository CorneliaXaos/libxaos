/**
 *  @file affine-tpp.h
 *  @brief Implementations for the affine template namespace.
 */

#include <cmath>
#include <exception>

namespace libxaos {
    namespace linear {
        namespace affine {

            // 2D Scaling
            template<typename T>
            inline Matrix3<T> get2DScaling(T x, T y) {
                return Matrix3<T>{
                    {
                        {   x, T{0}, T{0}},
                        {T{0},    y, T{0}},
                        {T{0}, T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix3<T> get2DScaling(const Vector2<T>& vec) {
                return get2DScaling(vec.x(), vec.y());
            }

            // 3D Scaling
            template<typename T>
            inline Matrix4<T> get3DScaling(T x, T y, T z) {
                return Matrix4<T>{
                    {
                        {   x, T{0}, T{0}, T{0}},
                        {T{0},    y, T{0}, T{0}},
                        {T{0}, T{0},    z, T{0}},
                        {T{0}, T{0}, T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix4<T> get3DScaling(const Vector3<T>& vec) {
                return get3DScaling(vec.x(), vec.y(), vec.z());
            }

            // 2D Rotation
            template<typename T>
            inline Matrix3<T> get2DRotation(T theta) {
                T cosTheta = T{std::cos(theta)};
                T sinTheta = T{std::sin(theta)};
                return Matrix3<T>{
                    {
                        {cosTheta, -sinTheta, T{0}},
                        {sinTheta,  cosTheta, T{0}},
                        {    T{0},      T{0}, T{1}}
                    }
                };
            }

            // 2D Rotation Onto
            template<typename T>
            inline Matrix3<T> get2DRotationOnto(const Vector2<T>& source,
                    const Vector2<T>& target) {
                T dotST = dot(source, target);
                T detST = source.x() * target.y() - source.y() * target.x();
                T theta = std::atan2(detST, dotST);
                return get2DRotation(theta);
            }

            // 3D Rotation
            template<typename T>
            inline Matrix4<T> get3DRotationX(T theta) {
                T cosTheta = T{std::cos(theta)};
                T sinTheta = T{std::sin(theta)};
                return Matrix4<T>{
                    {
                        {T{1},     T{0},      T{0}, T{0}},
                        {T{0}, cosTheta, -sinTheta, T{0}},
                        {T{0}, sinTheta,  cosTheta, T{0}},
                        {T{0},     T{0},      T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix4<T> get3DRotationY(T theta) {
                T cosTheta = T{std::cos(theta)};
                T sinTheta = T{std::sin(theta)};
                return Matrix4<T>{
                    { cosTheta, T{0}, sinTheta, T{0}},
                    {     T{0}, T{1},     T{0}, T{0}},
                    {-sinTheta, T{0}, cosTheta, T{0}},
                    {     T{0}, T{0},     T{0}, T{1}}
                };
            }
            template<typename T>
            inline Matrix4<T> get3DRotationZ(T theta) {
                T cosTheta = T{std::cos(theta)};
                T sinTheta = T{std::sin(theta)};
                return Matrix4<T>{
                    {
                        {cosTheta, -sinTheta, T{0}, T{0}},
                        {sinTheta,  cosTheta, T{0}, T{0}},
                        {    T{0},      T{0}, T{1}, T{0}},
                        {    T{0},      T{0}, T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix4<T> get3DRotation(T thetaX, T thetaY, T thetaZ) {
                Matrix4<T> ret {Matrix4<T>::IDENTITY};
                if (thetaZ > T{0} || thetaZ < T{0})
                    ret *= get3DRotationZ(thetaZ);
                if (thetaY > T{0} || thetaY < T{0})
                    ret *= get3DRotationY(thetaY);
                if (thetaX > T{0} || thetaX < T{0})
                    ret *= get3DRotationX(thetaX);
                return ret;
            }

            template<typename T>
            inline Matrix4<T> get3DRotation(const Vector3<T>& vec) {
                return get3DRotation(vec.x(), vec.y(), vec.z());
            }

            // 3D Rotation Onto.  Source from:
            // http://math.stackexchange.com/a/476311
            template<typename T>
            Matrix4<T> get3DRotationOnto(const Vector3<T>& source,
                    const Vector3<T>& target) {
                auto sourceNormalized = getNormalized(source);
                auto targetNormalized = getNormalized(target);

                auto crossST = cross(source, target);
                T dotST = T{dot(source, target)};

                Matrix4<T> ret {Matrix4<T>::IDENTITY};
                if (source == target) {
                    return ret;
                } else if (source == -target) {
                    // First calculate a vector perpendicular to source
                    // Sourced from: http://math.stackexchange.com/a/413235
                    Vector3<T> perp {};
                    int m = 0, n = 0;
                    if (source.x() < T{0.0001}) {
                        m = 0; n = 1;
                    } else if (source.y() < T{0.0001}) {
                        m = 1; n = 2;
                    } else {
                        m = 2; n = 0;
                    }
                    perp[n] =  source[m];
                    perp[m] = -source[n];
                    normalize(perp);

                    // Now, calculate a matrix that rotates around perp by PI
                    return get3DRotationArbitrary(T{std::acos(-1)}, perp);
                }

                Matrix4<T> Vx {
                    {
                        {        T{0}, -crossST.z(),  crossST.y(), T{0}},
                        { crossST.z(),         T{0}, -crossST.x(), T{0}},
                        {-crossST.y(),  crossST.x(),         T{0}, T{0}},
                        {        T{0},         T{0},         T{0}, T{0}}
                    }
                };

                return ret + Vx + (Vx * Vx) * (T{1} / (T{1} + dotST));
            }

            // 3D Rotation Arbitrary.  Sourced from:
            // http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
            template<typename T>
            Matrix4<T> get3DRotationArbitrary(T theta,
                    const Vector3<T>& axis) {
                auto normalized = getNormalized(axis);
                T cosTheta = T{std::cos(theta)};
                T sinTheta = T{std::sin(theta)};
                T cosThetaI = T{1} - cosTheta;

                T u = T{normalized.x()};
                T v = T{normalized.y()};
                T w = T{normalized.z()};

                T u2 = T{u * u};
                T v2 = T{v * v};
                T w2 = T{w * w};

                T u2I = T{1} - u2;
                T v2I = T{1} - v2;
                T w2I = T{1} - w2;
                return Matrix4<T>{
                    {
                        {         u2+u2I*cosTheta, u*v*cosThetaI-w*sinTheta, u*w*cosThetaI+v*sinTheta, T{0}},
                        {u*v*cosThetaI+w*sinTheta,          v2+v2I*cosTheta, v*w*cosThetaI-u*sinTheta, T{0}},
                        {u*w*cosThetaI-v*sinTheta, v*w*cosThetaI+u*sinTheta,          w2+w2I*cosTheta, T{0}},
                        {                    T{0},                     T{0},                     T{0}, T{1}}
                    }
                };
            }

            // 2D Translation
            template<typename T>
            inline Matrix3<T> get2DTranslation(T x, T y) {
                return Matrix3<T>{
                    {
                        {T{1}, T{0},    x},
                        {T{0}, T{1},    y},
                        {T{0}, T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix3<T> get2DTranslation(const Vector2<T>& vec) {
                return get2DTranslation(vec.x(), vec.y());
            }

            // 3D Translation
            template<typename T>
            inline Matrix4<T> get3DTranslation(T x, T y, T z) {
                return Matrix4<T>{
                    {
                        {T{1}, T{0}, T{0},    x},
                        {T{0}, T{1}, T{0},    y},
                        {T{0}, T{0}, T{1},    z},
                        {T{0}, T{0}, T{0}, T{1}}
                    }
                };
            }
            template<typename T>
            inline Matrix4<T> get3DTranslation(const Vector3<T>& vec) {
                return get3DTranslation(vec.x(), vec.y(), vec.z());
            }

        }
    }
}
