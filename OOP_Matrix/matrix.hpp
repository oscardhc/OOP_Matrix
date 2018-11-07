#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{
    
    template <class T> class Array {
    public:
        int N, M, sz;
        T* a;
        Array() {
            
        }
        Array(int n, int m) {
            N = n;
            M = m;
            sz = N * M;
            a = (T*)malloc(N * M * sizeof(T));
        }
        T& operator() (int i, int j) {
            return a[i * M + j];
        }
        const T& operator() (int i, int j) const {
            return a[i * M + j];
        }
        void resize(int n, int m) {
            N = n;
            M = m;
        }
        void print(){
            for (int i = 0; i < sz; i++) {
                std::cout << a[i] << " ";
            }
            std::cout << std::endl << std::endl;
        }
        
    };
    
    template <class T> class Matrix {
    private:
        int N, M;
        Array<T> ar;
        void initMat() {
            
        }
        void freeSpace() {
        }
    
    public:
        T& operator() (std::size_t i, std::size_t j) {
            return ar((int)i, (int)j);
        }
        const T& operator()(std::size_t i, std::size_t j) const {
            return ar((int)i, (int)j);
        }
        
//    3.1 INITIALIZATION
    public:
        Matrix() {
            
        }
        Matrix(std::size_t n, std::size_t m, T init = T()) {
            N = (int)n;
            M = (int)m;
            ar = Array<T>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) = init;
                }
            }
        }
        Matrix(std::initializer_list< std::initializer_list<T> > list) {
            std::cout << "TYPENAME: " << typeid(T).name() << std::endl;
            N = (int)list.size();
            M = (int)list.begin() -> size();
            ar = Array<T>(N, M);
            auto curRow = list.begin();
            for (int i = 0; i < N; i++, curRow++) {
                auto cur = curRow -> begin();
                for (int j = 0; j < M; j++, cur++) {
                    (*this)(i, j) = *cur;
                }
            }
            ar.print();
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
                    (*this)(i, j) += (T)b(i, j);
//                     += (T)b(i,j);
                }
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
            return (*this) != b;
        }
        template <class U> Matrix operator - (const Matrix<U> b) {
            Matrix<T> ret = (*this);
            return ret -= b;
        }
        
//        3.5 OTHERS
    public:
        void resize(std::size_t n, std::size_t m, T _init = T()) {
            N = (int)n;
            M = (int)m;
            if(ar.sz < n * m) {
                Array<T> b = Array<T>(N, M);
                for (int i = 0; i < ar.sz; i++) {
                    b.a[i] = ar.a[i];
                }
                for (int i = ar.sz; i < b.sz; i++) {
                    b.a[i] = _init;
                }
                free(ar.a);
                ar = b;
            }
        }
        
//        UTILITY
        void print() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    std::cout << ar(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}

#endif //SJTU_MATRIX_HPP

