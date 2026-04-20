#include <iostream>
#include <vector>
using std::vector;

void Quick_Sort ( vector<int> &v, int Start, int pivot );
int partition( vector<int> &v, int start, int pivot );
void randomize_pivot( vector<int> &v, int Start, int Pivot );
void swap( int &a, int &b );

int main(){
	vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    
	Quick_Sort( v, 0, v.size() - 1 );
    
	for ( int i = 0; i < v.size(); i++ ){
		printf("%d ", v[i]);
	}
	return 0;
}

void Quick_Sort ( vector<int> &v, int Start, int pivot ){
    if ( Start < pivot ){
        randomize_pivot( v, Start, pivot );
        int new_pivot = partition( v, Start, pivot );
        Quick_Sort( v, Start, new_pivot - 1 );
        Quick_Sort( v, new_pivot + 1, pivot);
    }
}

int partition( vector<int> &v, int start, int pivot ){
	int i = start - 1, r = v[pivot];
	for ( int j = start; j < pivot; j++ ){
		if ( v[j] <= r ){
			i++;
			swap(v[i], v[j]);
		}
	}
	swap(v[i+1], v[pivot]);
	return i + 1;
}

void randomize_pivot( vector<int> &v, int Start, int Pivot ){
    srand(time(NULL));
    int i = rand() % (Pivot - Start + 1) + Start;
    swap(v[i], v[Pivot]);
}

void swap( int &a, int &b ){
    int temp = a;
    a = b;
    b = temp;
    /*a ^= b;
    b ^= a;
    a ^= b;*/
}
