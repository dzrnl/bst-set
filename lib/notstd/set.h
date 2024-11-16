#pragma once

#include <algorithm>

#include "lib/notstd/bst/bst.h"

namespace notstd {

template<class Tp, class Order = bst_order::in_order_tag, class Compare = std::less<Tp>,
        class Allocator = std::allocator<Tp>>
class set {
  public:
    using key_type = Tp;
    using value_type = Tp;
    using key_compare = Compare;
    using value_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;

  private:
    using base = bst<value_type, Order, value_compare, allocator_type>;

    base tree_;

  public:
    using node_type = typename base::node_type;
    using pointer = typename base::pointer;
    using const_pointer = typename base::const_pointer;
    using iterator = typename base::const_iterator;
    using const_iterator = typename base::const_iterator;
    using difference_type = typename base::difference_type;
    using size_type = typename base::size_type;
    using reverse_iterator = typename std::reverse_iterator<iterator>;
    using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;

    explicit set() = default;

    explicit set(const key_compare& compare) : tree_(compare) {}

    explicit set(const allocator_type& alloc) : tree_(alloc) {}

    template<class InputIter>
    explicit set(InputIter i, InputIter j) {
        insert(i, j);
    }

    template<class InputIter>
    explicit set(InputIter i, InputIter j, const key_compare& compare) : set(i, j), tree_(compare) {}

    set(std::initializer_list<value_type> list, const key_compare& compare) : set(list.begin(), list.end(), compare) {}

    set(std::initializer_list<value_type> list) : set(list.begin(), list.end()) {}

    set& operator=(std::initializer_list<value_type> list) {
        clear();
        insert(list.begin(), list.end());

        return *this;
    }

    set(const set& other) : tree_(other.tree_) {}

    set& operator=(const set& other) {
        if (this == &other) {
            return *this;
        }

        tree_ = other.tree_;

        return *this;
    }

    ~set() = default;

    allocator_type get_allocator() const {
        return allocator_type();
    }

    key_compare key_comp() const {
        return key_compare();
    }

    value_compare value_comp() const {
        return value_compare();
    }

    iterator begin() {
        return tree_.cbegin();
    }

    iterator end() {
        return tree_.cend();
    }

    const_iterator cbegin() const {
        return tree_.cbegin();
    }

    const_iterator cend() const {
        return tree_.cend();
    }

    reverse_iterator rbegin() {
        return reverse_iterator(tree_.cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(tree_.cbegin());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(tree_.cend());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(tree_.cbegin());
    }

    bool operator==(const set& other) const {
        return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
    }

    bool operator!=(const set& other) const {
        return !(*this == other);
    }

    size_type size() const {
        return std::distance(cbegin(), cend());
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    [[nodiscard]] bool empty() const {
        return tree_.empty();
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        return tree_.insert(value);
    }

    template<class InputIter>
    void insert(InputIter i, InputIter j) {
        for (InputIter iter = i; iter != j; ++iter) {
            tree_.insert(*iter);
        }
    }

    void insert(std::initializer_list<value_type> list) {
        insert(list.begin(), list.end());
    }

    node_type extract(const value_type& value) {
        return tree_.extract(value);
    }

    node_type extract(const_iterator iter) {
        return tree_.extract(iter);
    }

    void merge(const set& other) {
        insert(other.cbegin(), other.cend());
    }

    size_type erase(const value_type& value) {
        return tree_.erase(value);
    }

    iterator erase(iterator iter) {
        return tree_.erase(iter);
    }

    iterator erase(const_iterator q1, const_iterator q2) {
        iterator q = q1;
        while (q != q2) {
            q = erase(q);
        }

        return q;
    }

    void clear() {
        erase(begin(), end());
    }

    iterator find(const value_type& value) {
        return tree_.find(value);
    }

    const_iterator find(const value_type& value) const {
        return tree_.find(value);
    }

    size_type count(const value_type& value) const {
        return contains(value) ? 1 : 0;
    }

    bool contains(const value_type& value) const {
        return find(value) != cend();
    }

    iterator lower_bound(const value_type& value) {
        return tree_.lower_bound(value);
    }

    const_iterator lower_bound(const value_type& value) const {
        return tree_.lower_bound(value);
    }

    iterator upper_bound(const value_type& value) {
        return tree_.upper_bound(value);
    }

    const_iterator upper_bound(const value_type& value) const {
        return tree_.upper_bound(value);
    }

    std::pair<iterator, iterator> equal_range(const value_type& value) {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }

    std::pair<const_iterator, const_iterator> equal_range(const value_type& value) const {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
};

} // notstd
