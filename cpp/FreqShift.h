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


	template<typename T, typename U, typename V>
	void dotmultiply(vector<T> &in1, vector<U> &in2, vector<V> &d)
	{
		typedef typename Calc<T, U>::output_type typeIneed;
		vector<typeIneed> *castedData = (vector<typeIneed>*)&d;
		castedData->resize(in1.size());
		for(unsigned int i=0;i<castedData->size();i++)
		{
			Calc<T, U> math(in1[i], in2[i]);
			(*castedData)[i] = math.multiply();
		}
	}

};

#endif // FREQSHIFT_IMPL_H
