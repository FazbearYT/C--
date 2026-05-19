#include <gtest/gtest.h>
#include "stack.h"
#include "queue.h"
#include "bst.h"

TEST(StackTest, PushPop) {
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, TopThrowsOnEmpty) {
    Stack<int> s;
    EXPECT_THROW(s.top(), std::underflow_error);
}

TEST(StackTest, PopThrowsOnEmpty) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), std::underflow_error);
}

TEST(StackTest, IsEmpty) {
    Stack<int> s;
    EXPECT_TRUE(s.isEmpty());
    s.push(42);
    EXPECT_FALSE(s.isEmpty());
}

TEST(StackTest, PeekN) {
    Stack<int> s;
    s.push(10); s.push(20); s.push(30);
    EXPECT_EQ(s.peekN(0), 30);
    EXPECT_EQ(s.peekN(1), 20);
    EXPECT_EQ(s.peekN(2), 10);
    EXPECT_EQ(s.peekN(5), std::nullopt);
    EXPECT_EQ(s.peekN(-1), std::nullopt);
}

TEST(StackTest, Reverse) {
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);
    s.reverse();
    EXPECT_EQ(s.pop(), 1);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 3);
}

TEST(StackTest, Clear) {
    Stack<int> s;
    s.push(1); s.push(2);
    s.clear();
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Top) {
    Stack<int> s;
    s.push(99);
    EXPECT_EQ(s.top(), 99);
    EXPECT_EQ(s.size(), 1);
}

TEST(QueueTest, EnqueueDequeue) {
    Queue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    EXPECT_EQ(q.dequeue(), 1);
    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_EQ(q.size(), 1);
}

TEST(QueueTest, FrontBackThrowOnEmpty) {
    Queue<int> q;
    EXPECT_THROW(q.front(), std::underflow_error);
    EXPECT_THROW(q.back(), std::underflow_error);
}

TEST(QueueTest, DequeueThrowsOnEmpty) {
    Queue<int> q;
    EXPECT_THROW(q.dequeue(), std::underflow_error);
}

TEST(QueueTest, IsEmpty) {
    Queue<int> q;
    EXPECT_TRUE(q.isEmpty());
    q.enqueue(1);
    EXPECT_FALSE(q.isEmpty());
}

TEST(QueueTest, FrontBack) {
    Queue<int> q;
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 30);
}

TEST(QueueTest, PeekN) {
    Queue<int> q;
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    EXPECT_EQ(q.peekN(0), 10);
    EXPECT_EQ(q.peekN(2), 30);
    EXPECT_EQ(q.peekN(5), std::nullopt);
    EXPECT_EQ(q.peekN(-1), std::nullopt);
}

TEST(QueueTest, Rotate) {
    Queue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.enqueue(4);
    q.rotate(1);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 1);
}

TEST(QueueTest, RotateFullCycle) {
    Queue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    q.rotate(3);
    EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, RotateNegative) {
    Queue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    q.rotate(-1);
    EXPECT_EQ(q.front(), 3);
}

TEST(QueueTest, Clear) {
    Queue<int> q;
    q.enqueue(1); q.enqueue(2);
    q.clear();
    EXPECT_TRUE(q.isEmpty());
}

TEST(BSTTest, InsertAndSearch) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(7);
    EXPECT_TRUE(t.search(5));
    EXPECT_TRUE(t.search(3));
    EXPECT_FALSE(t.search(99));
}

TEST(BSTTest, Contains) {
    BST<int> t;
    t.insert(10);
    EXPECT_TRUE(t.contains(10));
    EXPECT_FALSE(t.contains(0));
}

TEST(BSTTest, RemoveLeaf) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(7);
    t.remove(3);
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.search(5));
}

TEST(BSTTest, RemoveOneChild) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(2);
    t.remove(3);
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.search(2));
}

TEST(BSTTest, RemoveTwoChildren) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(7); t.insert(6); t.insert(8);
    t.remove(7);
    EXPECT_FALSE(t.search(7));
    EXPECT_TRUE(t.search(6));
    EXPECT_TRUE(t.search(8));
}

TEST(BSTTest, RemoveRoot) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(7);
    t.remove(5);
    EXPECT_FALSE(t.search(5));
    EXPECT_TRUE(t.search(3));
    EXPECT_TRUE(t.search(7));
}

TEST(BSTTest, InorderSorted) {
    BST<int> t;
    for (int v : {5, 2, 8, 1, 3}) t.insert(v);
    auto result = t.inorderRecursive();
    EXPECT_EQ(result, (DynArray<int>{1, 2, 3, 5, 8}));
}

TEST(BSTTest, InorderRecursiveVsIterative) {
    BST<int> t;
    for (int v : {10, 5, 15, 3, 7, 12, 20}) t.insert(v);
    EXPECT_EQ(t.inorderRecursive(), t.inorderIterative());
}

TEST(BSTTest, PreorderRecursiveVsIterative) {
    BST<int> t;
    for (int v : {10, 5, 15, 3, 7, 12, 20}) t.insert(v);
    EXPECT_EQ(t.preorderRecursive(), t.preorderIterative());
}

TEST(BSTTest, PostorderRecursiveVsIterative) {
    BST<int> t;
    for (int v : {10, 5, 15, 3, 7, 12, 20}) t.insert(v);
    EXPECT_EQ(t.postorderRecursive(), t.postorderIterative());
}

TEST(BSTTest, MinMax) {
    BST<int> t;
    for (int v : {5, 2, 8, 1, 9}) t.insert(v);
    EXPECT_EQ(t.min(), 1);
    EXPECT_EQ(t.max(), 9);
}

TEST(BSTTest, MinMaxEmpty) {
    BST<int> t;
    EXPECT_EQ(t.min(), std::nullopt);
    EXPECT_EQ(t.max(), std::nullopt);
}

TEST(BSTTest, HeightEmpty) {
    BST<int> t;
    EXPECT_EQ(t.height(), -1);
}

TEST(BSTTest, HeightAndSize) {
    BST<int> t;
    t.insert(5); t.insert(3); t.insert(7); t.insert(1);
    EXPECT_EQ(t.size(), 4);
    EXPECT_EQ(t.height(), 2);
}

TEST(BSTTest, Successor) {
    BST<int> t;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) t.insert(v);
    EXPECT_EQ(t.successor(5), 6);
    EXPECT_EQ(t.successor(4), 5);
    EXPECT_EQ(t.successor(8), std::nullopt);
}

TEST(BSTTest, Predecessor) {
    BST<int> t;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) t.insert(v);
    EXPECT_EQ(t.predecessor(5), 4);
    EXPECT_EQ(t.predecessor(6), 5);
    EXPECT_EQ(t.predecessor(1), std::nullopt);
}

TEST(BSTTest, Clear) {
    BST<int> t;
    t.insert(1); t.insert(2);
    t.clear();
    EXPECT_EQ(t.size(), 0);
    EXPECT_FALSE(t.search(1));
}

TEST(BSTTest, DuplicateInsert) {
    BST<int> t;
    t.insert(5); t.insert(5); t.insert(5);
    EXPECT_EQ(t.size(), 1);
}
