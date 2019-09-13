#ifndef RNUMGEN_H
#define RNUMGEN_H

#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<numeric>
#include<algorithm>

using namespace std;

class rnumgen
{
	public:
		rnumgen(const vector<int> &);
		int rand() const;

	private:
		vector<float> F;
};

#endif
