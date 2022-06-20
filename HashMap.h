//
// Created by Nate Lampros on 11/20/21.
//

#ifndef INC_9_CS235_POKEMON_HASHMAP_H
#define INC_9_CS235_POKEMON_HASHMAP_H
#include "HashMapInterface.h"
#include "Set.h"
#include "Pair.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

/** Hash Function Objects Template */
//template<typename K>
//struct myHash {};

template<typename K, typename VALUE>
class HashMap {};

template<typename T2>
struct Pair<string, T2>
{
    string first;
    T2 second;
    friend ostream& operator<<(ostream& os, const Pair& p)
    {
        os << p.first << "->" << p.second;
        return os;
    }
};

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

template <typename V>
class HashMap<string, V> : public HashMapInterface<string ,V> {
private:
    size_t hashSize = 0;
    size_t capacity;
    Pair<string, V>* myPairs;

public:
    HashMap(size_t totalSpace = DEFAULT_MAP_HASH_TABLE_SIZE) : capacity(totalSpace),
                myPairs(new Pair<string,V>[totalSpace]) {}
    virtual ~HashMap() {
        delete [] myPairs;
    }


    /** Read/write index access operator.
    If the key is not found, an entry is made for it.
    @return: Read and write access to the value mapped to the provided key. */
    virtual V& operator[](const string& key) {
        // check load factor...  resize if needed
        if (((hashSize * 100) / capacity) > LOAD_THRESHOLD) reallocate();
            size_t hashIndex = 0;

            for (char i : key) {
                hashIndex *= HASH_CONSTANT;
                hashIndex += i;
            }
            hashIndex = hashIndex % capacity;

            size_t k = 1;
            while (true) {
                if (myPairs[hashIndex].first.length() == 0)
                {
                    cout << endl << " " << "Insert " << key;
                    myPairs[hashIndex].first = key;
                    ++hashSize;
                    break;
                }
                if (myPairs[hashIndex].first == key) break;
                cout << endl << " " << key << " collided with " << myPairs[hashIndex].first;
                hashIndex = (hashIndex + k) % capacity;
                k += 2;
            }
            return myPairs[hashIndex].second;
    }



    friend ostream& operator<<(ostream& os, const HashMap& hm)
    {
        //os << hm.toString();
        for (size_t i = 0; i < hm.capacity; ++i)
        {
            os << endl << " [" << i << ":";
            if (hm.myPairs[i].first != "") os << hm.myPairs[i];
            os << "]";
        }
        return os;
    }
    long long hash(const string& key){
        long long total = 0;

        for (char i : key) {
            total *= HASH_CONSTANT;
            total += i;
        }
        return total;
    }

    void reallocate(){
        size_t newCapacity = 2 * capacity;

        Pair<string, V>* newPairs = new Pair<string, V>[newCapacity];

        for(size_t i = 0; i < capacity; ++i){
            if (myPairs[i].first.empty()) continue;
            long long tempIndex = hash(myPairs[i].first);
            tempIndex = tempIndex % newCapacity;

            size_t k = 1;
            while(true) {
                if (newPairs[tempIndex].first.length() == 0){
                    newPairs[tempIndex].first = myPairs[i].first;
                    newPairs[tempIndex].second = myPairs[i].second;
                    //++hashSize;
                    break;
                }
                tempIndex = (tempIndex + k) % newCapacity;
                k += 2;
            }
        }
        capacity = newCapacity;
        swap(myPairs, newPairs);
        delete [] newPairs;

    }

    /** @return: the number of elements that match the key in the Map. */
    virtual size_t count(const string& key) {
        for (size_t i = 0; i < capacity; ++i){
            if (myPairs[i].first == key) return 1;
        }
        return 0;

    }

    /** Removes all items from the Map. */
    virtual void clear(void) {
        delete [] myPairs;
        myPairs = new Pair<string, V>[DEFAULT_MAP_HASH_TABLE_SIZE];
        hashSize = 0;
        capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
    }

    /** @return: number of Key-Value pairs stored in the Map. */
    virtual size_t size(void) const {
        return hashSize;
    }

    /** @return: maximum number of Key-Value pairs that the Map can hold. */
    virtual size_t max_size(void) const {
        return capacity;
    }

    /** @return: string representation of Key-Value pairs in Map. */
    virtual std::string toString(void) const {
        stringstream out;
        out  << hashSize << "/" << capacity << endl;
        for (int i = 0; i < capacity; ++i){
            if (myPairs[i].first.empty()) continue;
            else out << "  [" << i << ":" << myPairs[i].first << "->" << myPairs[i].second << "]" << endl;
        }
        return out.str();
    }

};


#endif //INC_9_CS235_POKEMON_HASHMAP_H
