#include<vector>
#include<list>
#include<iostream>
using namespace std;

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    int sz;
    int maxsz;
    vector<list<pair<K,V>>> table;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // NOTE: These might be different depending on how you store your table.
        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;
    public:
        friend class const_iterator;
        friend class HashMap;

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
        // NOTE: These might be different depending on how you store your table.
        decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;
    public:
      friend class HashMap;
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,
            const decltype(table.cbegin()) me,
            const decltype(table[0].cbegin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {

        }

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf):hashFunction{hf} {
      sz = 0;
      maxsz = 100000;
      table.resize(maxsz);
    }
    //HashMap(const HashMap<K,V,Hash> &that); // Only if needed.

    //HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.

    bool empty() const {
      return sz == 0;
    }

    unsigned int size() const {
       return sz;
     }

    iterator find(const key_type& k) {
      //cout << "finding at " << hashFunction(k)%maxsz << endl;
      //cout << "Finding at "<<k<<endl;
      auto mi = table.begin() + (unsigned int)hashFunction(k)%maxsz;
      auto si = (*mi).begin();
      while (si != (*mi).end()) {
        if((*si).first == k)
          return iterator(mi,table.end(),si);
        si++;
      }
      return end();

    }

    const_iterator find(const key_type& k) const {
      //cout << "finding at " << hashFunction(k)%maxsz << endl;
      auto mi = table.cbegin() + (unsigned int)hashFunction(k)%maxsz;
      auto si = (*mi).cbegin();
      while (si != (*mi).cend()) {
        if((*si).first == k)
          return const_iterator(mi,table.cend(),si);
        si++;
      }
      return cend();
    }
    int count(const value_type& v) const {
      if (find(v.first) != cend())
        return 1;
      else return 0;
    }
    int count(const key_type& k) const {
      if (find(k) != cend())
        return 1;
      else return 0;
    }

    std::pair<iterator,bool> insert(const value_type& val){
      //cout << "inserting" << endl;
      int idx = (unsigned int)hashFunction(val.first)%maxsz;
      auto &lst = table[idx];
      bool exists = false;
      for(auto elem : lst) {
        if(elem.first == val.first) {
          exists = true;
        }
      }
      if(!exists){
        lst.push_back(val);
        sz+=1;
      }
      pair<iterator,bool> ret (find(val.first),!(exists));
      return ret;
      /*auto pos = find(val.first);
      if(pos == end()) {
        auto mi = table.begin() + (hashFunction(val.first)%maxsz);
        mi->push_front(val);
        sz += 1;
        pair<iterator,bool> ret (iterator(mi,table.end(),(*mi).begin()),false);
        return ret;
      } else {
        pair<iterator,bool> ret (pos,false);
        return ret;
      }*/

    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        auto rover = first;
        while(rover != last) {
          insert(*rover);
          rover++;
        }
    }

    iterator erase(const_iterator position) {
      //cout << "erasing" << endl;
      sz -= 1;
      auto val = (*position);
      auto newpos = find(val.first);
      decltype(table[0].begin()) retsb = (*newpos.mainIter).erase(newpos.subIter);
      return iterator(newpos.mainIter,newpos.mainEnd,retsb);
    }

    int erase(const key_type& k) {
      const_iterator pos = find(k);
      if(pos!=cend()) {
        erase(pos);
        return 1;
      }
      else
        return 0;
    }

    void clear() {
      sz = 0;
      table.clear();
      table.resize(maxsz);
    }

    mapped_type &operator[](const K &key) {
      //cout << "indexing" << endl;
      //cout <<"indexing at " << key << endl;
      auto resitr = find(key);
      if(resitr != end()) {
        //cout << "value exists "<<(*resitr).second<<endl;
        return (*resitr).second;
      } else {
        value_type elem;
        //cout << "value doesn't exist, inserting"<<endl;
        elem.first = key;
        insert(elem);
        return (*find(key)).second;
      }
    }

    bool operator==(const HashMap<K,V,Hash>& rhs) const {
      bool eq = true;
      if(rhs.size() != size()) return false;
      for(auto elem:(*this)) {
        if ( rhs.count(elem) != 1) {
          eq = false;
          break;
        }
      }
      return eq;
    }

    bool operator!=(const HashMap<K,V,Hash>& rhs) const {
      return !((*this) == rhs);
    }

    iterator begin() {
      return iterator(table.begin(),table.end());
    }

    const_iterator begin() const {
      return const_iterator(table.cbegin(),table.cend());
    }

    iterator end() {
      return iterator(table.end(),table.end());
    }

    const_iterator end() const {
      return const_iterator(table.cend(),table.cend());
    }

    const_iterator cbegin() const {
      return const_iterator(table.cbegin(),table.cend());
    }

    const_iterator cend() const {
      return const_iterator(table.cend(),table.cend());
    }

private:
    int getIdx(int i) {
      int idx = hashFunction(i)%maxsz;
      if(idx < 0) return -idx;
      else return idx;
    }
    void growTableAndRehash();
};
