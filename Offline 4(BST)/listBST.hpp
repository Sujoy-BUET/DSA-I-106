#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include<string>
#include <stdexcept>
using namespace std;

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    Node *parent(Node *nd){
        if(nd==nullptr || nd==root) return nullptr;
        Node *temp = root,*prev=nullptr;
        while(temp!=nd){
            prev= temp;
            if(nd->key < temp->key){
                temp = temp->left;
            }else{
                temp = temp->right;
            }
        } 
        return prev;
    }

    Node *find_key_node(Key key,Node *temp=nullptr) const{
        if(temp==nullptr) temp=root;
        while(temp!=nullptr){
            if(temp->key==key) return temp;
            else if(key<temp->key) temp = temp->left;
            else temp = temp->right;
        }
        return nullptr;
    }

    void print_inorder(Node *t)const{
        if(t!=nullptr){
            print_inorder(t->left);
            cout << "(" << t->key << ':' << t->value << ") ";
            print_inorder(t->right);
        }
        
    }
    
    void print_default(Node *t)const{
        if(t!=nullptr){
            cout << " (" << t->key << ':' << t->value;
            if(t->left==nullptr && t->right!=nullptr) cout << " ()";
            else print_default(t->left);
            print_default(t->right);
            cout << ")";
        } 
    }

    void print_preorder(Node *t)const{
        if(t!=nullptr){
            cout << "(" << t->key << ':' << t->value << ") ";
            print_preorder(t->left);
            print_preorder(t->right);
        }
    }
    void print_postorder(Node *t)const{
        
        if(t!=nullptr){
            print_postorder(t->left);
            print_postorder(t->right);
            cout << "(" << t->key << ':' << t->value << ") ";    
        }
        
    }
    void transplant(Node *a,Node *b){
        if(a==root){
            root = b;
            return;
        } 
        Node *u = parent(a);
        if(u->left==a) u->left = b;
        else u->right = b;
    }
    Node *find_min_node(Node *rt){
        while(rt->left!=nullptr){
            rt=rt->left;
        }
        return rt;
    }
    void private_clear(Node *t){
        if(t!=nullptr){
            private_clear(t->left);
            private_clear(t->right);
        }
        delete t;
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        // TODO: Implement destructor to free memory
        private_clear(root);
    }   
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic
        Node *t = find_key_node(key);
        if(t!=nullptr) return false;
        Node *n = new Node(key,value);
        Node *temp = root,*prev = nullptr;
        while(temp!=nullptr){
            prev = temp;
            if(key<temp->key) temp = temp->left;
            else temp = temp->right;
        }
        if(prev==nullptr){
            root = n;
            node_count++;
            return true;
        }
        if(key<prev->key){
            prev->left = n;
        }else{
            prev->right = n;
        }
        node_count++;
        return true;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override {
        // TODO: Implement removal logic
        Node *t = find_key_node(key);
        if(t==nullptr) return false;
        if(t->left==nullptr) transplant(t,t->right);
        else if(t->right==nullptr) transplant(t,t->left);
        else{
            Node *s = find_min_node(t->right);
            if(s!=t->right){
                transplant(s,s->right);
                s->right = t->right;

            }
            transplant(t,s);
            s->left = t->left; 
        }
        delete t;
        node_count--;
        return true;
    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        // TODO: Implement find logic
        if(find_key_node(key)==nullptr) return false;
        else return true;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        // TODO: Implement get logic
        Node *t = find_key_node(key);
        if(t==nullptr) throw runtime_error("Key not found");
        return t->value;
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        // TODO: Implement update logic
        Node *t = find_key_node(key);
        if(t==nullptr){
            // handle
        }else{
            t->value = value;
        }
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic
        private_clear(root);
        root = nullptr;
        node_count = 0;
    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic
        return node_count;
    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic
        return (node_count==0);
    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic
        if(empty()) throw runtime_error("BST is empty");
        Node *t = root;
        while(t->left!=nullptr){
            t = t->left;
        }
        return t->key;
    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic
        if(empty()) throw runtime_error("BST is empty");
        Node *t = root;
        while(t->right!=nullptr){
            t = t->right;
        }
        return t->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        // TODO: Implement print logic
        if(traversal_type=='D' || traversal_type=='d'){
            cout << "BST (Default):";
            print_default(root);
            cout << '\n';
        }else if(traversal_type=='I' || traversal_type=='i'){
            cout << "BST (In-order): ";
            print_inorder(root);
            cout << '\n';
        }else if(traversal_type=='P' || traversal_type=='p'){
            cout << "BST (Pre-order): ";
            print_preorder(root);
            cout << '\n';
        }else if(traversal_type=='O' || traversal_type=='o'){
            cout << "BST (Post-order): ";
            print_postorder(root);
            cout << '\n';
        }
    }
};

#endif // LISTBST_H