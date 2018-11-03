#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{
    template <class T> class Matrix {
    private:
        int N, M;
        T** a;
        void initMat() {
            a = (T**)malloc(N * sizeof(T*));
            for (int i = 0; i < N; i++) {
                a[i] = (T*)malloc(M * sizeof(T));
            }
        }
        void freeSpace() {
            free(a);
        }
    
//    3.1 INITIALIZATION
    public:
        Matrix() {
            
        }
        Matrix(std::size_t n, std::size_t m, T init = T()) {
            N = (int)n;
            M = (int)m;
            initMat();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    a[i][j] = init;
                }
            }
        }
        Matrix(std::initializer_list< std::initializer_list<T> > list) {
            N = (int)list.size();
            M = (int)list.begin() -> size();
            initMat();
            auto curRow = list.begin();
            for (int i = 0; i < N; i++, curRow++) {
                auto cur = curRow -> begin();
                for (int j = 0; j < M; j++, cur++) {
                    a[i][j] = *cur;
                }
            }
        }
        
//        3.2 GETTING ELEMENT
    public:
        T& operator() (std::size_t i, std::size_t j) {
            return a[i][j];
        }
        const T& operator()(std::size_t i, std::size_t j) const {
            return a[i][j];
        }
        Matrix<T> row(std::size_t i) const {
            Matrix<T> ret = Matrix<T>(1, M);
            for (int j = 0; j < M; j++) {
                ret(0, j) = a[i][j];
            }
            return ret;
        }
        Matrix<T> column(std::size_t j) const {
            Matrix<T> ret = Matrix<T>(N, 1);
            for (int i = 0; i < N; i++) {
                ret(i, 0) = a[i][j];
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
                    std::cout << a[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}

#endif //SJTU_MATRIX_HPP

