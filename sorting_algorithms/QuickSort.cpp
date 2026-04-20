#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <time.h>     
using std::string;
using std::vector;
using std::cout;

void swap_words(string& a, string& b){
	string temp = a;
	a = b;
	b = temp;
}

int partition(vector<string>& words, int start, int end){
	int p = words[end].size(); //identify pivot
	
	//intialize to start of section - this will determine the split between the values greater and less than the pivot
	//for ascending sort - any value less than or equal pivot will initiate a swap with current i and k and then i++
	//for descending sort - any value greater than or equal pivot will initiate a swap with current i and k and then i++
	//this seperates the values greater than the pivot from the values less than the pivot
	int i = start; 
	
	// traverse through section - if size of words is greater than or less than pivot we swap with current k and i++
	for (int k = start; k < end; k++){
		if ( words[k].size() >= p ){
			swap_words(words[i], words[k]);
			i++;
		}
	}

	//after we have traversed the region we swap the i value with the end value
	//the pivot is now in between the values greater than itself and less than itself
	swap(words[i], words[end]);

	//return the midpoint value so we can correctly partition the left and right sides
	return i;
}

int partition_r(vector<string>& words, int start, int end){
	string temp;
	
	//create random pivot
	srand(time(0));
	int r = (rand() % (end - start)) + start;

	//swap random value selected with last value in section to create pivot
	swap_words(words[r], words[end]);

	//return new partition
	return partition(words, start, end);
}

void QuickSort_words(vector<string>& words, int start, int end){
	if (start < end){
		cout << "\n[";
		for (int i = 0; i < words.size(); i++){
			cout << words[i] << " ";
		}
		cout << "]\n";
		int p = partition_r(words, start, end);
		cout << "\n" << p << "\n";
		QuickSort_words(words, start, p-1);
		QuickSort_words(words, p+1, end);  
	}
}

int main(){
	vector<string> words;
	words.push_back("Hello");
	words.push_back("all");
	words.push_back("cheese");
	words.push_back("be");
	words.push_back("cheesecake");
	QuickSort_words(words,0,words.size()-1);
	for (int i = 0; i < words.size(); i++){
		cout << words[i] << " ";
	}
	return 0;
}

