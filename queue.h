#pragma once
#include <optional>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
        explicit Node(T val) : value(std::move(val)), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t count_;

public:
    Queue() : head_(nullptr), tail_(nullptr), count_(0) {}
    
    ~Queue() {
        clear();
    }

    void enqueue(T value);
    T dequeue();
    
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    bool isEmpty() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;
    
    void rotate(int k);
    std::optional<T> peekN(int n) const;
};

#include "queue.cpp"