/*
 * SequenceMap.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Salem Saboori
 */

#ifndef SEQUENCEMAP_H_
#define SEQUENCEMAP_H_

#include <vector>
using namespace std;


class SequenceMap {
  public:
  	SequenceMap() =default;
	SequenceMap(const SequenceMap & )= default; //Copy Constractur
	SequenceMap(SequenceMap && )= default; //Move Constractur
	SequenceMap & operator =(const SequenceMap & )= default; //Copy assignment operator
	SequenceMap & operator =(SequenceMap && )= default; //Move assignment operator
	~SequenceMap() = default; // Destractur

	SequenceMap(const string &a_rec_seq, const string &an_enz_acro){ // Constructor to access private member
		enzyme_acronyms_.push_back(an_enz_acro); // Vector enzyme_acronyms_ get an_enz_acro data
		recognition_sequence_ = a_rec_seq; // manipulate private data
	}

	bool operator<(const SequenceMap &rhs) const{this-> recognition_sequence_ < rhs.SequenceMap};


  private:
	string recognition_sequence_ ;
	vector<string> enzyme_acronyms_;
};


#endif /* SEQUENCEMAP_H_ */
