#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

template <class T>
class Btn;

template <class T>
class AvlTree
{
    public:
        AvlTree();
        AvlTree(T r);
        ~AvlTree();

        Btn<T> * search(T key);
        Btn<T> * insertElement(T key);
        bool deleteElement(T key);

        Btn<T> * getRoot();
        int findHeight(Btn<T> * r);

        int balance(Btn<T> * r);
        void updateBalance(Btn<T> * n);

        void llRotation(Btn<T> * parent, Btn<T> * child, Btn<T> * pp);
        void rrRotation(Btn<T> * parent, Btn<T> * child, Btn<T> * pp);
        void lrRotation(Btn<T> * parent, Btn<T> * child, Btn<T> * pp);
        void rlRotation(Btn<T> * parent, Btn<T> * child, Btn<T> * pp);

        void print(Btn<T> * r);
        void InOrderPrint(Btn<T> * root);
        void PreOrderPrint(Btn<T> * root);
        void PostOrderPrint(Btn<T> * root);

        void output(std::string p);
        void pront(Btn<T> * n, std::ostream & f);
        void pront2(Btn<T> * n, std::ostream & f);

        void destroyTree(Btn<T> * n);

    protected:
    private:
        Btn<T> *root;
        int sizet;
};

#endif // AVLTREE_H
