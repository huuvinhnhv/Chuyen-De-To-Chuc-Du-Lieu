#include <iostream>

using namespace std;

struct Node {
    int value;
    int priority;
    Node* next;
};

class PriorityQueue {
private:
    Node* front;

    Node* createNode(int value, int priority) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->priority = priority;
        newNode->next = NULL;
        return newNode;
    }

public:
    PriorityQueue() {
        front = NULL;
    }

    void enqueue(int value, int priority) {
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

    void dequeue() {
        if (front == NULL) {
            cout << "Queue is empty\n";
            return;
        }

        Node* temp = front;
        front = front->next;
        cout << "Dequeued item: " << temp->value << endl;
        delete temp;
    }

    void display() {
        if (front == NULL) {
            cout << "Queue is empty\n";
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

    q.enqueue(5, 2);
    q.enqueue(2, 1);
    q.enqueue(8, 3);
    q.enqueue(4, 2);

    q.display();

    q.dequeue();

    q.display();

    q.enqueue(6, 1);

    q.display();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    return 0;
}