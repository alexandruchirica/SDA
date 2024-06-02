/**
 * @file main.c
 * @brief A program to create, manipulate, and display a binary search tree.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct TreeNode
 * @brief Structure defining a node in the binary search tree.
 */
struct TreeNode {
    int data; /**< Data stored in the node */
    struct TreeNode* left; /**< Pointer to the left child node */
    struct TreeNode* right; /**< Pointer to the right child node */
};

/**
 * @brief Creates a new node with the given value.
 * @param value The value to be stored in the new node.
 * @return A pointer to the newly created node.
 */
struct TreeNode* create_node(int value) {
    struct TreeNode* new_node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * @brief Inserts a node with the given value into the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 * @param value The value to be inserted.
 * @return A pointer to the root of the modified binary search tree.
 */
struct TreeNode* insert_node(struct TreeNode* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }
    if (value < root->data) {
        root->left = insert_node(root->left, value);
    } else if (value > root->data) {
        root->right = insert_node(root->right, value);
    }
    return root;
}

/**
 * @brief Performs an inorder traversal of the binary search tree and prints the elements.
 * @param root Pointer to the root of the binary search tree.
 */
void inorder_traversal(struct TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

/**
 * @brief Calculates the depth of the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 * @return The depth of the binary search tree.
 */
int calculate_depth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_depth = calculate_depth(root->left);
        int right_depth = calculate_depth(root->right);

        if (left_depth > right_depth) {
            return left_depth + 1;
        } else {
            return right_depth + 1;
        }
    }
}

/**
 * @brief Searches for a node with the given key in the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 * @param key The value of the node to search for.
 * @return A pointer to the node with the given key if found, otherwise NULL.
 */
struct TreeNode* search_node(struct TreeNode* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (root->data < key) {
        return search_node(root->right, key);
    }
    return search_node(root->left, key);
}

/**
 * @brief Calculates the depth of a node with the given key in the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 * @param key The value of the node whose depth is to be calculated.
 * @param depth The depth of the current node (initially set to 0).
 * @return The depth of the node with the given key. Returns -1 if the node is not found.
 */
int calculate_node_depth(struct TreeNode* root, int key, int depth) {
    if (root == NULL) {
        return -1;
    }
    if (root->data == key) {
        return depth;
    }
    if (key < root->data) {
        return calculate_node_depth(root->left, key, depth + 1);
    }
    return calculate_node_depth(root->right, key, depth + 1);
}

/**
 * @brief Calculates the height of a node with the given key in the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 * @param key The value of the node whose height is to be calculated.
 * @return The height of the node with the given key. Returns -1 if the node is not found.
 */
int calculate_node_height(struct TreeNode* root, int key) {
    struct TreeNode* node = search_node(root, key);
    if (node == NULL) {
        return -1;
    }
    return calculate_depth(node) - 1;
}

/**
 * @brief Displays all the leaves of the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 */
void print_leaves(struct TreeNode* root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            printf("%d ", root->data);
        }
        print_leaves(root->left);
        print_leaves(root->right);
    }
}

/**
 * @brief Cleans up the memory allocated for the binary search tree.
 * @param root Pointer to the root of the binary search tree.
 */
void free_tree(struct TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

/**
 * @brief Main function to run the program.
 * @return 0 on successful execution.
 */

enum MenuOption {
    READ_ELEMENTS = 1,
    DISPLAY_ELEMENTS,
    CALCULATE_TREE_DEPTH,
    SEARCH_NODE,
    CALCULATE_NODE_DEPTH,
    CALCULATE_NODE_HEIGHT,
    DISPLAY_LEAVES,
    CLEANUP_TREE,
    FREE_MEMORY,
    EXIT_PROGRAM
};


int main() {
    struct TreeNode* root = NULL;
    int choice, value, key;

    do {
        printf("\n%d. Read elements of the tree from the keyboard\n", READ_ELEMENTS);
        printf("2. Display the elements of the tree\n");
        printf("3. Calculate the depth of the tree\n");
        printf("4. Search for a node based on a search key\n");
        printf("5. Calculate the depth of a node\n");
        printf("6. Calculate the height of a node\n");
        printf("7. Display all the leaves of the tree\n");
        printf("8. Clean up the elements of the tree\n");
        printf("9. Free the memory of the tree\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_ELEMENTS:
                printf("Enter the elements of the tree (-1 to stop reading): ");
                while (1) {
                    scanf("%d", &value);
                    if (value == -1) break;
                    root = insert_node(root, value);
                }
                break;
            case DISPLAY_ELEMENTS:
                printf("Elements of the tree: ");
                inorder_traversal(root);
                printf("\n");
                break;
            case CALCULATE_TREE_DEPTH:
                printf("Depth of the tree: %d\n", calculate_depth(root));
                break;
            case SEARCH_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                if (search_node(root, key) != NULL) {
                    printf("Node with key %d exists in the tree.\n", key);
                } else {
                    printf("Node with key %d does not exist in the tree.\n", key);
                }
                break;
            case CALCULATE_NODE_DEPTH:
                printf("Enter the search key: ");
                scanf("%d", &key);
                printf("Depth of the node with key %d is: %d\n", key, calculate_node_depth(root, key, 0));
                break;
            case CALCULATE_NODE_HEIGHT:
                printf("Enter the search key: ");
                scanf("%d", &key);
                printf("Height of the node with key %d is: %d\n", key, calculate_node_height(root, key));
                break;
            case DISPLAY_LEAVES:
                printf("Leaves of the tree: ");
                print_leaves(root);
                printf("\n");
                break;
            case CLEANUP_TREE:
                free_tree(root);
                root = NULL;
                printf("Tree has been cleaned up.\n");
                break;
            case FREE_MEMORY:
                free_tree(root);
                printf("Memory of the tree has been freed.\n");
                return 0;
            case EXIT_PROGRAM:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (choice != EXIT_PROGRAM);


    return 0;
}
