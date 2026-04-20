#pragma once
#include <cstddef>
#ifndef VECTOR_H
#define VECTOR_H
#endif

class vector {
public:
    
    vector(); // constructor -> constructs the object (in this case the vector)
    vector( const vector& V ); // copy constructor - > allows you to make copies of the object.
                               // parameter to the copy constructor must be by reference to prevent an infinite number of recursive calls to the copy constructor. Passing by value would invoke the copy constructor! hence creating the infinite loop.
                               // If the copy constructor were to take the object by value then it needs the copy constructor of the given object. This would then result in the copy constructor calling itself recursively. Being passed by reference results in the variables becoming aliases of the supplied object.
                               // Basically creating a copy constructor function would not work with pass by value because when you call a function that passes by value it makes a copy of the argument and stores it into the parameter. In order to do that you would need to utilize the copy constructor but since you are creating a function for copy constructor you will have to use by reference. By reference allows you to use the data without making a copy of it since the original data is passed and it is not copied. Coping would invoke the copy constructor which is what creates the infinite loop.
                               /* link for further explanation https://stackoverflow.com/questions/2685854/why-should-the-copy-constructor-accept-its-parameter-by-reference-in-c */
    vector(vector&& V); // r - value copy constructor -> allows you to initialize a new variable or                 // assign the l value witht he value of the r value.
    ~vector(); // function that is called when an object is going to be discarded. It frees the               resources that the object may have acquired during its lifetime. Bascially to               free up space.
    // vector& operator=( const vector &rhs ); would be an very similar to copy constructor code
    vector& operator=( vector RHS ); // fancier way to define assignment operator
    
	void push_back( int x ); // adds value to existing array
	void pop_back(); // deletes last element
	int back() const; // returns last element of array
	 
	size_t size() const; // returns size of vector
	int & operator[](size_t i ); // allows V[i] notation

private:
    // components of vector
	int* data;
	size_t count;
	size_t capacity;
};
