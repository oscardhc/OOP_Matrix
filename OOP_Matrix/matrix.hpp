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
        T& element(int i, int j) {
            return a[i * M + j];
        }
        const T& element(int i, int j) const {
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
        Array<T> a;
        void initMat() {
            
        }
        void freeSpace() {
        }
    
//    3.1 INITIALIZATION
    public:
        Matrix() {
            
        }
        Matrix(std::size_t n, std::size_t m, T init = T()) {
            N = (int)n;
            M = (int)m;
            a = Array<T>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    a.element(i, j) = init;
                }
            }
        }
        Matrix(std::initializer_list< std::initializer_list<T> > list) {
            std::cout << "TYPENAME: " << typeid(T).name() << std::endl;
            N = (int)list.size();
            M = (int)list.begin() -> size();
            a = Array<T>(N, M);
            auto curRow = list.begin();
            for (int i = 0; i < N; i++, curRow++) {
                auto cur = curRow -> begin();
                for (int j = 0; j < M; j++, cur++) {
                    a.element(i, j) = *cur;
                }
            }
            a.print();
        }
        
//        3.2 GETTING ELEMENT
    public:
        T& operator() (std::size_t i, std::size_t j) {
            return a.element((int)i, (int)j);
        }
        const T& operator()(std::size_t i, std::size_t j) const {
            return a.element((int)i, (int)j);
        }
        Matrix<T> row(std::size_t i) const {
            Matrix<T> ret = Matrix<T>(1, M);
            for (int j = 0; j < M; j++) {
                ret(0, j) = a.element((int)i, j);
            }
            return ret;
        }
        Matrix<T> column(std::size_t j) const {
            Matrix<T> ret = Matrix<T>(N, 1);
            for (int i = 0; i < N; i++) {
                ret(i, 0) = a.element(i, (int)j);
            }
            return ret;
        }
        
        
//        3.3.1 UNARY OPERATORS
    public:
        Matrix operator - () const {
            Matrix<T> ret = Matrix<T>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret.a.element(i, j) = -a.element(i, j);
                }
            }
            return ret;
        }
        template <class U> Matrix& operator -= (const Matrix<U> b) {
            Matrix<double> ret = Matrix<double>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    a.element(i, j) -= (T)b(i, j);
                    ret.a.element(i, j) = a.element(i, j);
                }
            }
            return ret;
        }
        
//        3.3.2 BINARY OPERATORS
    public:
        
        
//        3.5 OTHERS
    public:
        void resize(std::size_t n, std::size_t m, T _init = T()) {
            N = (int)n;
            M = (int)m;
            if(a.sz < n * m) {
                Array<T> b = Array<T>(N, M);
                for (int i = 0; i < a.sz; i++) {
                    b.a[i] = a.a[i];
                }
                for (int i = a.sz; i < b.sz; i++) {
                    b.a[i] = _init;
                }
                free(a.a);
                a = b;
            }
        }
        
//        UTILITY
        void print() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    std::cout << a.element(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}

#endif //SJTU_MATRIX_HPP

