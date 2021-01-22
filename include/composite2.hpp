#ifndef COMPOSITE2_HPP
#define COMPOSITE2_HPP


#include <cstddef>
#include <functional>

struct composite2
{
	int first;
	int second;
};

inline bool operator== (const composite2& lhs, const composite2& rhs)
{
	if (lhs.first != rhs.first || lhs.second != rhs.second)
		return false;

	return true;
}

struct HashComposite2
{
	size_t operator()(composite2 const& hash_source) const noexcept
	{
		size_t seed;
		seed = 0;
		size_t hash_val;

		hash_val = std::hash<int>{}(hash_source.first);
		seed ^= hash_val + 0x9e3779b9 + (seed<<6) + (seed>>2);

		hash_val = std::hash<int>{}(hash_source.second);
		seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		return seed;
	}
};

#endif



 
