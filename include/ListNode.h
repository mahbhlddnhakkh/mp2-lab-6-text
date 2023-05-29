#ifndef __ListNode_H__
#define __ListNode_H__

template<class T>
class TListNode
{
public:
  bool do_deletion_data = false;
  bool marked = false;
  //TListNode<T>* prev = nullptr;
  TListNode<T>* next = nullptr;
  TListNode<T>* child = nullptr;
  T* data = nullptr;
  TListNode() {}
  TListNode(const TListNode<T>& node);
  ~TListNode();
  bool IsLast(void) noexcept;
  bool HasLevelDown(void) noexcept;
};

template<class T>
inline TListNode<T>::TListNode(const TListNode<T>& node)
{
  data = node.data;
  do_deletion_data = node.do_deletion_data;
  marked = node.marked;
}

template<class T>
inline TListNode<T>::~TListNode()
{
  //if (do_deletion_data && data)
    //delete data;
}

template<class T>
inline bool TListNode<T>::IsLast(void) noexcept
{
  return next == nullptr;
}

template<class T>
inline bool TListNode<T>::HasLevelDown(void) noexcept
{
  return child != nullptr;
}

#endif
