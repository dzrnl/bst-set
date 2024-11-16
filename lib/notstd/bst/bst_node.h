#pragma once

template<class Tp>
struct bst_node {
    using value_type = Tp;

    value_type key;
    bst_node* parent = nullptr;
    bst_node* left = nullptr;
    bst_node* right = nullptr;

    explicit bst_node(const value_type& key) : key(key) {};
};
