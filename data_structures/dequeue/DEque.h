#pragma once
#include <iostream>
#include <cstddef>
#ifndef DEQUE_H
#define DEQUE_H
#endif

using namespace std;

class deque {
public:
	deque(); //constructor
	deque( const deque& D ); // copy constructor
	deque( deque&& D ); // r-value copy constructor
	~deque(); // destructor
	deque& operator=( deque RHS ); // assignment operator
	
	deque( int* first, int* last ); // initialize last to first

	void push_back( int x ); // insert element at the end of deque
	void push_front( int x ); // insert element in front of DEque

	int pop_back(); // removes last element 
	int pop_front(); // removes first element
	
	bool empty() const; // returns true if DEque is empty

	int& operator[]( size_t i ) const; // for x[i] notation

	int back() const; // returns last element
	int front() const; // returns first element

	size_t size() const; // returns number of elements in DEque
	size_t capacity() const; // returns capacity of buffer

	void clear(); // empty DEque
		
private:
	int* data; // pointer to storage for elements
	size_t front_index; // index of front element
	size_t next_back_index; // index of memory after last element
	size_t cap; // capacity; size of buffer
    size_t count; // elements in buffer
	bool needs_realloc (); // can we push another element
    
};
