#pragma once
#include "Hexagon.h"
#include "Board.h"
#include "Button.h"

class GameDetails
{
public:
    GameDetails();
    void initText();
    void initCompTxt();
    void changeTurn(Turn owner);
    void initPlayerTxt();
    void initDfficulties();
    void hideDfficulties() const;
    void showDetails(RenderWindow&);
    bool checkExitClicked(const Vector2f& loc);
    bool checkPlayClicked(const Vector2f& loc);
    bool checkReplayClicked(const Vector2f& loc);
    bool DifficultyClicked(const Vector2f& loc, int& i);
    void calculatePercent(const float percent, Turn owner);
    Text setText(Vector2f, unsigned int, const std::string&, Color) const;

private:
    Board m_board;
    Text m_text;
    Text m_compText;
    Text m_turnText;
    Text m_compTextxt;
    Text m_colorsText;
    Text m_playerText;
    Button& m_buttons;

};