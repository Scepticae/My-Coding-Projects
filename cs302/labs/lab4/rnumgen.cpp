#include<iostream>

#include "rnumgen.h"

rnumgen::rnumgen(const vector<int> &v)
{
	F.resize(v.size());
	partial_sum(v.begin(), v.end(), F.begin());
	transform(F.begin(), F.end(), F.begin(), 
			bind2nd(divides<float>(), *(F.end() - 1)));
}

int rnumgen::rand()const
{
	const float randnorm = RAND_MAX + 1.0f;
	const float p = (float)std::rand() / randnorm;
	return upper_bound(F.begin(), F.end(), p) - F.begin();
}

