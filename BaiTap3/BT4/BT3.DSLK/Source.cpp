#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

struct List {
	Node* head;

	List() {
		head = NULL;
	}

	void insert(int data) {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = head;
		this->head = newNode;
	}

	void printList() {
		Node* current = this->head;
		cout << "DSLK: \n";
		while (current != NULL) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int sumNeg(Node* current) {
		if (current == NULL) return 0;
		int sum = 0;
		if (current->data < 0) sum = current->data;
		return sum + sumNeg(current->next);
	}

};

int main() {
	List list;
	list.insert(5);
	list.insert(7);
	list.insert(9);
	list.insert(-4);
	list.insert(-2);
	list.insert(-10);
	list.insert(9);
	list.insert(-19);

	Node* head = list.head;

	list.printList();

	cout <<"Tong phan tu am trong DSLK: "<< list.sumNeg(head);
	return 0;
}
