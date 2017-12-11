#import<iostream>

using namespace std;

template<typename K,typename V>
class AVLMap {
    struct Node {
      Node* par;
      Node* left;
      Node* right;
      std::pair<K,V> data;
      int height;
    };
    Node* root = nullptr;
    int sz = 0;
    // TODO: Define your Node
    // TODO: specify whatever member data you need.

    void seth(Node* n){
  		if(n==nullptr) return;
  		else {
  			n->height = std::max(get_height(n->right),get_height(n->left))+1;
  			seth(n->par);
  		}
  	}

  	int get_height(Node* n) {
  		if (n== nullptr) return 0;
  		else return n->height;
  	}

  	void lrotate(Node* n) {
  		Node *m = n->right;
  		if (n->par == nullptr) root = m;
  		else if(n->par->left == n) n->par->left=m;
  		else n->par->right = m;

  		n->par = m;
  		n->right = m->left;
  		if(m->left) m->left->par = n;
  		m->left = n;

  		seth(n);
  		seth(m);
  	}

  	void rrotate(Node* n) {
  		Node *m = n->left;
  		if (n->par == nullptr) root = m;
  		else if(n->par->right == n) n->par->right=m;
  		else n->par->left = m;

  		n->par = m;
  		n->left = m->right;
  		if(m->right) m->right->par = n;
  		m->right = n;

  		seth(n);
  		seth(m);
  	}

    void destroy(Node* n) {
      if(!n) return;
      destroy(n->left);
      destroy(n->right);
      delete n;
    }
    static Node* minimum(Node* root) {
      if (root == nullptr) return nullptr;
      Node * rover = root;
      while(rover->left != nullptr) {
        rover = rover->left;
      }
      return rover;
    }
    static Node* maximum(Node* root) {
      Node * rover = root;
      while(rover != nullptr && rover->right != nullptr) {
        rover = rover->right;
      }
      return rover;
    }

    static Node* succ(Node* node) {
      if (node->right) return minimum(node->right);
      else while(node->par && node->par->right == node) {
        node = node->par;
      }
      return node->par;
    }

    static Node* pred(Node* node) {
      if (node->left) return maximum(node->left);
      else while(node->par && node->par->left == node) {
        node = node->par;
      }
      return node->par;
    }

    void transplant(Node* dest, Node* src) {
      if (dest->par == nullptr) {
        root = src;
      } else if(dest == dest->par->left) {
        dest->par->left = src;
      } else dest->par->right = src;
      if (src != nullptr) {
        src->par = dest->par;
      }
    }

    void removeNode(Node *rover) {
  		if(rover->left==nullptr && rover->right==nullptr) {
  			if(rover==root) root = nullptr;
  			else if(rover==rover->par->left)
  				rover->par->left = nullptr;
  			else rover->par->right = nullptr;
  			delete rover;
  		} else if(rover->left==nullptr) {
  			if(rover==root) root = rover->right;
  			else if(rover==rover->par->left) {
  				rover->par->left = rover->right;
  				rover->right->par = rover->par;
  			} else {
  				rover->par->right = rover->right;
  				rover->right->par = rover->par;
  			}
  			delete rover;
  		} else if(rover->right==nullptr) {
  			if(rover==root) root = rover->left;
  			else if(rover==rover->par->left) {
  				rover->par->left = rover->left;
  				rover->left->par = rover->par;
  			} else {
  				rover->par->right = rover->left;
  				rover->left->par = rover->par;
  			}
  			delete rover;
  		} else {
  			if(rover->left->right==nullptr) {
  				Node *tmp = rover->left;
  				rover->data = rover->left->data;
  				rover->left = rover->left->left;
  				if(rover->left!=nullptr) rover->left->par = rover;
  				delete tmp;
  			} else {
  				Node *n = rover->left->right;
  				while(n->right!=nullptr) n=n->right;
  				n->par->right = n->left;
  				if(n->left!=nullptr) n->left->par = n->par;
  				rover->data = n->data;
  				delete n;
  			}
  		}
  	}
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data.
        //Need to be able to go back from end, i.e. --end() should
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the
        //maximum element. But to get the maximum element, we need to
        //store information about the tree, e.g. the root pointer, as member.
        Node * ptr;
        bool isEnd;
    public:
        friend class const_iterator;
        friend class AVLMap<K,V>;
        iterator(Node * n, bool e=false):ptr{n},isEnd{e}{ }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const { return isEnd == i.isEnd && ptr == i.ptr; }
        bool operator!=(const iterator &i) const { return !((*this)==i); }
        std::pair<K,V> &operator*() {
          return ptr->data;
        }
        iterator &operator++() {
            auto temp = succ(ptr);
            if(temp == nullptr) {
              isEnd = true;
            } else ptr = temp;


            return *this;
        }
        iterator &operator--() {
            // TODO
            if(isEnd) isEnd=false;
            else  {
              auto temp=pred(ptr);
              if(temp != nullptr) ptr = temp;
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
        Node * ptr;
        bool isEnd;
        value_type dt;
    public:
        friend class AVLMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node * n, bool e=false):ptr{n},isEnd{e}{ }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter){
          ptr = iter.ptr;
          isEnd = iter.isEnd;
        }

        bool operator==(const const_iterator &i) const { return isEnd == i.isEnd && ptr == i.ptr; }
        bool operator!=(const const_iterator &i) const { return !((*this)==i); }
        const std::pair<K,V> &operator*() {
          return ptr->data;
         }
        const_iterator &operator++() {
            auto temp = succ(ptr);
            if(temp == nullptr) {
              isEnd = true;
            } else ptr = temp;

            return *this;
        }
        const_iterator &operator--() {
          if(isEnd) isEnd=false;
          else  {
            auto temp=pred(ptr);
            if(temp != nullptr) ptr = temp;
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



    AVLMap() {
        root = nullptr;
        sz = 0;
    }
    ~AVLMap() {
      cout << "Destructor" << endl;
      destroy(root);
        //clear();
    }
    AVLMap(const AVLMap<K,V> &that) {
        root = nullptr;
        sz = 0;
        for (auto p: that)insert(p);
    }

    AVLMap &operator=(const AVLMap<K,V> &that) {
        // TODO
        clear();
        for (auto p: that)insert(p);
    }

    bool empty() const { return sz == 0; }

    unsigned size() const { return sz; }

    iterator find(const key_type& k) {
      Node * rover = root;
      while(rover != nullptr && rover->data.first != k) {
        if(rover->data.first > k) rover = rover->left;
        else rover = rover->right;
      }
      if(rover == nullptr) {
        return end();
      }
      else return iterator(rover);

    }

    const_iterator find(const key_type& k) const {
      auto rover = root;
      while(rover != nullptr && rover->data.first != k) {
        if(rover->data.first > k) rover = rover->left;
        else rover = rover->right;
      }
      if(rover == nullptr)
        return cend();
        else return const_iterator(rover);

    }

    unsigned int count(const key_type& k) const {
      if(find(k) == end())
        return 0;
      else return 1;
    }

    std::pair<iterator,bool> insert(const value_type& val) {
      Node * loc = nullptr;
      Node * rover = root;
      while (rover != nullptr) {
        loc = rover;
        if(val.first < rover->data.first)
          rover = rover->left;
        else if (val.first > rover->data.first)
          rover = rover->right;
        else {
          return(make_pair(find(val.first),false));
        }
      }
      Node *elem = new Node{loc,nullptr,nullptr,val,1};
      if(loc == nullptr) {
        root = elem;
      } else if(val.first < loc->data.first) {
        loc->left = elem;
      } else {
        loc->right = elem;
      }
      sz++;
      seth(elem);

      //AVL part
      rover = elem;
      while(rover != nullptr) {

        int balance = get_height(rover->left)-get_height(rover->right);
        cout << "Height = " << balance << endl;
        if(balance > 1) { //Requires at least a right rotate
          if(get_height(rover->left->left) >= get_height(root->left->right)) {
            cout << "Left is null" << endl;

            rrotate(rover);
          } else {
            //lrotate(rover->right);
            //rrotate(rover);
          }
        } else if(balance < -1) { //Requires at least a left rotate
          if(rover->right != nullptr) {// && height(rover->right->right) >= height(root->right->left)) {
            auto lh = get_height(rover->right->right);
            auto rh = get_height(rover->right->left);
            if(lh >= rh) {
              cout << "Right is smaller" << endl;
            //}
            lrotate(rover);
          } else {
            //rrotate(rover->left);
            //lrotate(rover);
          }
        }
        }
        rover = rover->par;
      }

      return (make_pair(iterator(elem),true));
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position) {
      /*auto ptr = position.ptr;
      auto ret = iterator(ptr);
      --ret;
      if(ptr->left == nullptr){
        transplant(ptr,ptr->right);
      } else if(ptr->right == nullptr) {
        transplant(ptr,ptr->left);
      } else {
        auto loc = minimum(ptr->right);
        if(loc->par != ptr) {
          transplant(loc,loc->right);
          loc->right = ptr->right;
          loc->right->par = loc;
        }
        transplant(ptr,loc);
        loc->left = ptr->left;
        loc->left->par = loc;


      }
      sz--;
      delete ptr;
      ptr = nullptr;
      return ++ret;*/
      const_iterator tmp = position;
      ++tmp;
    	removeNode(position.ptr);
    	sz--;
    	return iterator(tmp.ptr);
    }

    unsigned int erase(const key_type& k) {
      const_iterator pos = find(k);
      if (pos==cend()) return 0;
      else {
        erase(pos);
        return 1;
      }
    }

    void clear() {
      destroy(root);
      root = nullptr;
      sz = 0;
    }

    mapped_type &operator[](const K &key) {
      iterator itr = find(key);
      if(itr != end()) {
        return (*itr).second;
      } else {
        value_type elem;
        elem.first = key;
        insert(elem);
        return (*find(key)).second;
      }
    }

    bool operator==(const AVLMap<K,V>& rhs) const{
      for(auto elem:rhs) {
        auto found = find(elem.first);
        bool res = found == cend();
        if(found == cend() || (*found).second != elem.second)
        {
          return false;
        }
      }
      return sz == rhs.sz;
    }

    bool operator!=(const AVLMap<K,V>& rhs) const {
      return !((*this) == rhs);
    }

    void print_tree() {
      print_helper(0,root);
    }

    void print_helper(int depth, Node * ptr) {
      for(int i = 0; i<depth; i++) {
        cout << " ";
      }
      if(ptr == nullptr) {
        cout << "." << endl;
      } else {
        cout << ptr->data.second << endl;
        print_helper(depth+1,ptr->left);
        print_helper(depth+1,ptr->right);
      }
    }

    iterator begin() { return iterator(minimum(root)); }

    const_iterator begin() const { return const_iterator(minimum(root)); }

    iterator end() { return iterator(maximum(root),true); }

    const_iterator end() const { return const_iterator(maximum(root),true); }

    const_iterator cbegin() const { return const_iterator(minimum(root)); }

    const_iterator cend() const { return const_iterator(maximum(root),true); }

};
