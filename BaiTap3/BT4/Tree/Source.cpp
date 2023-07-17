#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data) {
		this->data = data;
		left = NULL;
		right = NULL;
	}
};

struct BinaryTree {
	Node* root;

	BinaryTree() {
		root = NULL;
	}

	void insert(int data) {
		Node* newNode = new Node(data);
		if (root == NULL) {
			root = newNode;
			return;
		}
		Node* current = root;
		while (true) {
			if (data < current->data) {
				if (current->left == NULL) {
					current->left = new Node(data);
					return;
				}
				current = current->left;
			}
			else {
				if (current->right == NULL) {
					current->right = new Node(data);
					return;
				}
				current = current->right;
			}
		}
	}
	void preOrder(Node* node) {
		if (node == NULL) return;
		cout << node->data << " ";
		preOrder(node->left);
		preOrder(node->right);
	}

	int sumNeg(Node* root) {
		if (root == NULL) return 0;
		int sum = 0;
		if (root->data < 0) {
			sum += root->data;
		}
		sum += sumNeg(root->left);
		sum += sumNeg(root->right);
		return sum;
	}
};

int main() {
	BinaryTree tree;
	tree.insert(6);
	tree.insert(3);
	tree.insert(4);
	tree.insert(7);
	tree.insert(9);
	tree.insert(-2);
	tree.insert(-4);
	cout << "Duyet truoc cay: \n";
	tree.preOrder(tree.root);
	cout << endl;
	cout << "Tong cac phan tu am trong cay: ";
	cout << tree.sumNeg(tree.root);
	return 0;
}
