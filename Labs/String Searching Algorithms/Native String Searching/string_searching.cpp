#ifndef STRING_SEARCH_CPP
#define STRING_SEARCH_CPP

#include <string>
#include <vector>

bool matches(const std::string& a, std::string::const_iterator itr, const std:: string& b){
	
	for (auto c : b){
		if (*itr != c) return false;
		++itr;
	}
	
	return true;
	
}

std::string::const_iterator substring_position(const std::string& a, const std::string& b){
	
	auto itr = a.begin();
	
	for (; itr != a.end(); ++itr){
		if (matches(a, itr, b)) return itr;
	}
	
	return a.end();
}

std::vector<std::string::const_iterator> all_matches(const std::string& a, const std::string& b){
	
	std::vector<std::string::const_iterator> all_matches;
	
	auto itr = a.begin();
	
	for (; itr != a.end(); ++itr){
		if (matches(a, itr, b)) all_matches.push_back(itr);
	}
	
	return all_matches;
}

#endif
