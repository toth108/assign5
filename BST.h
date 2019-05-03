// MADALYN TOTH

#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

template <class T>
class BST
{
    private:
        TreeNode<T> *root;
        int size;

    public:
        BST()
        {
            root = NULL;
            size = 0;
        }

        ~BST()
        {

        };

        void insert(TreeNode<T> *node)
        {
            if (root == NULL) // if tree is empty 
            {
                root = node;
            }

            else
            {
                TreeNode<T> *current = root;
                TreeNode<T> *parent; 

                while (true)
                {
                    parent = current;

                    if (node->key < current->key) // left 
                    {
                        current = current->left;

                        if (current == NULL) // leaf found 
                        {
                            parent->left = node;
                            break;
                        }
                    }

                    else // right 
                    {
                        current = current->right;

                        if (current == NULL) // leaf found 
                        {
                            parent->right = node;
                            break;
                        }
                    }
                }
            }

            size++;
        }

        bool isInTree(int k)
        {
            if (root == NULL) // if tree is empty 
            {
                return false;
            }

            TreeNode<T> *current = root;

            while (current->key != k) // search for node 
            {
                if (k < current->key) // left 
                {
                    current = current->left;
                }

                else // right 
                {
                    current = current->right;
                }

                if (current == NULL) // node not found 
                {
                    return false;
                }
            }

            return true;
        }

        T* search(int k)
        {
            if (isInTree(k))
            {
                TreeNode<T> *current = root;

                while (current->key != k) // search for node 
                {
                    if (k < current->key) // left 
                    {
                        current = current->left;
                    }

                    else // right 
                    {
                        current = current->right;
                    }
                }

                return current->data;
            }

            else
            {
                return NULL;
            }
        }

        TreeNode<T>* getSuccessor(TreeNode<T> *n)
        {
            TreeNode<T> *successorParent = n;
            TreeNode<T> *successor = n;
            TreeNode<T> *current = n->right;

            while (current != NULL)
            {
                successorParent = successor;
                successor = current;
                current = current->left;
            }

            if (successor != n->right)
            {
                successorParent->left = successor->right;
                successor->right = n->right;
            }

            return successor;
        }

        bool deleteNode(int k)
        {
            if (root == NULL) // if tree is empty 
            {
                return false;
            }

            TreeNode<T> *parent = root;
            TreeNode<T> *current = root;
            bool isLeft = true;

            while (current->key != k) // search for node 
            {
                parent = current;

                if (k < current->key) // left 
                {
                    isLeft = true;

                    current = current->left;
                }

                else // right 
                {
                    isLeft = false;

                    current = current->right;
                }

                if (current == NULL) // node not found 
                {
                    return false;
                }
            }

            // no children 
            if (current->left == NULL && current->right == NULL)
            {
                if (current == root) // delete root 
                {
                    root = NULL;
                }

                else if (isLeft)
                {
                    parent->left = NULL;
                }

                else
                {
                    parent->right = NULL;
                }
            }

            // one child: left 
            else if (current->right == NULL)
            {
                if (current == root)
                {
                    root = current->left;
                }

                else if (isLeft)
                {
                    parent->left = current->left;
                }

                else
                {
                    parent->right = current->left;
                }
            }

            // one child: right 
            else if (current->right == NULL)
            {
                if (current == root)
                {
                    root = current->right;
                }

                else if (isLeft)
                {
                    parent->left = current->right;
                }

                else
                {
                    parent->right = current->right;
                }
            }

            // two children 
            else
            {
                TreeNode<T> *successor = getSuccessor(current);

                if (current == root)
                {
                    root = successor;
                }

                else if (isLeft)
                {
                    parent->left = successor;
                }

                else
                {
                    parent->right = successor;
                }

                successor->left = current->left; // link successor to current's left child 
            }

            size--;
            return true;
        }

        void print(TreeNode<T> *node)
        {
            if (node == NULL)
            {
                return;
            }

            print(node->left);
            cout << node->data << endl;
            print(node->right);
        }

        void printTree()
        {
            print(root);
        }

        TreeNode<T>* getRoot()
        {
            return root;
        }

        int getSize()
        {
            return size;
        }

        bool isEmpty()
        {
            return (size == 0);
        }
};