#include <iostream>
using namespace std;
struct Node {
	int value;
	int priority;
	Node* next;
};

struct PriorityQueue {

	Node* front = NULL;

	Node* createNode(int value, int priority) {
		Node* newNode = new Node;
		newNode->value = value;
		newNode->priority = priority;
		newNode->next = NULL;
		return newNode;
	}

	//insert
	void insert(int value, int priority) {
		Node* newNode = createNode(value, priority);
		if (front == NULL || priority < front->priority) {
			newNode->next = front;
			front = newNode;
		}
		else {
			Node* current = front;
			while (current->next != NULL && current->next->priority <= priority) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
	}
	//removeMax
	Node* removeMax() {
		if (front == NULL) {
			cout << "Queue is empty!\n";
			return NULL;
		}
		Node* temp = front;
		front = front->next;
		return temp;
	}

	void display() {
		if (front == NULL) {
			cout << "Queue is empty!\n";
			return;
		}

		Node* current = front;
		while (current != NULL) {
			cout << current->value << "(" << current->priority << ") ";
			current = current->next;
		}
		cout << endl;
	}


};

int main() {
	PriorityQueue q;

	q.insert(5, 2);
	q.insert(2, 1);
	q.insert(8, 3);
	q.insert(4, 2);

	q.display();

	Node* max = q.removeMax();

	cout << "Value with highest priority: " << max->value << "("<< max->priority <<")" << endl;

	q.display();

	return 0;
}