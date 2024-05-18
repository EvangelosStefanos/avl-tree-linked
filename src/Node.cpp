#include <iostream>
#include "Node.h"
#include "AVLtree.h"

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
Node<T> * Node<T>::getLeftChild() { return this->leftchild; }

template <class T>
Node<T> * Node<T>::getRightChild() { return this->rightchild; }

template <class T>
AVLtree<T> * Node<T>::getNeighborhood() { return this->neighborhood; }

template <class T>
int Node<T>::getBalance() { return this->balance; }

template <class T>
void Node<T>::setKey(T akey) { this->key = akey; }

template <class T>
void Node<T>::setLeftChild(Node<T> * lc) { this->leftchild = lc; }

template <class T>
void Node<T>::setRightChild(Node<T> * rc) { this->rightchild = rc; }

template <class T>
void Node<T>::setBalance(int b) { this->balance = b; }

template <class T>
std::ostream & operator<<(std::ostream & output_stream, Node<T> & node)
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
