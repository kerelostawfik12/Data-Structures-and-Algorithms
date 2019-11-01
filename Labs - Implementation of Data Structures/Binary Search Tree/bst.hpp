#ifndef BST_HPP
#define BST_HPP

#include <vector>
#include <iostream>

template <typename T>
class bst {
	
	private:
	
	std::vector<T> tree;
	std::vector<bool> in_tree;
	
	bool has_left_child(const int&) const;
	bool has_right_child(const int&) const;
	void move_subtree_up(const int&, const int&);
	
	public:
	
	bst();
	void insert(const T&);
	bool contains(const T&) const;
	int index_of(const T&) const;
	void remove(const T&);
	
};

template <typename T>
bool bst<T>::has_left_child(const int& pos) const {
	return (pos >= 0) && (2*pos+1 < tree.size()) ? in_tree[2*pos + 1] : false;
}

template <typename T>
bool bst<T>::has_right_child(const int& pos) const { 
	return pos >= 0 && 2*pos+2 < tree.size() ? in_tree[2*pos + 2] : false;
}

template <typename T>
void bst<T>::move_subtree_up(const int& from, const int& to) {
	
	if (from < tree.size() && in_tree[from]){
 		
		tree[to] = tree[from];
		in_tree[to] = true;
		in_tree[from] = false;
		
		if (has_left_child(from) || has_right_child(from)){
			move_subtree_up(2*from + 1, 2*to + 1);
			move_subtree_up(2*from + 2, 2*to + 2);
		}

	}
	
}

template <typename T>
bst<T>::bst(){}

template <typename T>
void bst<T>::insert(const T& t){
	
	int pos = 0;
	
	while (pos < tree.size() && in_tree[pos]){
		pos = t < tree[pos] ? 2*pos + 1 : 2*pos +2;
	}
	
	if (pos >= tree.size()){
		tree.resize(2*tree.size() + 1, 0);
		in_tree.resize(2*in_tree.size() + 1, false);
	}
	
	tree[pos] = t;
	in_tree[pos] = true;
	
}

template <typename T>
bool bst<T>::contains(const T& t) const { 
	
	int pos = 0;
	
	while (pos < tree.size() && in_tree[pos] && tree[pos] != t){
		pos = t < tree[pos] ? 2*pos + 1 : 2*pos +2;
	}
	
	return pos < tree.size() && in_tree[pos];
	
}

template <typename T>
int bst<T>::index_of(const T& t) const { 
	
	int pos = 0;
	
	while (pos < tree.size() && in_tree[pos] && tree[pos] != t){
		pos = t < tree[pos] ? 2*pos + 1 : 2*pos +2;
	}
	
	return pos < tree.size() && in_tree[pos] ? pos : -1;
	
}

template <typename T>
void bst<T>::remove(const T& t){
	
	int pos_to_remove = index_of(t);
	
	if (pos_to_remove != -1){
		
		if (!has_left_child(pos_to_remove) && !has_right_child(pos_to_remove)){
			in_tree[pos_to_remove] = false;
		}
		else if (!has_left_child(pos_to_remove) || !has_right_child(pos_to_remove)){
			
			move_subtree_up(2*pos_to_remove + (has_left_child(pos_to_remove) ? 1 : 2), pos_to_remove);
			
		}
		else {
			
			int replacement_pos = 2*pos_to_remove + 2;
			
			while (has_left_child(replacement_pos)){
				replacement_pos = 2*replacement_pos + 1;
			}
			
			T replacement_val = tree[replacement_pos];
			remove(replacement_val);
			tree[pos_to_remove] = replacement_val;
		}
		
	}
	
}

#endif
