#include "Hexagon.h"

Colors Hexagon::OwnerForEach(Turn owner)
{
	m_owner = owner;
	return m_color;
}
//---------------------------------------------------------------------------
void Hexagon::setVisit(){ m_visited = true; }
//---------------------------------------------------------------------------
void Hexagon::notvisited(){ m_visited = false; }
//---------------------------------------------------------------------------
void Hexagon::setCheck() { m_checked = true; }
//---------------------------------------------------------------------------
void Hexagon::notCheck() { m_checked = false; }
//---------------------------------------------------------------------------
Turn Hexagon::getOwnerForEach(){ return m_owner; }
//---------------------------------------------------------------------------
void Hexagon::setColorForEach(Colors color){ m_color = color; }
//---------------------------------------------------------------------------
Colors Hexagon::getColorForEach(){ return m_color; }
//---------------------------------------------------------------------------
bool Hexagon::newColorForEach(Colors color, Turn owner, bool& newHexagon, bool to_change) {
	if (m_visited)
		return false;
	m_visited = true;
	if (m_owner == owner) {
		if (to_change) {
			m_color = color;
			setColorForEach(m_color);
		}
		return true;
	}
	else {
		if (m_color == color) {
			if (to_change)
				m_owner = owner;
			newHexagon = true;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool Hexagon::IfChecked() {
	if (m_checked)
		return false;
	return true;
}
//---------------------------------------------------------------------------
Hexagon& Hexagon::copy() {
	static auto resource = Hexagon();
	return resource;
}
//---------------------------------------------------------------------------
bool Hexagon::IfVisited() {
	if (m_visited)
		return false;
	return true;
}