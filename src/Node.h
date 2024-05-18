#ifndef NODE_H
#define NODE_H
#include <iostream>

template <class T>
class AVLtree;

template <class T>
class Node
{
  public:
    Node(T akey);
    ~Node();

    T getKey();
    Node<T> * getLeftChild();
    Node<T> * getRightChild();
    AVLtree<T> * getNeighborhood();
    int getBalance();


    void setKey(T akey);
    void setLeftChild(Node<T> * lc);
    void setRightChild(Node<T> * rc);
    void setBalance(int b);

    template <class Y>
    friend std::ostream &operator<<(std::ostream &output_stream, Node<Y> &node);

    bool hasNeighbor(T neighbor);
    Node<T> * insertNeighbor(T neighbor);
    bool deleteNeighbor(T neighbor);

  protected:
  private:
    T key;
    int balance;
    Node<T> * leftchild;
    Node<T> * rightchild;
    AVLtree<T> * neighborhood;
};

#endif // NODE_H
