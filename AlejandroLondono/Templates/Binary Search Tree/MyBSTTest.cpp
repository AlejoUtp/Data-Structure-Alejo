#ifndef __BST__
#define __BST__

template <typename Key, typename Value>
class BST
{

private:
    class Node
    {
    private:
        Key key;
        Value value;
        Node *left;
        Node *right;

    public:
        Node(const Key &k, const Value &v) : key(k), value(v), left(nullptr), right(nullptr) {}

        const Key &getKey() const { return key; }
        const Value &getValue() const { return value; }

        Node* getLeft() const { return left;}
        Node* getRight() const { return right;}

        void setLeft(Node *n) { left = n; }
        void setRight(Node *n) { right = n; }
        void setValue(const Value &v) { value = v; }

        bool hasLeft() const { return left != nullptr;}
        bool hasRight() const { return right != nullptr;}
    }

    private:
    Node* root;  ///< Raíz del árbol
    unsigned int sz; 

    