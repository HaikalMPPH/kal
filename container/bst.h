#pragma once

// BINARY SEARCH TREE

#include "../memory/allocator.h"
#include "../types.h"


// :: DECL ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
struct kal_bst_node {
    usize key;
    void* value;
    struct kal_bst_node* left;
    struct kal_bst_node* right;
};

struct kal_bst {
    struct kal_bst_node* root;
    usize value_size;
};

struct kal_bst_node*
kal_bst_node_init(const usize key,
                  usize value_size,
                  void* value);

void
kal_bst_node_add(struct kal_bst_node* node,
                 usize key,
                 void* value);

void
kal_bst_node_deinit(struct kal_bst_node* node);

struct kal_bst
kal_bst_init(usize value_size);

void
kal_bst_add(struct kal_bst* bst,
            usize key, 
            void* value);

void*
kal_bst_get(const struct kal_bst* bst,
            usize key);

void
kal_bst_deinit(struct kal_bst* bst);



// :: IMPL ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef KAL_CONTAINER_BST_IMPL
#include "../util/assert.h"

struct kal_bst_node*
kal_bst_node_init(usize value_size,
                  const usize key,
                  void* value) {
    struct kal_bst_node* node = KAL_ALLOC(sizeof(struct kal_bst_node));
    *node = (struct kal_bst_node) {
        .key = key,
        .value = KAL_ALLOC(sizeof(value_size)),
        .left = nullptr,
        .right = nullptr,
    };

    memcpy(node->value, value, value_size);

    return node;
}

void
kal_bst_node_deinit(struct kal_bst_node* node) {
    if (node->left != nullptr) {
        kal_bst_node_deinit(node->left);
    }
    if (node->right != nullptr) {
        kal_bst_node_deinit(node->right);
    }

    KAL_DEALLOC(node->value);
    KAL_DEALLOC(node);
}

struct kal_bst
kal_bst_init(usize value_size) {
    return (struct kal_bst) {
        .root = nullptr,
        .value_size = value_size,
    };
}

void
kal_bst_add(struct kal_bst* bst,
            usize key, 
            void* value)
{
    if (nullptr == bst->root) {
        bst->root = kal_bst_node_init(bst->value_size, key, value);
    }
    else {
        struct kal_bst_node* node = bst->root;
        for (;;) {
            if (key < node->key) {
                if (nullptr != node->left) {
                    node = node->left;
                }
                else {
                    node->left = kal_bst_node_init(bst->value_size, key, value);
                    break;
                }
            }
            else {
                if (nullptr != node->right) {
                    node = node->right;
                }
                else {
                    node->right = kal_bst_node_init(bst->value_size, key, value);
                    break;
                }
            }
        }
    }
}

void*
kal_bst_get(const struct kal_bst* bst,
            usize key) {
    struct kal_bst_node* node = bst->root;
    while (true) {
        if (key == node->key) {
            return node->value;
        }
        else if (key <= node->key && nullptr != node->left) {
            node = node->left;
        }
        else if (key > node->key && nullptr != node->right) {
            node = node->right;
        }
        else {
            // TODO: remove this and just return nullptr.
            printf("Can't find element of key: %ld\n", key);
            //exit(EXIT_FAILURE);
            return nullptr;
        }
    }
}

void
kal_bst_deinit(struct kal_bst* bst) {
    if (nullptr == bst->root) {
        return;
    }

    kal_bst_node_deinit(bst->root);
}

#endif
