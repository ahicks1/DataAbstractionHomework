#include<iostream>
using namespace std;

template<typename T>
class LinkedList {
                struct Node {
                        Node* next;
                        Node* prev;
                        T data;
                };
                Node * snt;
                int length;
                //NOTE: allocates memory
                Node * copyNode(Node * nd){
                  Node * ret = new Node();
                  ret->data = nd->data;
                  return ret;
                }
        public:
                typedef T value_type;

                class iterator {
                                Node * itr;
                        public:
                                iterator(){}
                                iterator(Node * nd){
                                  itr = nd;
                                }
                                T &operator*() { return itr->data; }
                                bool operator==(const iterator &i) const { return i.itr == itr; }
                                bool operator!=(const iterator &i) const { return i.itr != itr; }
                                iterator &operator=(const iterator &i) {
                                  itr = i.itr;
                                  return *this;
                                }
                                iterator &operator++() {
                                  itr = itr->next;
                                  return *this;
                                }
                                iterator &operator--() {
                                  itr = itr->prev;
                                  return *this;
                                }
                                iterator operator++(int) {
                                        iterator ret = iterator(itr);
                                        itr = itr->next;
                                        return ret;

                                }
                                iterator operator--(int) {
                                  iterator ret = iterator(itr);
                                  itr = itr->prev;
                                  return ret;
                                }
                                friend class const_iterator;
                                friend class LinkedList;
                };
                class const_iterator {
                                Node * itr;
                        public:
                                const_iterator(){}
                                const_iterator(Node * nd){
                                  itr = nd;
                                }
                                const_iterator(iterator i) {
                                  itr = i.itr;
                                }
                                const T &operator*() { return itr->data; }
                                bool operator==(const const_iterator &i) const { return i.itr == itr; }
                                bool operator!=(const const_iterator &i) const { return i.itr != itr; }
                                const_iterator &operator=(const const_iterator &i) {
                                  itr = i.itr;
                                  return *this;
                                }
                                const_iterator &operator++() {
                                  itr = itr->next;
                                  return *this;
                                }
                                const_iterator &operator--() {
                                  itr = itr->prev;
                                  return *this;
                                }
                                const_iterator operator++(int) {
                                  const_iterator ret = const_iterator(itr);
                                  itr = itr->next;
                                  return ret;
                                }
                                const_iterator operator--(int) {
                                  const_iterator ret = const_iterator(itr);
                                  itr = itr->prev;
                                  return ret;
                                }
                };

                // General Methods

                LinkedList() {
                  cout << "Constructor\n";
                  snt = new Node();
                  snt->next = snt;
                  snt->prev = snt;
                  length = 0;

                }
                LinkedList(const LinkedList &al) { //TODO make const input
                  cout << "copy constructor\n";
                  snt = new Node();
                  Node * rover = snt;
                  for(auto elem:al) {
                    Node * tmp = new Node();
                    rover->next = tmp;
                    tmp->prev = rover;
                    tmp->data = elem;
                    rover = rover->next;
                  }
                  rover->next = snt;
                  length = al.length;
                }
                LinkedList &operator=(const LinkedList &al) {
                  cout << "assignment operator\n";
                    this->clear();
                    Node * rover = snt;
                    for(auto elem:al) {
                      Node * tmp = new Node();
                      rover->next = tmp;
                      tmp->prev = rover;
                      tmp->data = elem;
                      rover = rover->next;
                    }
                    rover->next = snt;
                    length = al.length;
                    return *this;
                }
                ~LinkedList() {
                        delete snt;
                }
                void push_back(const T &t);           // add to the end.
                void pop_back();                      // remove last element.
                int size() const;
                void clear();
                iterator insert(iterator position,const T &t);    // insert this element before the given index.
                const T &operator[](int index) const; // get the element at index.
                T &operator[](int index);             // get the element at index.
                iterator erase(iterator position);               // remove the item at the given index.

                iterator begin(){
                  cout << "Iterator begin\n";
                  return iterator(snt->next);
                };
                const_iterator begin() const {
                  cout << "const_iterator begin\n";
                  return const_iterator(snt->next);
                };
                iterator end(){
                  cout << "iterator end\n";
                  return iterator(snt);
                };
                const_iterator end() const {
                  cout << "const_iterator end\n";
                  return const_iterator(snt);
                };
                const_iterator cbegin() const {
                  cout << "const_iterator begin\n";
                  return const_iterator(snt->next);
                };
                const_iterator cend() const {
                  cout << "const_iterator end\n";
                  return const_iterator(snt);
                };
};

template<typename T>
void LinkedList<T>::push_back(const T &t) {
  cout <<"push_back "<<t<<"\n";
  Node * tmp = new Node();
  tmp->next=snt;
  tmp->prev=snt->prev;
  snt->prev->next = tmp;
  snt->prev = tmp;
  tmp->data = t;
  length += 1;
}

template<typename T>
void LinkedList<T>::pop_back() {
  cout << "pop_back\n";
  Node * rm = snt->prev;
  rm->prev->next=snt;
  snt->prev = rm->prev;
  delete rm;
  length -= 1;
}

template<typename T>
int LinkedList<T>::size() const {
  cout << "size\n";
  return length;
}

template<typename T>
void LinkedList<T>::clear() {
  cout << "clear\n";
  for(auto elem = this->begin(); elem != this->end();elem++){
    delete elem.itr;
  }
  snt->next = snt;
  snt->prev = snt;
  length = 0;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert(typename LinkedList<T>::iterator position,const T &t) {
  cout << "insert\n";
  Node * tmp = new Node();
  tmp->next=position.itr;
  tmp->prev=position.itr->prev;
  position.itr->prev->next = tmp;
  position.itr->prev = tmp;
  tmp->data = t;
  length += 1;
  return iterator(tmp);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::erase(typename LinkedList<T>::iterator position) {
  cout << "erase\n";
  Node * rm = position.itr;
  rm->prev->next = rm->next;
  rm->next->prev = rm->prev;
  delete rm;
  length -= 1;
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const {
  auto rover = snt;
  for(int i = 0; i<index; ++i) {
    rover = rover->next;
  }
  cout << " const []"<<rover->data<<"\n";
  return rover->data;
}

template<typename T>
T& LinkedList<T>::operator[](int index){
  auto rover = snt;
  for(int i = 0; i<=index; ++i) {
    rover=rover->next;
  }
  cout << "[]"<<rover->data<<"\n";
  return rover->data;
}
