#pragma once

#include "bst.h"

template <typename T>
void BST<T>::insertImpl(std::unique_ptr<Node>& node, T value) {
    if (!node) {
        node = std::make_unique<Node>(std::move(value));
        return;
    }
    if (value < node->value) insertImpl(node->left, std::move(value));
    else if (value > node->value) insertImpl(node->right, std::move(value));
}

template <typename T>
void BST<T>::insert(T value) {
    insertImpl(root_, std::move(value));
}

template <typename T>
const typename BST<T>::Node* BST<T>::findMin(const Node* node) const noexcept {
    while (node && node->left) node = node->left.get();
    return node;
}

template <typename T>
const typename BST<T>::Node* BST<T>::findMax(const Node* node) const noexcept {
    while (node && node->right) node = node->right.get();
    return node;
}

template <typename T>
std::unique_ptr<typename BST<T>::Node> BST<T>::removeImpl(std::unique_ptr<Node> node, const T& value) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeImpl(std::move(node->left), value);
    } else if (value > node->value) {
        node->right = removeImpl(std::move(node->right), value);
    } else {
        if (!node->left) return std::move(node->right);
        if (!node->right) return std::move(node->left);
        const Node* minNode = findMin(node->right.get());
        node->value = minNode->value;
        node->right = removeImpl(std::move(node->right), minNode->value);
    }
    return node;
}

template <typename T>
void BST<T>::remove(T value) {
    root_ = removeImpl(std::move(root_), value);
}

template <typename T>
bool BST<T>::search(const T& value) const noexcept {
    const Node* cur = root_.get();
    while (cur) {
        if (value == cur->value) return true;
        cur = (value < cur->value) ? cur->left.get() : cur->right.get();
    }
    return false;
}

template <typename T>
bool BST<T>::contains(const T& value) const noexcept {
    return search(value);
}

template <typename T>
void BST<T>::inorderRec(const Node* node, std::vector<T>& result) const {
    if (!node) return;
    inorderRec(node->left.get(), result);
    result.push_back(node->value);
    inorderRec(node->right.get(), result);
}

template <typename T>
void BST<T>::preorderRec(const Node* node, std::vector<T>& result) const {
    if (!node) return;
    result.push_back(node->value);
    preorderRec(node->left.get(), result);
    preorderRec(node->right.get(), result);
}

template <typename T>
void BST<T>::postorderRec(const Node* node, std::vector<T>& result) const {
    if (!node) return;
    postorderRec(node->left.get(), result);
    postorderRec(node->right.get(), result);
    result.push_back(node->value);
}

template <typename T>
std::vector<T> BST<T>::inorderRecursive() const {
    std::vector<T> result;
    inorderRec(root_.get(), result);
    return result;
}

template <typename T>
std::vector<T> BST<T>::preorderRecursive() const {
    std::vector<T> result;
    preorderRec(root_.get(), result);
    return result;
}

template <typename T>
std::vector<T> BST<T>::postorderRecursive() const {
    std::vector<T> result;
    postorderRec(root_.get(), result);
    return result;
}

template <typename T>
std::vector<T> BST<T>::inorderIterative() const {
    std::vector<T> result;
    std::stack<const Node*> stk;
    const Node* cur = root_.get();
    while (cur || !stk.empty()) {
        while (cur) { stk.push(cur); cur = cur->left.get(); }
        cur = stk.top(); stk.pop();
        result.push_back(cur->value);
        cur = cur->right.get();
    }
    return result;
}

template <typename T>
std::vector<T> BST<T>::preorderIterative() const {
    std::vector<T> result;
    if (!root_) return result;
    std::stack<const Node*> stk;
    stk.push(root_.get());
    while (!stk.empty()) {
        const Node* cur = stk.top(); stk.pop();
        result.push_back(cur->value);
        if (cur->right) stk.push(cur->right.get());
        if (cur->left) stk.push(cur->left.get());
    }
    return result;
}

template <typename T>
std::vector<T> BST<T>::postorderIterative() const {
    std::vector<T> result;
    if (!root_) return result;
    std::stack<const Node*> stk;
    stk.push(root_.get());
    while (!stk.empty()) {
        const Node* cur = stk.top(); stk.pop();
        result.push_back(cur->value);
        if (cur->left) stk.push(cur->left.get());
        if (cur->right) stk.push(cur->right.get());
    }
    std::reverse(result.begin(), result.end());
    return result;
}

template <typename T>
std::optional<T> BST<T>::min() const noexcept {
    const Node* node = findMin(root_.get());
    if (!node) return std::nullopt;
    return node->value;
}

template <typename T>
std::optional<T> BST<T>::max() const noexcept {
    const Node* node = findMax(root_.get());
    if (!node) return std::nullopt;
    return node->value;
}

template <typename T>
int BST<T>::heightImpl(const Node* node) const noexcept {
    if (!node) return -1;
    return 1 + std::max(heightImpl(node->left.get()), heightImpl(node->right.get()));
}

template <typename T>
int BST<T>::height() const noexcept {
    return heightImpl(root_.get());
}

template <typename T>
std::size_t BST<T>::sizeImpl(const Node* node) const noexcept {
    if (!node) return 0;
    return 1 + sizeImpl(node->left.get()) + sizeImpl(node->right.get());
}

template <typename T>
std::size_t BST<T>::size() const noexcept {
    return sizeImpl(root_.get());
}

template <typename T>
void BST<T>::clear() noexcept {
    root_.reset();
}

template <typename T>
std::optional<T> BST<T>::successor(const T& value) const {
    const Node* cur = root_.get();
    const Node* succ = nullptr;
    while (cur) {
        if (value < cur->value) {
            succ = cur;
            cur = cur->left.get();
        } else if (value > cur->value) {
            cur = cur->right.get();
        } else {
            if (cur->right) return findMin(cur->right.get())->value;
            break;
        }
    }
    return succ ? std::optional<T>{succ->value} : std::nullopt;
}

template <typename T>
std::optional<T> BST<T>::predecessor(const T& value) const {
    const Node* cur = root_.get();
    const Node* pred = nullptr;
    while (cur) {
        if (value > cur->value) {
            pred = cur;
            cur = cur->right.get();
        } else if (value < cur->value) {
            cur = cur->left.get();
        } else {
            if (cur->left) return findMax(cur->left.get())->value;
            break;
        }
    }
    return pred ? std::optional<T>{pred->value} : std::nullopt;
}
