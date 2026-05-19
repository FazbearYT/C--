#pragma once

#include <vector>
#include <optional>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Stack {
public:
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
    std::vector<T> data_;
};

#include "stack.cpp"
