#ifndef     LIBXAOS_MATHS_AFFINE_H
#define     LIBXAOS_MATHS_AFFINE_H

#include "Matrix.h"
#include "Vector.h"

namespace libxaos {
    namespace maths {

        /**
         *  @brief Contains methods for producing 2D and 3D affine transforms.
         *
         *  Contains helper methods for producing scale, rotation, and
         *  translation transformations in two and three dimensions.  All
         *  matrices are in homogenous coordinates.
         */
        namespace affine {

            namespace {
                template<typename T>
                using Matrix3 = libxaos::maths::Matrix<T, 3, 3>;
                template<typename T>
                using Matrix4 = libxaos::maths::Matrix<T, 4, 4>;

                template<typename T>
                using Vector2 = libxaos::maths::Vector<T, 2>;
                template<typename T>
                using Vector3 = libxaos::maths::Vector<T, 3>;
            }

            //! 2D Scaling
            template<typename T>
            Matrix3<T> get2DScaling(T, T);
            template<typename T>
            Matrix3<T> get2DScaling(Vector2<T>);
            //! 3D Scaling
            template<typename T>
            Matrix4<T> get3DScaling(T, T, T);
            template<typename T>
            Matrix4<T> get3DScaling(const Vector3<T>&);

            //! 2D Rotation around the only possible axis
            template<typename T>
            Matrix3<T> get2DRotation(T);
            //! 2D Rotation of a Vector2 onto another Vector2
            template<typename T>
            Matrix3<T> get2DRotationOnto(const Vector2<T>&, const Vector2<T>&);
            //! 3D Rotation around coordinate axes: zRot * yRot * xRot = rot
            template<typename T>
            Matrix4<T> get3DRotation(T, T, T);
            template<typename T>
            Matrix4<T> get3DRotation(const Vector3<T>&);
            //! 3D Rotation of a Vector3 onto a Vector3
            template<typename T>
            Matrix4<T> get3DRotationOnto(const Vector3<T>&, const Vector3<T>&);
            //! 3D Rotation around an arbitrary axis vector
            template<typename T>
            Matrix4<T> get3DRotationArbitrary(T, const Vector3<T>&);

            //! 2D Translation
            template<typename T>
            Matrix3<T> get2DTranslation(T, T);
            template<typename T>
            Matrix3<T> get2DTranslation(const Vector2<T>&);
            //! 3D Translation
            template<typename T>
            Matrix4<T> get3DTranslation(T, T, T);
            template<typename T>
            Matrix4<T> get3DTranslation(const Vector3<T>&);

        }
    }
}

// pull in implementations
#include "affine-tpp.h"

#endif   // LIBXAOS_MATHS_AFFINE_H
