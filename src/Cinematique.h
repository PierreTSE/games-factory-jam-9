#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include <SFML/Graphics.hpp>
#include "constantes.hpp"

class Cinematique
{
private:
	std::vector<sf::Sprite> images;
	sf::Time temps = sf::Time::Zero;

public:
	sf::Time degradTime = sf::Time::Zero;
	sf::RectangleShape rect = sf::RectangleShape({ (float)WINDOW_SIZE_X,(float)WINDOW_SIZE_Y });
	int currentImg = 0;
	bool first = true;
	int count = 0;
	void fondu(sf::RenderWindow &window);
	Cinematique();
	void animation(sf::RenderWindow &window);
};
