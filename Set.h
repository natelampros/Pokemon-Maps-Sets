//
// Created by Nate Lampros on 11/20/21.
//

#ifndef INC_9_CS235_POKEMON_SET_H
#define INC_9_CS235_POKEMON_SET_H
#include "SetInterface.h"
#include <string>
using namespace std;

#include "BST.h"

template<typename T>
class Set : public SetInterface<T>{
private:
    BST<T> container_;

public:
    Set() : container_() {}
    virtual ~Set() = default;

    /** Inserts item into the set, if the container doesn't
        already contain an element with an equivalent value. */
    virtual bool insert(const T& item) { return container_.addNode(item); }

    /** Removes all items from the set. */
    virtual void clear() { container_.clearTree(); }

    /** @return: the number of elements contained by the Set. */
    virtual size_t size() const {
        return container_.size();
    }

    /** @return: return 1 if contains element equivalent to item, else 0. */
    virtual size_t count(const T& item) {
        return container_.find(item);
    }

    friend std::ostream& operator<< (ostream& os, Set<T>& set)
    {
        return os << set.container_.toString();
    }
    /** @return: string representation of items in Set. */
    virtual std::string toString() const {
        return container_.toString();
    }
};

#endif //INC_9_CS235_POKEMON_SET_H
