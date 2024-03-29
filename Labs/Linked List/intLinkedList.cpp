#include "intLinkedList.h"

intLinkedList::intNode::intNode() {
	data = 0;
	next = nullptr;
}

intLinkedList::intNode::intNode(intNode * n, int d){
	data = d;
	next = n;
}

intLinkedList::intNode::~intNode() {
  //You don't have to do anything for this one.
}

int intLinkedList::intNode::getData(){
	return data;
	
}

intLinkedList::intNode * intLinkedList::intNode::getNext(){
	return next;
}

void intLinkedList::intNode::setNext(intNode * n){
	 next = n;
}

intLinkedList::intLinkedList(){
	head = nullptr;
	length = 0;
}

intLinkedList::~intLinkedList(){
	intNode * current = head;
	intNode * next = current->getNext();
	while(next !=nullptr){
		delete current;
		current = next;
		next = current -> getNext();
	}
}

bool intLinkedList::isEmpty(){
	return length == 0;
	
}

void intLinkedList::prepend(int c){
	intNode * newNode = new intNode(head, c);
	head = newNode;
	length++;
		
}

void intLinkedList::append(int c){
	/*if(head == nullptr){
		prepend(c);
	}
	else{
		intNode * current = head;
		while(current -> getNext() != nullptr){
			current ->getNext();
		}
		current->setNext(new intNode(nullptr, c));
	}
	length++;
	*/
	  intNode * newintNode = new intNode(nullptr, c);
  if (head == nullptr){
    head = newintNode;
  }
  else{
    intNode * curr = head;
    while (curr->getNext() != nullptr){
      curr = curr->getNext();
    }
    curr->setNext(newintNode);
  }
  length++;
}

int intLinkedList::getHead(){
	return head -> getData();

}

intLinkedList * intLinkedList::tail(){
	intLinkedList * newList = new intLinkedList();
	
	if (head !=0){
		intNode * current = head -> getNext();
		
		while (current != nullptr){
			newList->append(current->getData());
			current = current->getNext();
			
		}
	}
	return newList;
	
	
}



