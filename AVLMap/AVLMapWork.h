template<typename K,typename V>
class AVLMap {
    // TODO: Define your Node
    // TODO: specify whatever member data you need.

    struct Node{
      Node* parent;
      Node* left;
      Node* right;
      int height;
      value_type data;
    };
    void seth(Node* n){
      if(n==nullptr) return;
      else {
        n->h = std::max(height(n->right),height(n->left));
        seth(n->parent);
      }
    }
    int height(Node* n) {
      if (n== nullptr) return 0;
      else return n->h;
    }
    void lrotate(Node* n) {
      Node *m = n->right;
      if (n->p == nullptr) root = m;
      else if(n->p->left == n) n->p->left=m;
      else n->p->right = m;

      n->p = m;
      n->right = m->left;
      if(m->left) m->left->p = n;
      m->left = n;

      seth(n);
      seth(m);
    }

    void rrotate(Node* n) {
      Node *m = n->left;
      if (n->p == nullptr) root = m;
      else if(n->p->right == n) n->p->right=m;
      else n->p->left = m;

      n->p = m;
      n->left = m->right;
      if(m->right) m->right->p = n;
      m->right = n;

      seth(n);
      seth(m);
    }

    
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
    public:
        friend class const_iterator;
        iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const { /*TODO*/ }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { /*TODO*/ }
        iterator &operator++() {
            // TODO
            return *this;
        }
        iterator &operator--() {
            // TODO
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
        // TODO: iterator data
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter)/*:...*/ {}

        bool operator==(const const_iterator &i) const { /*TODO*/ }
        bool operator!=(const const_iterator &i) const { /*TODO*/ }
        const std::pair<K,V> &operator*() { /*TODO*/ }
        const_iterator &operator++() {
            // TODO
            return *this;
        }
        const_iterator &operator--() {
            // TODO
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



    BSTMap() {
        // TODO
    }
    ~BSTMap() {
        // TODO
    }
    BSTMap(const BSTMap<K,V> &that) {
        // TODO
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        // TODO
    }

    bool empty() const { /*TODO*/ }

    unsigned size() const { /*TODO*/ }

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

    bool operator==(const BSTMap<K,V>& rhs) const;

    bool operator!=(const BSTMap<K,V>& rhs) const;

    iterator begin() { return iterator(/*TODO*/); }

    const_iterator begin() const { return const_iterator(/*TODO*/); }

    iterator end() { return iterator(/*TODO*/); }

    const_iterator end() const { return const_iterator(/*TODO*/); }

    const_iterator cbegin() const { return const_iterator(/*TODO*/); }

    const_iterator cend() const { return const_iterator(/*TODO*/); }

};
