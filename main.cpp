//This is the falling box game project

#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

int main()
{
	//Drawing background with name on top of window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Falling Box Game");

	//Creating bounderies for the window
	sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());

	//Long unseen box at the bottom of the display will "catch" EnemySquares and increase score
	sf::RectangleShape CatchBox(sf::Vector2f(1300, 10));
	CatchBox.setFillColor(sf::Color(255, 255, 255));
	sf::Vector2f CatchBoxPos(0, 720);
	CatchBox.setPosition(CatchBoxPos);

	//Creating instance of HeroSquare (height and width)
	sf::RectangleShape HeroSquare(sf::Vector2f(60, 60));
	//Setting the color of the HeroSquare
	HeroSquare.setFillColor(sf::Color(51, 255, 255));
	//Setting the starting postion for the HeroSquare shape using a variable
	sf::Vector2f HeroPos(635, 650);
	HeroSquare.setPosition(HeroPos);						//BEWARE: shape position is relative to top left corner
	
	//This is the bounding box for the HeroSquare
	sf::FloatRect HeroBoundingBox = HeroSquare.getLocalBounds();

	//Setting clock variable
	sf::Clock clock;

	//Make a dynamic vector made up filled with red squares (Don't need a specific RectangleShape variable for each one)
	std::vector<sf::RectangleShape> EnemySquares;

	//yVelocity is setting the speed for the falling anmimation
	float yVelocity = .5;
	float xVelocity = 0;

	//Variable to hold the score
	int score = 0;

	//This is the font used for showing the score at the bottom right corner of the screen
	sf::Font openSans;
	if (!openSans.loadFromFile("OpenSans-Bold.ttf"))
	{
		throw("ERROR: COULD NOT LOAD FONT");
	}

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
		//Level Easy
		if (score <= 20)
		{
			if (clock.getElapsedTime().asSeconds() > 0.25)	//how many EnemySquares fall per clock.asSeconds()...??
			{
				EnemySquares.push_back(sf::RectangleShape());
				EnemySquares.back().setSize(sf::Vector2f(60, 60));
				EnemySquares.back().setFillColor(sf::Color(255, 0, 0));
				EnemySquares.back().setPosition(rand() % 1280, 0);

				std::cout << EnemySquares.size() << std::endl;

				clock.restart();
			}
		}
		//Level Medium
		else if (score <= 40)
		{
			if (clock.getElapsedTime().asSeconds() > 0.15)
			{
				EnemySquares.push_back(sf::RectangleShape());
				EnemySquares.back().setSize(sf::Vector2f(60, 60));
				EnemySquares.back().setFillColor(sf::Color(255, 0, 0));
				EnemySquares.back().setPosition(rand() % 1280, 0);

				std::cout << EnemySquares.size() << std::endl;

				clock.restart();
			}
		}
		//Level Hard
		else
		{
			if (clock.getElapsedTime().asSeconds() > 0.10)
			{
				EnemySquares.push_back(sf::RectangleShape());
				EnemySquares.back().setSize(sf::Vector2f(60, 60));
				EnemySquares.back().setFillColor(sf::Color(255, 0, 0));
				EnemySquares.back().setPosition(rand() % 1280, 0);

				std::cout << EnemySquares.size() << std::endl;

				clock.restart();
			}
		}

		//Trying to create text at the bottom of the screen to keep track of score
		sf::Text Score;
		sf::Text ScoreNum;
		Score.setFont(openSans);
		Score.setStyle(sf::Text::Bold);
		Score.setString(("Score: ") + (std::to_string(score)));
		Score.setFillColor(sf::Color::White);
		Score.setPosition(1050, 50);
		
		//Draw event
		window.clear();
		window.draw(HeroSquare);
		window.draw(Score);
		window.draw(CatchBox);

		for (int i = 0; i < EnemySquares.size(); ++i)
		{
			//Animation for moving EnemySquares
			EnemySquares[i].move(0, yVelocity);

			window.draw(EnemySquares[i]);

			//This block of code is how the boundries work withing the game during gameplay
			sf::FloatRect catchBoxBound = CatchBox.getGlobalBounds();
			sf::FloatRect enemyBound = EnemySquares[i].getGlobalBounds();
			sf::FloatRect heroBoundingBox = HeroSquare.getGlobalBounds();
			if (heroBoundingBox.intersects(enemyBound))
			{
				window.close();
				std::cout << "Your final score is: " << score << "!" << std::endl;
			}
			//trying to create bounding boxes for the EnemySquares to increase score
			if (enemyBound.intersects(catchBoxBound))
			{
				//Collision!
				score = EnemySquares.size();
			}
		}
		window.display();
	}
	system("PAUSE");
	return 0;
}

/*
TODO:
- Fix score bug, how do I keep track of score and count each EnemySquares square that intersects the CatchBox?
*/