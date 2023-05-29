#include <iostream>
#include "HierarchyList.h"
#include "HListIterator.h"

int main()
{
  THierarchyList<int> l;
  int names[11];
  for (int i = 1; i < 11; i++)
    names[i] = i;
  size_t path1[] = {1};
  l.PushDataInLevel(&(names[1]), nullptr, 0, false);
  l.PushDataInLevel(&(names[2]), nullptr, 0, false);
  l.PushDataInLevel(&(names[3]), nullptr, 0, 0, false);
  l.InsertData(&(names[4]), nullptr, 0, 0, false);
  l.DeleteData(nullptr, 0, 2);
  l.DeleteData(path1, 1, 0);
  l.PushDataInLevel(&(names[2]), nullptr, 0, false);
  l.PushDataInLevel(&(names[3]), nullptr, 0, 0, false);
  l.PushDataInLevel(&(names[10]), nullptr, 0, 0, false);
  l.PushDataInLevel(&(names[9]), nullptr, 0, 0, false);
  for (auto i = l.begin(), end = l.end() ; i != end; ++i)
  {
    std::cout << *i << std::endl;
  }
  THierarchyList<int> l2(l);
  std::cout << "Let's do a copy" << std::endl;
  for (auto it = l2.begin(), end = l2.end() ; it != end; ++it)
  {
    auto& i = *it;
    std::cout << i << std::endl;
  }
  std::cout << "Comparing: " << (l == l2) << std::endl;
  l2.PopData(nullptr, 0);
  for (auto it = l2.begin(), end = l2.end() ; it != end; ++it)
  {
    auto& i = *it;
    std::cout << i << std::endl;
  }
  std::cout << "Comparing: " << (l == l2) << std::endl;
  return 0;
}
