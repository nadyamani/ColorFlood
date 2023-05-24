#pragma once
#include "Enum&Global.h"

class Button {
public:

	Button();
	Font& getFont();
	void setPlayButton();
	void setExitButton();
	static Button& copy();
	void setReplayButton();
	RectangleShape getExit();
	RectangleShape getReplay();
	RectangleShape& getPlayShape();
	RectangleShape& getExitShape();
	RectangleShape& getReplayShape();
	void NoShowDifButtons(const int i);
	RectangleShape getDfficulty(int i, int x);
	void setPlayShape(sf::RenderWindow& window);
	void setExitShape(sf::RenderWindow& window);
	void drawExitReplay(sf::RenderWindow& window);
	void drawMenuButton(sf::RenderWindow& window);
	void showDifButtons(sf::RenderWindow& window);
	RectangleShape& getDfficultiesShapes(const int i);

private:

	sf::Font m_font;
	sf::Texture m_exitTexture;
	sf::Texture m_startTexture;
	sf::Texture m_replayTexture;
	sf::RectangleShape m_exitButton;
	sf::RectangleShape m_playButton;
	sf::RectangleShape m_replayButton;
	sf::Texture m_difficTextures[difficultOptions];
	sf::RectangleShape m_difficButtons[difficultOptions];

};