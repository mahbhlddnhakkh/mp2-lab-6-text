#include "Stack.h"

#include <gtest.h>

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s1;
	ASSERT_NO_THROW(TStack<int> s2(s1));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s1;
	s1.Push(2);
	s1.Push(5);
	s1.Push(11);
	TStack<int> s2(s1);
	EXPECT_EQ(true, s1 == s2);
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> s1;
	for (size_t i = 0; i < 3; i++)
		s1.Push(i);
	TStack<int> s2(s1);
	s2.Pop();
	s2.Push(123);
	EXPECT_EQ(true, s1 != s2);
}

TEST(TStack, can_push_and_top_element)
{
	TStack<int> s;
	s.Push(5);
	s.Push(6);
	EXPECT_EQ(6, s.Top());
}

TEST(TStack, can_pop_element)
{
	TStack<int> s;
	s.Push(5);
	s.Push(6);
	s.Pop();
	EXPECT_EQ(5, s.Top());
}

TEST(TStack, can_top_pop_element)
{
	TStack<int> s;
	s.Push(5);
	s.Push(6);
	EXPECT_EQ(6, s.TopPop());
	EXPECT_EQ(5, s.TopPop());
}

TEST(TStack, knows_if_empty)
{
	TStack<int> s;
	EXPECT_EQ(true, s.IsEmpty());
	s.Push(11);
	EXPECT_EQ(false, s.IsEmpty());
	s.Pop();
	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, throws_when_pop_when_empty)
{
	TStack<int> s;
	s.Push(0);
	s.Pop();
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s;
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, can_assign_stack)
{
	TStack<int> s1, s2;
	s1.Push(15);
	s1.Push(16);
	s2 = s1;
	s2.Pop();
	s2.Pop();
	s2.Push(16);
	s2.Push(15);
	EXPECT_NE(16, s2.TopPop());
	EXPECT_NE(15, s2.Top());
}

TEST(TStack, compare_equal_stacks_return_true)
{
	TStack<int> s1, s2;
	s1.Push(5);
	s1.Push(6);
	s1.Push(7);

	s2.Push(5);
	s2.Push(6);
	s2.Push(7);
	EXPECT_EQ(true, s1 == s2);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
	TStack<int> s;
	s.Push(0);
	EXPECT_EQ(true, s == s);
}

TEST(TStack, stacks_with_different_size_are_not_equal)
{
	TStack<int> s1, s2;
	s1.Push(5);
	s1.Push(6);
	s2.Push(5);
	EXPECT_EQ(true, s1 != s2);
}