/*
 * SequenceMap.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Salem Saboori
 */

#ifndef SEQUENCEMAP_H_
#define SEQUENCEMAP_H_

#include<iostream>
#include <vector>
using namespace std;


class SequenceMap {
  public:
	SequenceMap() = default;
	SequenceMap(const SequenceMap & ) = default; //Copy Constractur
	SequenceMap(SequenceMap && ) = default; //Move Constractur
	SequenceMap & operator =(const SequenceMap & ) = default; //Copy assignment operator
	SequenceMap & operator =(SequenceMap && ) = default; //Move assignment operator
	~SequenceMap() = default; // Destractur

	SequenceMap(const string &a_rec_seq, const string &an_enz_acro) { // Constructor to access private member
		enzyme_acronyms_.push_back(an_enz_acro); // Vector enzyme_acronyms_ get an_enz_acro data
		recognition_sequence_ = a_rec_seq; // manipulate private data
	}
	friend ostream &operator <<(ostream &output, const SequenceMap &a_map) {}

	    bool operator<( const SequenceMap &rhs ) const{ return (this->recognition_sequence_ < rhs.recognition_sequence_); }

    friend ostream &operator<<( std::ostream &out, const SequenceMap &a_map ) {
      if( a_map.enzyme_acronyms_.empty() ){ abort(); }
      else{
    	    for( string it : a_map.enzyme_acronyms_ ){ // no const
    		    out<< it << " ";
    	    	}
      }
      return out;
    }
void Merge( const SequenceMap &other_sequence ){
      if( recognition_sequence_ == other_sequence.recognition_sequence_ ){ // Merge() will only be called in case of duplicates
			for( const auto& it : enzyme_acronyms_ ){
				if( it == other_sequence.enzyme_acronyms_[0] ){ // Check if the acronym already exist in *this
					return; // no need to Merge
				}
			}// Else merge the other_sequence.enzyme_acronym_ with the object’s enzyme_acronym_
      	enzyme_acronyms_.push_back( other_sequence.enzyme_acronyms_[0] );
      }
    }









  private:
	string recognition_sequence_ ;
	vector<string> enzyme_acronyms_;
};


#endif /* SEQUENCEMAP_H_ */
