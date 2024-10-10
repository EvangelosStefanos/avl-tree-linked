#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
////  Node
////////////////////////////////////////////////////////////////////////////////

template <class T>
class AVLtree;

template <class T>
class Node
{
public:
    Node(T akey);
    ~Node();

    T getKey();
    Node<T> *getLeftChild();
    Node<T> *getRightChild();
    AVLtree<T> *getNeighborhood();
    int getBalance();

    void setKey(T akey);
    void setLeftChild(Node<T> *lc);
    void setRightChild(Node<T> *rc);
    void setBalance(int b);

    template <class Y>
    friend std::ostream &operator<<(std::ostream &output_stream, Node<Y> &node);

    bool hasNeighbor(T neighbor);
    Node<T> *insertNeighbor(T neighbor);
    bool deleteNeighbor(T neighbor);

protected:
private:
    T key;
    int balance;
    Node<T> *leftchild;
    Node<T> *rightchild;
    AVLtree<T> *neighborhood;
};

template <class T>
Node<T>::Node(T akey)
{
    key = akey;
    balance = 0;
    leftchild = NULL;
    rightchild = NULL;
    neighborhood = new AVLtree<T>();
}

template <class T>
Node<T>::~Node() { delete this->neighborhood; }

template <class T>
T Node<T>::getKey() { return this->key; }

template <class T>
Node<T> *Node<T>::getLeftChild() { return this->leftchild; }

template <class T>
Node<T> *Node<T>::getRightChild() { return this->rightchild; }

template <class T>
AVLtree<T> *Node<T>::getNeighborhood() { return this->neighborhood; }

template <class T>
int Node<T>::getBalance() { return this->balance; }

template <class T>
void Node<T>::setKey(T akey) { this->key = akey; }

template <class T>
void Node<T>::setLeftChild(Node<T> *lc) { this->leftchild = lc; }

template <class T>
void Node<T>::setRightChild(Node<T> *rc) { this->rightchild = rc; }

template <class T>
void Node<T>::setBalance(int b) { this->balance = b; }

template <class T>
std::ostream &operator<<(std::ostream &output_stream, Node<T> &node)
{
    output_stream << "Node : " << node.getKey();
    if (node.getLeftChild())
        output_stream << "\tLeftchild : " << node.getLeftChild()->getKey();
    else
        output_stream << "\tNo Leftchild";

    if (node.getRightChild())
        output_stream << "\tRightchild : " << node.getRightChild()->getKey();
    else
        output_stream << "\tNo Rightchild";

    output_stream << std::endl;

    return output_stream;
}

template <class T>
bool Node<T>::hasNeighbor(T neighbor)
{
    if (this->neighborhood->search(neighbor))
    {
        std::cout << "Link already exists for " << key << " and " << neighbor << "." << std::endl;
        return true;
    }
    return false;
}

template <class T>
Node<T> *Node<T>::insertNeighbor(T neighbor)
{
    return this->neighborhood->insertElement(neighbor); // Add neighbor to the neighborhood
}

template <class T>
bool Node<T>::deleteNeighbor(T neighbor)
{
    bool deleted = this->neighborhood->deleteElement(neighbor);
    if (!deleted)
    {
        std::cout << "Failed to delete link. No link present for " << key << " and " << neighbor << "." << std::endl;
    }
    return deleted;
}

////////////////////////////////////////////////////////////////////////////////
////  AVLtree
////////////////////////////////////////////////////////////////////////////////

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
        Node<T> * root;
        int sizet;
};

// Constructors
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

// Destructor
template <class T>
AVLtree<T>::~AVLtree()
{
    destroyTree(this->root);
}

// Functions

/**
Given a value key, returns NULL if a node with that value doesn't
exist in the tree, otherwise returns the node with that value.
**/
template <class T>
Node<T> *AVLtree<T>::search(T key)
{
    if (!this->root)
    {
        return NULL;
    }
    Node<T> *sn = this->root;
    while (sn)
    {
        if (key == sn->getKey())
        {
            return sn;
        }
        else if (key < sn->getKey())
        {
            sn = sn->getLeftChild();
        }
        else if (key > sn->getKey())
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
Node<T> *AVLtree<T>::insertElement(T akey)
{
    Node<T> *snp = NULL;
    Node<T> *snode = this->root;
    std::vector<Node<T> *> path;

    if (!snode) // Tree is empty
    {
        snode = new Node<T>(akey);
        this->sizet++; // Increase the size of the tree
        this->root = snode;
        return snode;
    }
    while (snode) // Search for node's position in the tree
    {
        snp = snode;
        path.push_back(snode);

        if (akey == snode->getKey())
        {
            std::cout << "Node with key " << akey << " already exists." << std::endl;
            return NULL;
        }
        else if (akey < snode->getKey())
        {
            snode = snode->getLeftChild();
        }
        else if (akey > snode->getKey())
        {
            snode = snode->getRightChild();
        }
    }

    snode = new Node<T>(akey);
    this->sizet++; // Increase the size of the tree
    path.push_back(snode);

    if (akey < snp->getKey()) // Set new node as left child
    {
        snp->setLeftChild(snode);
    }
    else if (akey > snp->getKey()) // Set new node as right child
    {
        snp->setRightChild(snode);
    }

    for (int i = path.size() - 1; i > 0; i--) // Balance tree
    {
        Node<T> *c = path.at(i);
        Node<T> *p = path.at(i - 1);
        Node<T> *pp = NULL;

        if (i - 2 >= 0)
            pp = path.at(i - 2);

        updateBalance(p); // Compute the node's current balance

        if (p->getBalance() == 2)
        {
            if (c->getBalance() == 1)
                llRotation(p, c, pp);

            if (c->getBalance() == -1)
                lrRotation(p, c, pp);

            break;
        }
        else if (p->getBalance() == -2)
        {
            if (c->getBalance() == 1)
                rlRotation(p, c, pp);

            if (c->getBalance() == -1)
                rrRotation(p, c, pp);

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
    Node<T> *snp = NULL;
    Node<T> *snode = this->root;
    std::vector<Node<T> *> path;

    while (snode)
    {
        if (akey == snode->getKey())
            break;

        path.push_back(snode);

        snp = snode;

        if (akey < snode->getKey())
            snode = snode->getLeftChild();

        else if (akey > snode->getKey())
            snode = snode->getRightChild();
    }

    if (!snode) // If node not found in tree return false. Else continue.
        return false;

    if (snode->getLeftChild() && snode->getRightChild()) // Node to be deleted has two children.
    {
        Node<T> *pn = snode;                 // Father of max leftchild of snode.
        Node<T> *mn = snode->getLeftChild(); // max leftchild of snode.

        while (mn->getRightChild()) // Find snode's max leftchild and its parent.
        {
            path.push_back(pn);
            pn = mn;                  // Parent follows the child.
            mn = mn->getRightChild(); // Child moves to next node.
        }

        snode->setKey(mn->getKey()); // Transfer max leftchild to the position of the node set for deletion
        snode = mn;                  // Set max leftchild for deletion
        snp = pn;                    // Set max leftchild's parent as the parent of node to be deleted
    }
    // Node has one child or none.
    Node<T> *snc = NULL; // Child of snode.

    if (snode->getLeftChild()) // Store snode's child to snc.
    {
        snc = snode->getLeftChild();
        path.push_back(snc);
    }
    else
    {
        snc = snode->getRightChild();
        path.push_back(snc);
    }

    if (snode == this->root) // If snode is root set it's child as root.
        this->root = snc;
    else
    {
        if (snp->getLeftChild() == snode) // Replace snode with its child.
            snp->setLeftChild(snc);
        else
            snp->setRightChild(snc);
    }
    delete snode;

    for (int i = path.size() - 1; i > 0; i--) // Balance tree
    {
        Node<T> *c = path.at(i);
        Node<T> *p = path.at(i - 1);
        Node<T> *pp = NULL;
        if (i - 2 >= 0)
            pp = path.at(i - 2);

        updateBalance(p);

        if (p->getBalance() == 2)
        {
            if (!c)
            {
                if (p->getLeftChild())
                    c = p->getLeftChild();
                else
                    c = p->getRightChild();
                updateBalance(c);
            }
            if (c->getBalance() == 1)
                llRotation(p, c, pp);

            if (c->getBalance() == -1)
                lrRotation(p, c, pp);

            break;
        }
        else if (p->getBalance() == -2)
        {
            if (!c)
            {
                if (p->getLeftChild())
                    c = p->getLeftChild();
                else
                    c = p->getRightChild();
                updateBalance(c);
            }
            if (c->getBalance() == 1)
                rlRotation(p, c, pp);

            if (c->getBalance() == -1)
                rrRotation(p, c, pp);

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
    if (!r) // If node is null return -1.
        return -1;
    return 1 + std::max(findHeight(r->getLeftChild()), findHeight(r->getRightChild()));
}

/**
Given a node r, returns its balance factor.
**/
template <class T>
int AVLtree<T>::balance(Node<T> *r)
{
    if (!r)
        return 0;

    return findHeight(r->getLeftChild()) - findHeight(r->getRightChild());
}

/**
Given a node n, updates its balance factor.
**/
template <class T>
void AVLtree<T>::updateBalance(Node<T> *n)
{
    n->setBalance(balance(n));
}

/**
Left-left rotation.
**/
template <class T>
void AVLtree<T>::llRotation(Node<T> *p, Node<T> *c, Node<T> *pp)
{
    Node<T> *temp = c->getRightChild();
    c->setRightChild(p);
    p->setLeftChild(temp);

    if (p == root)
        root = c;

    if (pp && pp->getLeftChild() == p)
        pp->setLeftChild(c);

    if (pp && pp->getRightChild() == p)
        pp->setRightChild(c);
}

/**
Left-right rotation.
**/
template <class T>
void AVLtree<T>::lrRotation(Node<T> *p, Node<T> *c, Node<T> *pp)
{
    Node<T> *temp = c->getRightChild()->getLeftChild();
    p->setLeftChild(c->getRightChild());
    p->getLeftChild()->setLeftChild(c);
    c->setRightChild(temp);
    llRotation(p, p->getLeftChild(), pp);
}

/**
Right-right rotation.
**/
template <class T>
void AVLtree<T>::rrRotation(Node<T> *p, Node<T> *c, Node<T> *pp)
{
    Node<T> *temp = c->getLeftChild();
    c->setLeftChild(p);
    p->setRightChild(temp);

    if (p == root)
        root = c;

    if (pp && pp->getLeftChild() == p)
        pp->setLeftChild(c);

    if (pp && pp->getRightChild() == p)
        pp->setRightChild(c);
}

/**
Right-left rotation.
**/
template <class T>
void AVLtree<T>::rlRotation(Node<T> *p, Node<T> *c, Node<T> *pp)
{
    Node<T> *temp = c->getLeftChild()->getRightChild();
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
    if (!r)
        return;

    std::cout << *r;
    print(r->getLeftChild());
    print(r->getRightChild());
}

/**
In order traversal.
**/
template <class T>
void AVLtree<T>::InOrderPrint(Node<T> *r)
{
    if (r)
    {
        InOrderPrint(r->getLeftChild());
        std::cout << r->getKey() << " " << std::endl;
        InOrderPrint(r->getRightChild());
    }
}

/**
Pre order traversal.
**/
template <class T>
void AVLtree<T>::PreOrderPrint(Node<T> *r)
{
    if (r)
    {
        std::cout << r->getKey() << " " << std::endl;
        InOrderPrint(r->getLeftChild());
        InOrderPrint(r->getRightChild());
    }
}

/**
Post order traversal.
**/
template <class T>
void AVLtree<T>::PostOrderPrint(Node<T> *r)
{
    if (r)
    {
        InOrderPrint(r->getLeftChild());
        InOrderPrint(r->getRightChild());
        std::cout << r->getKey() << " " << std::endl;
    }
}

/**
Prints each node of a tree, the size of its neighborhood and the neighbor nodes to a file.
**/
template <class T>
void AVLtree<T>::output(std::string p)
{
    std::ofstream f;
    f.open(p);
    if (!f)
    {
        std::cerr << "ERROR: Failed to open file: {" << p << "} in write mode." << std::endl;
        return;
    }

    pront(this->root, f);
    f.close();
}

/**
Recurse through a tree(in order traversal), printing its nodes and the size of each node's neighborhood.
**/
template <class T>
void AVLtree<T>::pront(Node<T> *n, std::ostream &f)
{
    if (!n)
        return;

    pront(n->getLeftChild(), f);
    f << n->getKey();
    if (n->getNeighborhood())
    {
        f << " " << n->getNeighborhood()->sizet;
        pront2(n->getNeighborhood()->getRoot(), f);
    }
    else
    {
        f << " " << 0;
    }
    f << std::endl;
    pront(n->getRightChild(), f);
}

/**
Recurse through a tree(in order traversal), printing its nodes to a file.
**/
template <class T>
void AVLtree<T>::pront2(Node<T> *n, std::ostream &f)
{
    if (!n)
        return;

    pront2(n->getLeftChild(), f);
    f << " " << n->getKey();
    pront2(n->getRightChild(), f);
}

/**
Recurse through a tree(post order traversal) and delete every node in it.
**/
template <class T>
void AVLtree<T>::destroyTree(Node<T> *n)
{
    if (n)
    {
        destroyTree(n->getLeftChild());
        destroyTree(n->getRightChild());
        delete n;
    }
}

#endif // AVLTREE_H
