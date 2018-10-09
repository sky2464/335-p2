// Salem Saboori
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
// You will have to add #include "SequenceMap.h"
#include "SequenceMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
    // Code for running Part2(a)
    ifstream in_stream(db_filename);
    //Tree<SequenceMap> a_tree;
    string db_line = "";
    if (!in_stream.is_open()) {
        exit(EXIT_FAILURE);
    }
    // ELSE Read the file line -by - line:
    //Skip the first 10 lines!
    int topOfTheFile = 0;

    while (topOfTheFile < 10) {
        getline(in_stream, db_line);
        topOfTheFile++;
    }
    //data parser
    while (getline(in_stream, db_line)) {
        // Get the first part of the line:
        // If program read a bad line ignore it.
        if (db_line.length() < 1) { continue;}
        stringstream currentEnz(db_line);
        string an_enz_acro = "";
        string a_reco_seq = "";
        // GetEnzymeAcronym(db_line);
        // an_enz_acro are before the '/'
        getline(currentEnz, an_enz_acro, '/');

        // while  (GetNextRegocnitionSequence(db_line, a_rego_seq) {

        //Getting the next recognize sequences to insert in tree
        while (getline(currentEnz, a_reco_seq, '/')) {

            if ( a_reco_seq.length() > 0 ) { // Reach to the "/ or //"
                //SequenceMap new_sequence_map (a_reco_seq, an_enz_acro);
                SequenceMap new_seqMap( a_reco_seq, an_enz_acro ); // Create a new sequence map to insert in Tree
                a_tree.insert(new_seqMap);
            }

        }
    }

    // End second while.

    // End first while.
    string input = "";
    while ( input != "Q" ) {
        cout << "\nGet a recognition sequence to query: ";
        cin >> input;
        if ( input ==  "Q" ) { break; }

        SequenceMap query( input, "" ); // Query the sequence map

        if ( (a_tree.contains(query)) ) {

            cout << a_tree.getNode(query) << endl;
        } // only prints one acronym, needs iterator
        else { // print all the corresponding enzyme_acronyms from that recognition sequence.
            cout << "Not Found! \n";
            break;
        }
    }

}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
        return 0;
    }
    const string db_filename(argv[1]);
    const string param_tree(argv[2]);
    cout << "Input filename is " << db_filename << endl;
    cout << "Type of tree is " << param_tree << endl;
    if (param_tree == "BST") {

        BinarySearchTree<SequenceMap> a_tree;
        // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>

        QueryTree(db_filename, a_tree);
    } else if (param_tree == "AVL") {
        // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
        AvlTree<SequenceMap> a_tree;
        QueryTree(db_filename, a_tree);
    } else {
        cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
    }
    return 0;
}
