#pragma once

#include "bst.h"

template <typename T>
void BST<T>::destroySubtree(Node* node) noexcept {
    if (!node) return;
    destroySubtree(node->left);
    destroySubtree(node->right);
    delete node;
}

template <typename T>
void BST<T>::insertImpl(Node*& node, T value) {
    if (!node) {
        node = new Node(std::move(value));
        return;
    }
    if (value < node->value)
        insertImpl(node->left, std::move(value));
    else if (value > node->value)
        insertImpl(node->right, std::move(value));
}

template <typename T>
void BST<T>::insert(T value) {
    insertImpl(root_, std::move(value));
}

template <typename T>
const typename BST<T>::Node* BST<T>::findMin(const Node* node) const noexcept {
    while (node && node->left) node = node->left;
    return node;
}

template <typename T>
const typename BST<T>::Node* BST<T>::findMax(const Node* node) const noexcept {
    while (node && node->right) node = node->right;
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::removeImpl(Node* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = removeImpl(node->left, value);
    } else if (value > node->value) {
        node->right = removeImpl(node->right, value);
    } else {
        if (!node->left) {
            Node* r = node->right;
            delete node;
            return r;
        }
        if (!node->right) {
            Node* l = node->left;
            delete node;
            return l;
        }
        const Node* minNode = findMin(node->right);
        node->value = minNode->value;
        node->right = removeImpl(node->right, minNode->value);
    }
    return node;
}

template <typename T>
void BST<T>::remove(T value) {
    root_ = removeImpl(root_, value);
}

template <typename T>
bool BST<T>::search(const T& value) const noexcept {
    const Node* cur = root_;
    while (cur) {
        if (value == cur->value) return true;
        cur = (value < cur->value) ? cur->left : cur->right;
    }
    return false;
}

template <typename T>
bool BST<T>::contains(const T& value) const noexcept {
    return search(value);
}

template <typename T>
void BST<T>::inorderRec(const Node* node, DynArray<T>& out) const {
    if (!node) return;
    inorderRec(node->left, out);
    out.push_back(node->value);
    inorderRec(node->right, out);
}

template <typename T>
void BST<T>::preorderRec(const Node* node, DynArray<T>& out) const {
    if (!node) return;
    out.push_back(node->value);
    preorderRec(node->left, out);
    preorderRec(node->right, out);
}

template <typename T>
void BST<T>::postorderRec(const Node* node, DynArray<T>& out) const {
    if (!node) return;
    postorderRec(node->left, out);
    postorderRec(node->right, out);
    out.push_back(node->value);
}

template <typename T>
DynArray<T> BST<T>::inorderRecursive() const {
    DynArray<T> out;
    inorderRec(root_, out);
    return out;
}

template <typename T>
DynArray<T> BST<T>::preorderRecursive() const {
    DynArray<T> out;
    preorderRec(root_, out);
    return out;
}

template <typename T>
DynArray<T> BST<T>::postorderRecursive() const {
    DynArray<T> out;
    postorderRec(root_, out);
    return out;
}

template <typename T>
DynArray<T> BST<T>::inorderIterative() const {
    DynArray<T> out;
    ConstNodeStack stk;
    const Node* cur = root_;
    while (cur || !stk.empty()) {
        while (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.pop_top();
        out.push_back(cur->value);
        cur = cur->right;
    }
    return out;
}

template <typename T>
DynArray<T> BST<T>::preorderIterative() const {
    DynArray<T> out;
    if (!root_) return out;
    ConstNodeStack stk;
    stk.push(root_);
    while (!stk.empty()) {
        const Node* cur = stk.pop_top();
        out.push_back(cur->value);
        if (cur->right) stk.push(cur->right);
        if (cur->left)  stk.push(cur->left);
    }
    return out;
}

template <typename T>
DynArray<T> BST<T>::postorderIterative() const {
    DynArray<T> out;
    if (!root_) return out;
    ConstNodeStack stk;
    stk.push(root_);
    while (!stk.empty()) {
        const Node* cur = stk.pop_top();
        out.push_back(cur->value);
        if (cur->left)  stk.push(cur->left);
        if (cur->right) stk.push(cur->right);
    }
    std::size_t lo = 0, hi = out.size();
    while (lo + 1 < hi) {
        T tmp = out[lo];
        out[lo] = out[hi - 1];
        out[hi - 1] = tmp;
        ++lo; --hi;
    }
    return out;
}

template <typename T>
std::optional<T> BST<T>::min() const noexcept {
    const Node* n = findMin(root_);
    return n ? std::optional<T>{n->value} : std::nullopt;
}

template <typename T>
std::optional<T> BST<T>::max() const noexcept {
    const Node* n = findMax(root_);
    return n ? std::optional<T>{n->value} : std::nullopt;
}

template <typename T>
int BST<T>::heightImpl(const Node* node) const noexcept {
    if (!node) return -1;
    int lh = heightImpl(node->left);
    int rh = heightImpl(node->right);
    return 1 + (lh > rh ? lh : rh);
}

template <typename T>
int BST<T>::height() const noexcept {
    return heightImpl(root_);
}

template <typename T>
std::size_t BST<T>::sizeImpl(const Node* node) const noexcept {
    if (!node) return 0;
    return 1 + sizeImpl(node->left) + sizeImpl(node->right);
}

template <typename T>
std::size_t BST<T>::size() const noexcept {
    return sizeImpl(root_);
}

template <typename T>
void BST<T>::clear() noexcept {
    destroySubtree(root_);
    root_ = nullptr;
}

template <typename T>
std::optional<T> BST<T>::successor(const T& value) const {
    const Node* cur  = root_;
    const Node* succ = nullptr;
    while (cur) {
        if (value < cur->value) {
            succ = cur;
            cur  = cur->left;
        } else if (value > cur->value) {
            cur = cur->right;
        } else {
            if (cur->right) return findMin(cur->right)->value;
            break;
        }
    }
    return succ ? std::optional<T>{succ->value} : std::nullopt;
}

template <typename T>
std::optional<T> BST<T>::predecessor(const T& value) const {
    const Node* cur  = root_;
    const Node* pred = nullptr;
    while (cur) {
        if (value > cur->value) {
            pred = cur;
            cur  = cur->right;
        } else if (value < cur->value) {
            cur = cur->left;
        } else {
            if (cur->left) return findMax(cur->left)->value;
            break;
        }
    }
    return pred ? std::optional<T>{pred->value} : std::nullopt;
}

template <typename T>
void BST<T>::printImpl(std::ostream& os, const Node* node,
                       const std::string& prefix, bool isRight) const {
    if (!node) return;
    printImpl(os, node->right, prefix + (isRight ? "    " : "|   "), true);
    os << prefix << (isRight ? "/-- " : "\\-- ") << node->value << "\n";
    printImpl(os, node->left,  prefix + (isRight ? "|   " : "    "), false);
}

template <typename T>
void BST<T>::print(std::ostream& os) const {
    if (!root_) {
        os << "(empty)\n";
        return;
    }
    printImpl(os, root_->right, "    ", true);
    os << root_->value << "\n";
    printImpl(os, root_->left,  "    ", false);
}
