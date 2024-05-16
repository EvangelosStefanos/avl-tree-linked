#include "Btn.h"
#include <iostream>

using namespace std;


//Constructors
Btn::Btn()
{
    key = 0;
    balance = 0;
    leftchild = NULL;
    rightchild = NULL;
    neighborhood = NULL;
}

Btn::Btn(int akey)
{
    key = akey;
    balance = 0;
    leftchild = NULL;
    rightchild = NULL;
    neighborhood = NULL;
}

Btn::Btn(int akey, Btn *lchild, Btn *rchild, AvlTree *aneighbor)
{
    key = akey;
    balance = 0;
    leftchild = lchild;
    rightchild = rchild;
    neighborhood = aneighbor;
}

//MVP of the project
ostream &operator<<(ostream &str, Btn &n)
{
    str<<"Node : "<<n.getKey();
    if(n.getLeftChild())
        str<<"\tLeftchild : "<<n.getLeftChild()->getKey();
    else
        str<<"\tNo Leftchild";

    if(n.getRightChild())
        str<<"\tRightchild : "<<n.getRightChild()->getKey();
    else
        str<<"\tNo Rightchild";

    str<<endl;

    return str;
}

