#include "DEque.h"
#include <stdio.h>
#include <cassert>
#include <iostream>
#ifndef INIT_CAP
#define INIT_CAP 4
#endif

deque::deque(){ // constructor // works
    this->cap = INIT_CAP;
	this->data = new int[cap];
    this->front_index = (this->cap)/2;
	this->next_back_index = (this->cap)/2;
}

deque::deque( const deque& D ){ // copy constructor
	this->cap = D.cap;
	this->front_index = D.front_index;
	this->next_back_index = D.next_back_index;
    this->data = new int[D.cap];
    for ( size_t i = 0; i < D.size(); i++ ){
        this->data[i] = D.data[i];
    }
}

deque::deque( deque&& D ){ // r-value copy constructor
    this->cap = D.cap;
    this->front_index = D.front_index;
    this->next_back_index = D.next_back_index;
    this->data = D.data;
    D.data = NULL;
}

deque::~deque(){ //destructor
    if ( this->data != NULL ) delete [] this->data;
}

deque& deque::operator=( deque RHS ){ // assignment operator
    size_t temp;
    this->cap = RHS.cap;
    this->front_index = RHS.front_index;
    this->next_back_index = RHS.next_back_index;
    for ( size_t i = 0; i < RHS.size(); i++ ){
        temp = this->data[i];
        this->data[i] = RHS.data[i];
        RHS.data[i] = temp;
    }
    return *this;
}

deque::deque( int* first, int* last ){ // range constructor // works
    if ( last <= first ) return;
    this->cap = last - first + 1;
    this->data = new int[this->cap];
    this->front_index = 0;
    this->next_back_index = this->cap-1;
    for ( size_t i = 0; i < this->cap-1; i++ ){
        this->data[i] = first[i];
    }
}

void deque::push_back( int x ){ // works
    //printf("D is full?: %d\n", this->needs_realloc());
    if ( this->needs_realloc() == true ){
        int* more_data = new int[cap*2];
        size_t temp = front_index, temp_after_last = cap - 1;
        for ( size_t i = temp; i < cap; i++  ){
            more_data[++temp_after_last] = data[i];
        }
        for ( size_t j = 0; j < front_index; j++ ){
            more_data[++temp_after_last] = data[j];
        }
        delete [] data;
        printf("temp_after_last: %zu\n", temp_after_last);
        front_index = cap;
        next_back_index = temp_after_last;
        data = more_data;
        cap *= 2;
        printf("capacity: %zu\n", this->cap);
        printf("front_index: %zu\n", front_index);
        printf("next_last_index: %zu\n", next_back_index);
        for ( size_t i = 0; i < cap; i++ ){
            printf("D[%zu] = %i\n", i, this->data[i] );
        }
        printf("\n");
    }
    if ( next_back_index == cap ){
        next_back_index = 0;
        //printf("next_back_index ( before ) = %zu\n", next_back_index );
        data[next_back_index] = x;
        next_back_index++;
        //printf("next_back_index ( after ) = %zu\n", next_back_index );
    }
    else{
        //printf("next_back_index ( before ) = %zu\n", next_back_index );
        data[next_back_index] = x;
        next_back_index++;
        //printf("next_back_index ( after ) = %zu\n", next_back_index );
    }
    for ( size_t i = 0; i < cap; i++ ){
        printf("D[%zu] = %i\n", i, this->data[i] );
    }
    printf("\n");
    
}

void deque::push_front ( int x ){ // works
    printf("D is full?: %d\n", this->needs_realloc());
    if ( this->needs_realloc() == true ){
        printf("hello");
        int* more_data = new int[cap*2];
        size_t temp = front_index, temp_after_last = cap - 1;
        for ( size_t i = temp; i < cap; i++  ){
            more_data[++temp_after_last] = data[i];
        }
        for ( size_t j = 0; j < front_index; j++ ){
            more_data[++temp_after_last] = data[j];
        }
        delete [] data;
        printf("temp_after_last: %zu\n", temp_after_last);
        front_index = cap;
        next_back_index = temp_after_last;
        data = more_data;
        cap *= 2;
        printf("capacity: %zu\n", this->cap);
        printf("front_index: %zu\n", front_index);
        printf("next_last_index: %zu\n", next_back_index);
        for ( size_t i = 0; i < cap; i++ ){
            printf("D[%zu] = %i\n", i, this->data[i] );
        }
        printf("\n");
    }
    if ( front_index - 1 == SIZE_MAX ){
        printf("front_index ( before ) = %zu\n", front_index );
        front_index = cap - 1;
        printf("front_index ( after ) = %zu\n", front_index );
        data[front_index] = x;
    }
    else{
        printf("front_index ( before ) = %zu\n", front_index );
        front_index--;
        printf("front_index ( after ) = %zu\n", front_index );
        data[front_index] = x;
    }
    for ( size_t i = 0; i < cap; i++ ){
        printf("D[%zu] = %i\n", i, this->data[i] );
    }
    printf("\n");
}

int deque::pop_back(){
    printf("hello\n");
    int temp = data[next_back_index - 1];
    if ( this->empty() == true ) {
        printf("cannot pop_back because deque is empty! ERROR");
    }
    if ( next_back_index == 0 ){
        next_back_index = cap;
    }
    printf("hello\n");
    next_back_index = next_back_index - 1;
    return temp;
}

int deque::pop_front(){
    printf("hello\n");
    int temp = data[front_index];
    if ( this->empty() == true ) {
        printf("cannot pop_back because deque is empty! ERROR");
        return 0;
    }
    if ( front_index + 1 == cap ){
        front_index = 0;
    }
    printf("hello\n");
    front_index = front_index + 1;
    return temp;
}

bool deque::empty() const {
    if ( front_index == next_back_index  ) return true;
    return false;
}

int& deque::operator[]( size_t i ) const{ // allows x[i] notation
    // give elements their addresses based on how close the size is to the capacity.
    // ex-> 1st element would be in position 10 but since its 1/9 it would be x[0]
    //      2nd element would be in position 11 but since its 2/9 it would be x[1]
    //      3rd element would be in position 12 but since its 3/9 it would be x[2] etc.
    assert( i < this->size() );// stay in range
           return this->data[( this->front_index + i ) % this->cap];
}

int deque::back() const { // works
    if ( next_back_index == 0 ){
        return data[cap - 1];
    }
    size_t i = next_back_index - 1;
    return data[i];
}

int deque::front() const { //works
    return data[front_index];
}

size_t deque::size() const { // size function // works
    size_t temp = next_back_index + 1;
    if ( temp == front_index ){
        return cap - 1;
    }
    return ( (next_back_index - front_index) + cap ) % cap;
}

size_t deque::capacity() const{ // returns capacity works
    return this->cap - 1;
}

void deque::clear(){ // cant i just set front_index == next_back_index
    next_back_index = front_index;
    // when both the front index and next back index are equal, you have an empty deque!
}

bool deque::needs_realloc(){ // works
    size_t temp = next_back_index + 1;
    if ( temp == front_index  ) {
        return true; // true = 1;
    }
    return false; // false = 0;
}








