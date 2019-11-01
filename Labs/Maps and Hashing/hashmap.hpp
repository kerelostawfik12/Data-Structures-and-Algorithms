#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <utility>

template <typename value_type>
class hashmap{

	private:

	static const size_t SIZE = 5;
	std::pair<int, value_type> map[SIZE];
	bool in_use[SIZE] { false };
	
	public:
	
	unsigned hash(const int&) const;
	void add(const int&, const value_type&);
	const value_type get(const int&) const;
	bool has_key(const int&) const;
	bool has_value(const value_type&) const;
	int get_key(const value_type&) const;

};

template <typename value_type> unsigned hashmap<value_type>::hash(const int& key) const {
	return key % SIZE;
}

template <typename value_type> void hashmap<value_type>::add(const int& key, const value_type& value){
	auto hashed_key = hash(key);
	
	unsigned probes = 0;
	
	while (in_use[hashed_key] && map[hashed_key].first != key){
		hashed_key = (hashed_key + 1)%SIZE;
		++probes;
	}

	if (probes < SIZE){
		map[hashed_key] = {key, value};
		in_use[hashed_key] = true;
	}

}

template <typename value_type> const value_type hashmap<value_type>::get(const int& key) const{
	auto hashed_key = hash(key);
	unsigned attempts = 0;
	
	while (attempts < SIZE && in_use[hashed_key]){
		if (map[hashed_key].first == key) return map[hashed_key].second;
		hashed_key = (hashed_key + 1) % SIZE;
		++attempts;
	}
	
	return value_type();
}

template <typename value_type> bool hashmap<value_type>::has_key(const int& key) const {
	
	auto hashed_key = hash(key);
	
	while (in_use[hashed_key]){
		if (map[hashed_key].first == key) return true;
		hashed_key = (hashed_key + 1) % SIZE;
	}
	
	return false;
	
}

template <typename value_type> bool hashmap<value_type>::has_value(const value_type& value) const {
	
	for (int i = 0; i < SIZE; ++i){
		if (in_use[i] && map[i].second == value) return true;
	}
	
	return false;
	
}

template <typename value_type> int hashmap<value_type>::get_key(const value_type& value) const {
	
	for (int i = 0; i < SIZE; ++i){
		if (in_use[i] && map[i].second == value) return map[i].first;
	}
	
	return 0;
	
}

#endif
