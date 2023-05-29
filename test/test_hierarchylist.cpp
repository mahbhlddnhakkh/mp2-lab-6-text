#include "HierarchyList.h"
#include "MyString.h"

#include <gtest.h>

TEST(THierarchyList, can_create_list)
{
  ASSERT_NO_THROW(THierarchyList<int>());
}

TEST(THierarchyList, can_assing_to_itself)
{
  THierarchyList<int> l;
  ASSERT_NO_THROW(l = l);
}

TEST(THierarchyList, copied_list_is_equal_to_source_one)
{
  THierarchyList<int> l1;
  int datas[] = {0, 1, 2, 3};
  for (size_t i = 0; i < 3; i++)
  {
    l1.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l1.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  THierarchyList<int> l2(l1);
  EXPECT_EQ(true, l1 == l2);
}

TEST(THierarchyList, copied_list_has_its_own_memory)
{
  THierarchyList<int> l1;
  int datas[] = {0, 1, 2, 3, 4};
  for (size_t i = 0; i < 3; i++)
  {
    l1.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l1.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  THierarchyList<int> l2(l1);
  l2.PushDataInLevel(&(datas[4]), nullptr, 0, 1, false);
  EXPECT_EQ(true, l1 != l2);
}

TEST(THierarchyList, push_test_1)
{
  THierarchyList<int> l;
  int datas[] = {0, 1, 2, 3};
  size_t path[] = {0};
  for (size_t i = 0; i < 3; i++)
  {
    l.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  EXPECT_EQ(0, *(l.GetData(nullptr, 0, 0)));
  EXPECT_EQ(1, *(l.GetData(nullptr, 0, 1)));
  EXPECT_EQ(3, *(l.GetData(path, 1, 0)));
}

TEST(THierarchyList, insert_test_1)
{
  THierarchyList<int> l;
  int datas[] = {0, 1, 2, 3, 4};
  size_t path[] = {0};
  for (size_t i = 0; i < 3; i++)
  {
    l.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  EXPECT_EQ(3, *(l.GetData(path, 1, 0)));
  l.InsertData(&(datas[4]), path, 1, 0, false);
  EXPECT_EQ(4, *(l.GetData(path, 1, 0)));
  EXPECT_EQ(3, *(l.GetData(path, 1, 1)));
}

TEST(THierarchyList, delete_test_1)
{
  THierarchyList<int> l;
  int datas[] = {0, 1, 2, 3, 4};
  size_t path[] = {0};
  for (size_t i = 0; i < 3; i++)
  {
    l.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  EXPECT_EQ(3, *(l.GetData(path, 1, 0)));
  l.DeleteData(path, 1, 0);
  ASSERT_ANY_THROW(l.GetData(path, 1, 0));
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  l.PushDataInLevel(&(datas[4]), nullptr, 0, 0, false);
  l.DeleteData(path, 1, 0);
  EXPECT_EQ(4, *(l.GetData(path, 1, 0)));
}

TEST(THierarchyList, delete_test_2)
{
  THierarchyList<int> l;
  int datas[] = {0, 1, 2, 3, 4};
  size_t path[] = {0};
  for (size_t i = 0; i < 3; i++)
  {
    l.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  l.PushDataInLevel(&(datas[4]), nullptr, 0, 0, false);
  l.DeleteLevel(nullptr, 0, 0);
  EXPECT_EQ(0, *(l.GetData(nullptr, 0, 0)));
  ASSERT_ANY_THROW(l.GetData(path, 1, 0));
}

TEST(THierarchyList, delete_test_3)
{
  THierarchyList<int> l;
  int datas[] = {0, 1, 2, 3, 4};
  size_t path[] = {0};
  for (size_t i = 0; i < 3; i++)
  {
    l.PushDataInLevel(&(datas[i]), nullptr, 0, false);
  }
  l.PushDataInLevel(&(datas[3]), nullptr, 0, 0, false);
  l.PushDataInLevel(&(datas[4]), nullptr, 0, 0, false);
  EXPECT_EQ(4, *(l.GetData(path, 1, 1)));
  l.PopData(nullptr, 0, 0);
  EXPECT_EQ(3, *(l.GetData(path, 1, 0)));
  ASSERT_ANY_THROW(l.GetData(path, 1, 1));
  l.PopData(nullptr, 0, 0);
  ASSERT_ANY_THROW(l.GetData(path, 1, 0));
}

TEST(THierarchyList, test_iterator_1)
{
  THierarchyList<TString> text;
  TString datas1[] = {"Раздел 2", "\t2.1. Полиномы", "\t\t2.1.1. Определение", "\t\t2.1.2. Структура", "\t2.2. Тексты", "\t\t2.2.1. Определение", "\t\t2.2.2. Структура"};
  TString datas2[] = {"Раздел 3", "\t3.1. Таблицы", "\t\t3.1.1. Определение", "\t\t3.1.2. Структура", "\t3.2. Плексы", "\t\t3.2.1. Определение", "\t\t3.2.2. Структура"};
  size_t path1[] = {0}, path2[] = {1};
  
  text.PushDataInLevel(&(datas1[0]), nullptr, 0, false);

  text.PushDataInLevel(&(datas1[1]), nullptr, 0, 0, false);
  text.PushDataInLevel(&(datas1[4]), nullptr, 0, 0, false);

  text.PushDataInLevel(&(datas1[2]), path1, 1, 0, false);
  text.PushDataInLevel(&(datas1[3]), path1, 1, 0, false);

  text.PushDataInLevel(&(datas1[5]), path1, 1, 1, false);
  text.PushDataInLevel(&(datas1[6]), path1, 1, 1, false);

  text.PushDataInLevel(&(datas2[0]), nullptr, 0, false);

  text.PushDataInLevel(&(datas2[1]), nullptr, 0, 1, false);
  text.PushDataInLevel(&(datas2[4]), nullptr, 0, 1, false);

  text.PushDataInLevel(&(datas2[2]), path2, 1, 0, false);
  text.PushDataInLevel(&(datas2[3]), path2, 1, 0, false);

  text.PushDataInLevel(&(datas2[5]), path2, 1, 1, false);
  text.PushDataInLevel(&(datas2[6]), path2, 1, 1, false);

  TString* tmp = datas1;
  size_t i = 0;
  for (auto& e : text)
  {
    if (i >= 7)
    {
      tmp = datas2;
      i = 0;
    }
    EXPECT_EQ(tmp[i], e);
    i++;
  }
}
