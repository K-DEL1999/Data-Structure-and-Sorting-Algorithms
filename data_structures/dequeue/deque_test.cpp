#include <iostream>
#include "DEque.h"

using namespace std;

void copy_deque ( deque& D, deque& W );

int main( int argc, char* argv[] ){
    deque D, W;
    
    for ( int i = 1; i < argc; i++ ){
        D.push_back(atoi(argv[i]));
    }
    
    D.push_front(12);
    cout << "D.size()..." << D.size() << endl<<endl;
    for ( int i = 0; i < D.size(); i++ ){
        printf("D[%i] = %i\n", i, D[i]);
    }
    
    printf("\n");
    
    copy_deque( D, W );
    
    for ( int i = 0; i < W.size(); i++ ){
        printf("W[%i] = %i\n", i, W[i]);
    }
    
    cout << "next_back valued popped: " << W.pop_back() << endl;
    cout << "front value popped: " << W.pop_front() << endl;
    
    for ( int i = 0; i < W.size(); i++ ){
        printf("W[%i] = %i\n", i, W[i]);
    }
    
    printf("Last element: %i\nFirst elemenet: %i\n", W.back(), W.front());
    printf("capacity: %zu\n", W.capacity());
    
    return 0;
}

void copy_deque ( deque& D, deque& W ){
    for ( int i = 0; i < D.size(); i++ ){
        W.push_back(D[i]);
    }
}
