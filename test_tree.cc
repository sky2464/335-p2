// Salem Saboori
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
// You will have to add #include "SequenceMap.h"
#include "SequenceMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;



// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.

  namespace {
float recur; // total number of recursion calls
template <typename TreeType>
float SearchTree( TreeType& a_tree, const string seq_filename){ // Find() of part 4
  int match = 0; // Successful queries (number of strings found)
  recur = 0;
  ifstream line(seq_filename); // lines in seq_filename
  string input;

  while( getline( line, input) ){
    if( input.length() < 1 ){ continue; }

    SequenceMap query( input, "" ); // Query the sequence map

    //if( line.eof()){ cout<< "End of file \n";   break;    }
    recur += a_tree.find(query);
    if( a_tree.contains(query)){
      match++;
    }
  }
  cout<< "4a: "<< match << endl; // total number of successful queries (number of strings found).
  recur = recur/match; // Compute average number of recursion calls to return
  return recur;
}

template <typename TreeType>
float RemoveTree( TreeType& a_tree, const string seq_filename){ // Removes every other sequence in sequences.txt from the tree
  recur = 0;
  int removedStrings = 0;
  ifstream line(seq_filename); // lines in seq_filename
  string input;
  int count = 0;
  while( getline( line, input) ){
    if( input.length() < 1 ){ continue; }

    if( count % 2 == 0){
        SequenceMap query( input, "" ); // Query the sequence map
        if(a_tree.contains(query)){
          a_tree.remove(query);
          if(!a_tree.contains(query)){ removedStrings++; }
        }
    }
    count++;
  }
  recur += a_tree.removeCalls();
  cout<< "5a: "<< removedStrings << endl; // total number of removed queries
  recur = recur/removedStrings;
  return recur;
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  string db_line, input;
  ifstream in_stream(db_filename);
  int start = 10;
  while( start > 0 ){ getline(in_stream,db_line); // Get next line until line: AanI/TTA'TAA//
    start--;
  } // While loop to skip those 10 header lines on rebase.txt file

  // Parse the database into the tree like previous part
  while( getline( in_stream, db_line )){ // Get Next Line From DatabaseFile
    if( db_line.length() < 1 ){ continue; }
    string an_enz_acro, a_reco_seq;

    stringstream currentEnz(db_line);
    getline( currentEnz, an_enz_acro, '/' ); // first part of the string for an_enz_acronym

    while( getline( currentEnz, a_reco_seq, '/') ){
      if( a_reco_seq.length() > 0 ){
          SequenceMap new_SeqMap( a_reco_seq, an_enz_acro );
          a_tree.insert(new_SeqMap);
      }
    }
  }

  // Output of part 2b - Recursive ones are done/printed in function calls

  int n = a_tree.totalNodes();
  cout<< "2: "<< n << endl; //int

  float avgDepth = a_tree.totalDepth()/n;
  cout<< "3a: "<< avgDepth  << endl;  // float

  float l = std::log2f(n); // return log base 2, n = 565
  l = avgDepth/ l;
  cout<< "3b: "<< l << endl; // float

  float s = SearchTree( a_tree, seq_filename ); // Returns average number of recursive calls, prints 4a
  cout<< "4b:" << s << endl; // float

  // the total number successful removes.

  s = RemoveTree( a_tree, seq_filename ); // Returns average number of recursive calls, prints 5a
  cout<< "5b:" << s << endl; // float

  // Part 6 (basically after remove(), it recomputes the variables done in steps 2 & 3)

  n = a_tree.totalNodes();
    cout<< "6a: "<< n << endl; //int

  avgDepth = a_tree.totalDepth()/n;
    cout<< "6b: "<< avgDepth  << endl;  // float

    l = std::log2f(n); // return log base 2, n2 = 404
    l = avgDepth/ l;
  cout<< "6c: "<< l << endl; // float
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
