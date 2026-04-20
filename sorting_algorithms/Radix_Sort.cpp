#include <iostream>
#include <cmath>
#include <vector>
using std::vector;

void Count_Sort ( vector<int> &v, int Radix );
void Radix_Sort ( vector<int> &v );

int MOST_SIG_DIGIT_POSITION = 6;
int temp;

int main(){
	srand(time(NULL));
    for ( int k = 10; k <= 100; k = k*10 ){
        vector<int> v;
        for ( int j = 0; j < k; j++ ){
            temp = rand() % 10000 + 1;
            v.push_back(temp);
        }
        Radix_Sort( v );
        printf("\n\n");
        for ( int i = 0; i < v.size(); i++ ){
            printf("%d ", v[i]);
        }
        printf("\n\n");
    }
    return 0;
}

void Radix_Sort ( vector<int> &v ){
    for ( int i = 0; i < MOST_SIG_DIGIT_POSITION; i++ ){
        Count_Sort( v, pow( 10, i ) );
    }
}

void Count_Sort ( vector<int> &v, int Radix ){
    int max = INT_MIN;
    for ( int i = 0; i < v.size(); i++ ){ // get max
        if ( (v[i]/Radix)%10 > max ){
            max = (v[i]/Radix)%10;
        }
    }
    if ( max == 0 ){
        return;
    }
    int Array[++max];
    int BArray[v.size()];
    for ( int i = 0; i < max; i++ ){
        Array[i] = 0;
    }
    for ( int i = 0; i < v.size(); i++ ){
        Array[(v[i]/Radix)%10]++;
    }
    for ( int i = 1; i < max; i++ ){
        Array[i] = Array[i] + Array[i - 1];
    }
    for ( int i = v.size() - 1; i >= 0; i-- ){
        BArray[Array[(v[i]/Radix)%10]-1] = v[i];
        Array[(v[i]/Radix)%10]--;
        //printf("\n\n");
        /*for ( int i = 0; i < max; i++ ){
            printf("%d ", BArray[i]);
        }
        printf("\n\n");*/
    }
    for ( int i = 0; i < v.size(); i++ ){
        v[i] = BArray[i];
    }
}
