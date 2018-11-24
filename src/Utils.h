#ifndef UTILS-H
#define UTILS_H

#include <SFML/Graphics.hpp>

class Utils {
	public:
		template <class T> static T min(T x1, T x2);
		template <class T> static T max(T x1, T x2);
};


#endif // !UTILS_H

template<class T>
inline T Utils::min(T x1, T x2)
{
	return x1 < x2 ? x1 : x2;
}

template<class T>
inline T Utils::max(T x1, T x2)
{
	return x1 > x2 ? x1 : x2;
}
