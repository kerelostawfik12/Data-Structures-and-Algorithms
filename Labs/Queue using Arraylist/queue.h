template <typename T>
class queue {
	
	private:
	
	T * data;
	int capacity;
	int front;
	int size;
	
	public:
	
	//constructors
	queue(){
		capacity = 10;
		front = 0;
		size = 0;
		data = new T[capacity];
	}
	
	queue(int capacity){
		this->capacity = capacity;
		front = 0;
		size = 0;
		data = new T[capacity];
	}
	
	~queue(){
		delete[] data;
	}
	
	void offer(T t){
		
		if (size >= capacity){			
			//Move everything to a new array
			int newCapacity = capacity * 2;
			T * newData = new T[capacity];
			
			for (int i = 0 ; i < size; i++){
				newData[i] = data[(front + i)%capacity];
			}
			
			delete[] data;
			capacity = newCapacity;
			data = newData;
			front = 0;
			
		}
		
		data[(front+size)%capacity] = t;
		size++;
		
	}
	
	T poll(){
		
		if (size > 0){
			T ret = data[front];
			size--;
			front = (front + 1)%capacity;
			return ret;
		}
		
		return T();
	}
	
	bool empty(){
		return 0 == size;
	}
	
};
