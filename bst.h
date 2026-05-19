#pragma once

#include <optional>
#include <stdexcept>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <string>
#include <utility>

template <typename T>
class DynArray {
public:
    DynArray() noexcept : data_(nullptr), size_(0), cap_(0) {}

    DynArray(std::initializer_list<T> init) : data_(nullptr), size_(0), cap_(0) {
        for (const T& v : init) push_back(v);
    }

    ~DynArray() { delete[] data_; }

    DynArray(const DynArray& o) : data_(nullptr), size_(0), cap_(0) {
        reserveExact(o.size_);
        for (std::size_t i = 0; i < o.size_; ++i) data_[i] = o.data_[i];
        size_ = o.size_;
    }

    DynArray(DynArray&& o) noexcept : data_(o.data_), size_(o.size_), cap_(o.cap_) {
        o.data_ = nullptr;
        o.size_ = 0;
        o.cap_ = 0;
    }

    DynArray& operator=(const DynArray& o) {
        if (this != &o) {
            DynArray tmp(o);
            swapWith(tmp);
        }
        return *this;
    }

    DynArray& operator=(DynArray&& o) noexcept {
        swapWith(o);
        return *this;
    }

    void push_back(const T& v) {
        if (size_ == cap_) grow();
        data_[size_++] = v;
    }

    T& operator[](std::size_t i) noexcept { return data_[i]; }
    const T& operator[](std::size_t i) const noexcept { return data_[i]; }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    T* begin() noexcept { return data_; }
    T* end() noexcept { return data_ + size_; }
    const T* begin() const noexcept { return data_; }
    const T* end() const noexcept { return data_ + size_; }

    bool operator==(const DynArray& o) const noexcept {
        if (size_ != o.size_) return false;
        for (std::size_t i = 0; i < size_; ++i)
            if (!(data_[i] == o.data_[i])) return false;
        return true;
    }

    bool operator!=(const DynArray& o) const noexcept { return !(*this == o); }

private:
    T* data_;
    std::size_t size_;
    std::size_t cap_;

    void grow() {
        reserveExact(cap_ ? cap_ * 2 : 4);
    }

    void reserveExact(std::size_t newCap) {
        if (newCap <= cap_) return;
        T* newData = new T[newCap];
        for (std::size_t i = 0; i < size_; ++i) newData[i] = data_[i];
        delete[] data_;
        data_ = newData;
        cap_ = newCap;
    }

    void swapWith(DynArray& o) noexcept {
        T* td = data_; data_ = o.data_; o.data_ = td;
        std::size_t ts = size_; size_ = o.size_; o.size_ = ts;
        std::size_t tc = cap_; cap_ = o.cap_; o.cap_ = tc;
    }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const DynArray<T>& arr) {
    os << "[";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) os << ", ";
        os << arr[i];
    }
    return os << "]";
}

template <typename T>
class BST {
public:
    BST() noexcept : root_(nullptr) {}
    ~BST() { destroySubtree(root_); }
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(T value);
    void remove(T value);
    bool search(const T& value) const noexcept;
    bool contains(const T& value) const noexcept;

    DynArray<T> inorderRecursive() const;
    DynArray<T> preorderRecursive() const;
    DynArray<T> postorderRecursive() const;
    DynArray<T> inorderIterative() const;
    DynArray<T> preorderIterative() const;
    DynArray<T> postorderIterative() const;

    std::optional<T> min() const noexcept;
    std::optional<T> max() const noexcept;
    int height() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;

    std::optional<T> successor(const T& value) const;
    std::optional<T> predecessor(const T& value) const;

    void print(std::ostream& os = std::cout) const;

private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        explicit Node(T val) : value(std::move(val)), left(nullptr), right(nullptr) {}
    };

    struct ConstNodeStack {
        const Node** buf;
        std::size_t sz;
        std::size_t cap;

        ConstNodeStack() noexcept : buf(nullptr), sz(0), cap(0) {}
        ~ConstNodeStack() { delete[] buf; }

        ConstNodeStack(const ConstNodeStack&) = delete;
        ConstNodeStack& operator=(const ConstNodeStack&) = delete;

        void push(const Node* n) {
            if (sz == cap) {
                std::size_t nc = cap ? cap * 2 : 8;
                const Node** nb = new const Node*[nc];
                for (std::size_t i = 0; i < sz; ++i) nb[i] = buf[i];
                delete[] buf;
                buf = nb;
                cap = nc;
            }
            buf[sz++] = n;
        }

        const Node* top() const noexcept { return buf[sz - 1]; }
        const Node* pop_top() noexcept { return buf[--sz]; }
        bool empty() const noexcept { return sz == 0; }
    };

    Node* root_;

    void insertImpl(Node*& node, T value);
    Node* removeImpl(Node* node, const T& value);
    const Node* findMin(const Node* node) const noexcept;
    const Node* findMax(const Node* node) const noexcept;
    int heightImpl(const Node* node) const noexcept;
    std::size_t sizeImpl(const Node* node) const noexcept;
    void destroySubtree(Node* node) noexcept;

    void inorderRec(const Node* node, DynArray<T>& out) const;
    void preorderRec(const Node* node, DynArray<T>& out) const;
    void postorderRec(const Node* node, DynArray<T>& out) const;

    void printImpl(std::ostream& os, const Node* node,
                   const std::string& prefix, bool isRight) const;
};

#include "bst.cpp"
