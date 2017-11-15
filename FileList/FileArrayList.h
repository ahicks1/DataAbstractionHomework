#include<cstdio>
#include<string>
template<typename T>
class FileArrayList {
        FileArrayList(const FileArrayList<T> &that) = delete;
        FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        // TODO - Your private data.
        FILE * file;
        int sz;
        // TODO - Private helper functions. (Maybe file IO with an index.)
        int ReadSz() const{
          fseek(file,0,SEEK_SET);
          int ret;
          fread(&ret, sizeof(int), 1, file);
          return ret;
        }
        void WriteSz(int ns) {
          fseek(file,0,SEEK_SET);
          fwrite(&ns,sizeof(int),1,file);
        }
        T Read(int idx) const{
          fseek(file,(idx*sizeof(T))+sizeof(int),SEEK_SET);
          T res;
          fread(&res, sizeof(T), 1, file);
          return res;
        }
        void Write(int idx, const T* elem) {
          fseek(file,(idx*sizeof(T))+sizeof(int),SEEK_SET);
          fwrite(elem,sizeof(T),1,file);
        }
    public:
        typedef T value_type;

        class const_iterator {
                FILE * f;
                int idx;
            public:
                const_iterator(int i,FILE *file) {
                  idx = i;
                  f = file;
                }
                const_iterator(const const_iterator &i) {
                   idx = i.idx;
                   f = i.f;
                 }
                T operator*() {
                  fseek(f,(idx*sizeof(T))+sizeof(int),SEEK_SET);
                  T res;
                  fread(&res, sizeof(T),1, f);
                  return res;
                 }
                bool operator==(const const_iterator &i) const {
                  return idx == i.idx;
                }
                bool operator!=(const const_iterator &i) const {
                  return idx != i.idx;
                }
                const_iterator &operator=(const const_iterator &i) {
                  idx = i.idx;
                  f = i.f;
                  return *this;
                }
                const_iterator &operator++() {
                  idx++;
                  return *this;
                }
                const_iterator &operator--() {
                  idx--;
                  return *this;
                }
                const_iterator operator++(int) {
                  const_iterator ret = const_iterator(idx,f);
                  idx++;
                  return ret;
                }
                const_iterator operator--(int) {
                  const_iterator ret = const_iterator(idx,f);
                  idx--;
                  return ret;
                 }

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname)
        {
          file = fopen(fname.c_str(),"r+");
          if (file == nullptr) {
            file=fopen(fname.c_str(),"w+");
            sz = 0;
            WriteSz(sz);
          }
          else {
            sz = ReadSz();
          }

        }

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            file = fopen(fname.c_str(), "w+");
            sz = 0;
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
            for(auto i = begin; i != end; i++)
              push_back(*i);

        }
        ~FileArrayList(){
          fclose(file);
        };
        void push_back(const T &t);
        void pop_back();
        int size() const;
        void clear();
        const_iterator insert(const_iterator position, const T &t);
        T operator[](int index) const;
        const_iterator erase(const_iterator position);
        void set(const T &value,int index);

        const_iterator begin() {
          return const_iterator(0,file);
        }
        const_iterator begin() const {
          return const_iterator(0,file);
        }
        const_iterator end() {
          return const_iterator(sz,file);
        }
        const_iterator end() const {
          return const_iterator(sz,file);
        }
        const_iterator cbegin() const {
          return const_iterator(0,file);
        }
        const_iterator cend() const {
          return const_iterator(sz,file);
        }
};

template<typename T>
void FileArrayList<T>::push_back(const T &t) {
  Write(sz, &t);
  sz++;
  WriteSz(sz);
}

template<typename T>
void FileArrayList<T>::pop_back() {
  sz--;
  WriteSz(sz);
}

template<typename T>
int FileArrayList<T>::size() const{
  return sz;
}

template<typename T>
void FileArrayList<T>::clear() {
  sz =0;
  WriteSz(sz);
}

template<typename T>
typename FileArrayList<T>::const_iterator FileArrayList<T>::insert (typename FileArrayList<T>::const_iterator position, const T &t) {
  for(int i=sz; i>position.idx; --i) {
    //cout << "moving at " << i;
    T elem = Read(i-1);
    Write(i,&elem);
  }
  Write(position.idx,&t);
   ++sz;
   WriteSz(sz);
   return (position);
}

template<typename T>
T FileArrayList<T>::operator[](int index) const{
  return Read(index);
}

template<typename T>
typename FileArrayList<T>::const_iterator FileArrayList<T>::erase(typename FileArrayList<T>::const_iterator position) {
  if(position.idx >= sz)
    throw "Index out of bounds";
    for(int i=position.idx; i < sz-1; i++) {
      T elem = Read(i+1);
      Write(i,&elem);
    }
    sz--;
    WriteSz(sz);
    return position;
}

template<typename T>
void FileArrayList<T>::set(const T &value,int index) {
  Write(index,&value);
}
