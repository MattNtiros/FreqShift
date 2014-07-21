/*
 * Calc.h
 *
 *  Created on: Jun 17, 2014
 *      Author: ylr
 */

#ifndef CALC_H_
#define CALC_H_

#include <complex>
#include <math.h>

using std::complex;

template<typename T, typename U>
struct calc_type
{
	typedef std::string type;
};
template<typename T>
struct calc_type<T, complex<T> >
{
	typedef complex<T> type;
};
template<typename T>
struct calc_type<complex<T>, T>
{
	typedef complex<T> type;
};
template<typename T>
struct calc_type<T, T>
{
	typedef T type;
};



template<class T, class U>
class Calc
{
public:
	typedef typename calc_type<T, U>::type output_type;
private:
	T *value1;
	U *value2;
public:
	Calc()
	{
		value1 = NULL;
		value2 = NULL;
	}
	Calc(T &val1, U &val2)
	{
		value1 = &val1;
		value2 = &val2;
	}

	output_type add()
	{
		return *value1 + *value2;
	}
	output_type subtract()
	{
		return *value1 - *value2;
	}
	output_type multiply()
	{
		return *value1 * *value2;
	}
	output_type divide()
	{
		return *value1 / *value2;
	}
	output_type power()
	{
		return pow(*value1, *value2);
	}
};

#endif /* CALC_H_ */
