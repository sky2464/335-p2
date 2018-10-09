#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

template <typename Comparable>
class BinarySearchTree { // BinarySearchTree class Throws UnderflowException as warranted
    public:
        BinarySearchTree( ) : root{ nullptr } {  } // Zero parameter constructor
        BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr } { root = clone( rhs.root ); } // Copy constructor
        BinarySearchTree & operator=( const BinarySearchTree & rhs ) { // Copy assignment
            BinarySearchTree copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root } { rhs.root = nullptr; } // Move constructor
        BinarySearchTree & operator=( BinarySearchTree && rhs ) { // Move assignment
            std::swap( root, rhs.root );
            return *this;
        }
        ~BinarySearchTree( ) { makeEmpty( ); }

        void printTree( ostream & out = cout ) const { // Print the tree contents in sorted order.
            if( isEmpty( ) ) out << "Empty tree" << endl;
            else printTree( root, out );
        }

        bool isEmpty( ) const { return root == nullptr;  } // Test if the tree is logically empty.
        void makeEmpty( ) { makeEmpty( root );  } // Make the tree logically empty.

        // Insert x into the tree; duplicates are ignored.
        void insert( const Comparable & x ) { insert( x, root );    } // Constant comparable
        void insert( Comparable && x )  {   insert( std::move( x ), root ); }

        void remove( const Comparable & x ) { remove( x, root ); } // Remove x from the tree if x is found.

        bool contains( const Comparable & x ) const { return contains( x, root );   } // Returns true if x is found in the tree.

        const Comparable & findMin( ) const { // Return the node containing the smallest item in the tree. Throw UnderflowException if empty.
            if( isEmpty( ) )
                throw UnderflowException{ };
            return findMin( root )->element;
        }
        const Comparable & findMax( ) const { // Return the node containing the largest item in the tree. Throw UnderflowException if empty.
            if( isEmpty( ) )
                throw UnderflowException{ };
            return findMax( root )->element;
        }

// Functions made for the assignment
        const Comparable getNode( const Comparable& n){ return getNodehelper( n, root ); }// Get nodes from root to n

    int totalNodes(){ return getNodecount(root); } // 2b - part 2
    double totalDepth(){ return gettotalDepth( root,0 ); }
        double find( const Comparable & x ) { return find( x, root, 0 ); }
        int removeCalls(){ return remove_Calls; }

    private:
        struct BinaryNode {
            Comparable element;
            BinaryNode *left, *right;

            BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ theElement }, left{ lt }, right{ rt } { }

            BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
        };
        BinaryNode *root;
        int remove_Calls = 0;

        // Internal methods / Helper functions
        void printTree( BinaryNode *t, ostream & out ) const    { // Print a subtree rooted at t in sorted order.
            if( t != nullptr )  {
                printTree( t->left, out );
                out << t->element << endl;
                printTree( t->right, out );
            }
        }

        void makeEmpty( BinaryNode * & t ) { // Make subtree empty.
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

        void insert( const Comparable & x, BinaryNode * & t ) { // Constant comparable x
            if( t == nullptr )
                t = new BinaryNode{ x, nullptr, nullptr };
            else if( x < t->element )
                insert( x, t->left );
            else if( t->element < x )
                insert( x, t->right );
            else ;  // Duplicate; do nothing
        }
        void insert( Comparable && x, BinaryNode * & t ) {
            if( t == nullptr )
                t = new BinaryNode{ std::move( x ), nullptr, nullptr };
            else if( x < t->element )
                insert( std::move( x ), t->left );
            else if( t->element < x )
                insert( std::move( x ), t->right );
            else ;  // Duplicate; do nothing
        }

        void remove( const Comparable & x, BinaryNode * & t ) {
            remove_Calls++;
            if( t == nullptr )
                return;   // Item not found; do nothing
            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != nullptr && t->right != nullptr ) // Two children
                    {
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
                    }
            else
            {
                BinaryNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete oldNode;
            }
        }

        /* Test if an item is in a subtree.
         * x is item to search for. * t is the node that roots the subtree. */
        bool contains( const Comparable & x, BinaryNode *t ) const {
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
    bool contains( const Comparable & x, BinaryNode *t ) const {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else return true;    // Match

            return false;   // No match
    }
         *****************************************************/

        BinaryNode * clone( BinaryNode *t ) const { // Clone subtree.
            if( t == nullptr ) return nullptr;
            else return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
        }

        BinaryNode * findMin( BinaryNode *t ) const {
            if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMin( t->left );
        }
        BinaryNode * findMax( BinaryNode *t ) const {
            if( t != nullptr )
                while( t->right != nullptr )
                    t = t->right;
            return t;
        }

        const Comparable getNodehelper( const Comparable& x, BinaryNode* t ){ // Similar to contain() but returns Comparable
            if( t == nullptr ){ return Comparable(); }
            else if( x < t->element )
                return getNodehelper( x, t->left );
            else if( t->element < x )
                return getNodehelper( x, t->right );
            else{ return t->element; }
        }

        int getNodecount( BinaryNode* t){
            if( t == nullptr ){ return 0; }
            else return (1 + getNodecount(t->left) + getNodecount(t->right));
        }

        double gettotalDepth( BinaryNode* t, int counter){ // internal path length
            if( t == nullptr ){ return 0; }
            else return ( counter + ( gettotalDepth( ( t-> left),counter + 1) ) + gettotalDepth( ( t-> right),counter + 1) );
        }

        double find( const Comparable & x, BinaryNode *t, int totalCalls ) { // same as contain() but non const
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
