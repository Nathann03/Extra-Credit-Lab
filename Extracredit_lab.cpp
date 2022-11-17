// Binary Search Tree

#include <iostream>
#include <vector>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define COUNT 10

class Node {
public:
	int val;
	Node* left, * right;
	Node(int val) {
		this->val = val;
		this->left = this->right = nullptr;
	}
};

class BST {
private:
	
public:
	Node* root;
	// constructor
	BST() {
		this->root = nullptr;
	}

	//destructor
	~BST() {
		delete root;
	}

	// find the node with the given value and return pointer to node
	Node* find(int val) {
		Node* curr = root;
		while (curr != nullptr) {
			if (curr->val == val) {
				return curr;
			}
			else if (curr->val > val) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		return nullptr;
	}

	// returns the number of nodes in the tree.
	int size(Node* node) {
		if (node == nullptr) {
			return 0;
		}

		return 1 + size(node->left) + size(node->right);
	}


	// remove all nodes in tree except root (give root to start)
	void deleteTree(Node* node)
	{
		if (node == nullptr) return;

		deleteTree(node->left);
		deleteTree(node->right);

		delete node;
	}

	// in order tree traversal array
	void inOrder(Node* node, std::vector<int>& arr) {
		if (node == nullptr) {
			return;
		}
		inOrder(node->left, arr);
		arr.push_back(node->val);
		inOrder(node->right, arr);
	}




	// reverse in order tree traversal array
	void reverseInOrder(Node* node, std::vector<int>& arr) {
		if (node == nullptr) {
			return;
		}
		reverseInOrder(node->right, arr);
		arr.push_back(node->val);
		reverseInOrder(node->left, arr);
	}


	void insert(int val) {
		if (this->root == nullptr) {
			this->root = new Node(val);
			return;
		}
		Node* cur = this->root;
		while (cur != nullptr) {
			if (val < cur->val) {
				if (cur->left == nullptr) {
					cur->left = new Node(val);
					return;
				}
				cur = cur->left;
			}
			else {
				if (cur->right == nullptr) {
					cur->right = new Node(val);
					return;
				}
				cur = cur->right;
			}
		}
	}

	//remove the node with the given value and return pointer to removed node (or nullptr if not found) and rebalance tree if needed
	Node* remove(int val) {
		Node* curr = root;
		Node* parent = nullptr;
		while (curr != nullptr) {
			if (curr->val == val) {
				break;
			}
			else if (curr->val > val) {
				parent = curr;
				curr = curr->left;
			}
			else {
				parent = curr;
				curr = curr->right;
			}
		}
		if (curr == nullptr) {
			return nullptr;
		}
		if (curr->left == nullptr && curr->right == nullptr) {
			if (parent == nullptr) {
				root = nullptr;
			}
			else if (parent->left == curr) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		else if (curr->left == nullptr) {
			if (parent == nullptr) {
				root = curr->right;
			}
			else if (parent->left == curr) {
				parent->left = curr->right;
			}
			else {
				parent->right = curr->right;
			}
		}
		else if (curr->right == nullptr) {
			if (parent == nullptr) {
				root = curr->left;
			}
			else if (parent->left == curr) {
				parent->left = curr->left;
			}
			else {
				parent->right = curr->left;
			}
		}
		else {
			Node* temp = curr->right;
			Node* tempParent = curr;
			while (temp->left != nullptr) {
				tempParent = temp;
				temp = temp->left;
			}
			curr->val = temp->val;
			if (tempParent->left == temp) {
				tempParent->left = temp->right;
			}
			else {
				tempParent->right = temp->right;
			}
			curr = temp;
		}
		return curr;
	}

	// print tree
	void print2DUtil(Node* root, int space)
	{
		// Base case
		if (root == NULL)
			return;

		// Increase distance between levels
		space += COUNT;

		// Process right child first
		print2DUtil(root->right, space);

		// Print current node after space
		// count
		std::cout << std::endl;
		for (int i = COUNT; i < space; i++)
			std::cout << " ";
		std::cout << root->val << "\n";

		// Process left child
		print2DUtil(root->left, space);
	}

	// Wrapper over print2DUtil()
	void print2D(Node* root)
	{
		// Pass initial space count as 0
		print2DUtil(root, 0);
	}
};

void BST_test_program() {
	BST* tree = new BST();
	
	// ask user how many numbers to insert
	int num;
	std::cout << "How many numbers to insert? ";
	std::cin >> num;
	
	// insert numbers
	for (int i = 0; i < num; i++) {
		int val;
		std::cout << "Enter number: ";
		std::cin >> val;
		tree->insert(val);
	}
	
	// print tree
	std::cout << "Current Tree: " << std::endl;
	tree->print2D(tree->root);
	
	
	bool deleted = false;
	// ask user what functions to call on tree
	
	std::cout << "What function to call? (1: deleteTree, 2: inOrder, 3: reverseInOrder, 4: insert, 5: remove, 6: print tree , 7: exit) ";
	int choice;
	std::cin >> choice;
	while (choice != 7) {
		if (choice == 1) {
			tree->deleteTree(tree->root);
			std::cout << "\nTree deleted (Note: breaks out of function call loop!)" << std::endl;
			deleted = true;
			break;
		}
		else if (choice == 2) {
			std::vector<int> arr;
			tree->inOrder(tree->root, arr);
			std::cout << "\nIn order traversal: ";
			for (int i = 0; i < arr.size(); i++) {
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
		else if (choice == 3) {
			std::vector<int> arr;
			tree->reverseInOrder(tree->root, arr);
			std::cout << "\nReverse in order traversal: ";
			for (int i = 0; i < arr.size(); i++) {
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
		else if (choice == 4) {
			int val;
			std::cout << "\nEnter number to insert: ";
			std::cin >> val;
			tree->insert(val);
			std::cout << "\nNumber inserted" << std::endl;
		}
		else if (choice == 5) {
			int val;
			std::cout << "\nEnter number to remove: ";
			std::cin >> val;
			tree->remove(val);
			std::cout << "\nNumber removed" << std::endl;
		}
		else if (choice == 6) {
			tree->print2D(tree->root);
		}
		else {
			std::cout << "\nInvalid choice" << std::endl;
		}
		std::cout << "\nWhat function to call? (1: deleteTree, 2: inOrder, 3: reverseInOrder, 4: insert, 5: remove, 6: print tree , 7: exit) ";
		std::cin >> choice;
	}
	
	// call destructor to delete root.
	if (not(deleted)) {
		delete tree;
	}
	
	std::cout << "\nProgram ended, if memory leaks: crtdump command called after this will display" << std::endl;
	_CrtDumpMemoryLeaks();
	
	
	
	
	
	
	
}

int main() {
	
	BST_test_program();

}



