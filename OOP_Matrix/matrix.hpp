//                                    //==\\
//                                   /.....|
//                                  |......|
//                                  |......|         ==\
//     //=...\\\=......=========    |...../       /....\|
//   //........\\................===\\..//       /......|
// //...........||......./===\........\\\\      |......|
// ||.@@.........|.....//     \\..........\\\  |....../
// |........@@..||.....|   @@  |.//   \\\....=\|\...//
// ||.........../......\\  @  //||      ||.......\\\
//  \\........//.........\===/..||  @@@ ||..........\\
//    \\====//...................\\\ =///............\\
//       \\\...........................................\\
//         \\\..........................................\\
//            \\\\..............................!!!!!....|
//                ||..........................!!!!!!!!!..||
//                |..........................!!!!!!!!!!!..|
//                |....|.....................!!!!!!!!!!!..|
//                |..........................!!!!!!!!!!...|
//                ||....\\....................!!!!!!!....||
//                 |......\\........../..................|
//                 \\.......\======/....................//
//                  \\.................................//
//                    \\.............................//
//                     \\...........................//
//                       \\\.....................///
//                          \\\=.............=///
//                               ===========


#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <cassert>
#include <stdexcept>
#include <iostream>

using std::size_t;

namespace sjtu
{
    
    template <class T>
    class Matrix
    {
    private:
        // your private member variables here.
        int N, M;
        T* ar;
        
    public:
        Matrix(size_t n = 1, size_t m = 1, T _init = T())
        {
            N = (int)n;
            M = (int)m;
            ar = new T[N * M];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) = _init;
                }
            }
        }
        
        explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
        {
            N = (int)sz.first;
            M = (int)sz.second;
            ar = new T[N * M];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) = _init;
                }
            }
        }
        
        Matrix(const Matrix &o)
        {
            N = (int)o.rowLength();
            M = (int)o.columnLength();
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = o.element(i);
            }
        }
        
        template <typename U>
        Matrix(const Matrix<U> &o)
        {
            N = (int)o.rowLength();
            M = (int)o.columnLength();
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = (T)o.element(i);
            }
        }
        
        Matrix &operator=(const Matrix &o)
        {
            if (this == &o) return *this;
            N = o.N;
            M = o.M;
            if (ar != nullptr) delete [] ar;
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = o.element(i);
            }
            return *this;
        }
        
        template <typename U>
        Matrix &operator=(const Matrix<U> &o)
        {
            N = (int)o.rowLength();
            M = (int)o.columnLength();
            if (ar != nullptr) delete [] ar;
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = o.element(i);
            }
            return *this;
        }
        
        Matrix(Matrix &&o)
        {
            N = o.N;
            M = o.M;
            ar = o.ar;
            o.ar = nullptr;
        }
        
        Matrix &operator=(Matrix &&o)
        {
            N = o.N;
            M = o.M;
            if (ar == o.ar) return *this;
            if (ar != nullptr) delete [] ar;
            ar = o.ar;
            o.ar = nullptr;
            return *this;
        }
        
        ~Matrix() {
            if (N || M) delete [] ar;
        }
        
        Matrix(const std::initializer_list<std::initializer_list<T>> &list)
        {
            if (list.size() == 0) {
                throw std::invalid_argument("init");
            }
            N = (int)list.size();
            M = (int)list.begin() -> size();
            if (N && M) ar = new T[N * M];
            auto curRow = list.begin();
            for (int i = 0; i < N; i++, curRow++) {
                auto cur = curRow -> begin();
                if (curRow -> size() != M) {
                    delete [] ar;
                    throw std::invalid_argument("init");
                }
                for (int j = 0; j < M; j++, cur++) {
                    (*this)(i, j) = *cur;
                }
            }
        }
        
    public:
        size_t rowLength() const { return N; }
        
        size_t columnLength() const { return M; }
        
        void resize(size_t n, size_t m, T _init = T())
        {
            if (M * N != n * m) {
                T* tmp = ar;
                ar = new T[n * m];
                if (M * N < n * m) {
                    for (int i = 0; i < M * N; i++) {
                        ar[i] = tmp[i];
                    }
                    for (int i = M * N; i < n * m; i++) {
                        ar[i] = _init;
                    }
                } else {
                    for (int i = 0; i < n * m; i++) {
                        ar[i] = tmp[i];
                    }
                }
                delete [] tmp;
            }
            N = (int)n;
            M = (int)m;
        }
        
        void resize(std::pair<size_t, size_t> sz, T _init = T())
        {
            resize(sz.first, sz.second, _init);
        }
        
        std::pair<size_t, size_t> size() const
        {
            return {N, M};
        }
        
        void clear()
        {
            if (M || N) delete [] ar;
            N = 0;
            M = 0;
        }
        
    public:
        T& element(int i) {
            return ar[i];
        }
        const T& element(int i) const {
            return ar[i];
        }
        T& operator() (int i, int j) {
            if (i < 0 || i >= N || j < 0 || j >= M) {
                throw std::invalid_argument("foot");
            }
            return ar[i * M + j];
        }
        const T& operator()(int i, int j) const {
            if (i < 0 || i >= N || j < 0 || j >= M) {
                throw std::invalid_argument("foot");
            }
            return ar[i * M + j];
        }
        
        Matrix<T> row(size_t i) const
        {
            if (i < 0 || i >= N) {
                throw std::invalid_argument("row");
            }
            Matrix<T> ret(1, M);
            for (int j = 0; j < M; j++) {
                ret(0, j) = (*this)((int)i, j);
            }
            return ret;
        }
        
        Matrix<T> column(size_t j) const
        {
            if (j < 0 || j >= M) {
                throw std::invalid_argument("col");
            }
            Matrix<T> ret(N, 1);
            for (int i = 0; i < N; i++) {
                ret(i, 0) = (*this)(i, (int)j);
            }
            return ret;
        }
        
        
    public:
        bool operator==(const Matrix &b) const
        {
            if (N != b.rowLength() || M != b.columnLength()) return false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if ((*this)(i, j) != b(i, j)) return false;
                }
            }
            return true;
        }
        
        bool operator!=(const Matrix &b) const
        {
            return !((*this) == b);
        }
        
        Matrix operator-() const
        {
            Matrix<T> ret(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(i, j) = -(*this)(i, j);
                }
            }
            return ret;
        }
        
        template <typename U>
        Matrix operator+=(const Matrix<U> &b)
        {
            if (!(N == b.rowLength() && M == b.columnLength())) {
                throw std::invalid_argument("different size!");
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) += b(i, j);
                }
            }
            return *this;
        }
        
        template <typename U>
        Matrix operator-=(const Matrix<U> &b)
        {
            *this += (-b);
            return *this;
        }
        
        template <typename U>
        Matrix operator*=(const U &b)
        {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) *= b;
                }
            }
            return *this;
        }
        
        Matrix tran() const
        {
            Matrix<T> ret(M, N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(j, i) = (*this)(i, j);
                }
            }
            return ret;
        }
        
    public: // iterator
        class iterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = T;
            using pointer           = T *;
            using reference         = T &;
            using size_type         = size_t;
            using difference_type   = std::ptrdiff_t;
            
            iterator() = default;
            
            iterator(const iterator &) = default;
            
            iterator &operator=(const iterator &) = default;
            
            iterator(pointer _p, size_type _cx, size_type _cy, size_type _dy, size_type _yy): p(_p), cx(_cx), cy(_cy), dy(_dy), yy(_yy) {
                
            }
            
        private:
            pointer p;
            size_type cx, cy, lx, ly, dy, yy;
            
        public:
            void print(){
                std::cout << cx << " " << cy << " " << dy << " " << yy << std::endl;
            }
            difference_type operator-(const iterator &o)
            {
                return (cx - o.cx) * dy + cy - o.cy;
            }
            
            iterator &operator+=(difference_type offset)
            {
                size_type ns = cx * dy + cy + offset;
                if (!(ns >= 0)) {
                    throw std::invalid_argument("ns < 0");
                }
                size_type _cx = ns / dy;
                size_type _cy = ns % dy;
                p += (_cx - cx) * yy + (_cy - cy);
                cx = _cx;
                cy = _cy;
                return *this;
            }
            iterator operator+(difference_type offset) const
            {
                size_type ns = cx * dy + cy + offset;
                if (!(ns >= 0)) {
                    throw std::invalid_argument("ns < 0");
                }
                size_type _cx = ns / dy;
                size_type _cy = ns % dy;
                return iterator(p + (_cx - cx) * yy + (_cy - cy), _cx, _cy, dy, yy);
            }
            iterator &operator-=(difference_type offset)
            {
                (*this) += (-offset);
                return *this;
            }
            iterator operator-(difference_type offset) const
            {
                return (*this) + (-offset);
            }
            iterator &operator++()
            {
                (*this) += 1;
                return *this;
            }
            iterator operator++(int)
            {
                return (*this) + 1;
            }
            iterator &operator--()
            {
                (*this) -= 1;
                return *this;
            }
            
            iterator operator--(int)
            {
                return (*this) - 1;
            }
            
            reference operator*() const
            {
                return *p;
            }
            
            pointer operator->() const
            {
                return p;
            }
            
            bool operator==(const iterator &o) const
            {
                return p == o.p && cx == o.cx && cy == o.cy && dy == o.dy && yy == o.yy;
            }
            
            bool operator!=(const iterator &o) const
            {
                return !((*this) == o);
            }
        };
        
        iterator iterAtPos(int i, int j) {
            return iterator(ar + (i * M + j), i, j, M, M);
        }
        
        iterator begin()
        {
            return iterAtPos(0, 0);
        }
        
        iterator end()
        {
            return iterAtPos(N, 0);
        }
        
        std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
        {
            auto bg = iterator(ar + l.first * M + l.second, 0, 0, r.second - l.second + 1, M);
            auto ed = bg + (r.first - l.first + 1) * (r.second - l.second + 1);
            return {bg, ed};
        }
    };
}

//
namespace sjtu
{
    template <class T, class U>
    Matrix<decltype(U() * T())> operator*(const Matrix<T> &a, const U &x)
    {
        Matrix<decltype(T() * U())> ret(a.rowLength(), a.columnLength());
        for (int i = 0; i < a.rowLength(); i++) {
            for (int j = 0; j < a.columnLength(); j++) {
                ret(i, j) = a(i, j) * x;
            }
        }
        return ret;
    }
    
    template <class T, class U>
    Matrix<decltype(U() * T())> operator*(const U &x, const Matrix<T> &a)
    {
        Matrix<decltype(T() * U())> ret(a.rowLength(), a.columnLength());
        for (int i = 0; i < a.rowLength(); i++) {
            for (int j = 0; j < a.columnLength(); j++) {
                ret(i, j) = a(i, j) * x;
            }
        }
        return ret;
    }
    
    template <class U, class V>
    Matrix<decltype(U() * V())> operator*(const Matrix<U> &a, const Matrix<V> &b)
    {
        if (!(a.columnLength() == b.rowLength())) {
            throw std::invalid_argument("different size!");
        }
        Matrix<decltype(U() * V())> ret(a.rowLength(), b.columnLength());
        for (int i = 0; i < a.rowLength(); i++) {
            for (int j = 0; j < b.columnLength(); j++) {
                for (int k = 0; k < a.columnLength(); k++) {
                    ret(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return ret;
    }
    
    template <class U, class V>
    Matrix<decltype(U() + V())> operator+(const Matrix<U> &a, const Matrix<V> &b)
    {
        if (a.rowLength() != b.rowLength() || a.columnLength() != b.columnLength()) {
            throw std::invalid_argument("different size!");
        }
        Matrix<decltype(U() + V())> ret(a.rowLength(), a.columnLength());
        for (int i = 0; i < a.rowLength(); i++) {
            for (int j = 0; j < a.columnLength(); j++) {
                ret(i, j) = a(i, j) + b(i, j);
            }
        }
        return ret;
    }
    
    template <class U, class V>
    Matrix<decltype(U() - V())> operator-(const Matrix<U> &a, const Matrix<V> &b)
    {
        return (a + (-b));
    }
    
}

#endif //SJTU_MATRIX_HPP

