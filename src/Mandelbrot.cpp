//
// Created by harshal on 10/31/20.
//

#include "../include/Mandelbrot.hpp"
#include <cmath>
#include <complex>
#include <iostream>

const sf::Time Mandelbrot::TimePerFrame = sf::seconds(1.F/60.F);


Mandelbrot::Mandelbrot(int maxIterations_)
: mWindow(sf::VideoMode(1080,680), "Mandelbrot Set"), maxIterations(maxIterations_) {
	points.setPrimitiveType(sf::Points);
	points.resize(mWindow.getSize().x * mWindow.getSize().y);
}


void Mandelbrot::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()){
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame){
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Mandelbrot::processEvents() {
	sf::Event event{};
	while (mWindow.pollEvent(event)){
		switch (event.type){
			case sf::Event::KeyPressed:
//						handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
//						handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Mandelbrot::update(sf::Time elapsedTime) {
	double xFractal{};
	double yFractal{};
	int iterations{};
	for(int i = 0; i < mWindow.getSize().x; i++) {
		for(int j = 0; j < mWindow.getSize().y; j++) {

			xFractal = ((float)i - (float)mWindow.getSize().x/2) * 2.F/static_cast<float>(j);
			yFractal = ((float)j - (float)mWindow.getSize().y/2) * 2.F/static_cast<float>(j);
			iterations = getMaxIterations(xFractal,yFractal);
			auto n = (float)iterations;
			float a = 0.1F;

			auto index = (i * mWindow.getSize().x) + j;
			if(index < mWindow.getSize().x * mWindow.getSize().y) {
				points[index].color.r = std::lround(0.5f * std::sin(a * n) + 0.5f);
				points[index].color.g = std::lround(0.5f * std::sin(a * n + 2.094f) + 0.5f);
				points[index].color.b = std::lround(0.5f * std::sin(a * n + 4.188f) + 0.5f);
				points[index].position = sf::Vector2f(i,j);
			} else {
				std::cerr << "Out of bounds\n";
			}
			if(i == 2) {
				std::cout << "x: " << xFractal << " y:" << yFractal << " index:" << index << " iterations:" << iterations << std::endl;
			}
		}
	}
}

void Mandelbrot::render() {
	mWindow.clear();
	sf::RectangleShape r;
	sf::Vector2f vf((float)mWindow.getSize().x/2, (float)mWindow.getSize().y/2);
	mWindow.draw(points);
	mWindow.display();
}

void Mandelbrot::handelInput(sf::Keyboard::Key key, bool isPressed) {

}

int Mandelbrot::getMaxIterations(double x, double y) const {
	std::complex<double> z = 0;
	std::complex<double> c(x,y);
	int iterations{};
	while (iterations < maxIterations) {
		z = z * z + c;
		if(std::abs(z) > 2) {
			break;
		}
		iterations++;
	}
//	std::clog << iterations << " " << "x: " << x << " y: " << y << " z: " << z << "\n";
	return iterations;
}



