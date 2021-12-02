#include <iostream>
#pragma once

template<class T, class V>
struct TAVLTree {
	TAVLTree<T, V> *left = 0;
	TAVLTree<T, V> *right = 0;

	T key;
	V value;
	unsigned int h;

	//TAVLTree () = default;
	TAVLTree (const T& k, const V& v);
	~TAVLTree () = default;
	void RemoveTree(TAVLTree<T, V> *head);

	TAVLTree<T, V>* RightRotate(TAVLTree<T, V> *head);
	TAVLTree<T, V>* LeftRotate(TAVLTree<T, V> *head);
	TAVLTree<T, V>* Balancing(TAVLTree<T, V> *head);

	TAVLTree<T, V>* Insert(TAVLTree<T, V> *head, const T& key, const V& value);
	bool Search(TAVLTree<T, V> *head, const T& key);

	void Print(const TAVLTree<T, V> *head, unsigned int n);
	// void Save(const TAVLTree<T, V> *head, FILE *s);
	// TAVLTree<T, V>* BinInsert(TAVLTree<T, V> *head, const T& key, const V value);
	// TAVLTree<T, V>* Load(FILE *s);

	unsigned int Height(const TAVLTree<T, V> *head);
	int Balance(const TAVLTree<T, V> *head);
	void FixHeight(TAVLTree<T, V> *head);
};

template<class T, class V>
TAVLTree<T, V>::TAVLTree (const T& k, const V& v): key(k), value(v), h(1) {} 

template<class T, class V>
void TAVLTree<T, V>::RemoveTree(TAVLTree<T, V> *head){
	if (!head) return;
	if (head->right) {
		RemoveTree(head->right);
	}
	if (head->left) {
		RemoveTree(head->left);
	}
	delete head;
} 

template<class T, class V>
TAVLTree<T, V>* TAVLTree<T, V>::RightRotate(TAVLTree<T, V> *head) {
	TAVLTree *temp = head->left;
	head->left = temp->right;
	temp->right = head;
	FixHeight(head);
	FixHeight(temp);
	return temp;
}

template<class T, class V>
TAVLTree<T, V>* TAVLTree<T, V>::LeftRotate(TAVLTree<T, V> *head) {
	TAVLTree *temp = head->right;
	head->right = temp->left;
	temp->left = head;
	FixHeight(head);
	FixHeight(temp);
	return temp;
}

template<class T, class V>
TAVLTree<T, V>* TAVLTree<T, V>::Balancing(TAVLTree<T, V> *head) {
	FixHeight(head);
	if (Balance(head)==2) {
		if (Balance(head->left)<0) {
			head->left = LeftRotate(head->left);
		}
		return RightRotate(head); 
	} else if (Balance(head)==-2) {
		if (Balance(head->right)>0) {
			head->right = RightRotate(head->right);
		}
		return LeftRotate(head);
	}
	return head;
}

template<class T, class V>
TAVLTree<T, V>* TAVLTree<T, V>::Insert(TAVLTree<T, V> *head, const T& key, const V& value) {
	if (head) {
		if (key == head->key) {
			std::cout << "Exist\n";
			return head;
		} else if (key < head->key) {
			head->left = Insert(head->left, key, value);
		} else {
			head->right = Insert(head->right, key, value);
		}
		return Balancing(head);
	}
	std::cout << "OK\n";
	TAVLTree<T, V>* res = new TAVLTree<T, V>(key, value);
	return res;
}

template<class T, class V>
bool TAVLTree<T, V>::Search (TAVLTree<T, V> *head, const T& key) {
	TAVLTree<T, V> *temp = head;
	while (temp) {
		if (key==temp->key) {
			std::cout << "OK: " << temp->value << "\n";
			return true;
		} else if (key > temp->key) {
			temp = temp->right;
		} else {
			temp = temp->left;
		}
	}

	std::cout << "NoSuchWord\n";
	return false;
}

template<class T, class V>
void TAVLTree<T, V>::Print(const TAVLTree<T, V> *head, unsigned int n) {
	if (head) {
		Print(head->right, n+1);
		for (unsigned int i=0; i<n; i++) std::cout << "\t";
		std::cout << "(" << head->key << ", " << head->value << ")\n";
		Print(head->left, n+1);
	}
}

// void TAVLTree<T, V>::Save(const TAVLTree *head, FILE *s) {
// 	if (head) {
// 		fprintf(s, "%s %llu ", head->key.str, head->value);
// 		Save(head->left, s);
// 		Save(head->right, s);
// 	}
// }

// template<class T, class V>
// TAVLTree<T, V>* TAVLTree<T, V>::BinInsert(TAVLTree<T, V> *head, const T& key, const V value) {
// 	if (head) {
// 		if (key > head->key) {
// 			head->right = BinInsert(head->right, key, value);
// 		} else {
// 			head->left = BinInsert(head->left, key, value);
// 		} 
// 		return head;
// 	}
// 	return new TAVLTree<T, V>(key, value);
// }

// TAVLTree* TAVLTree<T, V>::Load(FILE *s) {
// 	TAVLTree *res = 0; 
// 	T k;
// 	V val;
// 	while (fscanf(s, "%s %llu ", k, &val)>0) {
// 		res = res->BinInsert(res, T(k), val);
// 	}
// 	return res;
// }

template<class T, class V>
unsigned int TAVLTree<T, V>::Height(const TAVLTree<T, V> *head) {
	return head ? head->h : 0;
}

template<class T, class V>
int TAVLTree<T, V>::Balance(const TAVLTree<T, V> *head) {
	return head ? Height(head->left)-Height(head->right) : 0;
}

template<class T, class V>
void TAVLTree<T, V>::FixHeight(TAVLTree<T, V> *head) {
	head->h = (Height(head->left)>Height(head->right) ? Height(head->left) : Height(head->right))+1;
}
