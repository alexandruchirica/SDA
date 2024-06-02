#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary tree
typedef struct Node {
    int key;            ///< Key value of the node
    struct Node *left;  ///< Pointer to the left child node
    struct Node *right; ///< Pointer to the right child node
} Node;

// Structure for the binary tree
typedef struct BinaryTree {
    Node *root; ///< Pointer to the root node of the tree
} BinaryTree;

/**
 * @brief Create a new node with a given key.
 * 
 * @param key The key value for the new node.
 * @return Node* A pointer to the newly created node.
 */
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * @brief Insert a key into the binary tree.
 * 
 * @param root The root node of the tree.
 * @param key The key value to insert.
 * @return Node* The new root node of the tree.
 */
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

/**
 * @brief Perform in-order traversal of the binary tree.
 * 
 * @param root The root node of the tree.
 */
void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->key);
        inorder_traversal(root->right);
    }
}

/**
 * @brief Display the tree nodes without sorting (pre-order traversal).
 * 
 * @param current_node The current node being traversed.
 */
void display_tree_without_sorting(Node* current_node) {
    if (current_node != NULL) {
        printf("%d ", current_node->key);
        display_tree_without_sorting(current_node->left);
        display_tree_without_sorting(current_node->right);
    }
}

/**
 * @brief Search for a node with a given key in the binary tree.
 * 
 * @param root The root node of the tree.
 * @param key The key value to search for.
 * @return Node* A pointer to the found node, or NULL if not found.
 */
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (root->key < key) {
        return search(root->right, key);
    }

    return search(root->left, key);
}

/**
 * @brief Search for a node with a given key in the binary tree.
 * 
 * @param tree The binary tree.
 * @param key The key value to search for.
 * @return Node* A pointer to the found node, or NULL if not found.
 */
Node* search_in_binary_tree(BinaryTree* tree, int key) {
    return search(tree->root, key);
}

/**
 * @brief Free all nodes in the binary tree.
 * 
 * @param root The root node of the tree.
 */
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

/**
 * @brief Enumeration for the menu options.
 */
typedef enum {
    INSERT_NODE = 1,
    DISPLAY_TREE,
    SEARCH_NODE,
    INORDER_TRAVERSAL,
    CLEAN_TREE,
    EXIT_PROGRAM
} MenuOptions;

/**
 * @brief Print the menu options.
 */
void print_menu() {
    printf("\nMenu:\n");
    printf("1. Insert a node\n");
    printf("2. Display the tree without sorting\n");
    printf("3. Search for a node\n");
    printf("4. Inorder traversal\n");
    printf("5. Clean the tree\n");
    printf("6. Exit\n");
}

/**
 * @brief Display the menu and handle user input.
 * 
 * @param tree The binary tree.
 */
void menu(BinaryTree* tree) {
    int choice, key;
    Node* found;

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case INSERT_NODE:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                tree->root = insert(tree->root, key);
                break;
            case DISPLAY_TREE:
                printf("Tree elements without sorting: ");
                display_tree_without_sorting(tree->root);
                printf("\n");
                break;
            case SEARCH_NODE:
                printf("Enter the key to search for: ");
                scanf("%d", &key);
                found = search_in_binary_tree(tree, key);
                if (found != NULL) {
                    printf("Node found with key %d\n", found->key);
                } else {
                    printf("Node not found\n");
                }
                break;
            case INORDER_TRAVERSAL:
                printf("Inorder traversal: ");
                inorder_traversal(tree->root);
                printf("\n");
                break;
            case CLEAN_TREE:
                free_tree(tree->root);
                tree->root = NULL;
                printf("Tree cleaned\n");
                break;
            case EXIT_PROGRAM:
                printf("Exiting program\n");
                free_tree(tree->root);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != EXIT_PROGRAM);
}

/**
 * @brief Main function.
 * 
 * @return int Exit status.
 */
int main() {
    BinaryTree tree;
    tree.root = NULL;
    menu(&tree);
    return 0;
}
