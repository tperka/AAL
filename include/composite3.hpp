#ifndef COMPOSITE3_HPP
#define COMPOSITE3_HPP

#include <cstddef>
#include <functional>

struct composite3
{
	int first;
	int second;
	int third;
};

inline bool operator== (const composite3& lhs, const composite3& rhs)
{
	if (lhs.first != rhs.first || lhs.second != rhs.second || lhs.third != rhs.third)
		return false;

	return true;
}

struct HashComposite3
{
	size_t operator()(composite3 const& hash_source) const noexcept
	{
		size_t seed;
		seed = 0;
		size_t hash_val;

		hash_val = std::hash<int>{}(hash_source.first);
		seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		hash_val = std::hash<int>{}(hash_source.second);
		seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		hash_val = std::hash<int>{}(hash_source.third);
		seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		return seed;
	}
};

#endif