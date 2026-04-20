#include <iostream>
#include <vector>

using namespace std;
	
void MergeSort( vector<int> &v );
void Merge( vector<int> &v, vector<int> &l, vector<int> &r );

int main( int argc, char* argv[] ){
	int temp;
	vector<int> v;
	
    for ( temp = 1; temp < argc; temp++ ){
        v.push_back(atoi(argv[temp]));
	}
    
	MergeSort(v);
    
	for ( temp = 0; temp < v.size(); temp++ ){
		
		cout << v[temp] << " ";	
	
	}
	cout << "\n";

	return 0;	
}

void MergeSort( vector<int> &v ){

	if ( v.size() == 1 ){
		return;
	}

	vector<int> l, r;
	int m = v.size() / 2;
	
	for ( int i = 0; i < m; i++ ){
		l.push_back(v[i]);
	}
	
	for ( int i = m; i < v.size(); i++ ){
		r.push_back(v[i]);
	}
    
	MergeSort( l );
	MergeSort( r );
	Merge( v, l, r );
	
}

void Merge( vector<int> &v, vector<int> &l, vector<int> &r ){
	
	int i = 0, j = 0, k = 0;
	l.push_back( INT_MAX );
	r.push_back( INT_MAX );
    
    int rCount = r.size(), lCount = l.size();
    
    while ( true ){
        if ( rCount == 1 && lCount == 1 ){
            break;
        }
		if ( r[i] > l[j] ){
			v[k] = l[j];
			j++;
			k++;
            lCount--;
		}
		else if ( r[i] <= l[j] ){
			v[k] = r[i];
			i++;
			k++;
            rCount--;
		}
	}
}










