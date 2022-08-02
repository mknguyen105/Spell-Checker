// SkipListSet.hpp
//
// A SkipListSet is an implementation of a Set that is a skip list
// A skip list is a sequence of levels
//
// Implemented dynamically-allocated nodes with pointers connecting them.
//
// Each node contains only two pointers: one to the node that follows it
// on the same level and another to the equivalent node on the level below it.

#ifndef SKIPLISTSET_HPP
#define SKIPLISTSET_HPP

#include <vector>
#include "Set.hpp"




// SkipListKind indicates a kind of key: a normal one, the special key
// -INF, or the special key +INF.  It's necessary for us to implement
// the notion of -INF and +INF separately, since we're building a class
// template and not all types of keys would have a reasonable notion of
// -INF and +INF.

enum class SkipListKind
{
    Normal,
    NegInf,
    PosInf
};




// A SkipListKey represents a single key in a skip list.  It is possible
// to compare these keys using < or == operators (which are overloaded here)
// and those comparisons respect the notion of whether each key is normal,
// -INF, or +INF.

template <typename T>
class SkipListKey
{
public:
    SkipListKey(SkipListKind kind, const T& key);

    bool operator==(const SkipListKey& other) const;
    bool operator<(const SkipListKey& other) const;

private:
    SkipListKind kind;
    T key;
};


template <typename T>
SkipListKey<T>::SkipListKey(SkipListKind kind, const T& key)
    : kind{kind}, key{key}
{
}


template <typename T>
bool SkipListKey<T>::operator==(const SkipListKey& other) const
{
    return kind == other.kind
        && (kind != SkipListKind::Normal || key == other.key);
}


template <typename T>
bool SkipListKey<T>::operator<(const SkipListKey& other) const
{
    switch (kind)
    {
    case SkipListKind::NegInf:
        return other.kind != SkipListKind::NegInf;

    case SkipListKind::PosInf:
        return false;

    default: // SkipListKind::Normal
        return other.kind == SkipListKind::PosInf
            || (other.kind == SkipListKind::Normal && key < other.key);
    }
}




template <typename T>
class SkipListSet : public Set<T>
{
public:
    // Initializes an SkipListSet to be empty.
    SkipListSet();

    // Cleans up the SkipListSet so that it leaks no memory.
    virtual ~SkipListSet();

    // Initializes a new SkipListSet to be a copy of an existing one.
    SkipListSet(const SkipListSet& s);

    // Initializes a new SkipListSet whose contents are moved from an
    // expiring one.
    SkipListSet(SkipListSet&& s);

    // Assigns an existing SkipListSet into another.
    SkipListSet& operator=(const SkipListSet& s);

    // Assigns an expiring SkipListSet into another.
    SkipListSet& operator=(SkipListSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a SkipListSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in an expected time
    // of O(log n) (i.e., over the long run, we expect the average to be
    // O(log n)) with very high probability.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in an expected time of O(log n)
    // (i.e., over the long run, we expect the average to be O(log n))
    // with very high probability.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node {
        SkipListKey key;
        Node* next;
        Node* down;
    };

    std::vector<int> level;
    Node* head;
    Node* tail;

    int maxLevel;

private:
    void copyAll(const SkipListSet& s);
    void destroyAll();

};

//Initialzes an empty SkipListSet
template <typename T>
SkipListSet<T>::SkipListSet()
    : maxLevel(16)
{
    


}

//Cleans up SkipListSet
template <typename T>
SkipListSet<T>::~SkipListSet()
{
    destroyAll();
}

//Initialize copy of existing SkipListSet
template <typename T>
SkipListSet<T>::SkipListSet(const SkipListSet& s)
    : maxLevel(16)
{
    copyAll(s);
}

//Move SkipListSet contents to new SkipListSet
template <typename T>
SkipListSet<T>::SkipListSet(SkipListSet&& s)
    : maxLevel(16)
{
    std::swap(head, s.head);
}

//Assigns existing SkipListSet into another
template <typename T>
SkipListSet<T>& SkipListSet<T>::operator=(const SkipListSet& s)
{
    if(this != &s) {
        destroyAll();
        head = nullptr;
        copyAll(s);
    }

    return *this;
}

//Assigns expiring SkipListSet into another
template <typename T>
SkipListSet<T>& SkipListSet<T>::operator=(SkipListSet&& s)
{
    std::swap(head, s.head);
    return *this;
}

//Implement SkipListSet
template <typename T>
bool SkipListSet<T>::isImplemented() const
{
    return false;
}

//Add element to SkipListSet
template <typename T>
void SkipListSet<T>::add(const T& element)
{
    Node* curr = head;

    while (curr != nullptr) {
        if (curr->key == element) {
            return;
        }
        else if (curr->key > element) {
            ////terminate search if already on bottom level
            curr = curr->down;
        }
        else {
            curr = curr->next;
        }
    }

    head = new Node{element, head};

}

//See if element is in SkipListSet
template <typename T>
bool SkipListSet<T>::contains(const T& element) const
{
    Node* curr = head;

    while (curr != nullptr) {
        if (curr->key == element) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

//Return number of elements in the set
template <typename T>
unsigned int SkipListSet<T>::size() const
{
    Node* curr = head;
    unsigned int count = 0;

    while (curr != nullptr) {
        ++count;
        curr = curr->next;
    }

    return count;
}

template <typename T>
void SkipListSet<T>::copyAll(const SkipListSet& s)
{
    Node* curr = s.head;

    while (curr != nullptr) {
        head = new Node{curr->key, head}
        curr = curr->next;
    }
}

template <typename T>
void SkipListSet<T>::destroyAll() 
{
    Node* curr = head;

    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}



#endif // SKIPLISTSET_HPP

