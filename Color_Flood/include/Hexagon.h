#pragma once
#include "Enum&Global.h"

class Hexagon{
public:
	Hexagon() {};
	~Hexagon() {};
	void setVisit();
	void setCheck();
	void notCheck();
	void notvisited();
	bool IfChecked();
	bool IfVisited();
	Turn getOwnerForEach();
	static Hexagon& copy();
	Colors getColorForEach();
	Colors OwnerForEach(Turn owner);
	void setColorForEach(Colors color);
	bool newColorForEach(Colors color, Turn owner, bool& newSquare, bool to_change);

private:
	Colors m_color;
	Turn m_owner = NO_PLAYER;
	bool m_visited = false;
	bool m_checked =  false;
	sf::Texture m_colors[COLOR_SIZE];
	sf::RectangleShape m_colorsShape[COLOR_SIZE];
};