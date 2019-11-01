#include <vector>

std::vector<int> insertion_sort(std::vector<int> v_copy){
	
	for (int i = 1; i < v_copy.size(); i++){
		int x = v_copy[i];
		int pos = i - 1;
		while (v_copy[pos] > x && pos >= 0){
			v_copy[pos + 1] = v_copy[pos];
			pos--;
		}
		v_copy[pos + 1] = x;	
	}
	
	return v_copy;
}
