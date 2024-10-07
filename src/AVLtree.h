#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

template <class T>
class Node;

template <class T>
class AVLtree
{
    public:
        AVLtree();
        AVLtree(T r);
        ~AVLtree();

        Node<T> * search(T key);
        Node<T> * insertElement(T key);
        bool deleteElement(T key);

        Node<T> * getRoot();
        int findHeight(Node<T> * r);

        int balance(Node<T> * r);
        void updateBalance(Node<T> * n);

        void llRotation(Node<T> * parent, Node<T> * child, Node<T> * pp);
        void rrRotation(Node<T> * parent, Node<T> * child, Node<T> * pp);
        void lrRotation(Node<T> * parent, Node<T> * child, Node<T> * pp);
        void rlRotation(Node<T> * parent, Node<T> * child, Node<T> * pp);

        void print(Node<T> * r);
        void InOrderPrint(Node<T> * root);
        void PreOrderPrint(Node<T> * root);
        void PostOrderPrint(Node<T> * root);

        void output(std::string p);
        void pront(Node<T> * n, std::ostream & f);
        void pront2(Node<T> * n, std::ostream & f);

        void destroyTree(Node<T> * n);

    protected:
    private:
        Node<T> *root;
        int sizet;
};

#endif // AVLTREE_H
