#pragma once
#include "Board.h"
#include "GameDetails.h"

class GameController{
public:
    void runGame();
    GameController();
    void FinishGame();
    void setPictures();
    void setGameName();
    void windowAction();
    void continueGame();
    void drawHexagons();
    void drawButtons();
    void HandleClick();
    void percentages();
    void ScreenDisplay();
    void DrawBoardGame();
    sf::Sprite setPicWin();
    sf::Sprite setPicLose();
    void ButtonsForColors();
    void ColorChoose(const int i);
    sf::Sprite setBackgroundPic();
    sf::Sprite setMenuBackground();
    HardnessLevel difficultyLevel();
    void GameBegin(HardnessLevel curDif);
    void MousePressed(const Event& event);
    sf::Sprite createSprite(const sf::Texture& texture);
    void checkColorButtons(const sf::Vector2f& location);
    void createColors(const int i, std::array<sf::RectangleShape, COLOR_SIZE>::iterator& it_1);
    void configureHexagon(sf::CircleShape& hexagon, int i, int j, float x, float y, float hexRadius);

private:
    Text m_turn;
    Font m_font;
    Board m_board;
    Text m_GameName;
    bool m_GameOver;
    Button& m_buttons;
    std::string turnText;
    GameDetails m_detail;
    int m_difficultyOption;
    bool m_firstTime = true;
    sf::Texture m_PictureMenu;
    sf::Texture m_PictureWin;
    sf::Texture m_PictureLose;
    HardnessLevel m_difficulty;
    sf::Texture m_PictureBackground;
    sf::Texture m_insideButtonTexture;
    std::vector<std::vector<sf::CircleShape>> m_hexagons;
    RenderWindow m_window = { VideoMode(724, 724,32), "Color Flood", sf::Style::Close };
    std::array<sf::RectangleShape, COLOR_SIZE> m_color_buttons;
};