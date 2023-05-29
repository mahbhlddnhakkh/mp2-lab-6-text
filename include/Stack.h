#ifndef __TStack_H__
#define __TStack_H__

#include <iostream>

template <typename T>
class TStackItem
{
public:
  T data;
  TStackItem<T>* next = nullptr;
  TStackItem<T>* prev = nullptr;
  TStackItem(const T& data)
  {
    this->data = data;
  }
};

template <typename T>
class TStack
{
protected:
  TStackItem<T>* root;
  TStackItem<T>* last;
  size_t count;
public:
	TStack();
	TStack(const TStack<T>& s);
	TStack(TStack<T>&& s) noexcept;
	TStack& operator=(const TStack<T>& s);
	TStack& operator=(TStack<T>&& s) noexcept;
	~TStack();
	
	bool IsEmpty(void) const noexcept;
  size_t GetCount(void) const noexcept;

	void Push(const T& e);
	T Top(void) const;
	void Pop(void);
	T TopPop(void);
  void Clear(void);

	bool operator==(const TStack<T>& s) const noexcept;
	bool operator!=(const TStack<T>& s) const noexcept;
};

template <typename T>
inline TStack<T>::TStack()
{
  root = nullptr;
  last = nullptr;
  count = 0;
}

template <typename T>
inline TStack<T>::TStack(const TStack<T>& s) : TStack()
{
  operator=(s);
}

template <typename T>
inline TStack<T>::TStack(TStack<T>&& s) noexcept
{
  operator=(s);
}

template <typename T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& s)
{
  if (root == s.root)
    return *this;
  Clear();
  if (s.IsEmpty())
  {
    return *this;
  }
  TStackItem<T>* tmp = s.root;
  while (tmp->next != nullptr)
  {
    Push(tmp->data);
    tmp = tmp->next;
  }
  Push(tmp->data);
  return *this;
}

template <typename T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& s) noexcept
{
  std::swap(root, s.root);
  std::swap(last, s.last);
  std::swap(count, s.count);
  return *this;
}

template <typename T>
inline TStack<T>::~TStack()
{
  Clear();
}

template <typename T>
inline bool TStack<T>::IsEmpty(void) const noexcept
{
  return count == 0;
}

template <typename T>
inline size_t TStack<T>::GetCount() const noexcept
{
  return count;
}

template <typename T>
inline void TStack<T>::Push(const T &e)
{
  if (!IsEmpty())
  {
    last->next = new TStackItem<T>(e);
    last->next->prev = last;
    last = last->next;
    count++;
  }
  else
  {
    root = new TStackItem<T>(e);
    last = root;
    count = 1;
  }
}

template <typename T>
inline T TStack<T>::Top(void) const
{
  if (IsEmpty())
    throw std::out_of_range("Stack if empty.");
  return last->data;
}

template <typename T>
inline void TStack<T>::Pop(void)
{
  if (IsEmpty())
    throw std::out_of_range("Stack if empty.");
  if (count != 1)
  {
    TStackItem<T>* tmp = last;
    last = last->prev;
    last->next = nullptr;
    delete tmp;
    count--;
  }
  else
  {
    Clear();
  }
}

template <typename T>
inline T TStack<T>::TopPop(void)
{
  if (IsEmpty())
    throw std::out_of_range("Stack if empty.");
  T data = last->data;
  Pop();
  return data;
}

template <typename T>
inline void TStack<T>::Clear(void)
{
  if (IsEmpty())
    return;
  TStackItem<T>* tmp = root;
  while (tmp->next != nullptr)
  {
    tmp = tmp->next;
    delete tmp->prev;
  }
  delete last;
  root = nullptr;
  last = nullptr;
  count = 0;
}

template <typename T>
inline bool TStack<T>::operator==(const TStack<T> &s) const noexcept
{
  if (root == s.root)
    return true;
  if (count != s.count)
    return false;
  TStackItem<T>* tmp = root, *tmp_s = s.root;
  while (tmp->next != nullptr)
  {
    if (tmp->data != tmp_s->data)
      return false;
    tmp = tmp->next;
    tmp_s = tmp_s->next;
  }
  return tmp->data == tmp_s->data;
}

template <typename T>
inline bool TStack<T>::operator!=(const TStack<T> &s) const noexcept
{
  return !operator==(s);
}

#endif
