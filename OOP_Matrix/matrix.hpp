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
        
    public:
        Matrix() = default;
        
        Matrix(size_t n, size_t m, T _init = T())
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
        
        template <class U>
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
            (*this) = Matrix(o);
            return *this;
        }
        
        template <class U>
        Matrix &operator=(const Matrix<U> &o)
        {
            (*this) = Matrix(o);
            return *this;
        }
        
        Matrix(Matrix &&o) noexcept
        {
            N = o.N;
            M = o.M;
            delete [] ar;
            ar = o.ar;
        }
        
        Matrix &operator=(Matrix &&o) noexcept
        {
            N = o.N;
            M = o.M;
            delete [] ar;
            ar = o.ar;
            return *this;
        }
        
        ~Matrix() {
            if (ar != NULL) {
                delete [] ar;
                ar = NULL;
            }
        }
        
        Matrix(std::initializer_list<std::initializer_list<T>> list)
        {
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
        
    public:
        size_t rowLength() const { return N; }
        
        size_t columnLength() const { return M; }
        
        void resize(size_t n, size_t m, T _init = T())
        {
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
        
        void resize(std::pair<size_t, size_t> sz, T _init = T())
        {
            resize(sz.first, sz.second, _init);
        }
        
        std::pair<size_t, size_t> size() const
        {
            return std::make_pair(N, M);
        }
        
        void clear()
        {
            N = 0;
            M = 0;
            delete [] ar;
        }
        
    public:
        T& element(int i) {
            return ar[i];
        }
        const T& element(int i) const {
            return ar[i];
        }
        T& operator() (std::size_t i, std::size_t j) {
            return ar[i * M + j];
        }
        const T& operator()(std::size_t i, std::size_t j) const {
            return ar[i * M + j];
        }
        
        Matrix<T> row(size_t i) const
        {
            Matrix<T> ret = Matrix<T>(1, M);
            for (int j = 0; j < M; j++) {
                ret(0, j) = (*this)((int)i, j);
            }
            return ret;
        }
        
        Matrix<T> column(size_t j) const
        {
            Matrix<T> ret = Matrix<T>(N, 1);
            for (int i = 0; i < N; i++) {
                ret(i, 0) = (*this)(i, (int)j);
            }
            return ret;
        }
        
        
    public:
        template <class U>
        bool operator==(const Matrix<U> &b) const
        {
            if (N != b.rowLength() || M != b.columnLength()) return false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if ((double)(*this)(i, j) != (double)b(i, j)) return false;
                }
            }
            return true;
        }
        
        template <class U>
        bool operator!=(const Matrix<U> &b) const
        {
            return !((*this) == b);
        }
        
        Matrix operator-() const
        {
            Matrix<T> ret = Matrix<T>(N, M);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    ret(i, j) = -(*this)(i, j);
                }
            }
            return ret;
        }
        
        template <class U>
        Matrix &operator+=(const Matrix<U> &b)
        {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) += (T)b(i, j);
                }
            }
            return *this;
        }
        
        template <class U>
        Matrix &operator-=(const Matrix<U> &b)
        {
            *this += (-b);
            return *this;
        }
        
        template <class U>
        Matrix &operator*=(const U &b)
        {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    (*this)(i, j) *= (T)b;
                }
            }
            return *this;
        }
        
        Matrix tran() const
        {
            Matrix<T> ret = Matrix<T>(M, N);
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
            
        private:

            
        public:
            difference_type operator-(const iterator &o)
            {
                
            }
            
            iterator &operator+=(difference_type offset)
            {
                
            }
            
            iterator operator+(difference_type offset) const
            {
                
            }
            
            iterator &operator-=(difference_type offset)
            {
                
            }
            
            iterator operator-(difference_type offset) const
            {
                
            }
            
            iterator &operator++()
            {
                
            }
            
            iterator operator++(int)
            {
                
            }
            
            iterator &operator--()
            {
                
            }
            
            iterator operator--(int)
            {
                
            }
            
            reference operator*() const
            {
                
            }
            
            pointer operator->() const
            {
                
            }
            
            bool operator==(const iterator &o) const
            {
                
            }
            
            bool operator!=(const iterator &o) const
            {
                
            }
        };
        
        iterator begin()
        {
            
        }
        
        iterator end()
        {
            
        }
        
        std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
        {
            
        }
    };
        
}

//
namespace sjtu
{
    template <class T, class U>
    Matrix<decltype(U() * T())> operator*(const Matrix<T> &a, const U &x)
    {
        auto ret = Matrix<decltype(T() + U())>(a.rowLength(), a.columnLength());
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
        auto ret = Matrix<decltype(T() + U())>(a.rowLength(), a.columnLength());
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
        auto ret = Matrix<decltype(U() * V())>(a.rowLength(), b.columnLength());
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
        auto ret = Matrix<decltype(U() + V())>(a.rowLength(), a.columnLength());
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

