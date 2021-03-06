#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class priority_queue {
public:
	class node {
	public:
		int key;
		node* tail;

		node() {
			key = 0;
			tail = nullptr;
		}

		node(int key) {
			this->key = key;
			this->tail = nullptr;
		}
	};

	node* head;
	int size;

	priority_queue() {
		this->head = nullptr;
		size = 0;
	}

	bool empty() {
		return head == nullptr;
	}

	void qsort(int beg, int end) {
		int f = beg;
		int l = end;
		node* mid = find((f + l) / 2);
		while (f < l) {
			while (find(f)->key < mid->key) f++;
			while (find(l)->key > mid->key) l--;
			if (f <= l) {
				int t = find(f)->key;
				find(f)->key = find(l)->key;
				find(l)->key = t;
				f++;
				l--;
			}
		}
		if (f < end) qsort(f, end);
		if (l > beg) qsort(beg, l);
	}

	void qsort() {
		qsort(0, size-1);
	}

	node* find(int i) {
		int k = 0;
		node* temp = head;
		if (temp != nullptr)
			while (k != i) {
				temp = temp->tail;
				k++;
			}

		return temp;
	}

	void push(int key) {
		node* n = new node(key);

		if (head == nullptr)
			head = n;
		else {
			n->tail = head;
			head = n;
		}
		size++;
		qsort();
	}

	int pop() {
		int k = head->key;
		head = head->tail;
		return k;
	}
};

class map_pair {
public:
	int first;
	char second[32];

	map_pair() {}

	map_pair(int key,  char* value) {
		this->first = key;
		strcpy(this->second, value);
	}

	bool operator > (map_pair& p) {
		return strcmp(this->second, p.second) > 0;
	}

	bool operator < (map_pair& p) {
		return strcmp(this->second, p.second) < 0;
	}

	bool operator == (map_pair& p) {
		return strcmp(this->second, p.second) == 0;
	}
};

ostream& operator << (ostream& o, map_pair& p) {
	return o << "{" << p.first << ", " << p.second << "}" << endl;
}

class map {
public:
	class node {
	public:
		node* right;
		node* left;
		map_pair key;

		node() {
			right = nullptr;
			left = nullptr;
		}
		node(map_pair& key) {
			this->key = key;
			right = nullptr;
			left = nullptr;
		}
	};

	node* root;

	map() {
		root = nullptr;
	}

	void push(node* parent, map_pair& key) {
		if (key > parent->key) {
			if (parent->right)
				push(parent->right, key);
			else
				parent->right = new node(key);
		}
		else if (key < parent->key) {
			if (parent->left)
				push(parent->left, key);
			else
				parent->left = new node(key);
		}
		else if (key == parent->key) {
			parent->key.first++;
		}
	}

	void push(map_pair& key) {
		if (root == nullptr)
			root = new node(key);
		else
			push(root, key);
	}

	void print(node* parent) {
		if (parent->left)
			print(parent->left);
		cout << parent->key;
		if (parent->right)
			print(parent->right);
	}

	void print() {
		print(root);
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
	
	// Приоритетная очередь

	priority_queue q1;

	q1.push(12);
	q1.push(4);
	q1.push(20);
	q1.push(8);
	q1.push(4);

	while (!q1.empty()) {
		cout << "{" << q1.pop() << "} ";
	}
	cout << "\n\n";

	// Частотный словарь

	map m1;

	ifstream fi("input.txt");
	string t, str;
	while (!fi.eof()) {
		getline(fi, t);
		str.append(t + " ");
	}
	fi.close();

	char sep[] = " :;.,!\t\n()[]+%";
	char* buffer = strtok((char*)str.c_str(), sep);

	map_pair temp;
	while (buffer != nullptr) {
		temp = map_pair(1, strlwr(buffer));
		m1.push(temp);
		buffer = strtok(nullptr, sep);
	}

	m1.print();
	
	return 0;
}