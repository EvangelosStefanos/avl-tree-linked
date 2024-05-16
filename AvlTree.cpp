#include "AvlTree.h"
#include <iostream>
#include "Btn.h"
#include <vector>
#include <fstream>

using namespace std;


//Constructors
AvlTree::AvlTree()
{
    root = NULL;
    sizet = 0;
}


AvlTree::AvlTree(int r)
{
    this->root = new Btn(r);
    sizet = 1;
}


//Destructor
AvlTree::~AvlTree()
{
    destroyTree(this->root);
}


//Functions

/**
Given a value key, returns NULL if a node with that value doesn't
exist in the tree, otherwise returns the node with that value.
**/
Btn* AvlTree::searcht(int key)
{

    if(!this->root)
    {
        return NULL;
    }

    Btn *sn = this->root;
    while(sn)
    {
        if(key == sn->getKey())
            return sn;

        else if(key < sn->getKey())
            sn = sn->getLeftChild();

        else if(key > sn->getKey())
            sn = sn->getRightChild();
    }
    return NULL;
}


/**
Given a value akey, creates a node and adds it to the tree(if no such node already exists).
Returns the node added or the one with the given value if it exists already.
**/
Btn* AvlTree::addElement(int akey)
{
    Btn *snp = NULL;
    Btn *snode = this->root;
    vector<Btn*> path;

    if(!snode) //Tree is empty
    {
        snode = new Btn(akey);
        this->root = snode;
        return snode;
    }
    while(snode) //Search for node's position in the tree
    {
        snp = snode;
        path.push_back(snode);

        if(akey < snode->getKey())
            snode = snode->getLeftChild();

        else if(akey > snode->getKey())
            snode = snode->getRightChild();

        else if (akey == snode->getKey())
        {
            cout << "Node with key " << akey << " already exists." <<endl;
            return NULL;
        }
    }

    snode = new Btn(akey);
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
        Btn *c = path.at(i);
        Btn *p = path.at(i-1);
        Btn *pp = NULL;

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
    this->sizet++; //Increase the size of the tree
    return snode;
}


/**
Given a value akey, deletes the node with that value(if it exists in the tree).
Returns true if a node was deleted or false if no nodes were deleted.
**/
bool AvlTree::deleteElement(int akey)
{
    Btn *snp = NULL;
    Btn *snode = this->root;
    vector<Btn*> path;

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
        Btn *pn = snode;                  // Father of max leftchild of snode.
        Btn *mn = snode->getLeftChild();  // max leftchild of snode.

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
    Btn *snc = NULL;                        // Child of snode.

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
        Btn *c = path.at(i);
        Btn *p = path.at(i-1);
        Btn *pp = NULL;
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


/**
Given two values n and akey, adds n to the primary tree(if it doesn't exist already)
and then adds akey to its neighbors(if it doesn't exist already).
**/
void AvlTree::addNeighbor(int n, int akey)
{
    Btn* nn = searcht(n); // Search for the first node
    if(!nn)
        nn = addElement(n); // If not found, add it to the primary tree

    if(!nn->getNeighborhood())
        nn->setNeighborhood(new AvlTree(akey)); // If node has no neighborhood, create one and add neighbor as root

    else
        nn->getNeighborhood()->addElement(akey); // Add neighbor to the neighborhood
}


/**
Given two values n and akey, deletes akey from n's neighborhood(if it exists).
**/
void AvlTree::delNeighbor(int n, int akey)
{
    Btn* nn = searcht(n); // Search for the first node
    if(!nn)
        return;  // If not found, return

    if(!nn->getNeighborhood()) // If node has no neighborhood, return
        return;

    if(!(nn->getNeighborhood()->searcht(akey))) // If neighbor isn't in the neighborhood, return
        return;

    nn->getNeighborhood()->deleteElement(akey); //  Neighbor is in the neighborhood so delete it
}


/**
Given a node r, returns its height.
**/
int AvlTree::findHeight(Btn *r)
{
    if(!r) // If node is null return -1.
        return -1;
    return 1+max( findHeight( r->getLeftChild() ), findHeight( r->getRightChild() ) );
}


/**
Given a node r, returns its balance factor.
**/
int AvlTree::balance(Btn *r)
{
    if(!r)
        return 0;

    return findHeight(r->getLeftChild()) - findHeight(r->getRightChild());
}


/**
Given a node n, updates its balance factor.
**/
void AvlTree::updateBalance(Btn *n)
{
    n->setBalance(balance(n));
}


/**
Left-left rotation.
**/
void AvlTree::llRotation(Btn* p, Btn* c, Btn *pp)
{
    Btn *temp = c->getRightChild();
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
void AvlTree::lrRotation(Btn *p, Btn* c, Btn *pp)
{
    Btn *temp = c->getRightChild()->getLeftChild();
    p->setLeftChild(c->getRightChild());
    p->getLeftChild()->setLeftChild(c);
    c->setRightChild(temp);
    llRotation(p, p->getLeftChild(), pp);
}


/**
Right-right rotation.
**/
void AvlTree::rrRotation(Btn *p, Btn* c, Btn *pp)
{
    Btn *temp = c->getLeftChild();
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
void AvlTree::rlRotation(Btn *p, Btn* c, Btn *pp)
{
    Btn *temp = c->getLeftChild()->getRightChild();
    p->setRightChild(c->getLeftChild());
    p->getRightChild()->setRightChild(c);
    c->setLeftChild(temp);
    rrRotation(p, p->getRightChild(), pp);
}


/**
Performs a pre order traversal and prints every node in the tree.
**/
void AvlTree::print(Btn *r)
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
void AvlTree::InOrderPrint(Btn *r)
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
void AvlTree::PreOrderPrint(Btn *r)
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
void AvlTree::PostOrderPrint(Btn *r)
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
void AvlTree::output()
{
    ofstream f;
    f.open("output.txt");
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
void AvlTree::pront(Btn *n,ostream &f)
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
void AvlTree::pront2(Btn *n,ostream &f)
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
void AvlTree::destroyTree(Btn *n)
{
    if(n)
    {
        destroyTree(n->getLeftChild());
        destroyTree(n->getRightChild());
        delete n;
    }
}



