// simple binary tree search
#pragma once
#include <ostream>
#include <cstdio>
#include <cstddef>
#include <cassert>
#include <algorithm>

template <typename K>
struct node {
	K data;
	node<K>* left;
	node<K>* right;
	node(K d=K(), node* l = NULL, node* r = NULL ): data(d), left(l), right(r){}
};

template <typename K>
class tree {
public:
	tree();
	tree(const tree<K>& T);
	tree<K>& operator=(tree<K> T);
	~tree();

	bool search(K x) const;
	void insert(K x);
	void remove(K x);
	void clear(); // remove all elements

	K max() const; // maximal value
	K min() const; // minimal value
	size_t size() const; // total number of nodes
	size_t height() const; // longest path from root
	size_t leaves() const; // returns number of leave nodes
    
    /* NOTE: we include a function that returns the location of the root node, but we do so "by value" and furthermore we make the pointee const. Hence without really going out of one's way, the state of the tree should not be easily modified via non-memember functions ( none of the internal pointers can be changed ). However one can still do something ridiculous like calling delete on one of the nodes .
     * NOTE: however that such thing is present in the STL as well.
     */

	node<K>* const rootptr() const;
    
    /* Our main application for this feature is that it allows us to draw the tree in a variety of formats (see main.cpp). Its not clear how useful this is in general for BST, but i hope you find it to have educational value.
     */
    void printPreorder();
    void printInorder();
    void printPostorder();

private:
	node<K>* root;
};


/* You cannot split this fill into a cpp and a header filer because of the template usage in the declaration of the prototypes. So definitions of the prototypes have to be in the same file as the prototypes.
 */

#define TK template <typename K>
//using TK allows us to avoid typing out the template parameter for every function

TK void insert(node<K>*& n, K x){
    if ( n == NULL ){
        n = new node<K>; // n = new node(x);
        n->data = x;
        return;
    }
    if ( x > n->data ){
        insert( n->right, x );
    }
    else if ( x < n->data ){
        insert( n->left, x );
    }
}

TK bool search(const node<K>* const& n, K x){
    /* checks whether node data is equal to x or whether node is null. If neither is satisfied, it proceeds to check left and right leaves.
     */
    bool temp;
    if ( n == NULL ){
        return false;
    }
    else if ( x == n->data ){
        return true;
    }
    else if ( x > n->data ){
        temp = search( n->right, x );
    }
    else if ( x < n->data ){
        temp = search( n->left, x );
            
    }
    return temp;
}


TK void remove(node<K>*& n, K x){
    if ( n == NULL ) return; // base case
    if ( x < n->data ){ // searches left sub-tree
        remove( n->left, x );
    }
    else if ( x > n->data ){ // searches right sub-tree
        remove( n->right, x );
    }
    // this is reached once we have found the node we want to remove
    // depending on the level of the node, we will implement different techniques
    else {
        if ( n->left == NULL && n->right == NULL ){ // leaf node
            delete n;
            n = NULL;
        }
        else if ( n->left == NULL ){ // one leaf node attached
            node<K>* temp_node = n;
            n = n->right;
            delete temp_node;
        }
        else if ( n->right == NULL ){ // one leaf mode attached
            node<K>* temp_node = n;
            n = n->left;
            delete temp_node;
        }
        else { // 2 leaves attached -> plan is to simplify case into a simpler case
            // task is to replace node to be deleted with successor!
            node<K>* v = n->right; // assigns v with right leaf of root
            //You then go all the way left in the right sub tree until you come across n->left == NULL//
            
            while ( v->left ){ // while v has a left pointer, traverse left!
                v = v->left;
            }
            // after reaching the left most node, assign value to node designated node for deletion.
            /* instead of deleting the node marked for deletion, which is a parent of 2 leaves, we instead
               shift the focus to its successor. If the successor is also a parent node, which will never
               the case the function will also act recursively and break it down into one of the simpler
               steps.
             */
            n->data = v->data;
            remove( n->right, v->data);
        }
    }
}

// These tree member functions will just hand off to the above functions acting on the nodes
TK void tree<K>::insert(K x){
    ::insert(this->root, x);
}

TK bool tree<K>::search(K x) const {
    return::search(this->root, x);
}

TK void tree<K>::remove(K x){
    ::remove(this->root, x);
}
// ----------------------------------- //

// "function pointer" type for things that operate on nodes
template <typename K>
using nodeProcFunc = void (*)(node<K>*& n, void* pParams);
/* NOTE: the above says that any function which accepts a node<K>* by reference
    and returns void counts as a "nodeProcFunc". Before, we did this typedef statement
    but thats no longer possible once templates are involved.
 */
// version for const input:
template <typename K>
using c_nodeProcFunc = void (*)(const node<K>* const& n, void* pParams);

//----------------------tree traversal functions --------------------------------//
TK void preorder(node<K>*& n, nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    f(n, pParams);
    preorder(n->left, f, pParams);
    preorder(n->right, f, pParams);
}

TK void inorder(node<K>*& n, nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    inorder(n->left, f, pParams);
    f(n, pParams);
    inorder(n->right, f, pParams);
}

TK void postorder(node<K>*& n, nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    postorder(n->left, f, pParams);
    postorder(n->right, f, pParams);
    f( n, pParams);
}

//---------------------same as the above functions but constant-------------------------//
TK void preorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    f(n, pParams);
    preorder(n->left, f, pParams);
    preorder(n->right, f, pParams);
}

TK void inorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    inorder(n->left, f, pParams);
    f(n, pParams);
    inorder(n->right, f, pParams);
}

TK void postorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams){
    if ( n == NULL ) return;
    postorder(n->left, f, pParams);
    postorder(n->right, f, pParams);
    f( n, pParams);
}

//----------------------- clear(), destructor -------------------------------//

TK void DeleteNode(node<K>*& n, void*){
    assert( n != NULL );
    delete n;
    n = NULL;
}

TK tree<K>::~tree(){
    postorder( this->root, &DeleteNode, (void*)0 );
}

TK void tree<K>::clear(){
    node<K>*& temp = this->root;
    printf("Hello\n");
    postorder( this->root, &DeleteNode, (void*)0 );
    
    this->root = temp;
    delete temp;
}

//----------------------- constructor, assigment -------------------------------//
//constructor
TK tree<K>::tree(){
    this->root = NULL;
}

//copy constructor-------------------------------------------------------------//
TK node<K>* copy_subtree( const node<K>* const& s ){
    if ( s == NULL ) return NULL;
    
    node<K>* c_node = new node<K>; // creates new node
    c_node->data = s->data; // assigns new node with copy of data
    
    c_node->left = copy_subtree(s->left); // applies copy_subtree to left node if there is one
    c_node->right = copy_subtree(s->right); // applies copy_subtree to right node of there is on
    // if leaves are empty then left and right pointers are set to NULL
    return c_node;
}
// copying data from T and set it to the root
TK tree<K>::tree(const tree<K>& T){
    this->root = copy_subtree( T.root );// sets this->root equal to a copy of the tree T....
}
//------------------------------------------------------------------------------//

TK tree<K>& tree<K>::operator=(tree<K> T){
    this->root->data = T.root->data;
    std::swap( this->root->left, T.root->left );
    std::swap( this->root->right, T.root->right );
    return *this;
}

TK size_t size_of_subtree(const node<K>* const& n){
    if ( n == NULL ){
        return 0;
    }
    else if ( n->right == NULL && n->left == NULL ){
        return 1;
    }
    else if ( n->right == NULL ){
        return size_of_subtree( n->left ) + 1;
    }
    else if ( n->left == NULL ){
        return size_of_subtree( n->right ) + 1;
    }
    else {
        return size_of_subtree( n->right ) + size_of_subtree( n->left ) + 1;
    }
}

TK size_t tree<K>::size() const{
    return size_of_subtree( this->root );
}

TK size_t leaf_count ( const node<K>* const& n ){
    
    if ( n->right == NULL && n->left == NULL ){
        return 1;
    }
    else if ( n->right == NULL ){
        return leaf_count( n->left );
    }
    else if ( n->left == NULL ){
        return leaf_count( n->right );
    }
    else {
        return leaf_count( n->left ) + leaf_count( n->right );
    }
}

TK size_t tree<K>::leaves() const{
    if ( this->root == NULL ){
        return 0;
    }
    
    return leaf_count( this->root );
}

TK size_t piece_height( const node<K>* const& n ){
    
    if ( n->left == NULL && n->right == NULL ){
        return 0;
    }
    else if ( n->left == NULL ){
        return 1 + piece_height( n->right );
    }
    else if ( n->right == NULL ){
        
        return 1 + piece_height( n->left );
    }
    else {
        if ( piece_height( n->right ) > piece_height( n->left ) ){
            return 1 + piece_height ( n->right );
        }
        else if ( piece_height( n->left ) > piece_height( n->right ) ){
            return 1 + piece_height ( n->left );
        }
        else {
            return 1 + piece_height ( n->left );
        }
    }
}

TK size_t tree<K>::height() const{
    if ( this->root == NULL ){
        return -1;
    }
    size_t max_height = piece_height( this->root );
    
    return max_height;
}

TK K tree<K>::min() const{
    assert(this->root != NULL);
    node<K>* temp = this->root;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    return temp->data;
}

TK K tree<K>::max() const{
    assert(this->root != NULL);
    node<K>* temp = this->root;
    
    while ( temp->right != NULL ){
        temp = temp->right;
    }
    return temp->data;
}

TK node<K>* const tree<K>::rootptr() const{
    return this->root;
}

TK void printNode( node<K>*& n, void* fmt ){
    std::cout << n->data << "\n";
}

TK void tree<K>::printPreorder(){
    preorder(this->root,&printNode,(void*)"%i ");
}

TK void tree<K>::printInorder(){
    inorder(this->root,&printNode,(void*)"%i ");
}

TK void tree<K>::printPostorder(){
    postorder(this->root,&printNode,(void*)"%i ");
}

