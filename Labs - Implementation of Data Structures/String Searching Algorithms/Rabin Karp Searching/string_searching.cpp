#ifndef STRING_SEARCH_CPP
#define STRING_SEARCH_CPP

#include <string>
#include <vector>
#include <random>
#include <iostream>

bool is_prime(const unsigned& p){
	unsigned i = 2;
	while (i*i <= p){
		if (p % i == 0) return false;
		++i;
	}
	return true;
}

unsigned next_prime(const unsigned& start_value){
	
	unsigned p = start_value;
	while (!is_prime(p)) ++p;
	return p;
	
}

bool matches(const std::string& a, std::string::const_iterator itr, const std:: string& b){
	
	for (auto c : b){
		if (*itr != c) return false;
		++itr;
	}
	
	return true;
	
}

std::string::const_iterator substring_position(const std::string& a, const std::string& b){
	
	unsigned p = next_prime(b.size()*a.size()*50);
	std::default_random_engine rng { std::random_device{}() };
	std::uniform_int_distribution<> dist(2, p-1);
	int r = dist(rng);
	
	int r_pow[b.size()];
	r_pow[b.size() - 1] = 1;
	if (b.size() > 1) r_pow[b.size() - 2] = r;
	for (int i = b.size() - 3; i >= 0; --i) r_pow[i] = (r * r_pow[i+1]) % p;
	
	int beta = 0;
	
	for (auto i = 0; i < b.size(); ++i) beta += (b.at(i)*r_pow[i]) % p;
	
	beta = beta % p;
	
	int alpha[a.size()-b.size()+1];

	alpha[0] = 0;
	
	for (auto i = 0; i < b.size(); ++i) alpha[0] += (a.at(i)*r_pow[i]) % p;
	
	alpha[0] = alpha[0] % p;
	
	for (auto j = 1; j < a.size() - b.size() + 1; ++j){
		auto prev_term = (a.at(j-1)*r_pow[0]) % p;
		auto prev_val = alpha[j-1];
		while (prev_val < prev_term) prev_val += p;
		auto adjustment = r * (prev_val - prev_term) % p;
		alpha[j] = (adjustment  + a.at(j + b.size() -1)) % p;
	}
	
	for (auto i = 0; i < a.size() - b.size() + 2; ++i){
		if (alpha[i] == beta && matches(a, a.begin() + i, b)) return a.begin() + i;
	}

	
	return a.end();

}

std::vector<std::string::const_iterator> all_matches(const std::string& a, const std::string& b){
	
	std::vector<std::string::const_iterator> results;
	
	unsigned p = next_prime(b.size()*a.size()*50);
	std::default_random_engine rng { std::random_device{}() };
	std::uniform_int_distribution<> dist(2, p-1);
	int r = dist(rng);
	
	int r_pow[b.size()];
	r_pow[b.size() - 1] = 1;
	if (b.size() > 1) r_pow[b.size() - 2] = r;
	for (int i = b.size() - 3; i >= 0; --i) r_pow[i] = (r * r_pow[i+1]) % p;
	
	int beta = 0;
	
	for (auto i = 0; i < b.size(); ++i) beta += (b.at(i)*r_pow[i]) % p;
	
	beta = beta % p;
	
	int alpha[a.size()-b.size()+1];

	alpha[0] = 0;
	
	for (auto i = 0; i < b.size(); ++i) alpha[0] += (a.at(i)*r_pow[i]) % p;
	
	alpha[0] = alpha[0] % p;
	
	for (auto j = 1; j < a.size() - b.size() + 1; ++j){
		auto prev_term = (a.at(j-1)*r_pow[0]) % p;
		auto prev_val = alpha[j-1];
		while (prev_val < prev_term) prev_val += p;
		auto adjustment = r * (prev_val - prev_term) % p;
		alpha[j] = (adjustment  + a.at(j + b.size() -1)) % p;
	}
	
	for (auto i = 0; i < a.size() - b.size() + 1; ++i){
		if (alpha[i] == beta && matches(a, a.begin() + i, b)){
			results.push_back(a.begin() + i);
		}
	}

	return results;

}

#endif
