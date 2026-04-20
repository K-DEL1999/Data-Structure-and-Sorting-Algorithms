#include<iostream>
#include<vector>
using std::vector;

void HeapSort( vector<int> &v );
void BuildHeap( vector<int> &v );
void heapify( vector<int> &v, size_t Position, size_t H_size );
void Swap( int &a, int &b);

int main( int argc, char* argv[] ){
	size_t i = 1;
    vector<int> v;
	while ( argv[i] != NULL ){
		v.push_back(atoi(argv[i]));
		i++;
	}
    printf("\nSize of vector: %lu\n", v.size());
    printf("\nUnSorted Array: [ ");
	for( size_t i = 0; i < v.size(); i++ ){
		if ( i == v.size() - 1 ){
			printf("%d ]\n", v[i] );
		}
		else{
			printf("%d, ", v[i] );
		}
	}
    
	HeapSort( v );
	
	printf("\nSorted Array: [ ");
	for( size_t i = 0; i < v.size(); i++ ){
		if ( i == v.size() - 1 ){
			printf("%d ]\n\n", v[i] );
		}
		else{
			printf("%d, ", v[i] );
		}
	}
	return 0;
}

void HeapSort( vector<int> &v ){
    size_t Position;
	BuildHeap(v);
	size_t Heap_Size = v.size();
    while (true) {
        
		Swap(v[Heap_Size - 1], v[0]);
        Heap_Size--;
        if ( Heap_Size == 1 ){
            break;
        }
        heapify(v, 0, Heap_Size);
    }
}

void BuildHeap( vector<int> &v ){
    size_t H_size = v.size();
	for( int i = int(H_size/2); i > -1; i-- ){
        heapify(v, size_t(i), H_size);
	}
}

void heapify( vector<int> &v, size_t Position, size_t H_size ){
	size_t i = Position, Largest = i;
	size_t l = (2*i) + 1; // index of left child
	size_t r = (2*i) + 2;// index of right child
    
	if ( l <= H_size - 1  && v[l] > v[i]  ){
		Largest = l;
	}
    if ( r <= H_size - 1 && v[r] > v[Largest]){
		Largest = r;
	}
	if ( Largest != i ){
		Swap(v[i], v[Largest]);
		heapify(v, Largest, H_size);
	}
}

void Swap( int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}





