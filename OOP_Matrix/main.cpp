//
//  main.cpp
//  OOP_Matrix
//
//  Created by Haichen Dong on 2018/11/3.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    sjtu::Matrix<int> mat = {{1,2,3},{2,3,4},{3,4,5},{4,5,6}};
//    mat.print();
    mat(1,1) = 100;
    auto hhh = mat.row(1);
    hhh.print();
    
    return 0;
}
