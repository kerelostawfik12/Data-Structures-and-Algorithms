#include <iostream>
#include "intList.h"
#include "intLinkedList.h"

int main(){
	
	intList * l = new intLinkedList();
	
	for (int i = 0; i < 10; i++){
		l->append(i);
	}
	
	intList * k = l;
	while (!k->isEmpty()){
		std::cout << k->getHead() << " ";
		intList * temp = k->tail();
		delete k;
		k = temp;
	}
	std::cout << std::endl;
	return 0;
}
