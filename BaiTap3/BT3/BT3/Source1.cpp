#include <iostream>
using namespace std;

struct PriorityQueue {
private:
	int* heap;
	int* priority;
	int size;
	int capacity;
public:
	//constructor
	PriorityQueue(int cap = 1000) {
		capacity = cap;
		size = 0;
		heap = new int[capacity];
		priority = new int[capacity];
	}

	int parent(int i) { return (i - 1) / 2; }
	int leftChild(int i) { return 2 * i + 1; }
	int rightChild(int i) { return 2 * i + 2; }

	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	//insert
	void enqueue(int value, int p) {
		if (size < capacity) {
			int i = size++;
			heap[i] = value;
			priority[i] = p;

			while (i != 0 && priority[parent(i)] > priority[i]) {
				swap(heap[i], heap[parent(i)]);
				swap(priority[i], priority[parent(i)]);
				i = parent(i);
			}
		}
		else {
			cout << "Priority queue is full!\n";
		}
	}

	//remove
	int dequeue() {
		if (size == 0) {
			cout << "Priority queue is empty!\n";
			return -1;
		}
		else {
			int root = heap[0];
			heap[0] = heap[--size];
			priority[0] = priority[size];

			minHeapify(0);
			return root;
		}
	}

	void minHeapify(int i) {
		int smallest = i;
		int l = leftChild(i);
		int r = rightChild(i);

		if (l < size && priority[l] < priority[smallest]) {
			smallest = l;
		}

		if (r < size && priority[r] < priority[smallest]) {
			smallest = r;
		}

		if (smallest != i) {
			swap(heap[i], heap[smallest]);
			swap(priority[i], priority[smallest]);
			minHeapify(smallest);
		}
	}

	//remove max
	int removeMax() {
		if (size == 0) {
			cout << "Priority queue is empty!\n";
			return -1;
		}
		else {
			int maxIndex = 0;
			for (int i = 1; i < size; i++) {
				if (priority[i] > priority[maxIndex]) {
					maxIndex = i;
				}
			}

			int maxValue = heap[maxIndex];
			heap[maxIndex] = heap[--size];
			priority[maxIndex] = priority[size];

			minHeapify(maxIndex);
			return maxValue;
		}
	}

	//print priority queue
	void display() {
		if (size == 0) {
			cout << "Priority queue is empty!\n";
			return;
		}
		cout << "Priority queue: ";
		for (int i = 0; i < size; i++) {
			cout << "(" << heap[i] << "," << priority[i] << ")" << " ";
		}
		cout << endl;
	}
};

//sort array
void sortArray(int arr[], int n) {
	PriorityQueue pq(n);
	for (int i = 0; i < n; i++) {
		pq.enqueue(arr[i], arr[i]);
	}
	for (int i = 0; i < n; i++) {
		arr[i] = pq.dequeue();
	}
}

//print array
void displayArray(int arr[], int n) {
	cout << "Sorted array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {

	cout << "Chay thu cau truc hang doi uu tien: " << endl;
	PriorityQueue pq = PriorityQueue();
	pq.dequeue();
	pq.enqueue(4, 2);
	pq.enqueue(1, 4);
	pq.enqueue(3, 1);
	pq.enqueue(9, 5);
	pq.enqueue(7, 3);

	pq.display();

	cout << "Value has max priority: " << pq.removeMax();

	cout << endl;
	cout << "-----------------------" << endl;
	cout << "Sap xep mang tang dan: " << endl;
	int arr[] = { 4, 1, 3, 9, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "Original array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	sortArray(arr, n);

	displayArray(arr, n);

	return 0;
}
