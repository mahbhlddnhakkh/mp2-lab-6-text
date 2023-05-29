#ifndef __HListIterator_H__
#define __HListIterator_H__

#include "ListNode.h"
#include "Stack.h"

template<class T>
class THierarchyList;

template<class T>
class THListIterator
{
protected:
  TStack<TListNode<T>*> st;
public:
  //THListIterator(TListNode<T>* node);
  //THListIterator(THierarchyList<T>* l);
  THListIterator(const TStack<TListNode<T>*>& st);
  bool operator==(THListIterator<T>& it);
  bool operator!=(THListIterator<T>& it);
  THListIterator<T>& operator++();

  T& operator*();
  T* operator->();
};

template<class T>
inline THListIterator<T>::THListIterator(const TStack<TListNode<T>*>& st)
{
  this->st = st;
}

template<class T>
inline bool THListIterator<T>::operator==(THListIterator<T> &it)
{
  return st == it.st;
}

template<class T>
inline bool THListIterator<T>::operator!=(THListIterator<T> &it)
{
  return st != it.st;
}

template<class T>
inline THListIterator<T>& THListIterator<T>::operator++()
{
  // Basically preorder travesal of the tree without recursion
  if (st.IsEmpty())
    return *this;
  TListNode<T>* curr = st.TopPop();
  if (curr->next)
    st.Push(curr->next);
  if (curr->child)
    st.Push(curr->child);
  return *this;
}

template<class T>
inline T& THListIterator<T>::operator*()
{
  return *(operator->());
}

template<class T>
inline T* THListIterator<T>::operator->()
{
  return st.Top()->data;
}

#endif
