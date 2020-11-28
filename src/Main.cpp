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
	
	/* Font */
	sf::Font font;
	std::cout << std::filesystem::current_path() << std::endl;
	font.loadFromFile("assets/fonts/Roboto-Regular.ttf");
	
	/* Text Box*/ objects.insert(std::pair<std::string, sf::Drawable*>("Text", new sf::Text(" ", font, 30U)));


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
					static int size = 27;
					static int MAX_SIZE = 40;
					std::string result = generate(bank, size++);
					if (result.size() <= MAX_SIZE) {
						Object(sf::Text, "Text")->setString(result);
					} else { 
						Object(sf::Text, "Text")->setString((result.substr(0, MAX_SIZE - 3).append("...")));
						std::cout << (result.substr(27).append("...")) << std::endl;
					}
					Object(sf::Text, "Text")->setCharacterSize(800 / Object(sf::Text, "Text")->getString().getSize());
					Object(sf::Text, "Text")->setOrigin(Object(sf::Text, "Text")->getGlobalBounds().width / 2, Object(sf::Text, "Text")->getGlobalBounds().height / 2);
					Object(sf::Text, "Text")->setPosition(sf::Vector2f(realMode.width / 2, (realMode.height / 3) * 1));
					std::cout << "Password is : [" << result << "]" << std::endl;
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