#include <vector>
#include <iostream>

int partition(std::vector<int>& v, int low, int high){
	
	int pivot = v[high];
	int part = low - 1;
	
	for (int j = low; j < high; ++j){
		
		if (v[j] < pivot){
			part++;
			int temp = v[j];
			v[j] = v[part];
			v[part] = temp;
		}

		
	}
	
	v[high] = v[part + 1];
	v[part + 1] = pivot;
	return part + 1;
	
}

void qsort(std::vector<int>& v, int low, int high){
	
	if (low < high){
		int p = partition(v, low, high);
		qsort(v, low, p-1);
		qsort(v, p+1, high);
	}
	
}

std::vector<int> quick_sort(std::vector<int> v_copy){
	qsort(v_copy, 0, v_copy.size() - 1);
	return v_copy;
}
