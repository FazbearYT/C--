#pragma once

#include "stack.h"

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept
    : head_(other.head_), size_(other.size_) {
    other.head_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void Stack<T>::push(T value) {
    Node* node = new Node{std::move(value), head_};
    head_ = node;
    ++size_;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    Node* node = head_;
    T val = std::move(node->value);
    head_ = node->next;
    delete node;
    --size_;
    return val;
}

template <typename T>
T& Stack<T>::top() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return head_->value;
}

template <typename T>
const T& Stack<T>::top() const {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return head_->value;
}

template <typename T>
bool Stack<T>::isEmpty() const noexcept {
    return head_ == nullptr;
}

template <typename T>
std::size_t Stack<T>::size() const noexcept {
    return size_;
}

template <typename T>
void Stack<T>::clear() noexcept {
    while (head_) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
    size_ = 0;
}

template <typename T>
std::optional<T> Stack<T>::peekN(int n) const {
    if (n < 0 || static_cast<std::size_t>(n) >= size_) return std::nullopt;
    Node* cur = head_;
    for (int i = 0; i < n; ++i) cur = cur->next;
    return cur->value;
}

template <typename T>
void Stack<T>::reverse() {
    Node* prev = nullptr;
    Node* cur = head_;
    while (cur) {
        Node* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head_ = prev;
}
