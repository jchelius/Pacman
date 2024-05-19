#ifndef POS2_HPP
#define POS2_HPP

#include <iostream>

struct Pos2
{
public:
	Pos2(int xPos = 0, int yPos = 0) : x (xPos), y (yPos) {}
	Pos2(const Pos2& other) : x(other.x), y(other.y) {}
	int x, y;
	friend std::ostream& operator<<(std::ostream& os, const Pos2& pos2);
	bool operator==(const Pos2& other) { return other.x == x && other.y == y; }
	bool operator!=(const Pos2& other) { return !operator==(other); }
};

inline std::ostream& operator<<(std::ostream& os, const Pos2& pos2) 
{
	os << "(" << pos2.x << ", " << pos2.y << ")";
	return os;
}

#endif // POS2_HPP