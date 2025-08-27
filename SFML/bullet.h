#pragma once
#ifndef BULLET
#define BULLET
#include <SFML/Graphics.hpp>
#include <cmath>

struct Bullet: public sf::CircleShape
{
	//Variables
public:
	sf::Vector2f	initPos{};			// initial position
	sf::Vector2f	currentPos{};		// current position
	sf::Vector2f	direction{};		// direction vector	

	float			velocity_y{};		// velocity in m/s
	float			velocity_x{};		// velocity in m/s

	int				timestep{};			// time elapsed in s

	// Constructor
public:

	Bullet(sf::Vector2f init, sf::Vector2f target)
		: initPos{ init }, currentPos{ init }
	{
		sf::Vector2f vector{ (target.x - init.x), (target.y - init.y) };
		direction = vector.normalized();

		float velocity{ 3.0f };
		velocity_x = velocity * direction.x;
		velocity_y = velocity * direction.y;

		setRadius(5);
		setFillColor(sf::Color::Red);
	}

};

#endif