/**
* Copyright (C) 2015 Axios, Inc.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FREQSHIFT_IMPL_H
#define FREQSHIFT_IMPL_H
#define COMPLEX tmp->SRI.mode

#include "FreqShift_base.h"
#include <string>
#include <map>
using std::vector;
using std::complex;
using std::cout;
using std::endl;
using std::transform;
using std::multiplies;
using std::map;
using std::string;

class FreqShift_i : public FreqShift_base
{
	ENABLE_LOGGING
public:
	FreqShift_i(const char *uuid, const char *label);
	~FreqShift_i();
	int serviceFunction();


private:
	vector<float> shiftedSignal;
	bool firstTime;	//indicates whether or not current iteration of the service function is the first
	complex<float> * phasor;
	map<string, complex<float> > phasor_map;

	//Function passes three vectors (two input vectors (in1 and in2) and one output vector (d))
	//and computes the product of the corresponding elements of in1 and in2. Template allows
	//compatibility with multiple data types
	template<typename T>
	void vectormultiply(vector<T> &in1, vector<complex<float> > &in2, vector<float> &out)
	{
		vector<complex<float> > *outputcx = (vector<complex<float> > *)&out;

		if(in1.size() < in2.size())
			in2.resize(in1.size());
		else if(in2.size() < in1.size())
			in1.resize(in2.size());

		outputcx->resize(in1.size());

		transform(in1.begin(), in1.end(), in2.begin(), outputcx->begin(), std::multiplies<complex<float> >());
	}

};

#endif // FREQSHIFT_IMPL_H
