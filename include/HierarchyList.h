#ifndef __HierarchyList_H__
#define __HierarchyList_H__

#define HIERARCHYLIST_ON_COPY__COPY_DATA

#include <iostream>
#include "ListNode.h"
#include "GarbageNodesCollector.h"
#include "Stack.h"
#include "HListIterator.h"

template<class T>
class THierarchyList
{
protected:
  TListNode<T>* root = nullptr;
  TGarbageNodesCollector<T>* garbage_collector;

  TListNode<T>* GetListNodeOnLevel(TListNode<T>* node, const size_t i);
  TListNode<T>* GetListNode(const size_t* lvl_path, const size_t sz, size_t i);
  TListNode<T>* GetListNode(const size_t* path, const size_t sz);
  TListNode<T>* GetLastListNodeOnLevel(TListNode<T>* node);
  friend class THListIterator<T>;
public:
  THierarchyList();
  THierarchyList(THierarchyList<T>& l);
  THierarchyList& operator=(THierarchyList<T>& l);
  THierarchyList(THierarchyList<T>&& l) noexcept;
  THierarchyList& operator=(THierarchyList<T>&& l) noexcept;
  ~THierarchyList();
  
  bool IsEmpty(void) noexcept;
  void PushDataInLevel(T* data, const size_t* lvl_path, const size_t sz, const size_t i, const bool do_deletion_data);
  void PushDataInLevel(T* data, const size_t* path, const size_t sz, const bool do_deletion_data);
  void InsertData(T* data, const size_t* lvl_path, const size_t sz, const size_t i, const bool do_deletion_data);
  void InsertData(T* data, const size_t* path, const size_t sz, const bool do_deletion_data);
  T* GetData(const size_t* lvl_path, const size_t sz, const size_t i);
  T* GetData(const size_t* path, const size_t sz);
  void DeleteData(const size_t* lvl_path, const size_t sz, const size_t i);
  void DeleteData(const size_t* path, const size_t sz);
  void DeleteLevel(const size_t* lvl_path, const size_t sz, const size_t i);
  void DeleteLevel(const size_t* path, const size_t sz);
  void PopData(const size_t* lvl_path, const size_t sz, const size_t i);
  void PopData(const size_t* path, const size_t sz);
  void Clear(void);
  void CollectGarbage(void);
  bool GarbageCollectorIsEmpty(void);
  bool operator==(THierarchyList<T>& l);
  bool operator!=(THierarchyList<T>& l);

  THListIterator<T> begin();
  THListIterator<T> end();
};

// PROTECTED

template<class T>
inline TListNode<T>* THierarchyList<T>::GetListNodeOnLevel(TListNode<T>* node, const size_t i)
{
  TListNode<T>* tmp = node;
  size_t j = 0;
  if (tmp == nullptr)
  {
    throw "node is nullptr";
  }
  while (!tmp->IsLast() && j < i)
  {
    tmp = tmp->next;
    j++;
  }
  if (j == i)
    return tmp;
  else
    throw "index is out of range";
}

template<class T>
inline TListNode<T>* THierarchyList<T>::GetListNode(const size_t* lvl_path, const size_t sz, size_t i)
{
  TListNode<T>* tmp = root;
  for (size_t j = 0; j < sz; j++)
  {
    tmp = GetListNodeOnLevel(tmp, lvl_path[j])->child;
  }
  return GetListNodeOnLevel(tmp, i);
}

template<class T>
inline TListNode<T>* THierarchyList<T>::GetListNode(const size_t* path, const size_t sz)
{
  return GetListNode(path, sz-1, path[sz-1]);
}

template <class T>
inline TListNode<T>* THierarchyList<T>::GetLastListNodeOnLevel(TListNode<T>* node)
{
  TListNode<T>* tmp = node;
  while (!tmp->IsLast())
    tmp = tmp->next;
  return tmp;
}

// PUBLIC

template<class T>
inline THierarchyList<T>::THierarchyList()
{
  garbage_collector = new TGarbageNodesCollector<T>();
}

template <class T>
inline THierarchyList<T>& THierarchyList<T>::operator=(THierarchyList<T> &l)
{
  if (root == l.root)
    return *this;
  // Don't copy garbage collector
  CollectGarbage();
  Clear();
  if (l.IsEmpty())
    return *this;
  TStack<TListNode<T>*> st_this, st_l;
  TListNode<T>* tmp_this, *tmp_l;
  root = new TListNode<T>(*l.root);
  st_this.Push(root);
  st_l.Push(l.root);
  while(!st_l.IsEmpty())
  {
    tmp_this = st_this.TopPop();
    tmp_l = st_l.TopPop();
    if (tmp_l->next != nullptr)
    {
      st_l.Push(tmp_l->next);
      tmp_this->next = new TListNode<T>(*tmp_l->next);
#ifdef HIERARCHYLIST_ON_COPY__COPY_DATA
      tmp_this->next->data = new T(*(tmp_l->next->data));
      tmp_this->next->do_deletion_data = true;
#endif
      st_this.Push(tmp_this->next);
    }
    if (tmp_l->child != nullptr)
    {
      st_l.Push(tmp_l->child);
      tmp_this->child = new TListNode<T>(*tmp_l->child);
#ifdef HIERARCHYLIST_ON_COPY__COPY_DATA
    tmp_this->child->data = new T(*(tmp_l->child->data));
    tmp_this->child->do_deletion_data = true;
#endif
      st_this.Push(tmp_this->child);
    }
  }
  return *this;
}

template<class T>
inline THierarchyList<T>::THierarchyList(THierarchyList<T>& l) : THierarchyList<T>()
{
  operator=(l);
}

template<class T>
inline THierarchyList<T>::THierarchyList(THierarchyList<T>&& l) noexcept
{
  operator=(l);
}

template<class T>
inline THierarchyList<T>& THierarchyList<T>::operator=(THierarchyList<T>&& l) noexcept
{
  std::swap(root, l.root);
  std::swap(garbage_collector, l.garbage_collector);
}

template<class T>
inline THierarchyList<T>::~THierarchyList()
{
  if (!IsEmpty())
  {
    Clear();
  }
  delete garbage_collector;
}

template<class T>
inline bool THierarchyList<T>::IsEmpty(void) noexcept
{
  return root == nullptr;
}

template<class T>
inline void THierarchyList<T>::PushDataInLevel(T* data, const size_t* lvl_path, const size_t sz, const size_t i, const bool do_deletion_data)
{
  if (!IsEmpty())
  {
    TListNode<T>* tmp = GetListNode(lvl_path, sz, i);
    if (tmp->HasLevelDown())
    {
      tmp = GetLastListNodeOnLevel(tmp->child);
      tmp->next = new TListNode<T>();
      tmp->next->data = data;
      tmp->next->do_deletion_data = do_deletion_data;
    }
    else
    {
      tmp->child = new TListNode<T>();
      tmp->child->data = data;
      tmp->child->do_deletion_data = do_deletion_data;
    }
  }
  else
  {
    throw "root is nullptr | out of range";
  }
}

template<class T>
inline void THierarchyList<T>::PushDataInLevel(T* data, const size_t* path, const size_t sz, const bool do_deletion_data)
{
  if (sz == 0 || path == nullptr)
  {
    if (!IsEmpty())
    {
      TListNode<T>* tmp = GetLastListNodeOnLevel(root);
      tmp->next = new TListNode<T>();
      tmp->next->data = data;
      tmp->next->do_deletion_data = do_deletion_data;
    }
    else
    {
      root = new TListNode<T>();
      root->data = data;
      root->do_deletion_data = do_deletion_data;
    }
  }
  else
    PushDataInLevel(data, path, sz-1, path[sz-1], do_deletion_data);
}

template<class T>
inline void THierarchyList<T>::InsertData(T* data, const size_t* lvl_path, const size_t sz, const size_t i, const bool do_deletion_data)
{
  TListNode<T>* tmp, *tmp_next;
  if (!IsEmpty())
  {
    if (i != 0)
    {
      tmp = GetListNode(lvl_path, sz, i - 1);
      tmp_next = tmp->next;
      tmp->next = new TListNode<T>();
      tmp->next->data = data;
      tmp->next->do_deletion_data = do_deletion_data;
      tmp->next->next = tmp_next;
    }
    else
    {
      if (sz == 0 || lvl_path == nullptr)
      {
        tmp = root;
        root = new TListNode<T>();
        root->data = data;
        root->do_deletion_data = do_deletion_data;
        root->next = tmp;
      }
      else
      {
        tmp = GetListNode(lvl_path, sz);
        tmp_next = tmp->child;
        tmp->child = new TListNode<T>();
        tmp->child->data = data;
        tmp->child->do_deletion_data = do_deletion_data;
        tmp->child->next = tmp_next;
      }
    }
  }
  else
  {
    PushDataInLevel(data, lvl_path, sz, i, do_deletion_data);
  }
}

template<class T>
inline void THierarchyList<T>::InsertData(T* data, const size_t* path, const size_t sz, const bool do_deletion_data)
{
  if (sz == 0 || path == nullptr)
  {
    throw "path cannot be empty";
  }
  InsertData(data, path, sz-1, path[sz-1], do_deletion_data);
}

template<class T>
inline T* THierarchyList<T>::GetData(const size_t* lvl_path, const size_t sz, const size_t i)
{
  if (IsEmpty())
    throw "list is empty";
  return GetListNode(lvl_path, sz, i)->data;
}

template<class T>
inline T* THierarchyList<T>::GetData(const size_t* path, const size_t sz)
{
  if (sz == 0 || path == nullptr)
    throw "path cannot be empty";
  return GetData(path, sz-1, path[sz-1]);
}

template<class T>
inline void THierarchyList<T>::DeleteData(const size_t* lvl_path, const size_t sz, const size_t i)
{
  if (IsEmpty())
    throw "list is empty";
  TListNode<T>* tmp, *tmp_next;
  if (i != 0)
  {
    tmp = GetListNode(lvl_path, sz, i - 1);
    if (tmp->IsLast())
      throw "out of range";
    garbage_collector->Add(tmp->next);
    tmp->next = tmp->next->next;
  }
  else
  {
    if (sz == 0 || lvl_path == nullptr)
    {
      garbage_collector->Add(root);
      root = root->next;
      return;
    }
    tmp = GetListNode(lvl_path, sz);
    if (tmp->HasLevelDown())
    {
      TListNode<T>* tmp2 = tmp->child;
      tmp->child = tmp->child->next;
      garbage_collector->Add(tmp2);
    }
    else
    {
      throw "out of range";
    }
  }
}

template<class T>
inline void THierarchyList<T>::DeleteData(const size_t* path, const size_t sz)
{
  if (sz == 0 || path == nullptr)
    Clear();
  else
    DeleteData(path, sz-1, path[sz-1]);
}

template<class T>
inline void THierarchyList<T>::DeleteLevel(const size_t* lvl_path, const size_t sz, const size_t i)
{
  if (IsEmpty())
    throw "list is empty";
  TListNode<T>* tmp = GetListNode(lvl_path, sz, i), *tmp_up;
  if (!tmp->HasLevelDown())
    throw "no level found";
  tmp_up = tmp;
  tmp = tmp->child;
  tmp_up->child = nullptr;
  TStack<TListNode<T>*> s;
  while (tmp != nullptr)
  {
    s.Push(tmp);
    tmp = tmp->next;
  }
  while (!s.IsEmpty())
  {
    garbage_collector->Add(s.TopPop());
  }
}

template<class T>
inline void THierarchyList<T>::DeleteLevel(const size_t* path, const size_t sz)
{
  if (sz == 0 || path == nullptr)
  {
    Clear();
  }
  else
  {
    DeleteLevel(path, sz-1, path[sz-1]);
  }
}

template<class T>
inline void THierarchyList<T>::PopData(const size_t* lvl_path, const size_t sz, const size_t i)
{
  if (IsEmpty())
    throw "list is empty";
  TListNode<T>* tmp = GetListNode(lvl_path, sz, i), *tmp_prev = nullptr, *tmp_up;
  if (!tmp->HasLevelDown())
    throw "no level found";
  tmp_up = tmp;
  tmp = tmp->child;
  while (tmp->next != nullptr)
  {
    tmp_prev = tmp;
    tmp = tmp->next;
  }
  if (tmp_prev != nullptr)
  {
    tmp_prev->next = nullptr;
  }
  else
  {
    tmp_up->child = nullptr;
  }
  garbage_collector->Add(tmp);
}

template<class T>
inline void THierarchyList<T>::PopData(const size_t* path, const size_t sz)
{
  if (sz == 0 || path == nullptr)
  {
    if (IsEmpty())
      throw "list is empty";
    TListNode<T>* tmp = root, *tmp_prev = nullptr;
    while (tmp->next != nullptr)
    {
      tmp_prev = tmp;
      tmp = tmp->next;
    }
    if (tmp_prev != nullptr)
    {
      tmp_prev->next = nullptr;
    }
    else
    {
      root = nullptr;
    }
    garbage_collector->Add(tmp);
  }
  else
  {
    PopData(path, sz-1, path[sz-1]);
  }
}

template<class T>
inline void THierarchyList<T>::Clear(void)
{
  if (!IsEmpty())
    garbage_collector->Add(root);
  root = nullptr;
}

template<class T>
inline void THierarchyList<T>::CollectGarbage(void)
{
  garbage_collector->DeleteGarbage();
}

template<class T>
inline bool THierarchyList<T>::GarbageCollectorIsEmpty(void)
{
  return garbage_collector->IsEmpty();
}

template<class T>
inline bool THierarchyList<T>::operator==(THierarchyList<T> &l)
{
  if (IsEmpty() || l.IsEmpty())
  {
    return root == l.root;
  }
  if (root == l.root)
    return true;
  TStack<TListNode<T>*> st_this, st_l;
  TListNode<T>* tmp_this, *tmp_l;
  st_this.Push(root);
  st_l.Push(l.root);
  while(!st_l.IsEmpty())
  {
    tmp_this = st_this.TopPop();
    tmp_l = st_l.TopPop();
    if (*(tmp_this->data) != *(tmp_l->data))
      return false;
    if (tmp_l->next != nullptr && tmp_this != nullptr)
    {
      st_l.Push(tmp_l->next);
      st_this.Push(tmp_this->next);
    }
    else
      if (tmp_l->next != tmp_this->next)
        return false;
    if (tmp_l->child != nullptr && tmp_this->child != nullptr)
    {
      st_l.Push(tmp_l->child);
      st_this.Push(tmp_this->child);
    }
    else
      if (tmp_l->child != tmp_this->child)
        return false;
  }
  return true;
}

template<class T>
inline bool THierarchyList<T>::operator!=(THierarchyList<T> &l)
{
  return !operator==(l);
}

template<class T>
inline THListIterator<T> THierarchyList<T>::begin()
{
  TStack<TListNode<T>*> st;
  if (root != nullptr)
    st.Push(root);
  return THListIterator<T>(st);
}

template<class T>
inline THListIterator<T> THierarchyList<T>::end()
{
  return THListIterator<T>(TStack<TListNode<T>*>());
}

#endif
