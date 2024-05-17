#include <iostream>
#include "Btn.h"
#include "AvlTree.h"

template <class T>
Btn<T>::Btn(T akey)
{
  key = akey;
  balance = 0;
  leftchild = NULL;
  rightchild = NULL;
  neighborhood = new AvlTree<T>();
}

template <class T>
Btn<T>::~Btn() { delete this->neighborhood; }

template <class T>
T Btn<T>::getKey() { return this->key; }

template <class T>
Btn<T> * Btn<T>::getLeftChild() { return this->leftchild; }

template <class T>
Btn<T> * Btn<T>::getRightChild() { return this->rightchild; }

template <class T>
AvlTree<T> * Btn<T>::getNeighborhood() { return this->neighborhood; }

template <class T>
int Btn<T>::getBalance() { return this->balance; }

template <class T>
void Btn<T>::setKey(T akey) { this->key = akey; }

template <class T>
void Btn<T>::setLeftChild(Btn<T> * lc) { this->leftchild = lc; }

template <class T>
void Btn<T>::setRightChild(Btn<T> * rc) { this->rightchild = rc; }

template <class T>
void Btn<T>::setBalance(int b) { this->balance = b; }

template <class T>
std::ostream & operator<<(std::ostream & output_stream, Btn<T> & node)
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
bool Btn<T>::hasNeighbor(T neighbor)
{
  if (this->neighborhood->search(neighbor))
  {
    std::cout << "Link already exists for " << key << " and " << neighbor << "." << std::endl;
    return true;
  }
  return false;
}

template <class T>
Btn<T> *Btn<T>::insertNeighbor(T neighbor)
{
  return this->neighborhood->insertElement(neighbor); // Add neighbor to the neighborhood
}

template <class T>
bool Btn<T>::deleteNeighbor(T neighbor)
{
  bool deleted = this->neighborhood->deleteElement(neighbor);
  if (!deleted)
  {
    std::cout << "Failed to delete link. No link present for " << key << " and " << neighbor << "." << std::endl;
  }
  return deleted;
}
