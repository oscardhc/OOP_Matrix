#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{
	
    template <class T> class Chain{
        T val;
        Chain<T>* next;
    private:
        
        
    public:
        
    };
    
    
    template <class T> class Matrix{
    private:
        int N, M;
        Chain<T*> rowHead;
        
        void init(){
            for (int i = 1; i <= N; i++) {
                
            }
        }
    public:
        Matrix(){
            
        }
        Matrix(std::size_t n, std::size_t m, T init = T()){
            
        }
    };
}

#endif //SJTU_MATRIX_HPP

