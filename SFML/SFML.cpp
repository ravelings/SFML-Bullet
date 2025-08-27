#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include "bullet.h"

const static float VIEW_HEIGHT{ 512.0f};

void handleText(const sf::Event::TextEntered* textEntered)
{
	if (textEntered->unicode < 128)
	{
		std::cout << static_cast<char>(textEntered->unicode) << std::endl;
	}
}

void Resized(const sf::RenderWindow& window,  sf::View& view) // calculates aspect ratio and multiplies by view_height so that resized is always relative to window size
{
	auto aspect_ratio = (float)(window.getSize().x) / (float)(window.getSize().y); // aspect ratio width / height

	view.setSize(sf::Vector2f(VIEW_HEIGHT * aspect_ratio, VIEW_HEIGHT));
}

bool inBoundary(Bullet& bullet, sf::View* view)
{
	float bound_x = view->getSize().x;
	float bound_y = view->getSize().y;

	if (std::abs(bullet.currentPos.x) > std::abs(bound_x) || std::abs(bullet.currentPos.y) > std::abs(bound_y)) { return false; }
	else { return true; }
}

void Shoot(Bullet& bullet, sf::RenderWindow* window, sf::View* view)
{
	sf::Clock dt{};
	dt.restart();

	while (inBoundary(bullet, view))
	{

		window->clear(sf::Color::Black);

		bullet.setPosition(bullet.currentPos);	// set bullet pos as current pos

		bullet.currentPos.x += bullet.velocity_x * dt.getElapsedTime().asSeconds();								// set new pos 
		bullet.currentPos.y += bullet.velocity_y * dt.getElapsedTime().asSeconds();		// set new pos 

		window->draw(bullet);		// render the bullet
		window->display();

		bullet.timestep += 1;

	}

	std::cout << "Bullet destroyed." << std::endl;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 512, 512 }), "Super Window", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	//sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f)); // define shape class
	//sf::Texture playerTexture;

	//playerTexture.loadFromFile("C:\\Users\\ravel\\source\\repos\\SFML\\SFML\\x64\\Debug\\texture\\bucktooth.jpg");
	//player.setTexture(&playerTexture);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) // getIf returns nullptr if TextEntered == false
			{
				handleText(textEntered);
			}
			if (event->is<sf::Event::Resized>())
			{
				Resized(window, view);
			}
			if (event->is<sf::Event::MouseButtonPressed>())
			{
				const auto& button = event->getIf<sf::Event::MouseButtonPressed>();
				if (button->button == sf::Mouse::Button::Left)
				{
					const sf::Vector2f target = window.mapPixelToCoords({ button->position.x, button->position.y });	// converts pixels to world coords

					Bullet bullet(view.getCenter(), target);

					Shoot(bullet, &window, &view);

				}
			}
		}

		window.setView(view);
	}

}	