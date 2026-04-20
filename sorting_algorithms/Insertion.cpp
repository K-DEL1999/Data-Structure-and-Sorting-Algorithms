#include <iostream>
#include <chrono>
#include <vector>
using std::vector;

void Insertion_Sort( vector<int> &v );
int temp;
static double Run_Time;

int main(){
	srand(time(NULL));
	for ( int k = 10; k <= 1000000; k = k*10 ){
		vector<int> v;
		for ( int j = 0; j < k; j++ ){
			temp = rand() % 10000 + 1;
			v.push_back(temp);
		}

		Insertion_Sort( v );

		printf("The running-time of Insertion_Sort for an array of size %d is %f nanoseconds\n\n", k, Run_Time);
	}
	return 0;
}

void Insertion_Sort( vector<int> &v  ){
	auto start = std::chrono::steady_clock::now();
	for ( int i = 1; i < v.size(); i++ ){
		int j = i - 1, k = i;
		while ( v[k] < v[j] && j >= 0 ){
			temp = v[k];
			v[k] = v[j];
			v[j] = temp;
			k = j;
			j--;
		}
	}
	auto end = std::chrono::steady_clock::now();
	Run_Time = double(std::chrono::duration_cast<std::chrono::nanoseconds> (end-start).count());
}
