#ifndef BTN_H
#define BTN_H
#include <iostream>

using namespace std;
class AvlTree;

class Btn
{
    public:
        Btn();
        Btn(int akey);
        Btn(int akey, Btn *lchild, Btn *rchild, AvlTree *aneighbor);

        int getKey(){return this->key;};
        Btn* getLeftChild(){return this->leftchild;};
        Btn* getRightChild(){return this->rightchild;};
        AvlTree* getNeighborhood(){return this->neighborhood;};
        int getBalance(){return this->balance;};


        void setKey(int akey){this->key = akey;};
        void setLeftChild(Btn *lc){this->leftchild = lc;};
        void setRightChild(Btn *rc){this->rightchild = rc;};
        void setNeighborhood(AvlTree *n){this->neighborhood = n;};
        void setBalance(int b){this->balance = b;}

        friend ostream &operator<<(ostream &str, Btn &n);

    protected:
    private:
        int key, balance;
        Btn *leftchild, *rightchild;
        AvlTree *neighborhood;
};

#endif // BTN_H
