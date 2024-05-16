#ifndef BTN_H
#define BTN_H
#include <iostream>

class AvlTree;

class Btn
{
  public:
    Btn(int akey);
    ~Btn();

    int getKey();
    Btn* getLeftChild();
    Btn* getRightChild();
    AvlTree* getNeighborhood();
    int getBalance();


    void setKey(int akey);
    void setLeftChild(Btn *lc);
    void setRightChild(Btn *rc);
    void setBalance(int b);

    friend std::ostream & operator<<(std::ostream & output_stream, Btn & node);

    bool hasNeighbor(int neighbor);
    Btn * addNeighbor(int neighbor);
    bool delNeighbor(int neighbor);

  protected:
  private:
    int key;
    int balance;
    Btn * leftchild;
    Btn * rightchild;
    AvlTree * neighborhood;
};

#endif // BTN_H
