#include "hashtbl.h"
#include <iostream>
using std::endl;
using std::ostream;
#include <string.h>
#include <algorithm>
using std::find;
#include <iomanip>
using std::setfill;
using std::setw;
#include <cassert>
#include <cmath>

#define R32 (rand()*100003 + rand())
#define R64 (((uint64_t)R32 << 32) + R32)
#define TLEN ((size_t)(1 << this->nBits))

namespace csc212 {
    // constructs vector of random odd numbers!
    hashtbl::hash::hash(unsigned rangebits, const uint32_t* a, const uint64_t* alpha,
			const uint64_t* beta){
		this->rangebits = rangebits;
		if(a){
			for(size_t i = 0; i < aLen; i++){
				this->a[i] = a[i] | 1;
			}
		}
		else{
			for(size_t i = 0; i < aLen; i++){
				this->a[i] = R32 | 1;
			}
		}
		this->alpha = ((alpha) ? *alpha : R64) | 1;
		this->beta = ((beta) ? *beta : R64);
		this->beta &= ((uint64_t)-1)>>(64-rangebits);
	}
    // hash function () operator
    uint64_t hashtbl::hash::operator()(const string& x) const {
        assert(x.length() <= 4*aLen);
        const uint32_t* s = reinterpret_cast<const uint32_t*>(x.c_str());
        //first hash function inmplementation x = h(s)
        uint64_t temp = 0;
        for ( size_t i = 0; i < x.length()/2; i++ ){
             temp += (s[2*i] + a[2*i])*(s[(2*i)+1]+a[(2*i)+1]);
        }
        temp = temp % int(pow(2,64));
        //second hash function implementation
        uint64_t g_h = (((this->alpha * (temp)) + this->beta)/(pow(2,(64 - this->rangebits))));
        return g_h;
    }

    //hashtbl constructor
    hashtbl::hashtbl(unsigned nBits, const uint32_t* ha, const uint64_t* halpha, const uint64_t* hbeta) : nBits(nBits), h(nBits,ha,halpha,hbeta){
        this->table = new list<val_type>[TLEN];
    }

    //hashtbl copy constructor
    hashtbl::hashtbl(const hashtbl& H){ //copy constructor
        this->h = H.h;
        this->nBits = H.nBits;
        for ( size_t i = 0; i < TLEN; i++){
             this->table[i] = H.table[i];
        }
    }
    
    //hashtbl destructor
    hashtbl::~hashtbl(){ // destructor
        delete[] this->table;
    }

    //assignment operator
    hashtbl& hashtbl::operator=(hashtbl H){
        for ( size_t i = 0; i < TLEN; i++ ){
             std::swap(this->table[i], H.table[i]);
        }
        this -> nBits = H.nBits;
        this -> h = H.h;
        return *this;
    }

    ostream& operator<<(ostream& o, const hashtbl& H){
        for (size_t i = 0; i < H.tableLength(); i++){
            o << "[" << setfill('0') << setw(2) << i << "] |";
            for (list<val_type>::iterator j = H.table[i].begin(); j != H.table[i].end(); j++ ){
                o << *j << "|";
            }
            o << endl;
        }
        return o;
    }

    void hashtbl::insert(val_type x){
        printf("hello I am insert\n");
        if ( search(x) != true ){
            printf("search == false\n");
            this->table[h(x)].push_front(x);
        }
        else {
            printf("Item already inserted!\n\n");
        }
    }

    void hashtbl::remove(val_type x){
        if ( search(x) == true ){
            this->table[h(x)].remove(x);
        }
    }

    void hashtbl::clear(){
        for(size_t i = 0; i < TLEN; i++){
            this->table[i].clear();
        }
    }
    
    bool hashtbl::isEmpty() const{
        for ( size_t i = 0; i < TLEN; i++ ){
            if ( this->table[i].size() != 0 ){
               return false;
            }
        }
        return true;
    }

    bool hashtbl::search(val_type x) const{
        printf("hello I am search\n");
        for (list<val_type>::iterator j = this->table[h(x)].begin(); j != this->table[h(x)].end(); j++ ){
            printf("h(%s) == %llu \n", x.c_str(), h(x));
            if ( *j == x ){
               return true;
            }
        }
               
        return false;
    }

    size_t hashtbl::countElements() const{
        size_t allElements = 0;
        for ( size_t i = 0; i < TLEN; i++ ){
             allElements += table[i].size();
        }
        return allElements;
    }

    size_t hashtbl::tableLength() const{
        return TLEN;
    }

    size_t hashtbl::countCollisions() const{
        size_t i, nCollisions = 0;
        for ( i = 0; i < TLEN; i++ ){
            if (table[i].size() > 1){
                ++nCollisions;
            }
        }
        return nCollisions;
    }

    size_t hashtbl::longestListLength() const{
        size_t longest_list = 0;
        for ( size_t i = 0; i < TLEN; i++ ){
            if ( this->table[i].size() > longest_list ){
                longest_list = this->table[i].size();
            }
        }
        return longest_list;
    }
            
	
}
