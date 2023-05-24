#include "GameDetails.h"

GameDetails::GameDetails() : m_buttons(Button::copy())
{
    initText();
    m_buttons.getExit();
    m_buttons.getReplay();
    calculatePercent(1, PLAYER);
    calculatePercent(1, COMPUTER);
    initDfficulties();
}
// -------------------------------------------------------------------------------------------------

Text GameDetails::setText(Vector2f pos, unsigned int size, const std::string& txt, Color color) const
{
    Text text(txt, m_buttons.getFont(), size);
    text.setFillColor(color);
    text.setPosition(pos);
    return text;
}
// -------------------------------------------------------------------------------------------------

void GameDetails::showDetails(RenderWindow& window)
{
    window.draw(m_playerText);
    window.draw(m_compText);
    window.draw(m_turnText);
    window.draw(m_colorsText);
}
// -------------------------------------------------------------------------------------------------

bool GameDetails::checkExitClicked(const Vector2f& location)
{
    if (m_buttons.getExitShape().getGlobalBounds().contains(location))
        return true;
    return false;
}
// -------------------------------------------------------------------------------------------------

bool GameDetails::checkReplayClicked(const Vector2f& location)
{
    if (m_buttons.getReplayShape().getGlobalBounds().contains(location))
        return true;
    return false;
}
// -------------------------------------------------------------------------------------------------

bool GameDetails::checkPlayClicked(const Vector2f& location)
{
    if (m_buttons.getPlayShape().getGlobalBounds().contains(location))
        return true;
    return false;
}
// -------------------------------------------------------------------------------------------------

void GameDetails::initText()
{
    initPlayerTxt();
    initCompTxt();
    m_text.setStyle(sf::Text::Bold);

}
// -------------------------------------------------------------------------------------------------

void GameDetails::calculatePercent(const float percent, Turn owner)
{
    std::ostringstream oString;
    oString.precision(3);

    std::string ownerString = (owner == COMPUTER) ? "Computer" : "Player";
    oString << std::fixed << ownerString << ": " << percent << "%";

    if (owner == COMPUTER)
    {
        m_compText.setString(oString.str());
        m_compText.setFillColor(Color::Black);
    }
    else
    {
        m_playerText.setString(oString.str());
        m_playerText.setFillColor(Color::White);
    }
}
// -------------------------------------------------------------------------------------------------

bool GameDetails::DifficultyClicked(const Vector2f& loc, int& i)
{
    i = 0;
    while (i < difficultOptions)
    {
        if (m_buttons.getDfficultiesShapes(i).getGlobalBounds().contains(loc))
            return true;
        i++;
    }
    return false;
}
// -------------------------------------------------------------------------------------------------

void GameDetails::initPlayerTxt()
{
    m_playerText.setStyle(sf::Text::Bold);
    m_playerText.setFillColor(Color::White);
    m_playerText = setText({ 100, 610 }, SIZE_TXT, "Player: ", sf::Color(255, 192, 203));
}
// -------------------------------------------------------------------------------------------------

void GameDetails::initCompTxt()
{
    m_compText.setStyle(sf::Text::Bold);
    m_compText.setFillColor(Color::Black);
    m_compText = setText({ 400, 610 }, SIZE_TXT, "Computer: ", sf::Color(255, 192, 203));
}

void GameDetails::changeTurn(Turn turn)
{
    if (turn == PLAYER) {
        m_playerText.setFillColor(Color::Black);
        m_compText.setFillColor(Color::White);
    }
    else if (turn == COMPUTER) {
        m_compText.setFillColor(Color::Black);
        m_playerText.setFillColor(Color::White);
    }
}

// -------------------------------------------------------------------------------------------------

void GameDetails::hideDfficulties() const {
    for (size_t i = 0; i < difficultOptions; i++)
        m_buttons.NoShowDifButtons(i);
}

// -------------------------------------------------------------------------------------------------
void GameDetails::initDfficulties()
{
    int x = 200, i = 0;
    while (i < difficultOptions)
    {
        m_buttons.getDfficulty(i, x);
        x += 100;
        i++;
    }
}