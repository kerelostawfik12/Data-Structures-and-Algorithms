#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "insertion_sort.cpp"

void randomise(std::vector<int>& v){
	
	for (int i = v.size() - 1; i > 0; --i){
		int rand_index = std::rand()%i;
		v[i] += v[rand_index];
		v[rand_index] = v[i] - v[rand_index];
		v[i] -= v[rand_index];		
	}
	
}

bool contains(const std::vector<int>& v, int i){
	for (int j : v){
		if (i == j) return true;
	}
	
	return false;
}

bool same_contents(const std::vector<int>& v1, const std::vector<int>& v2){
	for (int j : v1) if (!contains(v2,j)) return false;
	for (int j : v2) if (!contains(v1,j)) return false;
	
	return true;
}

bool is_sorted(const std::vector<int>& v){
	for (int i = 1; i < v.size(); i++){
		if (v[i] < v[i-1]) return false;
	}
	
	return true;
}

int main(){
	
	std::srand(std::time(NULL));
	std::cout << std::boolalpha;
	
	int random_size = (std::rand()%30) + 5;
	
	std::vector<int> v;
	for (int i = 1; i <= random_size; i++){
		v.push_back(i);
	}
	
	randomise(v);
	
	std::cout << "Is v sorted? " << is_sorted(v) << std::endl;
	std::cout << "Sort it!" << std::endl;
	std::vector<int> sorted = insertion_sort(v);
	std::cout << "Is the result sorted? " << is_sorted(sorted) << std::endl;
	std::cout << "Is it the same as the original? " << same_contents(v, sorted) << std::endl;
	
}
