#include <iostream>
#include "vector.h"
//when compiling include header file first then defintion of functions and then the desired c++ code.
// ex -> g++ =std=c++11 -o vector vector.cpp test.cpp
// links the files together

void reverse_elements ( vector& x ){
    size_t temp;
    for ( size_t i = 0; i < x.size()/2; i++ ){
        temp = x[i];
        x[i] = x[x.size()-i-1];
        x[x.size()-i-1] = temp;
    }
}

int main(){

	vector x; // vector constructed
    for ( size_t i = 0; i < 10; i++ ){
        x.push_back(i);
    }
    for ( size_t i = 0; i < x.size(); i++ ){
        printf("x[%zu] = %i\n", i , x[i]);
    }
    printf("\n");
    printf("Delete last element: \n");
    x.pop_back();
    for ( size_t i =0; i < x.size(); i++ ){
        printf("x[%zu] = %i\n", i , x[i]);
    }
    printf("\n");
    printf("Last element in vector: \n");
    printf("x[%zu] = %i", x.size() - 1, x.back());
    
    printf("\n");
    printf("Function call: \n");
    reverse_elements(x);
    
    for ( size_t i = 0; i < x.size(); i++ ){
        printf("x[%zu] = %i\n", i , x[i]);
    }
	
	return 0;
}
