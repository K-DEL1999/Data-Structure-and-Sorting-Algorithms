#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include <list>
using std::list;
#include <inttypes.h>
/* chained hash table
    -> entire structure is the union of all linked lists in the array
    -> an element with key == x is in the hash table IFF it is in the list with index h(x)...
        h(..) is the hash function!
    -> no duplicates ! search before insertion
    -> hash function is selected randomely from an almost universal hashing family during object construction
 */
#ifndef HASHTBL_H
#define HASHTBL_H
#endif

namespace csc212 {
    // namespace allows for 2 different functionalities for the same keyword! A variable defined in the
	typedef std::string val_type; // allows you to associate type with variable. In a way you are making your                               own type that can easily be changed by altering this line. val_type in                                this case refers to a string.
	class hashtbl { // creating hash table class ...
	public:
		hashtbl(unsigned nBits = 8, const uint32_t* ha = 0,
			const uint64_t* halpha = 0, const uint64_t* hbeta = 0);
        // hash table constructor parameters serve to construct a hash table with initialized components
        
		hashtbl(const hashtbl& H); // copy constructor
		~hashtbl(); // destructor

		hashtbl& operator=(hashtbl H); // assignment operator
		friend ostream& operator<<(ostream& o, const hashtbl& H);
        //Allows you to overload the already existing insertion operation '<<'. Enables you to print your objectdirectly!
/*
 https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
*/
        
		void insert(val_type x); // insert std::string x
		void remove(val_type x); // remove std::string x
		void clear(); // clear table
		
		bool isEmpty() const; // is table empty
		bool search(val_type x) const; // search for element
		size_t countElements() const; // count elements
		size_t tableLength() const; // size of table
		size_t countCollisions() const; // number of elements with same address ... h(x) = h(y) = h(z)...
		size_t longestListLength() const; // longest linked list

		class hash{ // hash function ...
			public:
            // initialized constructor
			hash(unsigned rangebits = 64,const uint32_t* a = 0,const uint64_t* alpha = 0,const uint64_t* beta = 0);
            
			uint64_t operator()(const std::string& x) const;
            // allows for hash h;
            //            uint64_t = h("string");
            
			static const size_t aLen = 32; // we can only hash 128 bytes of strings

            //http://www.cplusplus.com/reference/cstdint/
            //uint64_t -> unsigned 64 bit integer
            //uint32_t -> unsigned 32 bit integer
			unsigned rangebits; // the m bit int {0,1,2,...2^m - 1}
			uint32_t a[aLen]; // vector for initial hash; a vector of random odd numbers
			uint64_t alpha; // for second hash
			uint64_t beta; // for second hash
		};
	private:
		list<val_type>* table;
		unsigned nBits; // size of hash table is 2^nBits
		hash h;
	};
}
