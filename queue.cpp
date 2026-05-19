#pragma once
#include "queue.h"

template <typename T>
void Queue<T>::enqueue(T value) {
    Node* newNode = new Node(std::move(value));
    if (isEmpty()) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->next = newNode;
        tail_ = newNode;
    }
    ++count_;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    
    Node* temp = head_;
    T val = std::move(temp->value);
    
    head_ = head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr; 
    }
    
    delete temp;
    --count_;
    return val;
}

template <typename T>
T& Queue<T>::front() {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    return head_->value;
}

template <typename T>
const T& Queue<T>::front() const {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    return head_->value;
}

template <typename T>
T& Queue<T>::back() {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    return tail_->value;
}

template <typename T>
const T& Queue<T>::back() const {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    return tail_->value;
}

template <typename T>
bool Queue<T>::isEmpty() const noexcept {
    return count_ == 0;
}

template <typename T>
std::size_t Queue<T>::size() const noexcept {
    return count_;
}

template <typename T>
void Queue<T>::clear() noexcept {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
void Queue<T>::rotate(int k) {
    if (isEmpty()) return;
    int n = static_cast<int>(size());
    k = ((k % n) + n) % n; 
    
    for (int i = 0; i < k; ++i) {
        enqueue(dequeue());
    }
}

template <typename T>
std::optional<T> Queue<T>::peekN(int n) const {
    if (n < 0 || static_cast<std::size_t>(n) >= count_) return std::nullopt;
    
    Node* current = head_;
    for (int i = 0; i < n; ++i) {
        current = current->next;
    }
    return current->value;
}