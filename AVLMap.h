#ifndef AVLMAP
#define AVLMAP

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename K,typename V>
class AVLMap {
	struct Node {
		Node(Node *p):left(nullptr),right(nullptr),parent(p),height(1) {}
		Node():left(nullptr),right(nullptr),parent(nullptr),height(1) {}
		std::pair<K,V> data;
		Node *left;
		Node *right;
		Node *parent;
		int height;
	};

	int get_height(Node* n) {
		if (n == nullptr) return 0;
		else return n->height;
	}

	void seth(Node* n){
		auto rover = n;
        //int h = 0;
		while(rover!= nullptr) {
		    rover->height = (std::max(get_height(rover->right),get_height(rover->left))) +1;
    //cout << "Height: " << rover->height << endl;      
    rover = rover->parent;
		}
		//if(n==nullptr) return;
		//else {
			//n->height = (std::max(get_height(n->right),get_height(n->left))) +1;
			//seth(n->parent);
		//}
	}

	int height(Node* n) {
		if (n== nullptr) return 0;
		else return n->h;
	}

	void lrotate(Node* n) {
		
        //cout << "Rotating left" << endl;
		
        Node *m = n->right;
        if(!m) return;
		if (n->parent == nullptr) root = m;
		else if(n->parent->left == n) n->parent->left=m;
		else n->parent->right = m;
        m->parent = n->parent;        

		n->parent = m;
		n->right = m->left;
		if(m->left) m->left->parent = n;
		m->left = n;

		seth(n);
		seth(m);
	}

	void rrotate(Node* n) {
		//cout << "Rotating right" << endl;
		Node *m = n->left;
        if(!m) return;
		if (n->parent == nullptr) root = m;
		else if(n->parent->right == n) n->parent->right=m;
		else n->parent->left = m;
        m->parent = n->parent;
        
		n->parent = m;
		n->left = m->right;
		if(m->right) m->right->parent = n;
		m->right = n;

		seth(n);
		seth(m);
	}

	void restore_balance(Node * n) {
		seth(n);
		Node * rover = n;
        int balance;
		while(rover != nullptr) {

			balance = get_height(rover->left)-get_height(rover->right);
			//if(balance * balance >= 10 )cout << "Balance factor = " << balance << endl;
			if(balance > 1) { //Requires at least a right rotate
				if(get_height(rover->left->left) >= get_height(root->left->right)) {
					//cout << "Left is null" << endl;

   					rrotate(rover);
                    //rover = rover->parent;
				} else {
					lrotate(rover->left);
					rrotate(rover);
				}
                rover = rover->parent;
                //break;
			} else if(balance < -1) { //Requires at least a left rotate
				if(get_height(rover->right->right) >= get_height(root->right->left)) {
				
						
					lrotate(rover);
				} else {
					rrotate(rover->right);
					lrotate(rover);
				}
                rover = rover->parent;
                //break;
			
			}
			rover = rover->parent;
		}
	}

	Node *root;
	unsigned int numElems;

public:
	typedef K key_type;
	typedef V mapped_type;
	typedef std::pair<K,V> value_type;

	class const_iterator;

	class iterator {
		Node *n;
		bool end;
	public:
		friend class const_iterator;
		iterator(Node *node):n(node),end(n==nullptr) {}
		iterator(Node *node,bool isEnd):n(node),end(isEnd) {}

		bool operator==(const iterator &i) const { return end==i.end && n==i.n; }
		bool operator!=(const iterator &i) const { return !(*this==i); }
		std::pair<K,V> &operator*() { return n->data; }
		iterator &operator++() {
			if(n==nullptr) return *this;
			if(n->right==nullptr) {
				Node *tmp = n;
				Node *c = n;
				n = n->parent;
				while(n!=nullptr && c==n->right) {
					c = n;
					n = n->parent;
				}
				if(n==nullptr) {
					n = tmp;
					end = true;
				}
			} else {
				n = n->right;
				while(n->left!=nullptr) n = n->left;
			}
			return *this;
		}
		iterator &operator--() {
			if(end) end = !end;
			else {
				if(n->left==nullptr) {
					Node *tmp = n;
					Node *c = n;
					n = n->parent;
					while(n!=nullptr && c==n->left) {
						c = n;
						n = n->parent;
					}
					if(n==nullptr) {
						n = tmp;
						end = true;
					}
				} else {
					n = n->left;
					while(n->right!=nullptr) n = n->right;
				}
			}
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}
		iterator operator--(int) {
			iterator tmp(*this);
			--(*this);
			return tmp;
		}
	};

	class const_iterator {
		Node *n;
		bool end;
	public:
		friend class AVLMap<K,V>;
		const_iterator(Node *node):n(node),end(n==nullptr) {}
		const_iterator(Node *node,bool isEnd):n(node),end(isEnd) {}
		const_iterator(const iterator &iter):n(iter.n),end(iter.end) {}

		bool operator==(const const_iterator &i) const { return end==i.end && n==i.n; }
		bool operator!=(const const_iterator &i) const { return !(*this==i); }
		std::pair<K,V> &operator*() { return n->data; }
		const_iterator &operator++() {
			if(n==nullptr) return *this;
			if(n->right==nullptr) {
				Node *tmp = n;
				Node *c = n;
				n = n->parent;
				while(n!=nullptr && c==n->right) {
					c = n;
					n = n->parent;
				}
				if(n==nullptr) {
					n = tmp;
					end = true;
				}
			} else {
				n = n->right;
				while(n->left!=nullptr) n = n->left;
			}
			return *this;
		}
		const_iterator &operator--() {
			if(end) end = !end;
			else {
				if(n->left==nullptr) {
					Node *tmp = n;
					Node *c = n;
					n = n->parent;
					while(n!=nullptr && c==n->left) {
						c = n;
						n = n->parent;
					}
					if(n==nullptr) {
						n = tmp;
						end = true;
					}
				} else {
					n = n->left;
					while(n->right!=nullptr) n = n->right;
				}
			}
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--(*this);
			return tmp;
		}
	};

	AVLMap():root(nullptr),numElems(0) {}
	AVLMap(const AVLMap<K,V> &that):numElems(that.numElems) {
		root = recurCopy(that.root,nullptr);
	}
	~AVLMap() {
		deleteAll(root);
	}

	AVLMap &operator=(const AVLMap<K,V> &that) {
		if(&that == this) return *this;
		deleteAll(root);
		root = recurCopy(that.root,nullptr);
		numElems = that.numElems;
		return *this;
	}

	bool empty() const { return numElems == 0; }

	unsigned size() const { return numElems; }

	iterator find(const key_type& k);

	const_iterator find(const key_type& k) const;

	unsigned int count(const key_type& k) const;

	std::pair<iterator,bool> insert(const value_type& val);

	template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
		for(auto iter = first; iter!=last; ++iter) {
			insert(*iter);
		}
	}

	iterator erase(const_iterator position);

	unsigned int erase(const key_type& k);

	void clear();

	mapped_type &operator[](const K &key);

	bool operator==(const AVLMap<K,V>& rhs) const;

	bool operator!=(const AVLMap<K,V>& rhs) const;

	iterator begin() {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return iterator(n);
	}

	const_iterator begin() const {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return const_iterator(n);
	}

	iterator end() {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return iterator(n,true);
	}

	const_iterator end() const {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return const_iterator(n,true);
	}

	const_iterator cbegin() const {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return const_iterator(n);
	}

	const_iterator cend() const {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return const_iterator(n,true);
	}

	void printTree() {
		printTreeRecur(root);
		std::cout << std::endl;
	}

private:
	void deleteAll(Node *n) {
		if(n!=nullptr) {
			deleteAll(n->left);
			deleteAll(n->right);
			delete(n);
		}
	}
	Node *recurCopy(Node *n,Node *p) {
		if(n==nullptr) return nullptr;
		Node *n2 = new Node;
        n2->height = n->height;
		n2->parent = p;
		n2->data = n->data;
		n2->left = recurCopy(n->left,n2);
		n2->right = recurCopy(n->right,n2);
		return n2;
	}
	void printTreeRecur(Node *n) {
		if(n!=nullptr) {
			std::cout << "(";
			printTreeRecur(n->left);
			std::cout << n->data.first << "-" << n->data.second << " ";
			printTreeRecur(n->right);
			std::cout << ")";
		}
	}
	void removeNode(Node *rover) {
		auto tpar = rover->parent;
        //cout << "removing " << endl;
		if(rover->left==nullptr && rover->right==nullptr) {
			if(rover==root) root = nullptr;
			else if(rover==rover->parent->left)
				rover->parent->left = nullptr;
			else rover->parent->right = nullptr;
			delete rover;
		} else if(rover->left==nullptr) {
			if(rover==root) root = rover->right;
			else if(rover==rover->parent->left) {
				rover->parent->left = rover->right;
				rover->right->parent = rover->parent;
			} else {
				rover->parent->right = rover->right;
				rover->right->parent = rover->parent;
			}
			delete rover;
		} else if(rover->right==nullptr) {
			if(rover==root) root = rover->left;
			else if(rover==rover->parent->left) {
				rover->parent->left = rover->left;
				rover->left->parent = rover->parent;
			} else {
				rover->parent->right = rover->left;
				rover->left->parent = rover->parent;
			}
			delete rover;
		} else {
			if(rover->left->right==nullptr) {
				Node *tmp = rover->left;
				rover->data = rover->left->data;
				rover->left = rover->left->left;
				if(rover->left!=nullptr) rover->left->parent = rover;
                tpar = tmp->parent;
				delete tmp;
			} else {
				Node *n = rover->left->right;
				while(n->right!=nullptr) n=n->right;
				n->parent->right = n->left;
				if(n->left!=nullptr) n->left->parent = n->parent;
				rover->data = n->data;
                tpar = n->parent;
				delete n;
			}
		}
        //seth(tpar);
        restore_balance(tpar);
	}
};

template <class K, class V>
bool AVLMap<K,V>::operator==(const AVLMap<K,V>& rhs) const {
	if(size()!=rhs.size()) return false;
	for(auto &p:rhs) {
		auto iter = find(p.first);
		if(iter==end() || p.second!=(*iter).second) return false;
	}
	return true;
}

template <class K, class V>
bool AVLMap<K,V>::operator!=(const AVLMap<K,V>& rhs) const {
	return !(*this==rhs);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::find(const K& key) {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) return iterator(rover);
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return end();
}

template<typename K,typename V>
typename AVLMap<K,V>::const_iterator AVLMap<K,V>::find(const K& key) const {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) return const_iterator(rover);
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return end();
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::count(const key_type& key) const {
	if(find(key)==end()) return 0;
	else return 1;
}

template<typename K,typename V>
std::pair<typename AVLMap<K,V>::iterator,bool> AVLMap<K,V>::insert(const value_type& val) {
	Node *rover = root;
	Node *prev = nullptr;
	while(rover!=nullptr) {
		if(rover->data.first==val.first) return make_pair(iterator(rover),false);
		prev = rover;
		if(val.first<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	++numElems;
	Node *n = new Node;
	n->parent = prev;
	n->data = val;
	if(prev==nullptr) {
		root = n;
	} else {
		if(val.first<prev->data.first) prev->left = n;
		else prev->right = n;
	}
	//cout << "Test" << endl;
	//seth(prev);
	restore_balance(n);
	return make_pair(iterator(n),true);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::erase(const_iterator position) {
	const_iterator tmp = position;
	++tmp;
	removeNode(position.n);
	numElems--;
	return iterator(tmp.n);
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::erase(const K& key) {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) {
			removeNode(rover);
			--numElems;
			return 1;
		}
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return 0;
}

template<typename K,typename V>
void AVLMap<K,V>::clear() {
	numElems = 0;
	deleteAll(root);
	root = nullptr;
}

template<typename K,typename V>
typename AVLMap<K,V>::mapped_type &AVLMap<K,V>::operator[](const K &key) {
    //cout << get_height(root) << endl;
	Node *rover = root;
	Node *prev = nullptr;
	while(rover!=nullptr) {
		if(rover->data.first==key) return rover->data.second;
		prev = rover;
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	++numElems;
	Node *n = new Node;
	n->parent = prev;
	n->data.first = key;
	if(prev==nullptr) {
		root = n;
	} else {
		if(key<prev->data.first) prev->left = n;
		else prev->right = n;
	}
    seth(n);
	restore_balance(prev);
	return n->data.second;
}

#endif
