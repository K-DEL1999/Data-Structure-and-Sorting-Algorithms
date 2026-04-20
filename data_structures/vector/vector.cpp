#include "vector.h"
#include <cassert>
#include <algorithm>

vector::vector(){ // constructor
    //creates new vector with size 16
    capacity = 16; // sets size
    count = 0; // how many elements in vector
    data = new int[16]; // allocates space for vector
}

vector::vector( const vector& V ){ // copy constructor
    this->count = this->capacity = V.count; //set capacity and count of the copy equal to the count of V
    this->data = new int[this->capacity]; // allocates appropriate amount of space for copy of vector. Basically constructs a new vector with the same size of vector V. hence the new int[this->capacity]
    for ( size_t i = 0; i < capacity; i++ ){
        this->data[i] = V.data[i]; // for loop that transfers data from V to new vector
    }
}

vector::~vector(){ // destructor
    if ( this->data != NULL ) delete [] data;
    /* possible alternative?
    for (size_t i = 0; i < capacity; i++ ){
        delete this->data[i];
    }
     */
}

vector::vector( vector&& V ){ // r - value copy constructor
    // objective -> steal the data from the V, and just leave V in some valid state so its destructor doesnt blow up / crach / etc. //
    this->data = V.data; // copy's data from old vector into new vector
    this->count = V.count; // copy's count from old vector to new vector
    this->capacity = V.capacity; // copy's capacity from old vector to new vector
    V.data = NULL; // leaves V in some state for destructor to delete
    
    /* possible alternative, swap data?
    would you have to individually swap each component?
    */
}

vector& vector::operator=( vector RHS ){
    std::swap(this->data, RHS.data); //swaps data with newly initialized RHS vector
    this->count = RHS.count; // copy count
    this->capacity = RHS.capacity; // copy capacity
    return *this; // return dereferenced vector
}

int& vector::operator[](size_t i){
    assert( i < this->count ); //prevents out of bounds access
    return data[i];
    //V[i] translates to V.operator[](i)
}

void vector::push_back( int x ){
    if ( count == capacity ){
        int* new_data = new int[capacity*2];
        for ( size_t i = 0; i < capacity; i++ ){
            new_data[i] = data[i];
        }
        delete [] data;
        data = new_data;
        capacity *= 2;
    }
    
    data[count++] = x;
}

size_t vector::size() const{
    //returns size of vector
    return count;
}

void vector::pop_back(){
    assert( count > 0 );
    count--;
}

int vector::back() const {
    assert( count > 0);
    return this->data[count-1];
}
