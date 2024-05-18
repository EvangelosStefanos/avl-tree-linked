#include <iostream>
#include <fstream>
#include <vector>
#include "AVLtree.h"
#include "Node.h"

using namespace std;


//Constructors
template <class T>
AVLtree<T>::AVLtree()
{
    root = NULL;
    sizet = 0;
}

template <class T>
AVLtree<T>::AVLtree(T r)
{
    this->root = new Node<T>(r);
    sizet = 1;
}


//Destructor
template <class T>
AVLtree<T>::~AVLtree()
{
    destroyTree(this->root);
}


//Functions

/**
Given a value key, returns NULL if a node with that value doesn't
exist in the tree, otherwise returns the node with that value.
**/
template <class T>
Node<T> * AVLtree<T>::search(T key)
{
    if(!this->root)
    {
        return NULL;
    }
    Node<T> * sn = this->root;
    while(sn)
    {
        if(key == sn->getKey())
        {
            return sn;
        }
        else if(key < sn->getKey())
        {
            sn = sn->getLeftChild();
        }
        else if(key > sn->getKey())
        {
            sn = sn->getRightChild();
        }
    }
    return NULL;
}


/**
Given a value akey, creates a node and adds it to the tree(if no such node already exists).
Returns the node added or the one with the given value if it exists already.
**/
template <class T>
Node<T> * AVLtree<T>::insertElement(T akey)
{
    Node<T> * snp = NULL;
    Node<T> * snode = this->root;
    vector<Node<T> * > path;

    if(!snode) //Tree is empty
    {
        snode = new Node<T>(akey);
        this->sizet++; // Increase the size of the tree
        this->root = snode;
        return snode;
    }
    while(snode) //Search for node's position in the tree
    {
        snp = snode;
        path.push_back(snode);

        if (akey == snode->getKey())
        {
          cout << "Node with key " << akey << " already exists." << endl;
          return NULL;
        }
        else if (akey < snode->getKey())
        {
            snode = snode->getLeftChild();
        }
        else if(akey > snode->getKey())
        {
            snode = snode->getRightChild();
        }
    }

    snode = new Node<T>(akey);
    this->sizet++; // Increase the size of the tree
    path.push_back(snode);

    if(akey < snp->getKey()) //Set new node as left child
    {
        snp->setLeftChild(snode);
    }
    else if(akey > snp->getKey()) //Set new node as right child
    {
        snp->setRightChild(snode);
    }

    for(int i = path.size() - 1; i > 0; i--) //Balance tree
    {
        Node<T> * c = path.at(i);
        Node<T> * p = path.at(i-1);
        Node<T> * pp = NULL;

        if(i-2 >= 0)
            pp = path.at(i-2);

        updateBalance(p); //Compute the node's current balance

        if(p->getBalance() == 2)
        {
            if(c->getBalance() == 1)
                llRotation(p,c,pp);

            if(c->getBalance() == -1)
                lrRotation(p,c,pp);

            break;
        }
        else if(p->getBalance() == -2)
        {
            if(c->getBalance() == 1)
                rlRotation(p,c,pp);

            if(c->getBalance() == -1)
                rrRotation(p,c,pp);

            break;
        }
    }
    return snode;
}


/**
Given a value akey, deletes the node with that value(if it exists in the tree).
Returns true if a node was deleted or false if no nodes were deleted.
**/
template <class T>
bool AVLtree<T>::deleteElement(T akey)
{
    Node<T> * snp = NULL;
    Node<T> * snode = this->root;
    vector<Node<T> * > path;

    while(snode)
    {
        if(akey == snode->getKey())
            break;

        path.push_back(snode);

        snp = snode;

        if(akey < snode->getKey())
            snode = snode->getLeftChild();

        else if(akey > snode->getKey())
            snode = snode->getRightChild();
    }

    if(!snode)                        // If node not found in tree return false. Else continue.
        return false;

    if(snode->getLeftChild() && snode->getRightChild()) // Node to be deleted has two children.
    {
        Node<T> * pn = snode;                  // Father of max leftchild of snode.
        Node<T> * mn = snode->getLeftChild();  // max leftchild of snode.

        while(mn->getRightChild())         // Find snode's max leftchild and its parent.
        {
            path.push_back(pn);
            pn = mn;                      // Parent follows the child.
            mn = mn->getRightChild();      // Child moves to next node.
        }

        snode->setKey(mn->getKey());      // Transfer max leftchild to the position of the node set for deletion
        snode = mn;                       // Set max leftchild for deletion
        snp = pn;                         // Set max leftchild's parent as the parent of node to be deleted

    }
                                          // Node has one child or none.
    Node<T> * snc = NULL;                        // Child of snode.

    if (snode->getLeftChild())              //Store snode's child to snc.
    {
        snc = snode->getLeftChild();
        path.push_back(snc);
    }
    else
    {
        snc = snode->getRightChild();
        path.push_back(snc);
    }

    if (snode == this->root)          // If snode is root set it's child as root.
        this->root = snc;
    else
    {
        if(snp->getLeftChild() == snode)            // Replace snode with its child.
            snp->setLeftChild(snc);
        else
            snp->setRightChild(snc);
    }
    delete snode;

    for(int i = path.size() - 1; i > 0; i--) //Balance tree
    {
        Node<T> * c = path.at(i);
        Node<T> * p = path.at(i-1);
        Node<T> * pp = NULL;
        if(i-2 >= 0)
            pp = path.at(i-2);

        updateBalance(p);

        if(p->getBalance() == 2)
        {
            if(!c)
            {
                if(p->getLeftChild())
                    c = p->getLeftChild();
                else
                    c = p->getRightChild();
                updateBalance(c);
            }
            if(c->getBalance() == 1)
                llRotation(p,c,pp);

            if(c->getBalance() == -1)
                lrRotation(p,c,pp);

            break;
        }
        else if(p->getBalance() == -2)
        {
            if(!c)
            {
                if(p->getLeftChild())
                    c = p->getLeftChild();
                else
                    c = p->getRightChild();
                updateBalance(c);
            }
            if(c->getBalance() == 1)
                rlRotation(p,c,pp);

            if(c->getBalance() == -1)
                rrRotation(p,c,pp);

            break;
        }
    }
    this->sizet--;
    return true;
}


template <class T>
Node<T> *AVLtree<T>::getRoot()
{
  return this->root;
}


/**
Given a node r, returns its height.
**/
template <class T>
int AVLtree<T>::findHeight(Node<T> *r)
{
    if(!r) // If node is null return -1.
        return -1;
    return 1+max( findHeight( r->getLeftChild() ), findHeight( r->getRightChild() ) );
}


/**
Given a node r, returns its balance factor.
**/
template <class T>
int AVLtree<T>::balance(Node<T> *r)
{
    if(!r)
        return 0;

    return findHeight(r->getLeftChild()) - findHeight(r->getRightChild());
}


/**
Given a node n, updates its balance factor.
**/
template <class T>
void AVLtree<T>::updateBalance(Node<T> * n)
{
    n->setBalance(balance(n));
}


/**
Left-left rotation.
**/
template <class T>
void AVLtree<T>::llRotation(Node<T> *p, Node<T> *c, Node<T> *pp)
{
    Node<T> * temp = c->getRightChild();
    c->setRightChild(p);
    p->setLeftChild(temp);

    if(p == root)
        root = c;

    if(pp && pp->getLeftChild() == p)
        pp->setLeftChild(c);

    if(pp && pp->getRightChild() == p)
        pp->setRightChild(c);
}


/**
Left-right rotation.
**/
template <class T>
void AVLtree<T>::lrRotation(Node<T> * p, Node<T> * c, Node<T> * pp)
{
    Node<T> * temp = c->getRightChild()->getLeftChild();
    p->setLeftChild(c->getRightChild());
    p->getLeftChild()->setLeftChild(c);
    c->setRightChild(temp);
    llRotation(p, p->getLeftChild(), pp);
}


/**
Right-right rotation.
**/
template <class T>
void AVLtree<T>::rrRotation(Node<T> * p, Node<T> * c, Node<T> * pp)
{
    Node<T> * temp = c->getLeftChild();
    c->setLeftChild(p);
    p->setRightChild(temp);

    if(p == root)
        root = c;

    if(pp && pp->getLeftChild() == p)
        pp->setLeftChild(c);

    if(pp && pp->getRightChild() == p)
        pp->setRightChild(c);
}


/**
Right-left rotation.
**/
template <class T>
void AVLtree<T>::rlRotation(Node<T> * p, Node<T> * c, Node<T> * pp)
{
    Node<T> * temp = c->getLeftChild()->getRightChild();
    p->setRightChild(c->getLeftChild());
    p->getRightChild()->setRightChild(c);
    c->setLeftChild(temp);
    rrRotation(p, p->getRightChild(), pp);
}


/**
Performs a pre order traversal and prints every node in the tree.
**/
template <class T>
void AVLtree<T>::print(Node<T> *r)
{
    if(!r)
        return;

    cout<<*r;
    print(r->getLeftChild());
    print(r->getRightChild());
}


/**
In order traversal.
**/
template <class T>
void AVLtree<T>::InOrderPrint(Node<T> *r)
{
    if(r)
    {
        InOrderPrint(r->getLeftChild());
        cout << r->getKey()<<" "<<endl;
        InOrderPrint(r->getRightChild());
    }
}


/**
Pre order traversal.
**/
template <class T>
void AVLtree<T>::PreOrderPrint(Node<T> * r)
{
    if(r)
    {
        cout << r->getKey()<<" "<<endl;
        InOrderPrint(r->getLeftChild());
        InOrderPrint(r->getRightChild());
    }
}


/**
Post order traversal.
**/
template <class T>
void AVLtree<T>::PostOrderPrint(Node<T> * r)
{
    if(r)
    {
        InOrderPrint(r->getLeftChild());
        InOrderPrint(r->getRightChild());
        cout << r->getKey()<<" "<<endl;
    }
}


/**
Prints each node of a tree, the size of its neighborhood and the neighbor nodes to a file.
**/
template <class T>
void AVLtree<T>::output(std::string p)
{
    ofstream f;
    f.open(p);
    if(!f)
    {
        cerr<<"File problem"<<endl;
        return;
    }

    pront(this->root, f);
    f.close();
}


/**
Recurse through a tree(in order traversal), printing its nodes and the size of each node's neighborhood.
**/
template <class T>
void AVLtree<T>::pront(Node<T> * n, ostream & f)
{
    if(!n)
        return;

    pront(n->getLeftChild(), f);
    f<<n->getKey();
    if(n->getNeighborhood())
    {
        f<<" "<<n->getNeighborhood()->sizet;
        pront2(n->getNeighborhood()->getRoot(), f);
    }
    else
    {
        f<<" "<<0;
    }
    f<<endl;
    pront(n->getRightChild(), f);
}


/**
Recurse through a tree(in order traversal), printing its nodes to a file.
**/
template <class T>
void AVLtree<T>::pront2(Node<T> * n, ostream & f)
{
    if(!n)
        return;

    pront2(n->getLeftChild(), f);
    f<<" "<<n->getKey();
    pront2(n->getRightChild(), f);
}


/**
Recurse through a tree(post order traversal) and delete every node in it.
**/
template <class T>
void AVLtree<T>::destroyTree(Node<T> * n)
{
    if(n)
    {
        destroyTree(n->getLeftChild());
        destroyTree(n->getRightChild());
        delete n;
    }
}



