#include<cstdio>
#include<string>
#include<iostream>

//Pledged Alexander Hicks

using namespace std;
template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        FILE * file;
        int sz;
        int freeHead;
        struct Node {
                int next;
                int prev;
                T data;
        };

        Node sent;

        // TODO - Private helper functions. (Maybe file IO with an index.)
        static int ReadSz(FILE * file){
          fseek(file,0,SEEK_SET);
          int ret;

          fread(&ret, sizeof(int), 1, file);
          //cout <<"Read size " << ret<<endl;
          return ret;
        }
        static void WriteSz(int ns,FILE * file) {
          fseek(file,0,SEEK_SET);
          //cout <<"Wrote size "<<ns<<endl;
          fwrite(&ns,sizeof(int),1,file);
        }
        static int ReadFreeNode(FILE * file) {
          fseek(file,sizeof(int),SEEK_SET);
          int ret;
          fread(&ret, sizeof(int), 1, file);
          return ret;
        }
        static void WriteFreeNode(int idx, FILE * file) {
          fseek(file,sizeof(int),SEEK_SET);
          fwrite(&idx,sizeof(int),1,file);
        }
        static Node Read(int idx, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+8;
          fseek(file,loc,SEEK_SET);
          Node res;
          fread(&res, sizeof(Node), 1, file);
          return res;
        }
        static void Write(int idx, const Node* elem, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+8;
          fseek(file,loc,SEEK_SET);
          fwrite(elem,sizeof(Node),1,file);
        }
        static void WriteNext(int idx, int next, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+8;
          fseek(file,loc,SEEK_SET);
          //cout <<"Wrote next " <<next<< " at "<<idx <<endl;
          fwrite(&next,sizeof(int),1,file);
        }
        static void WritePrev(int idx, int prev, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+12;
          fseek(file,loc,SEEK_SET);
          //cout <<"Wrote prev " <<prev<< " at "<<idx <<endl;
          fwrite(&prev,sizeof(int),1,file);
        }

        static int ReadPrev(int idx, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+12;
          fseek(file,loc,SEEK_SET);
          int res;
          fread(&res,sizeof(int),1,file);
          //cout <<"Read prev " <<res<< " at "<<idx <<endl;
          return res;
        }
        static int ReadNext(int idx, FILE * file) {
          int loc = (idx+1)*sizeof(Node)+8;
          fseek(file,loc,SEEK_SET);
          int res;
          fread(&res,sizeof(int),1,file);
          //cout <<"Read next " <<res << " at "<<idx <<endl;
          return res;
        }

        int GetFreeIdx() {
          int ret = ReadFreeNode(file);
          if(ret == -1) {
            return sz;
          } else {
            WriteFreeNode(ReadNext(ret,file),file);
            return ret;
          }
        }
        // TODO - Your private data.
        // TODO - Private helper functions. (Maybe file IO with an index.)
    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                int ptr;
                FILE *f;
            public:
                const_iterator(int i,FILE *fl) {
                  ptr = i;
                  f = fl;
                }
                const_iterator(const const_iterator &i) {
                  ptr = i.ptr;
                  f = i.f;
                }
                T operator*() {
                  Node ret = Read(ptr,f);
                  return ret.data;
                }
                bool operator==(const const_iterator &i) const {
                  return ptr == i.ptr;
                }
                bool operator!=(const const_iterator &i) const {

                  return ptr != i.ptr;
                }
                const_iterator &operator=(const const_iterator &i){
                  ptr = i.ptr;
                  f = i.f;
                  return *this;
                }
                const_iterator &operator++() {
                  ptr = ReadNext(ptr,f);
                  return *this;
                }
                const_iterator &operator--() {
                  ptr = ReadPrev(ptr,f);
                  return *this;
                }
                const_iterator operator++(int) {
                  const_iterator ret = const_iterator(ptr,f);
                  ptr = ReadNext(ptr,f);
                  return ret;
                }
                const_iterator operator--(int) {
                  const_iterator ret = const_iterator(ptr,f);
                  ptr = ReadPrev(ptr,f);
                  return ret;
                }

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname) {
          file = fopen(fname.c_str(),"r+");
          if (file == nullptr) {
            file=fopen(fname.c_str(),"w+");
            sz = 0;
            freeHead = -1;
            sent.next = -1;
            sent.prev = -1;
            WriteFreeNode(freeHead,file);
            Write(-1,&sent,file);
            WriteSz(sz,file);

          }
          else {
            freeHead = ReadFreeNode(file);
            sz = ReadSz(file);
            sent = Read(-1,file);
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
          file=fopen(fname.c_str(),"w+");
          sz = 0;
          freeHead = -1;
          sent.next = -1;
          sent.prev = -1;
          WriteFreeNode(freeHead,file);
          WriteSz(sz,file);
          for(auto i = begin; i != end; i++)
            push_back(*i);
        }
        ~FileLinkedList() {
            fclose(file);
        }
        void push_back(const T &t);
        void pop_back();
        int size() const;
        void clear();
        const_iterator insert(const_iterator position, const T &t);
        T operator[](int index) const;
        const_iterator erase(const_iterator position);
        void set(const T &value,int index);
        void set(const T &value,const_iterator position);

        const_iterator begin() {
          return const_iterator(ReadNext(-1,file),file);
        }
        const_iterator begin() const {
          return const_iterator(ReadNext(-1,file),file);
        }
        const_iterator end() {
          return const_iterator(-1,file);
        }
        const_iterator end() const {
          return const_iterator(-1,file);
        }
        const_iterator cbegin() const {
          return const_iterator(ReadNext(-1,file),file);
        }
        const_iterator cend() const {
          return const_iterator(-1,file);
        }
};

template<typename T>
void FileLinkedList<T>::push_back(const T &t) {
  insert(const_iterator(-1,file),t);
}

template<typename T>
void FileLinkedList<T>::pop_back() {
  erase(const_iterator(ReadPrev(-1,file),file));
}

template<typename T>
int FileLinkedList<T>::size() const {
  return sz;
}

template<typename T>
void FileLinkedList<T>::clear() {
  while(sz > 0 ) {
    pop_back();
  }
}

template<typename T>
typename FileLinkedList<T>::const_iterator FileLinkedList<T>::insert(typename FileLinkedList<T>::const_iterator position,const T &t) {
  Node tmp;
  int pos = GetFreeIdx();
  tmp.next=position.ptr;
  tmp.prev= ReadPrev(position.ptr,file);
  WriteNext(ReadPrev(position.ptr,file),pos,file);
  WritePrev(position.ptr,pos,file);
  tmp.data = t;
  sz += 1;
  WriteSz(sz,file);
  //cout<<"Inserting elem: "<<tmp.data;
  //cout<< " next: " << tmp.next;
  //cout<< " prev: " << tmp.prev << endl;
  Write(pos,&tmp,file);
  return position;
}

template<typename T>
T FileLinkedList<T>::operator[](int index) const {
  auto rover = ReadNext(-1,file);
  for(int i = 0; i<index; ++i) {
    rover = ReadNext(rover,file);
  }
  return Read(rover,file).data;
}

template<typename T>
typename FileLinkedList<T>::const_iterator FileLinkedList<T>::erase(typename FileLinkedList<T>::const_iterator position) {

  //Remove node
  auto ret = ReadNext(position.ptr,file);
  WriteNext(ReadPrev(position.ptr,file),ret,file);
  WritePrev(ReadNext(position.ptr,file),ReadPrev(position.ptr,file),file);
  sz -= 1;
  WriteSz(sz,file);
  WriteNext(position.ptr,ReadFreeNode(file),file);
  WriteFreeNode(position.ptr,file);
  return FileLinkedList<T>::const_iterator(ret,file);
}

template<typename T>
void FileLinkedList<T>::set(const T &value,int index) {
  auto rover = ReadNext(-1,file);
  for(int i = 0; i<index; ++i) {
    rover = ReadNext(rover,file);
  }
  set(value,FileLinkedList<T>::const_iterator(rover,file));
}

template<typename T>
void FileLinkedList<T>::set(const T &value, typename FileLinkedList<T>::const_iterator position) {
  Node val = Read(position.ptr,file);
  val.data = value;
  Write(position.ptr,&val,file);
}
