#pragma once

#include "bst_const_iterator.h"

#include <memory>

template<class Tp, class Order = bst_order::in_order_tag, class Compare = std::less<Tp>,
        class Allocator = std::allocator<Tp>>
class bst {
  public:
    using value_type = Tp;
    using node_type = bst_node<value_type>;
    using value_compare = Compare;
    using allocator_type = Allocator;

  private:
    using alloc_traits = std::allocator_traits<allocator_type>;

  public:
    using pointer = typename alloc_traits::pointer;
    using const_pointer =  typename alloc_traits::const_pointer;
    using const_iterator = bst_const_iterator<Tp, Order>;
    using difference_type = typename const_iterator::difference_type;
    using size_type = typename const_iterator::size_type;

    using node_allocator_type = typename alloc_traits::template rebind_alloc<node_type>;

  private:
    node_allocator_type allocator_;
    value_compare compare_;

    node_type* root_;

    node_type* find_node(const value_type& value) const {
        node_type* current = root_;

        while (current != nullptr) {
            if (compare_(value, current->key)) {
                current = current->left;
            } else if (compare_(current->key, value)) {
                current = current->right;
            } else {
                return current;
            }
        }

        return nullptr;
    }

    const_iterator cbegin(const bst_order::in_order_tag&) const {
        const node_type* node = root_;
        if (node != nullptr) {
            while (node->left != nullptr) {
                node = node->left;
            }
        }

        return const_iterator(node, root_);
    }

    const_iterator cbegin(const bst_order::pre_order_tag&) const {
        return const_iterator(root_, root_);
    }

    const_iterator cbegin(const bst_order::post_order_tag&) const {
        const node_type* node = root_;
        if (node != nullptr) {
            while (node->left != nullptr) {
                node = node->left;
            }
        }

        return const_iterator(node, root_);
    }

  public:
    explicit bst() : root_(nullptr) {};

    explicit bst(const value_compare& compare) : root_(nullptr), compare_(compare) {};

    explicit bst(const allocator_type& alloc) : root_(nullptr), allocator_(alloc) {};

    bst(const bst& other) {
        root_ = copyTree(other.root_);
    };

    bst& operator=(const bst& other) {
        if (this == &other) {
            return *this;
        }

        deleteTree(root_);
        root_ = copyTree(other.root_);

        return *this;
    }

    std::pair<const_iterator, bool> insert(const value_type& value) {
        node_type* new_node = createNode(value);

        if (root_ == nullptr) {
            root_ = new_node;
            return std::make_pair(const_iterator(new_node, root_), true);
        }

        node_type* current = root_;
        node_type* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (compare_(value, current->key)) {
                current = current->left;
            } else if (compare_(current->key, value)) {
                current = current->right;
            } else {
                deleteNode(new_node);
                return std::make_pair(const_iterator(current, root_), false);
            }
        }

        new_node->parent = parent;
        if (compare_(value, parent->key)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        return std::make_pair(const_iterator(new_node, root_), true);
    }

    node_type extract(const value_type& value) {
        node_type* node_to_delete = find_node(value);
        if (node_to_delete == nullptr) {
            return *createNode(0);
        }

        if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) {
            if (node_to_delete->parent == nullptr) {
                root_ = nullptr;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = nullptr;
            } else {
                node_to_delete->parent->right = nullptr;
            }
            return *node_to_delete;
        }

        if (node_to_delete->left == nullptr || node_to_delete->right == nullptr) {
            node_type* child = (node_to_delete->left != nullptr) ? node_to_delete->left : node_to_delete->right;
            if (node_to_delete->parent == nullptr) {
                root_ = child;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = child;
            } else {
                node_to_delete->parent->right = child;
            }
            child->parent = node_to_delete->parent;
            return *node_to_delete;
        }

        node_type* successor = node_to_delete->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        node_to_delete->key = successor->key;

        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        if (successor->right != nullptr) {
            successor->right->parent = successor->parent;
        }

        return *successor;
    }

    node_type extract(const_iterator iter) {
        if (iter == const_iterator(nullptr, root_)) {
            return *createNode(0);
        }
        node_type* node_to_delete = find_node(*iter);
        if (node_to_delete == nullptr) {
            return *createNode(0);
        }

        if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) {
            if (node_to_delete->parent == nullptr) {
                root_ = nullptr;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = nullptr;
            } else {
                node_to_delete->parent->right = nullptr;
            }
            return *node_to_delete;
        }

        if (node_to_delete->left == nullptr || node_to_delete->right == nullptr) {
            node_type* child = (node_to_delete->left != nullptr) ? node_to_delete->left : node_to_delete->right;
            if (node_to_delete->parent == nullptr) {
                root_ = child;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = child;
            } else {
                node_to_delete->parent->right = child;
            }
            child->parent = node_to_delete->parent;
            return *node_to_delete;
        }

        node_type* successor = node_to_delete->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        node_to_delete->key = successor->key;

        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        if (successor->right != nullptr) {
            successor->right->parent = successor->parent;
        }

        return *successor;
    }

    size_type erase(const value_type& value) {
        node_type* node_to_delete = find_node(value);
        if (node_to_delete == nullptr) {
            return 0;
        }

        if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) {
            if (node_to_delete->parent == nullptr) {
                root_ = nullptr;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = nullptr;
            } else {
                node_to_delete->parent->right = nullptr;
            }
            delete node_to_delete;
            return 1;
        }

        if (node_to_delete->left == nullptr || node_to_delete->right == nullptr) {
            node_type* child = (node_to_delete->left != nullptr) ? node_to_delete->left : node_to_delete->right;
            if (node_to_delete->parent == nullptr) {
                root_ = child;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = child;
            } else {
                node_to_delete->parent->right = child;
            }
            child->parent = node_to_delete->parent;
            delete node_to_delete;
            return 1;
        }

        node_type* successor = node_to_delete->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        node_to_delete->key = successor->key;

        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        if (successor->right != nullptr) {
            successor->right->parent = successor->parent;
        }

        delete successor;
        return 1;
    }

    const_iterator erase(const_iterator iter) {
        if (iter == const_iterator(nullptr, root_)) {
            return iter;
        }
        node_type* node_to_delete = find_node(*iter);
        if (node_to_delete == nullptr) {
            return cend();
        }

        node_type* successor;
        if (node_to_delete->left != nullptr && node_to_delete->right != nullptr) {
            successor = node_to_delete->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            node_to_delete->key = successor->key;

            if (successor->parent->left == successor) {
                successor->parent->left = successor->right;
            } else {
                successor->parent->right = successor->right;
            }

            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
        } else {
            node_type* child = (node_to_delete->left != nullptr) ? node_to_delete->left : node_to_delete->right;
            if (node_to_delete->parent == nullptr) {
                root_ = child;
            } else if (node_to_delete == node_to_delete->parent->left) {
                node_to_delete->parent->left = child;
            } else {
                node_to_delete->parent->right = child;
            }
            if (child != nullptr) {
                child->parent = node_to_delete->parent;
            }
            successor = child;
        }

        delete node_to_delete;
        return const_iterator(successor, root_);
    }

    const_iterator find(const value_type& value) const {
        node_type* current = root_;

        while (current != nullptr) {
            if (compare_(value, current->key)) {
                current = current->left;
            } else if (compare_(current->key, value)) {
                current = current->right;
            } else {
                return const_iterator(current, root_);
            }
        }

        return cend();
    }

    [[nodiscard]] bool empty() const {
        return root_ == nullptr;
    }

    const_iterator lower_bound(const value_type& value) {
        node_type* current = root_;
        node_type* lower_bound = nullptr;

        while (current != nullptr) {
            if (!compare_(value, current->key)) {
                lower_bound = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }

        return const_iterator(lower_bound, root_);
    }

    const_iterator upper_bound(const value_type& value) {
        node_type* current = root_;
        node_type* upper_bound = nullptr;

        while (current != nullptr) {
            if (!compare_(current->key, value)) {
                upper_bound = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return const_iterator(upper_bound, root_);
    }

    const_iterator cbegin() const {
        return cbegin(Order());
    }

    const_iterator cend() const {
        return const_iterator(nullptr, root_);
    }

    ~bst() {
        deleteTree(root_);
    }

  private:
    node_type* createNode(const value_type& key) {
        node_type* new_node = allocator_.allocate(1);

        new(new_node) node_type(key);

        return new_node;
    }

    void deleteNode(node_type* node) {
        allocator_.deallocate(node, 1);
    }

    node_type* copyTree(const node_type* other_node, node_type* parent = nullptr) {
        if (other_node == nullptr) {
            return nullptr;
        }

        node_type* node = createNode(other_node->key);
        node->parent = parent;
        node->left = copyTree(other_node->left, node);
        node->right = copyTree(other_node->right, node);

        return node;
    }

    void deleteTree(node_type* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            deleteNode(node);
        }
    }
};
