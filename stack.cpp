#pragma once

#include "stack.h"

template <typename T>
void Stack<T>::push(T value) {
    data_.push_back(std::move(value));
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    T val = std::move(data_.back());
    data_.pop_back();
    return val;
}

template <typename T>
T& Stack<T>::top() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return data_.back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return data_.back();
}

template <typename T>
bool Stack<T>::isEmpty() const noexcept {
    return data_.empty();
}

template <typename T>
std::size_t Stack<T>::size() const noexcept {
    return data_.size();
}

template <typename T>
void Stack<T>::clear() noexcept {
    data_.clear();
}

template <typename T>
std::optional<T> Stack<T>::peekN(int n) const {
    if (n < 0 || static_cast<std::size_t>(n) >= data_.size()) return std::nullopt;
    return data_[data_.size() - 1 - n];
}

template <typename T>
void Stack<T>::reverse() {
    std::reverse(data_.begin(), data_.end());
}
