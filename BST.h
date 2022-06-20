//
// Created by Nate Lampros on 11/22/21.
//

#ifndef INC_9_CS235_POKEMON_BST_H
#define INC_9_CS235_POKEMON_BST_H
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
class BST {
private:
    int counter = 0;
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        Node(T d) : data(d), left(NULL), right(NULL) { }
    };
    Node* root;

public:
    //***************************** CONSTRUCTOR **********************
    BST(void) { this->root = NULL; }
    virtual ~BST(void) { clearTree(); }
    //****************************************************************


    //***************************** COPY CONSTRUCTOR **********************
    BST(const BST& bst): root(NULL)
    {
        this->copyNodes(bst.root);
    }
    //*********************************************************************


    //********************** ASSIGNMENT OPERATOR **************************
    BST& operator=(const BST& rhs)
    {
        BST<T> the_copy(rhs);
        swap(this->root, the_copy.root);
        return *this;
    }
    //*********************************************************************


    //***************************** ADD NODE *******************************
    virtual bool addNode(const T& value) { //Add
        ++counter;
        return insert(root, value);
    }
    bool insert (Node*& node, const T& value) { //recursive add
        if (node == NULL){
            node = new Node(value);
            return true;
        }
        if (value == node->data){
            --counter;
            //throw string ("Error");
            return false;
        }
        if (value < node->data){
            insert(node->left, value);
            return true;
            //return insert(node->left, value);
        }
        if (value > node->data){
            insert(node->right, value);
            return true;
            return insert(node->right, value);
        }
    }
    //****************************************************************


    //***************************** COPY *****************************
    void copyNodes(Node* node)
    {
        if (node == NULL) return;
        insert(this->root, node->data);
        copyNodes(node->left);
        copyNodes(node->right);
    }
    //****************************************************************


    //***************************** REMOVE NODE *****************************
    virtual bool removeNode(const T& value) {
        --counter;
        remove(root, value);
        return true;
    } //TODO
    bool remove(Node*& node, const T& value){
        if (node == NULL){
            ++counter;
            throw string("Error");
        }
        else if (value < node->data){
            remove(node->left, value);
        }
        else if (value > node->data){
            remove(node->right, value);
        }
        else if (value == node->data) {
            if (node->right == NULL && node->left == NULL) {
                delete node;
                node = NULL;
                return true;
            } else if (node->left == NULL) {
                Node *temp = node;
                node = node->right;
                delete temp;
                return true;
            } else if (node->right == NULL) {
                Node *temp = node;
                node = node->left;
                delete temp;
                return true;
            } else if (node->left != NULL && node->right != NULL) { //if both are full
                Node *temp = findMax(node->left);
                node->data = temp->data;

                return remove(node->left, temp->data);
            }
        }
        else if (node->data != value) {
            throw string("Error");
        }
        return true;
    }
    //****************************************************************


    //***************************** FIND MAX NODE *****************************
    Node* findMax(Node*& node){
        if (node == NULL) return NULL;
        if (node->right != NULL){
            return findMax(node->right);
        }
        return node;
    }
    //****************************************************************



    //***************************** CLEAR TREE *****************************
    virtual bool clearTree() { //clear
        counter = 0;
        clearTree(root);
        root == NULL;
        return true;
    }
    void clearTree(Node*& data){ //recursive clear
        if (data == NULL) {return;}

        clearTree(data -> left);
        clearTree(data -> right);

        delete data;
        data = NULL;
        return;
    }
    //****************************************************************


    //***************************** FIND NODE *****************************
    bool find(const T& value) { //find <data>
        return search(root, value);
    }
    bool search(Node*& node, const T& value) { //recursive find
        if (node == NULL) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        if (value < node->data) {
            return search(node->left, value);
        }
        if (value > node->data) {
            return search(node->right, value);
        }
        else { return false; }
    }
    //****************************************************************

    //***************************** SIZE *****************************
    int size() const{
        return counter;
    }
    //****************************************************************


    //***************************** TO_STRING **********************
//    bool outLevel(Node* root, int level, stringstream& out) const
//    {
//        if (root == NULL) return false;
//        if (level == 1) {
//            out << " " << root->data;
//            if ((root->left != NULL) || (root->right != NULL)) return true;
//            return false;
//        }
//        if ((level == 2) && !root->left && root->right) out << " _";
//        bool left = outLevel(root->left, level - 1, out);
//        bool right = outLevel(root->right, level - 1, out);
//        if ((level == 2) && root->left && !root->right) out << " _";
//        return left || right;
//    } // end outLevel()

    /** Return a level order traversal of a BST as a string */
    virtual std::string toString() const {
        stringstream out;
        size_t index = 0;
        if (root == nullptr) {
            out << "empty";
            return out.str();
        }
        else {
            inOrder(index, root, out);
            return out.str().substr(0, out.str().size() - 1);
        }
    }
    void inOrder(size_t index, const Node* node, stringstream& out) const {
        if (node == nullptr) return;
        inOrder(index, node->left, out);
        ++index;
        out << node->data << ","; //(index < counter ? "" : ",");
        inOrder(index, node->right, out);
    }
//    virtual std::string toString() const {
//        return toStringInorder(root);
//    }
//    string toStringInorder(Node* root) {
//        stringstream out;
//        if (root == NULL) {
//            return "";
//        }
//
//        out << toStringInorder(root->left);
//        out << root->toString();
//        out << toStringInorder(root->right);
//        return out.str();
//    }
    //************************************************************************


};
#endif //INC_9_CS235_POKEMON_BST_H
