
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

using std::size_t;

namespace sjtu
{
    template <class T> class Matrix {
    private:
        int N, M;
        T* ar;
        
    public:
        size_t rowLength() const {
            return N;
        }
        size_t columnLength() const {
            return M;
        }
        size_t size() const {
            return N * M;
        }
        T& operator() (std::size_t i, std::size_t j) {
            return ar[i * M + j];
        }
        const T& operator()(std::size_t i, std::size_t j) const {
            return ar[i * M + j];
        }
        
//    3.1 INITIALIZATION
    public:
        Matrix() = default;
        Matrix(std::size_t n, std::size_t m, T _init = T()) {
            N = (int)n;
            M = (int)m;
            ar = new T[N * M];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) = _init;
                }
            }
            std::cout << "NEWING ... " << N << " " << M << std::endl;
            print();
        }
        explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()) {
            N = (int)sz.first;
            M = (int)sz.second;
            ar = new T[N * M];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) = _init;
                }
            }
        }
        Matrix(std::initializer_list< std::initializer_list<T> > list) {
            std::cout << "TYPENAME: " << typeid(T).name() << std::endl;
            N = (int)list.size();
            M = (int)list.begin() -> size();
            ar = new T[N * M];
            auto curRow = list.begin();
            for (int i = 0; i < N; i++, curRow++) {
                auto cur = curRow -> begin();
                for (int j = 0; j < M; j++, cur++) {
                    (*this)(i, j) = *cur;
                }
            }
        }
        Matrix(const Matrix &o) {
            N = (int)o.rowLength();
            M = (int)o.columnLength();
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = o.ar[i];
            }
        }
        template <class U> Matrix(const Matrix<U> &o) {
            N = (int)o.rowLength();
            M = (int)o.columnLength();
            ar = new T[N * M];
            for (int i = 0; i < N * M; i++) {
                ar[i] = (T)o.ar[i];
            }
        }
        Matrix &operator = (const Matrix &o) {
            (*this) = Matrix(o);
            return *this;
        }
        template <class U> Matrix &operator = (const Matrix<U> &o) {
            (*this) = Matrix(o);
            return *this;
        }
        Matrix(Matrix &&o) noexcept {
            N = o.N;
            M = o.M;
            delete [] ar;
            ar = o.ar;
        }
        Matrix &operator = (Matrix &&o) noexcept {
            N = o.N;
            M = o.M;
            delete [] ar;
            ar = o.ar;
            return *this;
        }
        ~Matrix() {
            std::cout << "TRYING TO DESTROY ... " << N << " " << M << std::endl;
            print();
            if (ar != NULL) {
                delete [] ar;
                ar = NULL;
            }
        }
        
//        3.2 GETTING ELEMENT
    public:
        Matrix<T> row(std::size_t i) const {
            Matrix<T> ret = Matrix<T>(1, M);
            for (int j = 0; j < M; j++) {
                ret(0, j) = ar((int)i, j);
            }
            return ret;
        }
        Matrix<T> column(std::size_t j) const {
            Matrix<T> ret = Matrix<T>(N, 1);
            for (int i = 0; i < N; i++) {
                ret(i, 0) = ar(i, (int)j);
            }
            return ret;
        }
        
        
//        3.3.1 UNARY OPERATORS
    public:
        Matrix operator - () const {
            Matrix<T> ret = Matrix<T>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(i, j) = -(*this)(i, j);
                }
            }
            return ret;
        }
        template <class U> Matrix& operator += (const Matrix<U> b) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) += (T)b(i, j);                }
            }
            return *this;
        }
        template <class U> Matrix& operator -= (const Matrix<U> b) {
            return *this += (-b);
        }
        template <class U> Matrix& operator *= (U b) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) *= (T)b;
                }
            }
            return *this;
        }
        Matrix trans() const {
            Matrix<T> ret = Matrix<T>(M, N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(j, i) = (*this)(i, j);
                }
            }
            return ret;
        }
        
//        3.3.2 BINARY OPERATORS
    public:
        template <class U> bool operator == (const Matrix<U> b) {
            if (N != b.N || M != b.M) return false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if ((double)ar(i, j) != (double)b(i, j)) return false;
                }
            }
            return true;
        }
        template <class U> bool operator != (const Matrix<U> b) {
            return !((*this) == b);
        }
        template <class U> Matrix<decltype(T() + U())> operator + (const Matrix<U> &b) const {
            assert(N == b.rowCnt() && M == b.columnCnt());
            Matrix<decltype(T() + U())> ret = Matrix<decltype(T() + U())>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(i, j) = (*this)(i, j) + b(i, j);
                }
            }
            return ret;
        }
        template <class U> Matrix<decltype(T() + U())> operator - (const Matrix<U> &b) const {
            return (*this) + (-b);
        }
        template <class U> Matrix<decltype(T() * U())> operator * (const U b) const {
            Matrix<decltype(T() * U())> ret = Matrix<decltype(T() * U())>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(i, j) = (*this)(i, j) * b(i, j);
                }
            }
            return ret;
        }
        template <class U> Matrix<decltype(T() * U())> operator * (const Matrix<U> &b) const {
            assert(M == b.rowLength());
            Matrix<decltype(T() * U())> ret = Matrix<decltype(T() * U())>(N, b.columnLength());
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < b.columnLength(); j++) {
                    for (int k = 0; k < M; k++) {
                        ret(i, j) += (*this)(i, k) * b(k, j);
                    }
                }
            }
            return ret;
        }
        
//        3.5 OTHERS
    public:
        void resize(std::size_t n, std::size_t m, T _init = T()) {
            if (M * N < n * m) {
                T* b = new T[n * m];
                for (int i = 0; i < M * N; i++) {
                    b[i] = ar[i];
                }
                for (int i = M * N; i < n * m; i++) {
                    b[i] = _init;
                }
                delete [] ar;
                ar = b;
            }
            N = (int)n;
            M = (int)m;
        }
        void resize(std::pair<std::size_t, std::size_t> sz, T _init = T()) {
            resize(sz.first, sz.second, _init);
        }
        
//        UTILITY
        void print() {
            std::cout << "{";
            for (int i = 0; i < N; i++) {
                std::cout << "{" ;
                for (int j = 0; j < M; j++) {
                    std::cout << (*this)(i, j) << (j == M-1 ? "": ",");
                }
                std::cout << "}" << (i == N-1 ? "}" : ",")  << std::endl;
            }
            std::cout << std::endl;
        }
    };
    
}

#endif //SJTU_MATRIX_HPP

