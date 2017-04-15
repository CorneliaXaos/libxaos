/**
 *  @file SSEType-tpp.h
 *  @brief Common implementations for the SSEType template class.
 */

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace libxaos {
    namespace sse {

        // Default constructor redirects to expansion constructor
        template<typename T>
        SSEType<T>::SSEType() : SSEType<T>{T{0}} {}
        template<typename T>
        SSEType<T>::SSEType(T val) {
            for (unsigned int i = 0; i < SSEType<T>::MEMBER_COUNT; i++) {
                _data[i] = val;
            }
        }
        template<typename T>
        SSEType<T>::SSEType(std::initializer_list<T> values) {
            unsigned int index = 0;
            for (auto it = values.begin(); it < values.end(); it++) {
                _data[index++] = *it;
                if (index >= SSEType<T>::MEMBER_COUNT)
                    break;
            }
        }

        template<typename T>
        SSEType<T>::SSEType(const SSEType<T>& other) {
            std::copy(std::begin(other._data), std::end(other._data),
                    std::begin(_data));
        }
        template<typename T>
        SSEType<T>& SSEType<T>::operator=(const SSEType<T>& other) {
            if (this != &other) {
                std::copy(std::begin(other._data), std::end(other._data),
                        std::begin(_data));
            }
            return *this;
        }
        template<typename T>
        SSEType<T>::SSEType(SSEType<T>&& other) {
            std::copy(std::begin(other._data), std::end(other._data),
                    std::begin(_data));
        }
        template<typename T>
        SSEType<T>& SSEType<T>::operator=(SSEType<T>&& other) {
            if (this != &other) {
                std::copy(std::begin(other._data), std::end(other._data),
                        std::begin(_data));
            }
            return *this;
        }

        // The Accessors are the only other common functions.
        // All the others need to be custom defined per intrinsic type.
        template<typename T>
        inline T& SSEType<T>::operator[](unsigned int index) {
            assert(index < SSEType<T>::MEMBER_COUNT);
            return _data[index];
        }
        template<typename T>
        inline const T& SSEType<T>::operator[](unsigned int index) const {
            assert(index < SSEType<T>::MEMBER_COUNT);
            return _data[index];
        }

        template<typename T>
        inline T& SSEType<T>::at(unsigned int index) {
            if (index >= SSEType<T>::MEMBER_COUNT)
                throw std::out_of_range{"Index out of range for SSEType."};
            return _data[index];
        }
        template<typename T>
        inline const T& SSEType<T>::at(unsigned int index) const {
            if (index >= SSEType<T>::MEMBER_COUNT)
                throw std::out_of_range{"Index out of range for SSEType."};
            return _data[index];
        }

        // Inequality
        template<typename T>
        inline bool operator!=(const SSEType<T>& a, const SSEType<T>& b) {
            return !(a == b);
        }

        // Addition
        template<typename T>
        inline SSEType<T> operator+(const SSEType<T>& a, const SSEType<T>& b) {
            SSEType<T> ret = a;
            return ret += b;
        }

        // Subtraction
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>& a, const SSEType<T>& b) {
            SSEType<T> ret = a;
            return ret -= b;
        }

        // Multiplication
        template<typename T>
        inline SSEType<T> operator*(const SSEType<T>& a, const SSEType<T>& b) {
            SSEType<T> ret = a;
            return ret *= b;
        }

        // Division
        template<typename T>
        inline SSEType<T> operator/(const SSEType<T>& a, const SSEType<T>& b) {
            SSEType<T> ret = a;
            return ret /= b;
        }
    }
}
