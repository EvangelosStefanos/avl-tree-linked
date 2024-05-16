#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

class Btn;

using namespace std;

class AvlTree
{
    public:
        AvlTree();
        AvlTree(int r);
        ~AvlTree();

        Btn* searcht(int key);
        Btn* addElement(int key);
        bool deleteElement(int key);

        Btn* getRoot(){return root;};
        int findHeight(Btn *r);

        int balance(Btn *r);
        void updateBalance(Btn *n);

        void llRotation(Btn *parent, Btn *child, Btn *pp);
        void rrRotation(Btn *parent, Btn *child, Btn *pp);
        void lrRotation(Btn *parent, Btn *child, Btn *pp);
        void rlRotation(Btn *parent, Btn *child, Btn *pp);

        void print(Btn *r);
        void InOrderPrint(Btn *root);
        void PreOrderPrint(Btn *root);
        void PostOrderPrint(Btn *root);

        void output(std::string p);
        void pront(Btn *n, ostream &f);
        void pront2(Btn *n, ostream &f);

        void destroyTree(Btn *n);

    protected:
    private:
        Btn *root;
        int sizet;
};

#endif // AVLTREE_H
