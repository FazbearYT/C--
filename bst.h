#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <stack>
#include <stdexcept>
#include <algorithm>

template <typename T>
class BST {
public:
    void insert(T value);
    void remove(T value);
    bool search(const T& value) const noexcept;
    bool contains(const T& value) const noexcept;

    std::vector<T> inorderRecursive() const;
    std::vector<T> preorderRecursive() const;
    std::vector<T> postorderRecursive() const;
    std::vector<T> inorderIterative() const;
    std::vector<T> preorderIterative() const;
    std::vector<T> postorderIterative() const;

    std::optional<T> min() const noexcept;
    std::optional<T> max() const noexcept;
    int height() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;

    std::optional<T> successor(const T& value) const;
    std::optional<T> predecessor(const T& value) const;

private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        explicit Node(T val) : value(std::move(val)) {}
    };

    std::unique_ptr<Node> root_;

    void insertImpl(std::unique_ptr<Node>& node, T value);
    std::unique_ptr<Node> removeImpl(std::unique_ptr<Node> node, const T& value);
    const Node* findMin(const Node* node) const noexcept;
    const Node* findMax(const Node* node) const noexcept;
    int heightImpl(const Node* node) const noexcept;
    std::size_t sizeImpl(const Node* node) const noexcept;

    void inorderRec(const Node* node, std::vector<T>& result) const;
    void preorderRec(const Node* node, std::vector<T>& result) const;
    void postorderRec(const Node* node, std::vector<T>& result) const;
};

#include "bst.cpp"
