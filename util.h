#pragma once
#include <string>
#include <cmath>
#include <set>
#include <vector>
#define PI 3.141592653589793
#define HALF_LOG_TWO_PI 0.91893853320467267
#define EARTH_RADIUS 6378137.0
#define EULER_MASCHERONI -0.5772156649015328606065121
const double DIGAMMA_COEF_1 = 1 / 12;
const double DIGAMMA_COEF_2 = 1 / 120;
const double DIGAMMA_COEF_3 = 1 / 252;
const double DIGAMMA_COEF_4 = 1 / 240;
const double DIGAMMA_COEF_5 = 1 / 132;
const double DIGAMMA_COEF_6 = 691 / 32760;
const double DIGAMMA_COEF_7 = 1 / 12;
const double DIGAMMA_COEF_8 = 3617 / 8160;
const double DIGAMMA_COEF_9 = 43867 / 14364;
const double DIGAMMA_COEF_10 = 174611 / 6600;
#define DIGAMMA_LARGE 9.5
#define DIGAMMA_SMALL .000001

typedef std::pair<double, double> pdd;
typedef std::pair<int, int> pii;
typedef std::pair<double, int> pdi;
typedef std::pair<pdi, int> pdi_i;
typedef std::set<int> i_set;
typedef std::pair<double, i_set> outlier;
typedef std::set<pdi_i> pdi_i_set;
typedef std::vector<int> i_vec;
typedef std::vector<double> d_vec;
typedef std::pair<d_vec*, i_set> skyline_item;
typedef std::set<skyline_item*> skyline_set;

class util
{
public:

	static inline double toRad(double deg)
	{
		return deg / 180 * PI;
	}

	static inline double radOverflow(double r)
	{
		r += 2 * PI;
		while (r > 2 * PI)
			r -= 2 * PI;
		return r;
	}

	static inline double geoDist(double lat1, double lon1, double lat2, double lon2)
	{
		lat1 = toRad(lat1);
		lon1 = toRad(lon1);
		lat2 = toRad(lat2);
		lon2 = toRad(lon2);
		double a = std::sin((lat1 - lat2) / 2) * std::sin((lat1 - lat2) / 2) + std::cos(lat1) * std::cos(lat2) * std::sin((lon1 - lon2) / 2) * std::sin((lon1 - lon2) / 2);
		double c = 2 * std::atan2(std::sqrt(a), sqrt(1 - a));
		return EARTH_RADIUS * c;
	}

	static inline double getAngleToNorth(double lat1, double lon1, double lat2, double lon2)
	{
		double deltaLon = toRad(lon1 - lon2);
		return atan2(sin(deltaLon) * cos(lat2), cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLon));
	}

	static inline pdd getAngles(double r, double lat1, double lon1, double lat2, double lon2)
	{
		double dist = geoDist(lat1, lon1, lat2, lon2);
		if (dist >= 2 * r)
		{
			return std::make_pair(0, 0);
		}
		double angleToN = getAngleToNorth(lat1, lon1, lat2, lon2);
		double angleBetween = acos(dist / 2 / r);
		return std::make_pair(radOverflow(angleToN - angleBetween), radOverflow(angleToN + angleBetween));
	}

	template<class T>
	static void create1dArray(T* &ptr, int d1)
	{
		ptr = new T[d1];
		for (int i = 0; i < d1; ++i)
		{
			ptr[i] = 0;
		}
	}
	template<class T>
	static void createArray(T* &ptr, int d1)
	{
		ptr = new T[d1];
	}

	template<class T>
	static void create2dArray(T** &ptr, int d1, int d2)
	{
		ptr = new T*[d1];
		for (int i = 0; i < d1; ++i)
		{
			ptr[i] = new T[d2];
			for (int j = 0; j < d2; ++j)
			{
				ptr[i][j] = 0;
			}
		}
	}

	template<class T>
	static void create3dArray(T*** &ptr, int d1, int d2, int d3)
	{
		ptr = new T**[d1];
		for (int i = 0; i < d1; ++i)
		{
			ptr[i] = new T*[d2];
			for (int j = 0; j < d2; ++j)
			{
				ptr[i][j] = new T[d3];
				for (int k = 0; k < d3; ++k)
				{
					ptr[i][j][k] = 0;
				}
			}
		}
	}

	template<class T>
	static void create4dArray(T**** &ptr, int d1, int d2, int d3, int d4)
	{
		ptr = new T***[d1];
		for (int i = 0; i < d1; ++i)
		{
			ptr[i] = new T**[d2];
			for (int j = 0; j < d2; ++j)
			{
				ptr[i][j] = new T*[d3];
				for (int k = 0; k < d3; ++k)
				{
					ptr[i][j][k] = new T[d4];
					for (int l = 0; l < d4; ++l)
						ptr[i][j][k][l] = 0;
				}
			}
		}
	}

	template<class T>
	static void delete1dArray(T* &ptr)
	{
		if (!ptr)
			return;
		delete[] ptr;
		ptr = NULL;
	}

	template<class T>
	static void deleteArray(T* &ptr)
	{
		if (!ptr)
			return;
		delete[] ptr;
		ptr = NULL;
	}

	template<class T>
	static void delete2dArray(T** &ptr, int d1)
	{
		if (!ptr)
			return;
		for (int i = 0; i < d1; ++i)
		{
			delete[] ptr[i];
			ptr[i] = NULL;
		}
		delete[] ptr;
		ptr = NULL;
	}

	template<class T>
	static void delete3dArray(T*** &ptr, int d1, int d2)
	{
		if (!ptr)
			return;
		for (int i = 0; i < d1; ++i)
		{
			for (int j = 0; j < d2; ++j)
			{
				delete[] ptr[i][j];
				ptr[i][j] = NULL;
			}
			delete[] ptr[i];
			ptr[i] = NULL;
		}
		delete[] ptr;
		ptr = NULL;
	}

	template<class T>
	static void delete4dArray(T**** &ptr, int d1, int d2, int d3)
	{
		if (!ptr)
			return;
		for (int i = 0; i < d1; ++i)
		{
			for (int j = 0; j < d2; ++j)
			{
				for (int k = 0; k < d3; ++k)
				{
					delete[] ptr[i][j][k];
					ptr[i][j][k] = NULL;
				}
				delete[] ptr[i][j];
				ptr[i][j] = NULL;
			}
			delete[] ptr[i];
			ptr[i] = NULL;
		}
		delete[] ptr;
		ptr = NULL;
	}

	static void ODassert(bool t, std::string s)
	{
		if (!t)
			printf("%s\n", s.c_str());
	}

	static void TopicAssert(bool t, std::string s)
	{
		if (!t)
			printf("%s\n", s.c_str());
	}

	static double logGammaStirling(double z)
	{
		_ASSERT(z >= 0);
		//当z很小时Stirling变得不准确，所以我们计算更大的z并向后移动, [ gamma(z) = gamma(z-1)*(z-1) ]

		int shift = 0;
		while (z < 2)
		{
			z++;
			shift++;
		}

		double result = HALF_LOG_TWO_PI + (z - 0.5) * log(z) - z +	1 / (12 * z) - 1 / (360 * z * z * z) + 1 / (1260 * z * z * z * z * z);

		while (shift > 0)
		{
			shift--;
			z--;
			result -= log(z);
		}

		return result;
	}

	static double digamma(double z)
	{
		//_ASSERT(z >= 0);
		double psi = 0;

		if (z < DIGAMMA_SMALL)
		{
			psi = EULER_MASCHERONI - (1 / z);
			return psi;
		}

		while (z < DIGAMMA_LARGE)
		{
			psi -= 1 / z;
			z++;
		}

		double invZ = 1 / z;
		double invZSquared = invZ * invZ;

		psi += log(z) - .5 * invZ
			- invZSquared * (DIGAMMA_COEF_1 - invZSquared *
			(DIGAMMA_COEF_2 - invZSquared *
			(DIGAMMA_COEF_3 - invZSquared *
			(DIGAMMA_COEF_4 - invZSquared *
			(DIGAMMA_COEF_5 - invZSquared *
			(DIGAMMA_COEF_6 - invZSquared *
			DIGAMMA_COEF_7))))));

		return psi;
	}
	// CDF of normal distribution (standard deviation)
	static double phi(double x)
	{
		// constants
		double a1 = 0.254829592;
		double a2 = -0.284496736;
		double a3 = 1.421413741;
		double a4 = -1.453152027;
		double a5 = 1.061405429;
		double p = 0.3275911;

		// Save the sign of x
		int sign = 1;
		if (x < 0)
			sign = -1;
		x = fabs(x) / sqrt(2.0);

		// A&S formula 7.1.26
		double t = 1.0 / (1.0 + p*x);
		double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

		return 0.5*(1.0 + sign*y);
	}
};