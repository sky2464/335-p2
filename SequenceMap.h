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


  private:
	string recognition_sequence_ ;
	vector<string> enzyme_acronyms_;
};


#endif /* SEQUENCEMAP_H_ */
