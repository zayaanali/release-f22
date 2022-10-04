/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* & findNode = find(root, key);
    return findNode->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    /*if(subtree==NULL){
        return subtree;
    }*/
        
    
    if(subtree->key == key) return subtree;

    if(key<subtree->key) {
        if(subtree->left == NULL) return subtree;
        return find(subtree->left, key);
    }
    else {
        if(subtree->right==NULL) return subtree;
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    if (root==NULL) { root = new Node(key, value); return; }
    insert(root,key,value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
     Node *findNode = find(root,key);

    if(findNode->key == key) return;

    if(findNode->key > key) { findNode->left = new Node(key, value); }
            
    else { findNode->right = new Node(key, value); }

    return;
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    K tempKey = first->key;
    V tempVal = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = tempKey;
    second->value = tempVal;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::findIOP(Node* & subtree)
{
    if(subtree==NULL) return subtree;
    if(subtree->right == NULL) return subtree;
    
    return findIOP(subtree->right);
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::findParent(Node* & subtree, const K& key)
{
    // your code here
    if((subtree->left)->key == key|| (subtree->right)->key == key) return subtree;

    if(key<subtree->key){
    
        if(subtree->left == NULL) return subtree;
        return findParent(subtree->left, key);
    } else{
        if(subtree->right ==NULL) return subtree;
        return findParent(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root,key);
    return;
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    Node *& findNode = find(root,key);
    if(findNode->key != key) return;

    if (findNode->left==NULL && findNode->right == NULL){ 
        delete findNode;
        findNode = NULL;
        return;
    } else {
        if(findNode->left==NULL && findNode->right != NULL) {
            Node * RIGHT = findNode->right; 
            delete findNode;
            findNode = RIGHT;
            return;
        } else {
            Node *& IOP = findIOP(findNode->left);
            swap(findNode, IOP);
            Node* temp = IOP->left;
            while(temp !=NULL){
                IOP = findIOP(temp);
                swap(temp, IOP);
                temp= temp->left;
            }
            delete IOP; 
            IOP=NULL;
            return;
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST <K, V> tree;
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> newVector;
    return newVector;
}