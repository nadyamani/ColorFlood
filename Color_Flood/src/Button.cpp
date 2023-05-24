#include "Button.h"

Button::Button()
{
    m_font.loadFromFile("IMPRISHA.TTF");

    setReplayButton();
    setExitButton();
    setPlayButton();

    int i = 0;
    while (true) {
        std::string difficulties = "level_";
        difficulties.append(std::to_string(i));
        difficulties += ".png";
        m_difficTextures[i].loadFromFile(difficulties);
        m_difficButtons[i].setTexture(&m_difficTextures[i]);
        i++;

        if (i >= difficultOptions)
            break;
    }
}
// -------------------------------------------------------------------------------------------------

void Button::setPlayShape(sf::RenderWindow& window)
{
    m_playButton.setSize(sf::Vector2f(SIZE_X + 10, SIZE_Y + 10));
    m_playButton.setPosition(70, 150);
    window.draw(m_playButton);

}
// -------------------------------------------------------------------------------------------------

void Button::setPlayButton()
{
    m_startTexture.loadFromFile("play.png");
    m_playButton.setTexture(&m_startTexture);

}
// -------------------------------------------------------------------------------------------------

Button& Button::copy()
{
    static auto button = Button();
    return button;
}
// -------------------------------------------------------------------------------------------------
void Button::setExitButton()
{
    m_exitTexture.loadFromFile("exit.png");
    m_exitButton.setTexture(&m_exitTexture);

}
// -------------------------------------------------------------------------------------------------

void Button::setExitShape(sf::RenderWindow& window)
{
    m_exitButton.setSize(sf::Vector2f(SIZE_X + 10, SIZE_Y + 10));
    m_exitButton.setPosition(450, 150);
    window.draw(m_exitButton);

}
// -------------------------------------------------------------------------------------------------

RectangleShape Button::getExit()
{
    m_exitButton.setSize(sf::Vector2f(SIZE_X, SIZE_Y));
    m_exitButton.setPosition(BUTTON_POS_X, BUTTON_INIT_Y);

    return m_exitButton;
}
// -------------------------------------------------------------------------------------------------

void Button::NoShowDifButtons(const int i)
{
    m_difficButtons[i].setSize(sf::Vector2f(0, 0));
}
// -------------------------------------------------------------------------------------------------

RectangleShape& Button::getDfficultiesShapes(const int i)
{
    return m_difficButtons[i];
}
// -------------------------------------------------------------------------------------------------

Font& Button::getFont()
{
    return m_font;
}
// -------------------------------------------------------------------------------------------------

void Button::showDifButtons(sf::RenderWindow& window)
{
    for (int i = 0; i < difficultOptions; i++)
        window.draw(m_difficButtons[i]);
}
// -------------------------------------------------------------------------------------------------

RectangleShape& Button::getReplayShape()
{
    return m_replayButton;
}
// -------------------------------------------------------------------------------------------------

RectangleShape& Button::getPlayShape()
{
    return m_playButton;
}
// -------------------------------------------------------------------------------------------------

void Button::drawMenuButton(sf::RenderWindow& window)
{
    setPlayShape(window);
    setExitShape(window);
}
// -------------------------------------------------------------------------------------------------

void Button::setReplayButton()
{
    m_replayTexture.loadFromFile("replay.png");
    m_replayButton.setTexture(&m_replayTexture);
}
// -------------------------------------------------------------------------------------------------

RectangleShape Button::getReplay()
{
    m_replayButton.setSize(sf::Vector2f(SIZE_X, SIZE_Y));
    m_replayButton.setPosition(BUTTON_INIT_X, BUTTON_INIT_Y);

    return m_replayButton;
}
// -------------------------------------------------------------------------------------------------

RectangleShape Button::getDfficulty(int i, int x)
{
    m_difficButtons[i].setSize(sf::Vector2f(SIZE_X + 80, SIZE_Y + 40));
    m_difficButtons[i].setPosition(200, x);
    return m_difficButtons[i];
}
// -------------------------------------------------------------------------------------------------

void Button::drawExitReplay(sf::RenderWindow& window)
{
    window.draw(m_replayButton);
    getExit();
    window.draw(m_exitButton);
}
// -------------------------------------------------------------------------------------------------

RectangleShape& Button::getExitShape()
{
    return m_exitButton;
}
// -------------------------------------------------------------------------------------------------
