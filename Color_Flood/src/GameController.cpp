#include "GameController.h"
#include <random> 
// -------------------------------------------------------------------------------------------------
GameController::GameController() : m_difficulty(NO_DIFFICULTY), m_buttons(Button::copy()), m_GameOver(false), m_difficultyOption(3)
{
    m_hexagons.resize(SIZE_BRD);
    for (auto it_1 = m_hexagons.begin(); it_1 != m_hexagons.end(); ++it_1)
        (*it_1).resize(SIZE_BRD);

    setPictures();
    runGame();
}
// -------------------------------------------------------------------------------------------------
void GameController::setPictures() {
    m_PictureBackground.loadFromFile("background.jpg");
    m_PictureMenu.loadFromFile("menuBackground.jpg");
    m_PictureWin.loadFromFile("win.jpg");
    m_insideButtonTexture.loadFromFile("heart.png");
    m_PictureLose.loadFromFile("lose.jpg");
}
// -------------------------------------------------------------------------------------------------
void GameController::setGameName()
{
    m_GameName.setFont(m_font);
    m_GameName.setStyle(sf::Text::Bold);
    m_GameName.setFillColor(sf::Color(255, 192, 203));
    m_GameName.setCharacterSize(TITLE_SIZE);
    m_GameName.setPosition({ 230, 80 });
}
// -------------------------------------------------------------------------------------------------
void GameController::runGame()
{
    std::string name = "Color Flood";
    m_GameName.setString(name);
    m_font.loadFromFile("IMPRISHA.TTF");
    setGameName();
    windowAction();
}
// -------------------------------------------------------------------------------------------------
void GameController::windowAction()
{
    while (m_window.isOpen())
    {
        m_window.clear();

        m_window.draw(setMenuBackground());
        m_window.draw(m_GameName);
        m_buttons.drawMenuButton(m_window);
        m_window.display();

        bool continueLoop = true;
        sf::Event event;

        while (continueLoop && m_window.pollEvent(event))
        {
            auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            if (event.type == sf::Event::Closed || m_detail.checkExitClicked(location))
            {
                m_window.close();
                return;
            }

            else if (m_detail.checkPlayClicked(location))
            {
                m_window.clear();
                m_buttons.showDifButtons(m_window);
                m_window.display();
                m_difficulty = difficultyLevel();
                if (m_difficulty != NO_DIFFICULTY)
                    GameBegin(m_difficulty);
            }
            continueLoop = m_window.isOpen();
        }
    }
}
// -------------------------------------------------------------------------------------------------
void GameController::GameBegin(HardnessLevel m_difficulty) {
    m_detail.hideDfficulties();
    ScreenDisplay();
    while (m_window.isOpen())
    {
        DrawBoardGame();
        m_detail.showDetails(m_window);
        m_buttons.drawExitReplay(m_window);
        m_window.display();

        bool continueLoop = true;
        sf::Event event_2;

        while (continueLoop && m_window.pollEvent(event_2))
        {
            switch (event_2.type)
            {
            case sf::Event::MouseButtonPressed:
                MousePressed(event_2);
                break;
            case sf::Event::Closed:
                m_window.close();
                return;
            case sf::Event::KeyPressed:
                if (event_2.key.code == sf::Keyboard::Escape)
                    m_window.close();
                break;
            }
            continueLoop = m_window.pollEvent(event_2);
        }

    }
}
// -------------------------------------------------------------------------------------------------
void GameController::ColorChoose(const int i)
{
    if (m_GameOver)
        return;
    Colors chosenColor = Colors(0); 
    if ( i == m_board.getPlayerColor(COMPUTER) || 
         i == m_board.getPlayerColor(PLAYER))
        return;

    m_board.visitingHexa();
    m_board.newColor(PLAYER, (Colors)i,m_window,m_turn);
    m_detail.changeTurn(PLAYER);
    m_detail.showDetails(m_window);
    m_window.display();
    const sf::Time sleepdown = sf::seconds(0.5);
    	sleep(sleepdown);
    m_board.fillHexagon(SIZE_BRD - 1, 0, (Colors)i, PLAYER, true);

    switch (m_difficulty)
    {
    case MEDIUM:
        chosenColor = m_board.MediumLevel();
        break;
    case HARD:
        chosenColor = m_board.hardLevel();
        break;
    case EASY:
        chosenColor = m_board.EasyLevel();
        break;
    default:
        break;
    }
 
    m_board.setPercentage();
    m_detail.changeTurn(COMPUTER);
    m_detail.showDetails(m_window);
    m_window.display();
    m_board.newColor(COMPUTER, (Colors)chosenColor, m_window,m_turn);
    m_board.fillHexagon(0, SIZE_BRD - 1, (Colors)chosenColor, COMPUTER, true);
    ScreenDisplay();
}
// -------------------------------------------------------------------------------------------------
void GameController::configureHexagon(sf::CircleShape& hexagon, int i, int j, float x, float y, float hexRadius)
{
    hexagon.setPointCount(6);
    hexagon.setRadius(hexRadius);

    if (i % 2 != 0)
        x += hexRadius;

    hexagon.setPosition(x, y);
    switch (m_board.getHexagonColor(i, j))
    {
    case ORANGE:
        hexagon.setFillColor(sf::Color(255, 165, 0));
        hexagon.setOutlineColor(sf::Color(255, 165, 0));
        break;

    case RED:
        hexagon.setFillColor(sf::Color::Red);
        hexagon.setOutlineColor(sf::Color::Red);
        break;

    case BLUE:
        hexagon.setFillColor(sf::Color(137, 207, 240));
        hexagon.setOutlineColor(sf::Color(137, 207, 240));
        break;

    case YELLOW:
        hexagon.setFillColor(sf::Color::Yellow);
        hexagon.setOutlineColor(sf::Color::Yellow);
        break;

    case PURPLE:
        hexagon.setFillColor(sf::Color(160, 32, 240));
        hexagon.setOutlineColor(sf::Color(160, 32, 240));
        break;

    case PINK:
        hexagon.setFillColor(sf::Color(255, 192, 203));
        hexagon.setOutlineColor(sf::Color(255, 192, 203));
        break;

    }

    hexagon.setOutlineThickness(1.f);

    if (m_board.getHexagonOwner(i, j) != NO_PLAYER)
    {
        hexagon.setOutlineColor(sf::Color::Blue);
        hexagon.setOutlineThickness(2.f);
    }
}
// -------------------------------------------------------------------------------------------------
void GameController::ScreenDisplay()
{
    float space = 1.f;
    float hexRadius = 10.f * std::sqrt(3.f) / 2;
    float boardWidth = (SIZE_BRD * (2.f * hexRadius + space)) - space;
    float boardHeight = (SIZE_BRD * (2.f * hexRadius));
    float balance = (700.f - boardWidth) / 2.f;
    float xCoordenate = balance + (boardWidth - (SIZE_BRD * (2.f * hexRadius + space))) / 2.f;

    float x, y;
    for (auto it_1 = m_hexagons.begin(); it_1 != m_hexagons.end(); ++it_1)
    {
        for (auto it_2 = (*it_1).begin(); it_2 != (*it_1).end(); ++it_2)
        {
            sf::CircleShape& hexagon = (*it_2);

            int i = static_cast<int>(std::distance(m_hexagons.begin(), it_1));
            int j = static_cast<int>(std::distance((*it_1).begin(), it_2));

            x = xCoordenate + (j * (2.f * hexRadius + space));
            y = balance + (i * (2.f * hexRadius));

            configureHexagon(hexagon, i, j, x, y, hexRadius);
        }
    }

    ButtonsForColors();
}
// -------------------------------------------------------------------------------------------------
void GameController::MousePressed(const Event& event)
{
    int option;
    auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

    if (m_detail.DifficultyClicked(location, option)) 
        m_difficultyOption = option;

    else if (m_detail.checkReplayClicked(location))
        HandleClick();

    else if (m_detail.checkExitClicked(location)) {
          m_window.close();
          return;
    }

    checkColorButtons(location);
}
// -------------------------------------------------------------------------------------------------
void GameController::checkColorButtons(const sf::Vector2f& location)
{
    size_t i = 0;
    bool continueLoop = true;

    while (i < COLOR_SIZE && continueLoop){
        if (m_color_buttons[i].getGlobalBounds().contains(location)){
            ColorChoose(i);
            continueLoop = false;
        }
        i++;
    }
}
// -------------------------------------------------------------------------------------------------
void GameController::ButtonsForColors()
{
    float width = 40.f;
    float heigth = 40.f;
    float buttonSpacing = 10.f;
    float totalWidth = (SIZE_BRD * width) + ((SIZE_BRD - 1) * buttonSpacing);
    float xCoordenate = (1630.f - totalWidth) / 2.f;
    for (auto it_1 = m_color_buttons.begin(); it_1 != m_color_buttons.end(); ++it_1)
    {
        int i = static_cast<int>(std::distance(m_color_buttons.begin(), it_1));
        (*it_1) = sf::RectangleShape(sf::Vector2f(width, heigth));
        (*it_1).setPosition(xCoordenate + (i * (width + buttonSpacing)), 570.f);

        createColors(i,it_1);

        (*it_1).setOutlineColor(sf::Color::Cyan);
        (*it_1).setOutlineThickness(2.f);
    }
}
// -------------------------------------------------------------------------------------------------
void GameController::createColors( const int i, std::array<sf::RectangleShape, COLOR_SIZE>::iterator& it_1)
{
    if (i == PINK)
        (*it_1).setFillColor(sf::Color(255, 192, 203));
    else if (i == RED)
        (*it_1).setFillColor(sf::Color::Red);
    else if (i == ORANGE)
        (*it_1).setFillColor(sf::Color(255, 165, 0));
    else if (i == BLUE)
        (*it_1).setFillColor(sf::Color(137, 207, 240));
    else if (i == PURPLE)
        (*it_1).setFillColor(sf::Color(160, 32, 240));
    else if (i == YELLOW)
        (*it_1).setFillColor(sf::Color::Yellow);
}
// -------------------------------------------------------------------------------------------------
void GameController::percentages()
{
    auto PlayerPercent = m_board.getPercentage(PLAYER);
    m_detail.calculatePercent(PlayerPercent, PLAYER);
    auto ComputerPercent = m_board.getPercentage(COMPUTER);
    m_detail.calculatePercent(ComputerPercent, COMPUTER);

    if (ComputerPercent > WIN_LIMIT) {
        FinishGame();
        m_window.draw(setPicLose());
    }

    else if (PlayerPercent > WIN_LIMIT) {
        FinishGame();
        m_window.draw(setPicWin());
    }
    m_color_buttons[m_board.getPlayerColor(PLAYER)].setOutlineColor(sf::Color::Black);
    m_color_buttons[m_board.getPlayerColor(COMPUTER)].setOutlineColor(sf::Color::Black);
    m_color_buttons[m_board.getPlayerColor(PLAYER)].setTexture(&m_insideButtonTexture);
    m_color_buttons[m_board.getPlayerColor(COMPUTER)].setTexture(&m_insideButtonTexture);
}
// -------------------------------------------------------------------------------------------------
void GameController::continueGame(){
    m_window.clear(Color::Black);
    m_buttons.showDifButtons(m_window);
    m_buttons.drawExitReplay(m_window);
    m_window.display();
    m_difficulty = difficultyLevel();

    if (m_difficulty != NO_DIFFICULTY)
        GameBegin(m_difficulty);
}
// -------------------------------------------------------------------------------------------------
void GameController::HandleClick(){
    m_GameOver = false;
    m_board.setPercentage();
    m_board.BoardRestart();
    m_detail.initDfficulties();
    continueGame();
}
// -------------------------------------------------------------------------------------------------
void GameController::DrawBoardGame(){
    m_window.clear();
    m_window.draw(setBackgroundPic());
    drawHexagons();
    drawButtons();
    percentages();
   
}
// -------------------------------------------------------------------------------------------------
void GameController::FinishGame(){
    m_GameOver = true;
    m_window.clear();
}
// -------------------------------------------------------------------------------------------------
HardnessLevel GameController::difficultyLevel() {
    while (!m_GameOver) {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed){
                m_window.close();
                return NO_DIFFICULTY;
            }

            switch (event.type) {
            case sf::Event::MouseButtonPressed:
                MousePressed(event);
                while (m_difficultyOption != 3) {
                    switch (m_difficultyOption)
                    {
                    case 0:
                        m_difficulty = EASY;
                        break;
                    case 1:
                        m_difficulty = MEDIUM;
                        break;
                    case 2:
                        m_difficulty = HARD;
                        break;
                    default:
                        break;
                    }
                    m_buttons.drawExitReplay(m_window);
                    return m_difficulty;
                }
            }
        }
    }
}
// -------------------------------------------------------------------------------------------------
sf::Sprite GameController::createSprite(const sf::Texture& texture)
{
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(m_window.getSize().x / sprite.getLocalBounds().width,
        m_window.getSize().y / sprite.getLocalBounds().height);
    return sprite;
}
// -------------------------------------------------------------------------------------------------
sf::Sprite GameController::setPicWin(){ return createSprite(m_PictureWin); }
// -------------------------------------------------------------------------------------------------
sf::Sprite GameController::setPicLose(){ return createSprite(m_PictureLose);}
// -------------------------------------------------------------------------------------------------
sf::Sprite GameController::setMenuBackground(){ return createSprite(m_PictureMenu); }
// -------------------------------------------------------------------------------------------------
sf::Sprite GameController::setBackgroundPic(){ return createSprite(m_PictureBackground);}
// -------------------------------------------------------------------------------------------------
void GameController::drawHexagons()
{
    for (std::vector<std::vector<sf::CircleShape>>::iterator it_1 = m_hexagons.begin(); it_1 != m_hexagons.end(); ++it_1) {
        for (std::vector<sf::CircleShape>::iterator it_2 = (*it_1).begin(); it_2 != (*it_1).end(); ++it_2)
            m_window.draw(*it_2);
    }
}
// -------------------------------------------------------------------------------------------------
void GameController::drawButtons()
{
    for (std::array<sf::RectangleShape, COLOR_SIZE>::iterator it = m_color_buttons.begin(); it != m_color_buttons.end(); ++it)
        m_window.draw(*it);
}
