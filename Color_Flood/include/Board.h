#pragma once
#include "Enum&Global.h"
#include "Hexagon.h"
#include "Button.h"

class Board {
public:
	Board();
	void init();
	void Checking();
	Colors hardLevel();
	Colors EasyLevel();
	void BoardRestart();
	void visitingHexa();
	void setPercentage();
	void restartAfterMedium();
	Colors MediumLevel();
	float getPercetage4Comp();
	float getPercetage4Player();
	float getPercentage(Turn owner);
	Colors getPlayerColor(Turn owner);
	Turn getHexagonOwner(int i, int j);
	Colors getHexagonColor(int i, int j);
	void paintingTheMeduim(int i, int j, Turn owner, bool change);
	void doneWithNeighbours(int i, int j, Turn owner, bool change);
	void fillHexagon(int i, int j, Colors color, Turn owner, bool change);
	void newColor(Turn owner, Colors color, sf::RenderWindow& window, Text turn);
	void checkMeduimNeighbours(int i, int j, Colors compColor, Turn owner, bool change);
	void checkingHardNeighbors(int& i, int& j, Colors& color, Turn& owner, bool& change);
	Text createText(Vector2f pos, unsigned int size, const std::string& txt, Color color) const;

private:
	Colors m_compColor;
	Colors m_playerColor;
	float m_OwnedByComp = 1;
	float m_OwnedByPlayer = 1;
	Hexagon m_hexagons[SIZE_BRD];
	float m_playerPercentage = 0;
	float m_computerPercentage = 0;
	std::vector<std::vector<Hexagon>> m_board;
	std::array<float, COLOR_SIZE> m_colorMeduiCounter;
};