//
// Created by harshal on 10/31/20.
//

#pragma once
#include <SFML/Window.hpp>
#include <array>
#include <SFML/Graphics.hpp>

class Mandelbrot {
public:
	explicit                    Mandelbrot(int maxIterations_ = 100);
	void                        run();

private:
	void                        processEvents();
	void                        update(sf::Time elapsedTime);
	void                        render();
	void                        handelInput(sf::Keyboard::Key key, bool isPressed);
	int                         getMaxIterations(double x, double y) const;

private:
	static const sf::Time                       TimePerFrame;
	sf::RenderWindow                            mWindow;
	sf::VertexArray                             points;
	int                                         maxIterations;
};
