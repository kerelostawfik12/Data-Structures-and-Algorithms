#include <vector>

std::vector<int> merge(std::vector<int> v1, std::vector<int> v2){
	
	std::vector<int> merged;
	
	auto it1 = v1.begin();
	auto it2 = v2.begin();
	

	
	while (it1 < v1.end() && it2 < v2.end()){
		if (*it1 < *it2){ 
			merged.push_back(*it1);
			++it1;
		}
		else{
			 merged.push_back(*it2);
			++it2;
		}
	}
	
	while (it1 < v1.end()){ 
			merged.push_back(*it1);
			++it1;
	}
	
	while (it2 < v2.end()){
			 merged.push_back(*it2);
			++it2;
	}
	
	return merged;
}

std::vector<int> msort(std::vector<int> v){
	
	if (v.size() == 1) return v;
	
	std::vector<int> v1;
	for (int i = 0; i < v.size()/2; i++){

		v1.push_back(v[i]);
	}
	
	std::vector<int> v2;
	for (int i = v.size()/2; i < v.size(); i++){
		v2.push_back(v[i]);
	}
	
	return merge(msort(v1), msort(v2));
	
}

std::vector<int> merge_sort(std::vector<int> v_copy){
	return msort(v_copy);
}
