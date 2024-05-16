#include <iostream>
#include "Btn.h"
#include "AvlTree.h"

Btn::Btn(int akey)
{
  key = akey;
  balance = 0;
  leftchild = NULL;
  rightchild = NULL;
  neighborhood = new AvlTree();
}

Btn::~Btn(){delete this->neighborhood;}

int Btn::getKey() { return this->key; }

Btn * Btn::getLeftChild() { return this->leftchild; }

Btn * Btn::getRightChild() { return this->rightchild; }

AvlTree * Btn::getNeighborhood() { return this->neighborhood; }

int Btn::getBalance() { return this->balance; }

void Btn::setKey(int akey) { this->key = akey; }

void Btn::setLeftChild(Btn *lc) { this->leftchild = lc; }

void Btn::setRightChild(Btn *rc) { this->rightchild = rc; }

void Btn::setBalance(int b) { this->balance = b; }

std::ostream &operator<<(std::ostream &output_stream, Btn &node)
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

bool Btn::hasNeighbor(int neighbor)
{
  if (this->neighborhood->searcht(neighbor))
  {
    std::cout << "Link already exists for " << key << " and " << neighbor << "." << std::endl;
    return true;
  }
  return false;
}

Btn * Btn::addNeighbor(int neighbor)
{
  return this->neighborhood->addElement(neighbor); // Add neighbor to the neighborhood
}

bool Btn::delNeighbor(int neighbor)
{
  bool deleted = this->neighborhood->deleteElement(neighbor);
  if (!deleted)
  {
    std::cout << "Failed to delete link. No link present for " << key << " and " << neighbor << "." << std::endl;
  }
  return deleted;
}
