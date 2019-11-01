#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "string_searching.cpp"

std::string random_string(size_t length, std::vector<char> allowed_chars){
	
	std::default_random_engine rng { std::random_device{}() };
	std::uniform_int_distribution<> dist(0, allowed_chars.size()-1);
	
	auto random_char = [&allowed_chars, &rng, &dist ] () { return allowed_chars[dist(rng)]; };
	
	std::string str(length, 0);
	std::generate_n(str.begin(), length, random_char);
	return str;
}

bool check_match(const std::string& a, std::string::const_iterator itr, const std:: string& b){
	
	for (auto c : b){
		if (*itr != c) return false;
		++itr;
	}
	
	return true;
	
}

int main(){
	
	std::default_random_engine rng {std::random_device{}()};
	std::uniform_int_distribution<size_t> b_dist(5, 10);
	auto b_chars = {'a', 'b', 'c', 'd', 'e'};
	auto b = random_string(b_dist(rng), b_chars);
	
	std::uniform_int_distribution<size_t> a_dist(20, 100);
	auto a_chars = {'u', 'v', 'w', 'x', 'y', 'z'};

	std::cout << std::boolalpha;
	
	std::uniform_int_distribution<> parts_dist(3, 8);
	int num_parts = parts_dist(rng);
	std::string long_a;
	for (auto i = 0; i < num_parts; ++i) long_a += random_string(a_dist(rng), a_chars) + b;
	long_a += random_string(a_dist(rng), a_chars);
	
	auto results = all_matches(long_a, b);
	
	std::cout << "Were enough matches found? " << (results.size() == num_parts) << std::endl;
	
	bool all_matches_work = true;
	for (auto itr : results) all_matches_work &= check_match(long_a, itr, b);
	
	std::cout << "Are all those matches correct? " << all_matches_work << std::endl;
	
}
