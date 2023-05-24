#include "Board.h"
#include <vector> 
#include <queue>
#include <utility>
#include <random> 
// -------------------------------------------------------------------------------------------------
Board::Board(){
	m_board.resize(SIZE_BRD);
	for (auto it1 = m_board.begin(); it1 != m_board.end(); ++it1)
		(*it1).resize(SIZE_BRD);
	BoardRestart();
}
// -------------------------------------------------------------------------------------------------
Colors Board::getPlayerColor(Turn owner) { return (owner == Turn::PLAYER) ? m_playerColor : m_compColor; }
// -------------------------------------------------------------------------------------------------
void Board::newColor(Turn owner, Colors color, sf::RenderWindow& window,Text turn)
{
	switch (owner)
	{
	case COMPUTER:
		m_compColor = color;
		break;
	case PLAYER:
		m_playerColor = color;
		break;
	default:
		break;
	}
}
//-------------------------------- USED ONLY IN TURN -----------------------
Text Board::createText(Vector2f pos, unsigned int size, const std::string& txt, Color color) const
{
	Text text(txt, Button::copy().getFont(), size);
	text.setFillColor(color);
	text.setPosition(pos);

	return text;
}
//-------------------------------- USED ONLY IN TURN -----------------------
void Board::visitingHexa()
{
	for (auto it1 = m_board.begin(); it1 != m_board.end(); ++it1)
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
			(*it2).notvisited();
}
// -------------------------------------------------------------------------------------------------
void Board::BoardRestart() {
	srand((unsigned int)time(0));
	for (auto it1 = m_board.begin(); it1 != m_board.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			(*it2).setColorForEach((Colors)(rand() % 6));
			(*it2).OwnerForEach(NO_PLAYER);
		}
	}
	init();
}
// -------------------------------------------------------------------------------------------------
void Board::init() {
	m_OwnedByComp = 1;
	m_OwnedByPlayer = 1;
	m_computerPercentage = 0;
	m_playerPercentage = 0;
	m_playerColor = m_board[SIZE_BRD - 1][0].OwnerForEach(PLAYER);
	m_compColor = m_board[0][SIZE_BRD - 1].OwnerForEach(COMPUTER);
}
//---------------------------------------------------------------------------
void Board::fillHexagon(int i, int j, Colors color, Turn owner, bool change)
{
	bool if_newHexagon = false;
	if (i < 0 || j < 0 || j > SIZE_BRD - 1 || i > SIZE_BRD - 1)
		return;
	else{
		auto it1 = m_board.begin();
		advance(it1, i);
		auto it2 = (*it1).begin();
		advance(it2, j);
		if ((*it2).newColorForEach(color, owner, if_newHexagon, change)){
			if (if_newHexagon)  {
				if (owner == COMPUTER)
					m_OwnedByComp++;
				if (owner == PLAYER)
					m_OwnedByPlayer++;
			}
			checkingHardNeighbors(i, j, color, owner, change);
		}
	}
}
//---------------------------------------------------------------------------
void Board::checkMeduimNeighbours(int i, int j, Colors compColor, Turn owner, bool change) {
	bool newSquare = false;
	if (i < 0 || j < 0 || j > SIZE_BRD - 1 || i > SIZE_BRD - 1)
		return;
	else {
		auto it1 = m_board.begin();
		advance(it1, i);
		auto it2 = (*it1).begin();
		advance(it2, j);
		Colors curColor = (*it2).getColorForEach();
		if ((*it2).IfChecked()) {
			if (curColor != compColor && curColor != m_playerColor) {
				m_colorMeduiCounter[curColor]++;
				(*it2).setCheck();
				return;
			}
			else {
				(*it2).setCheck();
				return;
			}
		}
		else
			return;
	}
}
//---------------------------------------------------------------------------
void Board::checkingHardNeighbors(int& i, int& j, Colors& color, Turn& owner, bool& change) {

	fillHexagon((i - 1), j, color, owner, change);
	fillHexagon((i + 1), j, color, owner, change);
	fillHexagon(i, j - 1, color, owner, change);
	fillHexagon(i, j + 1, color, owner, change);

	if (i % 2 == 0) {
		fillHexagon((i - 1), (j - 1), color, owner, change);
		fillHexagon((i + 1), (j - 1), color, owner, change);
	}
	else {
		fillHexagon((i - 1), (j + 1), color, owner, change);
		fillHexagon((i + 1), (j + 1), color, owner, change);
	}
}
//---------------------------------------------------------------------------
void Board::setPercentage()
{
	m_playerPercentage = ((m_OwnedByPlayer / (SIZE_BRD * SIZE_BRD)) * 100);
	m_computerPercentage = (m_OwnedByComp / (SIZE_BRD * SIZE_BRD)) * 100;
}
void Board::restartAfterMedium()
{
	for (int i = 0; i < COLOR_SIZE; ++i) {
		m_colorMeduiCounter[i] = 0;
	}
	Checking();
	visitingHexa();
	paintingTheMeduim(0, SIZE_BRD - 1, COMPUTER, false);
}
//---------------------------------------------------------------------------
float Board::getPercentage(Turn owner) { return (owner == Turn::PLAYER) ? m_playerPercentage : m_computerPercentage; }
//---------------------------------------------------------------------------
Colors Board::hardLevel()
{
	float currentCompOwned = m_OwnedByComp;
	Colors maximumPlayerColor = m_compColor;
	float maximumCompOwned = m_OwnedByComp;
	for (int i = 0; i < COLOR_SIZE; i++)
	{
		m_OwnedByComp = currentCompOwned;

		if (i == m_compColor || i == m_playerColor)
			continue;
		visitingHexa();
		fillHexagon(0, SIZE_BRD - 1,Colors(i), COMPUTER, false);
		if (m_OwnedByComp > maximumCompOwned){
			maximumCompOwned = m_OwnedByComp;
			maximumPlayerColor = (Colors)i;
		}
	}

	m_OwnedByComp = currentCompOwned;
	visitingHexa();

	return maximumPlayerColor;
}
//---------------------------------------------------------------------------
void Board::Checking()
{
	for (auto it1 = m_board.begin(); it1 != m_board.end(); ++it1)
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
			(*it2).notCheck();
}
//---------------------------------------------------------------------------
Colors Board::MediumLevel()
{
	Colors maxColor = Colors(0);
	Colors currentColorComp = m_compColor;
	Colors currentColorPlayer = m_playerColor;
	int maxIndex = 0;
	restartAfterMedium();
	auto maxElement = std::max_element(m_colorMeduiCounter.begin(), m_colorMeduiCounter.end());
	if (maxElement != m_colorMeduiCounter.end()) {
		maxIndex = std::distance(m_colorMeduiCounter.begin(), maxElement);
		maxColor = static_cast<Colors>(maxIndex);
	}
	Checking();
	visitingHexa();
	return maxColor;
}
// -------------------------------------------------------------------------------------------------
void Board::paintingTheMeduim(int i, int j, Turn owner, bool change)
{
	if (i < 0 || j < 0 || j > SIZE_BRD - 1 || i > SIZE_BRD - 1)
		return;
	else
	{
		auto it1 = m_board.begin();
		auto it2 = (*it1).begin();
		advance(it1, i);
		advance(it2, j);
		Colors compColor = (*it2).getColorForEach();
		if ((*it2).IfVisited()) {
			if ((*it2).getOwnerForEach() == COMPUTER) {
				checkMeduimNeighbours(i + 1, j, compColor, owner, change);
				checkMeduimNeighbours(i - 1, j, compColor, owner, change);
				checkMeduimNeighbours(i, j + 1, compColor, owner, change);
				checkMeduimNeighbours(i, j - 1, compColor, owner, change);

				if (i % 2 != 0)
				{
					checkMeduimNeighbours((i - 1), (j + 1), compColor, owner, change);
					checkMeduimNeighbours((i + 1), (j + 1), compColor, owner, change);
				}
				else
				{
					checkMeduimNeighbours((i - 1), (j - 1), compColor, owner, change);
					checkMeduimNeighbours((i + 1), (j - 1), compColor, owner, change);
				}
			}
			(*it2).setVisit();
		}
		else
			return;
		doneWithNeighbours(i, j, owner, change);
	}
}
//---------------------------------------------------------------------------
void Board::doneWithNeighbours(int i, int j, Turn owner, bool change) {
	paintingTheMeduim((i - 1), j, owner, change);
	paintingTheMeduim((i + 1), j, owner, change);
	paintingTheMeduim(i, j - 1, owner, change);
	paintingTheMeduim(i, j + 1, owner, change);
	if (i % 2 != 0)
	{
		paintingTheMeduim((i - 1), (j + 1), owner, change);
		paintingTheMeduim((i + 1), (j + 1), owner, change);
	}
	else
	{
		paintingTheMeduim((i - 1), (j - 1), owner, change);
		paintingTheMeduim((i + 1), (j - 1), owner, change);
	}
}
//---------------------------------------------------------------------------
Colors Board::EasyLevel() {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> dis(0, 5);
	std::srand(static_cast<unsigned int>(std::time(0)));
	Colors colorForComputer;

	do {
		colorForComputer = static_cast<Colors>(dis(gen));
	} while (colorForComputer == getPlayerColor(PLAYER));

	return colorForComputer;
}
//---------------------------------------------------------------------------
float Board::getPercetage4Player() { return (float)(m_OwnedByPlayer / (SIZE_BRD * SIZE_BRD)); }
//---------------------------------------------------------------------------
float Board::getPercetage4Comp() { return (float)(m_OwnedByComp / (SIZE_BRD * SIZE_BRD)); }
// -------------------------------------------------------------------------------------------------
Colors Board::getHexagonColor(int i, int j) { return m_board[i][j].getColorForEach(); }
// -------------------------------------------------------------------------------------------------
Turn Board::getHexagonOwner(int i, int j) { return m_board[i][j].getOwnerForEach(); }