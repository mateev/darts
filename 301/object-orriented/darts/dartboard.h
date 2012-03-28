#ifndef DARTBOARD_H
#define DARTBOARD_H

#include "dartsCore.h"

class Dartboard
{
public:
	Dartboard() {}			//	Default constructor
	int HitTarget(int,int);	//	This handles hitting a target on the board
};

#endif