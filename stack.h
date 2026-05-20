#pragma once

#include <optional>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack();
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) noexcept;
    Stack& operator=(Stack&&) noexcept;

    void push(T value);
    T pop();
    T& top();
    const T& top() const;
    bool isEmpty() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;
    std::optional<T> peekN(int n) const;
    void reverse();

private:
    struct Node {
        T value;
        Node* next;
    };

    Node* head_ = nullptr;
    std::size_t size_ = 0;
};

#include "stack.cpp"
