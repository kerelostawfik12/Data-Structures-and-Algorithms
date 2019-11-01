#include <vector>

template <typename T>
class stack {

	private:

	std::vector<T> data;
	
	public:
	
	stack(){}
	~stack(){}
	
	void push(T t){
		data.push_back(t);
	}
	
	T pop() {
		T ret = data.back();
		data.pop_back();
		return ret;
	}
	
	T peek() {
		return data.back();
	} 
	
	bool empty() {
		return data.size() == 0;
	}

};
