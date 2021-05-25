// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* head;
    int treeSize;

private:
    void copyNode(Node& copy, Node& orig);
    void deleteTree(Node* n);
};


template <typename T>
BSTSet<T>::BSTSet()
    :head{nullptr}, treeSize{0}
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    deleteTree(head);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
    :head{nullptr}
{
    copyNode(head, s.head);
    treeSize = s.treeSize;
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
    :head{nullptr}
{
    std::swap(head, s.head);
    treeSize = s.treeSize;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if (this != &s) {
        deleteTree(head);
        head = nullptr;
        copyNode(head, s.head);
        treeSize = s.treeSize;
    return *this;
    }
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
    std::swap(head, s.head)
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    if(head = nullptr){
        head = new Node{element};
        treeSize++;
    }
    else{
        Node* curr = head;

        while(curr != nullptr){
            if(element < curr->key) curr = curr->left;
            else if(element > curr->key) curr = curr->right;
        }

        head = new Node{element}
        treeSize++
    }
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    Node* curr = head;

    while(curr != nullptr){
        if(curr->key == element) return true;
        else if(element < curr->key) curr = curr->left;
        else curr = curr->right;
    }

    return false;
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return treeSize;
}

template <typename T>
void BSTSet<T>::copyNode(Node& copy, Node& orig){
    if(orig == nullptr) copy = nullptr;
    else{
        copy = new Node();
        copy->key = orig->key;
        copy->left = orig->left;
        copy->right = orig->right;

        if(orig->left != nullptr) copyNode(copy->left, orig->left);
        if(origh->right != nullptr) copyNode(copy->right, orig->right);
    }
}

template <typename T>
void BSTSet<T>::deleteTree(Node* n){
    if(n->left != nullptr) deleteTree(n->left);
    if(n->right != nullptr) deleteTree(n->right);
    if(n != nullptr) delete n;
}



#endif // BSTSET_HPP

