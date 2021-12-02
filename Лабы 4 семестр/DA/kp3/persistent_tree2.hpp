#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

template<class T>
vector<T> range(T l, T r, T step = 1) {
	vector<T> result;
	for (T i = l; i < r; i += step) {
		result.push_back(i);
	}
	return result;
}

template<class T>
void print(vector<T> objects) {
	for (const T& object : objects) {
		cout << object << " ";
	}

	cout << endl;
}

template<class T>
void print(initializer_list<T> objects) {
	for (const T& object : objects) {
		cout << object << " ";
	}

	cout << endl;
}

template<class T>
void print(T object, bool end = true) {
	if (end == true)
		cout << object << endl;
	else
		cout << object << " ";
}

template<class T, class... Args>
void print(T& first, Args... next) {
	print(first, false);
	print(next...);
}

template<class K, class V>
struct PersistentTree {

	struct node {

		using h_type = unsigned int;
		using nre_type = unsigned int;
		using node_ptr = shared_ptr<node>;

		node_ptr l = nullptr;
		node_ptr r = nullptr;
		K key;
		V value;
		h_type h;
		nre_type nre;

		node(const K& _k, const V& _v): key(_k), value(_v), h(1), nre(0) {}
		node(const K& _k, const V& _v, const h_type& _h, const nre_type& _nre): key(_k), value(_v), h(_h), nre(_nre) {}

		node_ptr RightRotate(node_ptr head) {
			node_ptr temp1 = make_shared<node>(head->l->key, head->l->value, head->l->h, 1 + head->l->nre + head->nre);
			node_ptr temp2 = make_shared<node>(head->key, head->value, head->h, head->nre);
			temp1->l = head->l->l;
			temp1->r = temp2;
			temp2->l = head->l->r;
			temp2->r = head->r;
			FixHeight(temp2);
			FixHeight(temp1);
			return temp1;
		}

		node_ptr LeftRotate(node_ptr head) {

			if (head->key == head->r->key)
				return head;

			node_ptr temp1 = make_shared<node>(head->r->key, head->r->value, head->r->h, head->r->nre);
			node_ptr temp2 = make_shared<node>(head->key, head->value, head->h, head->nre - 1 - head->r->nre);
			temp1->l = temp2;
			temp1->r = head->r->r;
			temp2->l = head->l;
			temp2->r = head->r->l;
			FixHeight(temp2);
			FixHeight(temp1);
			return temp1;
		}

		node_ptr Balancing(node_ptr head) {
			node_ptr temp = make_shared<node>(head->key, head->value, head->h, head->nre);
			temp->l = head->l;
			temp->r = head->r;
			FixHeight(temp);
			if (Balance(temp)==2) {
				if (Balance(temp->l)<0) {
					temp->l = LeftRotate(head->l);
				}
				return RightRotate(temp); 
			} else if (Balance(temp)==-2) {
				if (Balance(temp->r)>0) {
					temp->r = RightRotate(head->r);
				}
				return LeftRotate(temp);
			}
			return temp;
		}

		node_ptr Insert(const node_ptr parent, const K& key, const V& value) {

			if (parent) {
				node_ptr temp;
				if (key >= parent->key) {
					temp = make_shared<node>(parent->key, parent->value, parent->h, parent->nre + 1);
					temp->l = parent->l;
					temp->r = Insert(parent->r, key, value);
				} else if (key < parent->key) {
					temp = make_shared<node>(parent->key, parent->value, parent->h, parent->nre);
					temp->r = parent->r;
					temp->l = Insert(parent->l, key, value);
				}

				return Balancing(temp);
			}

			return make_shared<node>(key, value);
		}

		node_ptr MinRight(node_ptr head) {
			node_ptr temp = head;
			while (temp->l) {
				temp = temp->l;
			}
			return temp;
		}

		node_ptr RemoveMin(node_ptr head) {
			if (!head->l) {
				node_ptr temp = head->r;
				return temp;
			}
			node_ptr temp = make_shared<node>(head->key, head->value, head->h, head->nre);
			temp->r = head->r;
			temp->l = RemoveMin(head->l);
			return Balancing(temp);
		}

		node_ptr Remove(node_ptr parent, const K& key) {
			if (!parent) 
				return nullptr;

			node_ptr temp;
			if (key == parent->key) {
				if (!parent->l and !parent->r) {
					return nullptr;
				}

				if (!parent->r) {
					return parent->l;
				}

				node_ptr min_right = MinRight(parent->r);
				temp = make_shared<node>(min_right->key, min_right->value, parent->h, parent->nre - 1);
				temp->l = parent->l;
				temp->r = RemoveMin(parent->r);
			} else if (key < parent->key) {
				temp = make_shared<node>(parent->key, parent->value, parent->h, parent->nre);
				temp->r = parent->r;
				temp->l = Remove(parent->l, key);
			} else {
				temp = make_shared<node>(parent->key, parent->value, parent->h, parent->nre - 1);
				temp->l = parent->l;
				temp->r = Remove(parent->r, key);
			}
			
			return Balancing(temp);

		}

		nre_type FindNumberAbove(const node_ptr head, const K& key) {
			if (head) {
				if (key >= head->key) {
					return FindNumberAbove(head->r, key);
				} else {
					return head->nre + 1 + FindNumberAbove(head->l, key);
				}
			}

			return 0;
		}

		h_type Height(const node_ptr head) const {
			return head ? head->h : 0;
		}

		int Balance(const node_ptr head) const {
			return head ? Height(head->l)-Height(head->r) : 0;
		}

		void FixHeight(node_ptr head) {
			head->h = (Height(head->l)>Height(head->r) ? Height(head->l) : Height(head->r))+1;
		}

		void Print(const node_ptr head, unsigned int tab) const {
			if (head) {
				Print(head->r, tab + 1);
				for (unsigned int i = 0; i < tab; i++) std::cout << "\t";
				std::cout << "(" << head->key << ", " << head->value << ", " << head->h << ", " << head->nre << ")\n";
				Print(head->l, tab + 1);
			}
		}


	};

	using node_ptr = shared_ptr<node>;

	unsigned int number_of_versions = 0;
	vector<node_ptr> trees;

	void Insert(const K& key, const V& value, const bool flag = false) {
		if (!flag) {
			if (trees.empty()) {
				trees.push_back(nullptr);
				trees[0] = make_shared<node>(key, value);
			} else {
				trees.push_back(nullptr);
				trees[number_of_versions] = trees[number_of_versions]->Insert(trees[number_of_versions - 1], key, value);
			}
			number_of_versions++;
		} else {
			if (trees.empty()) {
				trees.push_back(nullptr);
				trees[0] = make_shared<node>(key, value);
				number_of_versions++;
			} else {
				trees[number_of_versions - 1] = trees[number_of_versions - 1]->Insert(trees[number_of_versions - 1], key, value);
			}
		}
	}

	void Remove(const K& key, const bool flag = false) {
		if (!flag) {
			trees.push_back(nullptr);
			trees[number_of_versions] = trees[number_of_versions]->Remove(trees[number_of_versions - 1], key);
			number_of_versions++;
		} else {
			trees[number_of_versions - 1] = trees[number_of_versions - 1]->Remove(trees[number_of_versions - 1], key);
		}
	}

	void NotChange() {
		trees.push_back(nullptr);
		trees[number_of_versions] = trees[number_of_versions - 1];
		number_of_versions++;
	}

	unsigned int FindNumberAbove(const unsigned int version, const K& key) {
		if (version >= trees.size()) {
			print("bad version: ", version);
			throw "There is no such version";
		}

		return trees[version]->FindNumberAbove(trees[version], key); 
	}

	void Print(const unsigned int version) const {
		if (version >= trees.size()) {
			cout << "|--------------------------------------------------|" << endl;
			cout << "There is no such version of tree" << endl;
			cout << "|--------------------------------------------------|" << endl;
			return;
		}

		cout << "|--------------------------------------------------|" << endl;
		cout << "[" << version << "]" << endl;
		trees[version]->Print(trees[version], 0);
		cout << "|--------------------------------------------------|" << endl;
	}

	void Print() const {
		unsigned int v = 0;
		cout << number_of_versions << " versions in total:\n";
		for (node_ptr tree : trees) {
			cout << "|--------------------------------------------------|" << endl;
			cout << "[" << v << "]" << endl;
			tree->Print(tree, 0);
			cout << "|--------------------------------------------------|" << endl;
			v++;
		}
	}

};