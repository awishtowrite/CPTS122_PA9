#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Paddle.h"
#include "Ball.h"

using std::cout; 
using std::endl; 

int main(void)
{
	srand(time(NULL)); 

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Works!"); 
	sf::CircleShape shape(100.f); 

	Paddle p1Paddle(sf::Vector2f(0, 0), sf::Vector2f(50, 100), sf::Color::Magenta),
		p2Paddle(sf::Vector2f(450, 0), sf::Vector2f(50, 100), sf::Color::Cyan); 

	Ball gameBall(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2),
		p1Paddle.getSize().y / 6, sf::Color::Green); 

	shape.setFillColor(sf::Color::Green); 
	int direction = 1; 
	double ballVert = 0; 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close(); 
			}
		}

		// Player 1 Paddle control: 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1Paddle.move(0, 0.03); 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			p1Paddle.move(0, -0.03); 
		}

		// Player 2 Paddle control: 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			p2Paddle.move(0, 0.03); 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			p2Paddle.move(0, -0.03); 
		}

		// Collisions: 
		if (p2Paddle.getGlobalBounds().intersects(gameBall.getGlobalBounds()))
		{
			direction *= -1; 

			// Set random height value: 
			ballVert = double(rand() % 2) / 100;
		}
		if (p1Paddle.getGlobalBounds().intersects(gameBall.getGlobalBounds()))
		{
			direction *= -1; 

			// Set random height value: 
			ballVert = double(rand() % 2) / 100;
		}

		// Move ball: 
		gameBall.move(0.03 * direction, ballVert); 

		window.clear(); 
		window.draw(p1Paddle); 
		window.draw(p2Paddle); 
		window.draw(gameBall); 
		window.display(); 

		//// Check bounds: 
		//if (gameBall.getPosition().x > 500)
		//{
		//	cout << "Player 1 Wins!" << endl; 
		//	window.close(); 
		//}
		//if (gameBall.getPosition().x < 0)
		//{
		//	cout << "Player 2 Wins!" << endl; 
		//	window.close(); 
		//}
	}

}
