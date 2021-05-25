// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <algorithm>



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
        int height=0;
    };

    Node* head;
    int treeSize;

private:
    void copyNode(Node& copy, Node& orig);
    void deleteTree(Node* n);
    int getHeight(Node* n);
    void leftRotate(Node* n);
    void rightRotate(Node* n);
};



template <typename T>
AVLSet<T>::AVLSet()
    :head{nullptr}, treeSize{0}
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    deleteTree(head);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    copyNode(head, s.head);
    treeSize = s.treeSize;
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
    :head{nullptr}
{
    std::swap(head, s.head);
    treeSize = s.treeSize;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
    std::swap(head, s.head);
    return *this;
}



template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    if(head == nullptr){
        head = new Node{element};
        treeSize++;
    }
    else{
        Node* curr = head;

        while(curr != nullptr){
            if(element == curr->key) return;
            else if(element < curr->key) curr = curr->left;
            else if(element > curr->key) curr = curr->right;
        }

        head = new Node{element};
        head->height = 1+max(getHeight(head->left),getHeight(head->right));
        treeSize++;
    }

    int balance = getHeight(head->left) - getHeight(head->right);

    //left left
    if(balance>1 && element < head->left->key) rightRotate(head);

    //right right
    if(balance<-1 && element > head->right->key) leftRotate(head);

    //left right
    if(balance>1 && element > head->left->key){
        leftRotate(head->left);
        rightRotate(head);
    }

    //right left
    if(balance<-1 && element < head->right->key){
        rightRotate(head->right);
        leftRotate(head->left);
    }
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
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
unsigned int AVLSet<T>::size() const
{
    return treeSize;
}

template <typename T>
void AVLSet<T>::copyNode(Node& copy, Node& orig){
    if(orig == nullptr) copy = nullptr;
    else{
        copy = new Node();
        copy->key = orig->key;
        copy->height = orig->height;
        copy->left = orig->left;
        copy->right = orig->right;

        if(orig->left != nullptr) copyNode(copy->left, orig->left);
        if(orig->right != nullptr) copyNode(copy->right, orig->right);
    }
}

template <typename T>
void AVLSet<T>::deleteTree(Node* n){
    if(n->left != nullptr) deleteTree(n->left);
    if(n->right != nullptr) deleteTree(n->right);
    if(n != nullptr) delete n;
}

template <typename T>
int AVLSet<T>::getHeight(Node* n){
    return n->height;
}

template <typename T>
void AVLSet<T>::leftRotate(Node* n){
    Node* m = n->right;
    Node* t2 = m->left;

    m->left = n;
    n->right = t2;

    n->height = 1+ max(getHeight(n->left), getHeight(n->right));
    m->height = 1+ max(getHeight(m->left), getHeight(m->right));
}

template <typename T>
void AVLSet<T>::rightRotate(Node* n){
    Node* m = n->left;
    Node* t2 = m->right;

    m->right = n;
    n->left = t2;

    n->height = 1+ max(getHeight(n->left), getHeight(n->right));
    m->height = 1+ max(getHeight(m->left), getHeight(m->right));
}
#endif // AVLSET_HPP

