/*
 * SequenceMap.h
 *
 *  Created on: Sep 27, 2018
 *      Author: sky2464
 */

#ifndef SEQUENCEMAP_H_
#define SEQUENCEMAP_H_

class SequenceMap {
public:
	SequenceMap();
	virtual ~SequenceMap();


private:
	string recognition_sequence_ ;
	vector<string> enzyme_acronyms_;
};


#endif /* SEQUENCEMAP_H_ */
