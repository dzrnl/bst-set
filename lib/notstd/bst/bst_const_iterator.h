#pragma once

#include "bst_node.h"
#include "bst_order.h"

#include <cstddef>

template<class Tp, class Order>
class bst_const_iterator {
  public:
    using difference_type = ptrdiff_t;
    using size_type = size_t;
    using value_type = Tp;
    using node_type = const bst_node<value_type>;
    using pointer = node_type*;
    using reference = node_type&;
    using iterator_category = std::bidirectional_iterator_tag;

  protected:
    pointer ptr_;
    pointer root_;

  public:
    explicit bst_const_iterator(pointer ptr, pointer root) : ptr_(ptr), root_(root) {}

    bst_const_iterator(const bst_const_iterator& other) : ptr_(other.ptr_), root_(other.root_) {}

    bool operator==(const bst_const_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const bst_const_iterator& other) const {
        return !(*this == other);
    }

    const value_type& operator*() const {
        return ptr_->key;
    }

    bst_const_iterator& operator++() {
        increment(Order());

        return *this;
    }

    bst_const_iterator operator++(int) {
        bst_const_iterator result(*this);
        ++(*this);

        return result;
    }

    bst_const_iterator& operator--() {
        decrement(Order());

        return *this;
    }

    bst_const_iterator operator--(int) {
        bst_const_iterator result(*this);
        --(*this);

        return result;
    }

  protected:
    void increment(const bst_order::in_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            while (ptr_->left != nullptr) {
                ptr_ = ptr_->left;
            }
            return;
        }

        if (ptr_->right != nullptr) {
            ptr_ = ptr_->right;
            while (ptr_->left != nullptr) {
                ptr_ = ptr_->left;
            }
        } else {
            while (ptr_->parent != nullptr && ptr_->parent->right == ptr_) {
                ptr_ = ptr_->parent;
            }
            if (ptr_->parent != nullptr) {
                ptr_ = ptr_->parent;
            } else {
                ptr_ = nullptr;
            }
        }
    }

    void increment(const bst_order::pre_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            return;
        }

        if (ptr_->left != nullptr) {
            ptr_ = ptr_->left;
        } else if (ptr_->right != nullptr) {
            ptr_ = ptr_->right;
        } else {
            while (ptr_->parent != nullptr && (ptr_->parent->right == nullptr || ptr_->parent->right == ptr_)) {
                ptr_ = ptr_->parent;
            }
            if (ptr_->parent != nullptr) {
                ptr_ = ptr_->parent->right;
            } else {
                ptr_ = nullptr;
            }
        }
    }

    void increment(const bst_order::post_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            while (ptr_->left != nullptr) {
                ptr_ = ptr_->left;
            }
            return;
        }

        if (ptr_->parent == nullptr) {
            ptr_ = nullptr;
        } else if (ptr_->parent->right == ptr_ || ptr_->parent->right == nullptr) {
            ptr_ = ptr_->parent;
        } else {
            pointer next = ptr_->parent->right;
            while (next->left != nullptr || next->right != nullptr) {
                if (next->left != nullptr) {
                    next = next->left;
                } else {
                    next = next->right;
                }
            }
            ptr_ = next;
        }
    }

    void decrement(const bst_order::in_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            while (ptr_->right != nullptr) {
                ptr_ = ptr_->right;
            }
            return;
        }

        if (ptr_->left != nullptr) {
            ptr_ = ptr_->left;
            while (ptr_->right != nullptr) {
                ptr_ = ptr_->right;
            }
        } else {
            while (ptr_->parent != nullptr && ptr_->parent->left == ptr_) {
                ptr_ = ptr_->parent;
            }
            ptr_ = ptr_->parent;
        }
    }

    void decrement(const bst_order::pre_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            while (ptr_->right != nullptr) {
                ptr_ = ptr_->right;
            }
            return;
        }

        if (ptr_->parent->left != ptr_ && ptr_->parent->left != nullptr) {
            ptr_ = ptr_->parent->left;
            while (ptr_->right != nullptr) {
                ptr_ = ptr_->right;
            }
        } else {
            ptr_ = ptr_->parent;
        }
    }

    void decrement(const bst_order::post_order_tag&) {
        if (ptr_ == nullptr) {
            ptr_ = root_;
            return;
        }

        if (ptr_->right != nullptr) {
            ptr_ = ptr_->right;
        } else if (ptr_->left != nullptr) {
            ptr_ = ptr_->left;
        } else {
            if (ptr_->parent->left == ptr_) {
                ptr_ = ptr_->parent->parent;
            }
            while (ptr_->left == nullptr) {
                ptr_ = ptr_->parent;
            }
            ptr_ = ptr_->left;
        }
    }
};
