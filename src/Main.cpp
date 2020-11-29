#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>
#include "funcs.hpp"

#define Object(a, b) static_cast<a*>(objects[b])

std::vector<std::string> bank{
	"0", "1", "2", "3", "4",
	"5", "6", "7", "8", "9",
	"a", "b", "c", "d", "e",
	"f", "g", "h", "i", "j",
	"k", "l", "m", "n", "o",
	"p", "q", "r", "s", "t",
	"u", "v", "w", "x", "y",
	"z", "A", "B", "C", "D",
	"E", "F", "G", "H", "I",
	"J", "K", "L", "M", "N",
	"O", "P", "Q", "R", "S",
	"T", "U", "V", "W", "X",
	"X", "Z", "!", "?"
};

// Password Generator
int main() {
	/* Various Variables */
	int passwordLength = 10;
	int maxPasswordLength = 64;
	int maxPasswordVisibleLength = 30;
	int minPasswordLength = 1;

	// Graphics Setup
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "PasswordMaker", sf::Style::Default);
	std::map<std::string, sf::Drawable*> objects;
	auto realMode = sf::VideoMode::getDesktopMode();

	
	// Setup Scene
	/* BG */ objects.insert(std::pair<std::string, sf::Drawable*>("BG", new sf::RectangleShape(sf::Vector2f(realMode.width, realMode.height))));
	Object(sf::RectangleShape, "BG")->setFillColor(sf::Color(137, 82, 95, 255));

	/* Generate Button */ objects.insert(std::pair<std::string, sf::Drawable*>("Box", new sf::RectangleShape(sf::Vector2f(300, 100))));
	Object(sf::RectangleShape, "Box")->setOrigin(Object(sf::RectangleShape, "Box")->getSize().x / 2, Object(sf::RectangleShape, "Box")->getSize().y / 2);
	Object(sf::RectangleShape, "Box")->setPosition(sf::Vector2f(realMode.width / 2, (realMode.height / 3) * 2));
	sf::Texture boxTexture;
//	boxTexture.loadFromFile();
//	Object(sf::RectangleShape, "Box")->setTexture();

	/* Size Buttons */
	objects.insert(std::pair<std::string, sf::Drawable*>("Size Up", new sf::RectangleShape(sf::Vector2f(100, 100)))); // Up
	Object(sf::RectangleShape, "Size Up")->setOrigin(Object(sf::RectangleShape, "Size Up")->getSize().x / 2, Object(sf::RectangleShape, "Size Up")->getSize().y / 2);
	Object(sf::RectangleShape, "Size Up")->setPosition(sf::Vector2f((realMode.width / 2) + (Object(sf::RectangleShape, "Box")->getSize().x / 2) + (Object(sf::RectangleShape, "Size Up")->getSize().x / 2), (realMode.height / 3) * 2));
	sf::Texture sizeUpTexture;
	sizeUpTexture.loadFromFile("assets/textures/plus_sign.png");
	Object(sf::RectangleShape, "Size Up")->setTexture(&sizeUpTexture);
	objects.insert(std::pair<std::string, sf::Drawable*>("Size Down", new sf::RectangleShape(sf::Vector2f(100, 100)))); // Down
	Object(sf::RectangleShape, "Size Down")->setOrigin(Object(sf::RectangleShape, "Size Down")->getSize().x / 2, Object(sf::RectangleShape, "Size Down")->getSize().y / 2);
	Object(sf::RectangleShape, "Size Down")->setPosition(sf::Vector2f((realMode.width / 2) - ((Object(sf::RectangleShape, "Box")->getSize().x / 2) + (Object(sf::RectangleShape, "Size Down")->getSize().x / 2)), (realMode.height / 3) * 2));
	sf::Texture sizeDownTexture;
	sizeDownTexture.loadFromFile("assets/textures/minus_sign.png");
	Object(sf::RectangleShape, "Size Down")->setTexture(&sizeDownTexture);

	/* Font */ sf::Font font;
	std::cout << std::filesystem::current_path() << std::endl;
	font.loadFromFile("assets/fonts/Roboto-Regular.ttf");
	
	/* Password Box*/ objects.insert(std::pair<std::string, sf::Drawable*>("Password Text", new sf::Text(" ", font, 30U)));
	
	/* Password Size Box*/ objects.insert(std::pair<std::string, sf::Drawable*>("Password Size Text", new sf::Text(std::to_string(passwordLength), font, 30U)));
	Object(sf::Text, "Password Size Text")->setOrigin(sf::Vector2f(Object(sf::Text, "Password Size Text")->getGlobalBounds().width / 2, (Object(sf::Text, "Password Size Text")->getGlobalBounds().height / 2)));
	Object(sf::Text, "Password Size Text")->setPosition(sf::Vector2f( realMode.width / 2, ((realMode.height / 3) * 2) + ((Object(sf::Text, "Password Size Text")->getGlobalBounds().height / 2) + ((Object(sf::RectangleShape, "Box")->getGlobalBounds().height / 2)))));

	while (window.isOpen()) {
		// Input
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
			case sf::Event::MouseButtonPressed:
				sf::Vector2f mousePosF;
				mousePosF.x = sf::Mouse::getPosition().x;
				mousePosF.y = sf::Mouse::getPosition().y;
				if (static_cast<sf::RectangleShape*>(objects["Box"])->getGlobalBounds().contains(mousePosF)) {
					std::string result = generate(bank, passwordLength);
					if (result.size() <= maxPasswordVisibleLength) {
						Object(sf::Text, "Password Text")->setString(result);
					} else { 
						Object(sf::Text, "Password Text")->setString((result.substr(0, maxPasswordVisibleLength - 3).append("...")));
						std::cout << (result.substr(27).append("...")) << std::endl;
					}
					Object(sf::Text, "Password Text")->setCharacterSize(800 / Object(sf::Text, "Password Text")->getString().getSize());
					Object(sf::Text, "Password Text")->setOrigin(Object(sf::Text, "Password Text")->getGlobalBounds().width / 2, Object(sf::Text, "Password Text")->getGlobalBounds().height / 2);
					Object(sf::Text, "Password Text")->setPosition(sf::Vector2f(realMode.width / 2, (realMode.height / 3) * 1));
					std::cout << "Password is : [" << result << "]" << std::endl;
				} else if (static_cast<sf::RectangleShape*>(objects["Size Up"])->getGlobalBounds().contains(mousePosF)) {
					if (passwordLength != maxPasswordLength) {
						passwordLength++;
						Object(sf::Text, "Password Size Text")->setString(std::to_string(passwordLength));
					} else {
						std::cout << "Cannot go above size [" << maxPasswordLength << "]" << std::endl;
					}
				} else if (static_cast<sf::RectangleShape*>(objects["Size Down"])->getGlobalBounds().contains(mousePosF)) {
					if (passwordLength != minPasswordLength) {
						passwordLength--;
						Object(sf::Text, "Password Size Text")->setString(std::to_string(passwordLength));
					} else {
						std::cout << "Cannot go below size [" << minPasswordLength << "]" << std::endl;
					}
				}
				break;
			}
		}
		//Draw
		window.clear();
		for (const auto& drawable : objects) {
			window.draw(*drawable.second);
		}
		window.display();
	}
}