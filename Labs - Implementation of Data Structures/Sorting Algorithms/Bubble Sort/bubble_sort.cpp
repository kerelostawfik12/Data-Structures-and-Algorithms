#include <vector>

std::vector<int> bubble_sort(std::vector<int> v_copy){
	
	bool swapped;
	do {
		swapped = false;
		
		for (int i = 0; i < v_copy.size() - 1; i++){
			if (v_copy[i] > v_copy[i+1]){
				v_copy[i] += v_copy[i+1];
				v_copy[i+1] = v_copy[i] - v_copy[i+1];
				v_copy[i] -= v_copy[i+1];
				swapped = true;
			}
		}
		
	}while(swapped);
	
	return v_copy;
}
