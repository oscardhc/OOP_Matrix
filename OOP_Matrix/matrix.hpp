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
        int N, M;
        T* a;
      
    public:
        Array() {
            
        }
        Array(int n, int m) {
            N = n;
            M = m;
            a = (T*)malloc(n * m * sizeof(T));
        }
        
    public:
        T& element(int i, int j) {
            return a[i * N + j];
        }
        const T& element(int i, int j) const {
            return a[i * N + j];
        }
        void resize(int n, int m) {
            N = n;
            M = m;
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
        
        
//        3.3.2 BINARY OPERATORS
    public:
        
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

