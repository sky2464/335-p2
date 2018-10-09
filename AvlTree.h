#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

template<typename Comparable>
class AvlTree { // AvlTree class Throws UnderflowException as warranted
    public:
        AvlTree() : root { nullptr} {}
        AvlTree( const AvlTree & rhs ) : root {nullptr} {root = clone( rhs.root ); } // Copy constructor
        AvlTree & operator=( const AvlTree & rhs ) { // Deep copy assignment
            AvlTree copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        AvlTree( AvlTree && rhs ) : root{ rhs.root } {  rhs.root = nullptr; } // Move constructor
        AvlTree & operator=( AvlTree && rhs ) { //Move assignment
            std::swap( root, rhs.root );
            return *this;
        }
        ~AvlTree( ) { makeEmpty( ); }

        void printTree( ) const {   // Print the tree contents in sorted order.
            if( isEmpty( ) )    cout << "Empty tree" << endl;
            else    printTree( root );
        }

        bool isEmpty( ) const { return root == nullptr; } // Test if the tree is logically empty
        void makeEmpty( ) { makeEmpty( root );  } // Make the tree logically empty.

        // Insert x into the tree; duplicates are ignored.
        void insert( const Comparable & x ) { insert( x, root );    } // Constant comparable
        void insert( Comparable && x )  {   insert( std::move( x ), root ); }

        void remove( const Comparable & x ) { remove( x, root ); } // Remove x from the tree if x is found.

        bool contains( const Comparable & x ) const { return contains( x, root );   } // Returns true if x is found in the tree.

        const Comparable & findMin( ) const { // Return the smallest item in the tree. Throw UnderflowException if empty.
            if( isEmpty( ) )
                throw UnderflowException{ };
            return findMin( root )->element;
        }
        const Comparable & findMax( ) const { // Return the largest item in the tree. Throw UnderflowException if empty.
            if( isEmpty( ) )
                throw UnderflowException{ };
            return findMax( root )->element;
        }

        // Functions made for the assignment
        const Comparable getNode( const Comparable& n){ // Get nodes from root to n
            return getNodehelper( n, root );
        }

        int totalNodes(){ return getNodecount(root);    }
        double totalDepth(){ return gettotalDepth(root,0); }
        double find( const Comparable & x ) { return find( x, root, 0 ); }
        int removeCalls(){ return remove_Calls; }

    private:
        struct AvlNode{
            Comparable element;
            AvlNode *left, *right;
            int height;

            AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
            : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

            AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
            : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
        };
        AvlNode *root;
        int remove_Calls = 0;

        // Internal methods / Helper functions
        void printTree( AvlNode *t ) const { // Internal method to print a subtree rooted at t in sorted order.
            if( t != nullptr )  {
                printTree( t->left );
                cout << t->element << endl;
                printTree( t->right );
            }
        }

    void makeEmpty( AvlNode * & t ) { // Internal method to make subtree empty.
            if( t != nullptr )  {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = nullptr;
        }

    /* Insert/ Remove into/ from a subtree.
         * x is the item. * t is the node that roots the subtree.
         * Set the new root of the subtree. */
        void insert( const Comparable & x, AvlNode * & t )  { // Constant comparable
            if( t == nullptr )
                t = new AvlNode{ x, nullptr, nullptr };
            else if( x < t->element )
                insert( x, t->left );
            else if( t->element < x )
                insert( x, t->right );
            balance( t );
        }
        void insert( Comparable && x, AvlNode * & t ) {
            if( t == nullptr )
                t = new AvlNode{ std::move( x ), nullptr, nullptr };
            else if( x < t->element )
                insert( std::move( x ), t->left );
            else if( t->element < x )
                insert( std::move( x ), t->right );
            balance( t );
        }

        void remove( const Comparable & x, AvlNode * & t ) {
            remove_Calls++;
            if( t == nullptr ) return;   // Item not found; do nothing
            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != nullptr && t->right != nullptr ) { // Two children
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else    {
                AvlNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete oldNode;
            }
            balance( t );
        }

        /* Test if an item is in a subtree.
         * x is item to search for.
         * t is the node that roots the tree. */
        bool contains( const Comparable & x, AvlNode *t ) const {
            if( t == nullptr )
                return false;
            else if( x < t->element )
                return contains( x, t->left );
            else if( t->element < x )
                return contains( x, t->right );
            else
                return true;    // Match
        }
        /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, AvlNode *t ) const {
            while( t != nullptr )
                    if( x < t->element )
                            t = t->left;
                    else if( t->element < x )
                            t = t->right;
                    else
                            return true;    // Match

            return false;   // No match
      }
                 *****************************************************/

        AvlNode * clone( AvlNode *t ) const { // Internal method to clone subtree.
            if( t == nullptr )  return nullptr;
            else return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
        }

    AvlNode * findMin( AvlNode *t ) const {
            if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMin( t->left );
        }
        AvlNode * findMax( AvlNode *t ) const {
            if( t != nullptr )
                while( t->right != nullptr )    t = t->right;
            return t;
        }

        int height( AvlNode *t ) const {    return t == nullptr ? -1 : t->height; } // The height of node t or -1 if nullptr.
        int max( int lhs, int rhs ) const { return lhs > rhs ? lhs : rhs;   }

        // Avl manipulations
        static const int ALLOWED_IMBALANCE = 1;

        void balance( AvlNode * & t ) { // Assume t is balanced or within one of being balanced
            if( t == nullptr ){ return; }

            if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){
                if( height( t->left->left ) >= height( t->left->right ) ){
                    rotateWithLeftChild( t );
                }else{   doubleWithLeftChild( t ); }
            }
            else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ){
                if( height( t->right->right ) >= height( t->right->left ) ){
                    rotateWithRightChild( t );
                }else{ doubleWithRightChild( t ); }
            }
            t->height = max( height( t->left ), height( t->right ) ) + 1;
        }

        /**
         * Rotate binary tree node with left child.
         * For AVL trees, this is a single rotation for case 1.
         * Update heights, then set new root.
         */
        void rotateWithLeftChild( AvlNode * & k2 ) {
            AvlNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
            k1->height = max( height( k1->left ), k2->height ) + 1;
            k2 = k1;
        }

        /**
         * Rotate binary tree node with right child.
         * For AVL trees, this is a single rotation for case 4.
         * Update heights, then set new root.
         */
        void rotateWithRightChild( AvlNode * & k1 ) {
            AvlNode *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
            k2->height = max( height( k2->right ), k1->height ) + 1;
            k1 = k2;
        }

        /**
         * Double rotate binary tree node: first left child.
         * with its right child; then node k3 with new left child.
         * For AVL trees, this is a double rotation for case 2.
         * Update heights, then set new root.
         */
        void doubleWithLeftChild( AvlNode * & k3 ) {
            rotateWithRightChild( k3->left );
            rotateWithLeftChild( k3 );
        }

        /**
         * Double rotate binary tree node: first right child.
         * with its left child; then node k1 with new right child.
         * For AVL trees, this is a double rotation for case 3.
         * Update heights, then set new root.
         */
        void doubleWithRightChild( AvlNode * & k1 ) {
            rotateWithLeftChild( k1->right );
            rotateWithRightChild( k1 );
        }

        const Comparable getNodehelper( const Comparable& x, AvlNode* t ){ // Similar to contain() but returns Comparable
            if( t == nullptr ){ return Comparable(); }
            else if( x < t->element )
                return getNodehelper( x, t->left );
            else if( t->element < x )
                return getNodehelper( x, t->right );
            else{ return t->element; }
        }

        int getNodecount( AvlNode* t){
            if( t == nullptr ){ return 0; }
            else return (1 + getNodecount(t->left) + getNodecount(t->right));
        }

        double gettotalDepth( AvlNode* t, int counter){ // internal path length
            if( t == nullptr ){ return 0; }
            else return ( counter + ( gettotalDepth( ( t-> left),counter + 1) ) + gettotalDepth( ( t-> right),counter + 1) );
        }

        double find( const Comparable & x, AvlNode *t, int totalCalls ) {
            totalCalls++;
            if( t == nullptr )
                return 1;
            else if( x < t->element )
                return find( x, t->left, totalCalls );
            else if( t->element < x )
                return find( x, t->right, totalCalls );
            return totalCalls;    // Match
        }
};
#endif
