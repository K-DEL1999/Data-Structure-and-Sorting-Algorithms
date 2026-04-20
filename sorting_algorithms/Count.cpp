#include <iostream>
#include <vector>

using std::vector;

void Count_Sort ( vector<int> &v );

int main(){
	vector<int> v = {10, 9, 8, 8, 8, 5, 4, 3, 3, 1, 0};
    printf("\n\n");
    for ( int i = 0; i < v.size(); i++ ){
        printf("%d ", v[i]);
    }
    printf("\n\n");
	Count_Sort( v );
    
	for ( int i = 0; i < v.size(); i++ ){
		printf("%d ", v[i]);
	}
	return 0;
}

void Count_Sort ( vector<int> &v ){
    int max = INT_MIN;
    for ( int i = 0; i < v.size(); i++ ){ // get max
        if ( v[i] > max ){
            max = v[i];
        }
    }
    int Array[++max];
    int BArray[max];
    for ( int i = 0; i < max; i++ ){
        Array[i] = 0;
    }
    for ( int i = 0; i < v.size(); i++ ){
        Array[v[i]]++;
    }
    for ( int i = 1; i < max; i++ ){
        Array[i] = Array[i] + Array[i - 1];
    }
    for ( int i = v.size() - 1; i >= 0; i-- ){
        BArray[Array[v[i]]-1] = v[i];
        Array[v[i]]--;
    }
    for ( int i = 0; i < v.size(); i++ ){
        v[i] = BArray[i];
    }
}
