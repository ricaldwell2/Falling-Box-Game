//This is the falling box game project

#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//Drawing background with name on top of window
sf::RenderWindow window(sf::VideoMode(1280, 720), "Falling Box Game");

//This funciton will handle increasing the speed of the enemy falling in relation to the score
void setLevel(int score, int speed)
{

}

int main()
{
	

	//Creating bounderies for the window
	sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());

	//Creating instance of HeroSquare (height and width)
	sf::RectangleShape HeroSquare(sf::Vector2f(60, 60));
	//Setting the color of the HeroSquare
	HeroSquare.setFillColor(sf::Color(51, 255, 255));
	//Setting the starting postion for the HeroSquare shape using a variable
	sf::Vector2f HeroPos(635, 650);
	HeroSquare.setPosition(HeroPos);						//BEWARE: shape position is relative to top left corner

	//Make a dynamic vector made up filled with red squares (Don't need a specific RectangleShape variable for each one)
	std::vector<sf::RectangleShape> EnemySquares;

	//This is the bounding box for the EnemySquares
	sf::FloatRect EnemyBoundingBox = HeroSquare.getGlobalBounds();	//Have a problem getting bounds for the EnemySquares since it's in a vector
	
	//yVelocity is setting the speed for the falling anmimation
	float yVelocity = 2;
	float xVelocity = 0;

	int score = 0;

	//Creating Event class so window will open.
	sf::Event event;

	//While loop handles what is happening while game window is open
	while (window.isOpen()) 
	{

		while (window.pollEvent(event)) 
		{
			//If statement handles if the display is closed or the game is quit
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}

			//Attempt at getting user to be able to move square shape
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//If else conditions keep HeroSquare within the bounds of the screen
				sf::Vector2f position = HeroSquare.getPosition();
				if (position.x <= windowBounds.left)
				{
					position.x = std::min(position.x, windowBounds.left + windowBounds.width - HeroSquare.getSize().x);
				}
				else 
				{
					HeroSquare.move(-60, 0);
				}
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//If else conditions keep HeroSquare within the bounds of the screen
				sf::Vector2f position = HeroSquare.getPosition();
				if (position.x >= windowBounds.left + windowBounds.width - HeroSquare.getSize().x)
				{
					position.x = std::max(position.x, windowBounds.left);
					position.x = std::min(position.x, windowBounds.left + windowBounds.width - HeroSquare.getSize().x);
				}

				else
				{
					HeroSquare.move(60, 0);
				}
			}
			
		}
		EnemySquares.push_back(sf::RectangleShape());
		EnemySquares.back().setSize(sf::Vector2f(60, 60));
		EnemySquares.back().setFillColor(sf::Color(255, 0, 0));
		EnemySquares.back().setPosition(rand() % 1280, 0);

		std::cout << EnemySquares.size() << std::endl;

		//Draw event
		window.clear();
		window.draw(HeroSquare);
		for (int i = 0; i < EnemySquares.size(); ++i)	//Using this for loop to try to draw each element withing the vector Enemy
		{
			//Animation for moving EnemySquares
			EnemySquares[i].move(0, yVelocity);

			//Trying to set the position of each different square right before drawing it
			window.draw(EnemySquares[i]);
		}
		
		window.display();
	}

	return 0;
}

/*
TODO:
- Create bounding box for square and falling squares to create collision priciple
- Have multiple EnemySquares show up in random spots at top of screen
- Keep track of score
- Make sure to keep HeroSquare and EnemySquares within bounds of screen (right and left sides)
- Make the bounds not let out half the square...if that makes sense
*/