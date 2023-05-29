#ifndef __GarbageNodesCollector_H__
#define __GarbageNodesCollector_H__

#include <iostream>
#include "ListNode.h"
#include "Stack.h"

template <class T>
class TGarbageNodesCollector
{
protected:
  TListNode<T>* root;
  TListNode<T>* last;
  void DeleteNode(TListNode<T>* node);

  TGarbageNodesCollector(TGarbageNodesCollector<T>& g);
  TGarbageNodesCollector<T>& operator=(TGarbageNodesCollector<T>& g);
public:
  TGarbageNodesCollector();
  TGarbageNodesCollector(TGarbageNodesCollector<T>&& g) noexcept;
  TGarbageNodesCollector& operator=(TGarbageNodesCollector<T>&& g) noexcept;
  ~TGarbageNodesCollector();

  void Add(TListNode<T>* node);
  void DeleteGarbage(void);
  bool IsEmpty(void);
};

template<class T>
inline void TGarbageNodesCollector<T>::DeleteNode(TListNode<T>* node)
{
  if (node == nullptr)
    return;
  if (node->do_deletion_data && node->data)
    delete node->data;
  delete node;
}

template<class T>
inline TGarbageNodesCollector<T>::TGarbageNodesCollector()
{
  root = new TListNode<T>();
  last = root;
}

template<class T>
inline TGarbageNodesCollector<T>::TGarbageNodesCollector(TGarbageNodesCollector<T>&& g) noexcept
{
  operator=(g);
}

template <class T>
inline TGarbageNodesCollector<T>& TGarbageNodesCollector<T>::operator=(TGarbageNodesCollector<T> &&g) noexcept
{
  std::swap(root, g.root);
  std::swap(last, g.last);
  return *this;
}

template<class T>
inline TGarbageNodesCollector<T>::~TGarbageNodesCollector()
{
  DeleteGarbage();
  delete root;
}

template<class T>
inline void TGarbageNodesCollector<T>::Add(TListNode<T> *node)
{
  if (node != nullptr)
  {
    last->next = node;
    node->next = nullptr;
    last = node;
  }
}

template<class T>
inline void TGarbageNodesCollector<T>::DeleteGarbage(void)
{
  if (last == root)
    return;
  TListNode<T>* tmp = root->next;
  TStack<TListNode<T>*> deletion_list;
  TStack<TListNode<T>*> s;
  s.Push(tmp);
  while (!s.IsEmpty())
  {
    tmp = s.TopPop();
    if (!tmp->marked)
    {
      tmp->marked = true;
      deletion_list.Push(tmp);
    }
    if (tmp->next)
      s.Push(tmp->next);
    if (tmp->child)
      s.Push(tmp->child);
  }
  while (!deletion_list.IsEmpty())
  {
    DeleteNode(deletion_list.TopPop());
  }
  last = root;
}

template<class T>
inline bool TGarbageNodesCollector<T>::IsEmpty(void)
{
  return last == root;
}

#endif
