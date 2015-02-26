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

#include "FreqShift_base.h"
using std::vector;
using std::complex;
using std::cout;
using std::endl;

#include "Calc.h"

class FreqShift_i : public FreqShift_base
{
	ENABLE_LOGGING
public:
	FreqShift_i(const char *uuid, const char *label);
	~FreqShift_i();
	int serviceFunction();


private:
	double sampleRate;
	vector<float> data;
	bool firstTime;	//indicates whether or not current iteration of the service function is the first

	//Function passes three vectors (two input vectors (in1 and in2) and one output vector (d))
	//and computes the product of the corresponding elements of in1 and in2. Template allows
	//compatibility with multiple data types
	template<typename T, typename U, typename V>
	void vectormultiply(vector<T> &in1, vector<U> &in2, vector<V> &out)
	{
		typedef typename Calc<T, U>::output_type typeIneed;
		vector<typeIneed> *castedData = (vector<typeIneed>*)&out;
		castedData->resize(in1.size());
		for(unsigned int i=0;i<castedData->size();i++)
		{
			Calc<T, U> math(in1[i], in2[i]);
			(*castedData)[i] = math.multiply();
		}
	}

};

#endif // FREQSHIFT_IMPL_H
