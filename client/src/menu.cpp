// #include "../include/game.hpp"

// Menu::Menu(textures& tx, sf::RenderWindow& window) {
//     _font.loadFromFile("../../client/assets/fonts/francis.ttf");

//     _titleText.setFont(_font);
//     _titleText.setString("R-Type");
//     _titleText.setCharacterSize(96);
//     FloatRect titleBounds = _titleText.getLocalBounds();
//     _titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
//     _titleText.setPosition(window.getSize().x / 2, window.getSize().y * 0.20);

//     setUpSprite(_playSprite, tx.getPlayTexture(), window, 0);
//     setUpSprite(_settingsSprite, tx.getSettingsTexture(), window, -1);
//     setUpSprite(_tutorialSprite, tx.getTutorialTexture(), window, 1);
//     setUpSprite(_exitSprite, tx.getExitTexture(), window, -2);
//     setUpSprite(_aboutSprite, tx.getAboutTexture(), window, 2);

//     sprites.push_back(_playSprite);
//     sprites.push_back(_settingsSprite);
//     sprites.push_back(_exitSprite);
//     sprites.push_back(_tutorialSprite);
//     sprites.push_back(_aboutSprite);

//     selectedItemIndex = 2;
// }

// void Menu::setUpSprite(sf::Sprite& sprite, const sf::Texture& texture, sf::RenderWindow& window, int positionOffset) {
//     sprite.setTexture(texture);
//     sprite.setScale(0.4f, 0.4f);

//     float centerX = window.getSize().x / 2;
//     float centerY = window.getSize().y * 0.6;
//     float spriteWidth = sprite.getGlobalBounds().width;
//     _spacing = 100.0f;

//     sprite.setPosition(centerX + positionOffset * (spriteWidth + _spacing) - spriteWidth / 2, centerY);
// }

// void Menu::moveMenu(int direction) {
//     float moveDistance = calculateMoveDistance();

//     for (auto& sprite : sprites) {
//         sprite.move(direction * moveDistance, 0);
//     }

//     wrapSprites();
//     updateSelectedItemIndex(direction);
// }

// float Menu::calculateMoveDistance() const {
//     if (!sprites.empty()) {
//         return sprites[0].getGlobalBounds().width + _spacing;
//     }
//     return 0;
// }

// void Menu::wrapSprites() {
//     // Wrap around logic for sprites
//     // If a sprite goes off-screen on one side, it reappears on the other
//     // Adjust the positions of the sprites accordingly
// }

// void Menu::updateSelectedItemIndex(int direction) {
//     // Update the selected item index based on the direction of movement
//     // Ensure that the index wraps around correctly
// }

// void Menu::draw(sf::RenderWindow& window) {
//     window.draw(_titleText);

//     for (const auto& sprite : sprites) {
//         window.draw(sprite);
//     }
// }

// GameState Menu::getCurrentState() const {
//     return currentState;
// }

// void Menu::setCurrentState(GameState state) {
//     currentState = state;
// }

// Menu::~Menu() {}
