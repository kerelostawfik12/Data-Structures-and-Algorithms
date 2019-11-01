#ifndef STRING_SEARCH_CPP
#define STRING_SEARCH_CPP

#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

std::vector<int> build_table(const std::string& b){
	
	std::vector<int> table(b.size(), 0);
	auto cnd = 0;
	auto pos = 1;
	table[0] = -1;
	
	while (pos < b.size()){
		if (b.at(pos) == b.at(cnd)){
			table[pos++] = table[cnd++];
		}
		else{
			
			cnd = table[cnd];
			while (cnd >= 0 && b.at(pos) != b.at(cnd)){
				cnd = table[cnd];
			}
			cnd++;
			pos++;
		}
	}
	
	table[pos] = cnd;
	
	return table;
	
}

std::vector<std::string::const_iterator> all_matches(const std::string& a, const std::string& b){
	
	auto table = build_table(b);
	std::vector<std::string::const_iterator> positions;
	
	auto j = 0;
	auto k = 0;
	
	while (j < a.size()){
		if (b.at(k) == a.at(j)){
			j++;
			k++;
			if (k == b.size()){
				positions.push_back(a.begin() + j - k);
				k = table[k];
			}
		}
		else{
			k = table[k];
			if (k < 0){
				j++;
				k++;
			}
		}
	}
	
	return positions;

}

#endif
