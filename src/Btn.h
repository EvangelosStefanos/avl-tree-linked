#ifndef BTN_H
#define BTN_H
#include <iostream>

template <class T>
class AvlTree;

template <class T>
class Btn
{
  public:
    Btn(T akey);
    ~Btn();

    T getKey();
    Btn<T> * getLeftChild();
    Btn<T> * getRightChild();
    AvlTree<T> * getNeighborhood();
    int getBalance();


    void setKey(T akey);
    void setLeftChild(Btn<T> * lc);
    void setRightChild(Btn<T> * rc);
    void setBalance(int b);

    template <class Y>
    friend std::ostream &operator<<(std::ostream &output_stream, Btn<Y> &node);

    bool hasNeighbor(T neighbor);
    Btn<T> * insertNeighbor(T neighbor);
    bool deleteNeighbor(T neighbor);

  protected:
  private:
    T key;
    int balance;
    Btn<T> * leftchild;
    Btn<T> * rightchild;
    AvlTree<T> * neighborhood;
};

#endif // BTN_H
