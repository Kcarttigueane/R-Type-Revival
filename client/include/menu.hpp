// #ifndef MENU_HPP_
// #define MENU_HPP_

// #include "includes.hpp"
// #include "game_states.hpp"
// #include "textures.hpp"

// class Menu {
// private:
//     GameState currentState;
//     std::vector<std::string> menuItems;
//     std::size_t selectedItemIndex;
//     sf::Font _font;
//     sf::Text _titleText;
//     sf::Text _startText;
//     sf::Text _settingsText;
//     sf::Text _exitText;
//     std::vector<sf::Text> texts;
//     sf::Sprite _playSprite;
//     sf::Sprite _settingsSprite;
//     sf::Sprite _exitSprite;
//     sf::Sprite _tutorialSprite;
//     sf::Sprite _aboutSprite;
//     std::vector<sf::Sprite> sprites;
//     float _spacing;

// public:
//     Menu(textures& tx, sf::RenderWindow& window);
//     void draw(sf::RenderWindow& window);
//     GameState getCurrentState() const;
//     void setCurrentState(GameState state);
//     void setUpSprite(sf::Sprite &sprite, const sf::Texture &texture, sf::RenderWindow &window, int positionOffset);
//     void moveMenu(int direction);
//     float calculateMoveDistance() const;
//     void wrapSprites();
//     void updateSelectedItemIndex(int direction);
//     ~Menu();
// };

// #endif /* !MENU_HPP_ */
