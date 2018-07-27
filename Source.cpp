#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <queue>
#include <fstream>
#include <string>

#include "HitObject.h"

using namespace std;

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "nano rythm"/*, sf::Style::Fullscreen*/);
	window.setKeyRepeatEnabled(false);
	
	queue <HitObject> objectQueue;
	queue <HitObject> objToDrawQ;

	bool queued = false;

	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();

	sf::Sprite dummy;
	sf::Texture texture;
	texture.loadFromFile("Skin\\fruit-drop.png");

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	sf::SoundBuffer hitSoundBuffer;
	sf::Music music;
	music.openFromFile("Songs\\Team Nekokan - Can't Defeat Airman\\airman.ogg");
	hitSoundBuffer.loadFromFile("Skin\\sound.wav");
	sf::Sound hitSound;
	hitSound.setBuffer(hitSoundBuffer);

	sf::Text ms;
	ms.setFont(arial);
	ms.setPosition(0, 0);

	double AR = 10;
	int start = 0;
	bool playing = false;
	HitObject dumm;
	while (window.isOpen()) 
	{
		elapsed = clock.getElapsedTime();
		ms.setString(to_string(elapsed.asMilliseconds()));

		//if (queued && elapsed.asMilliseconds() >= start) {
		//	music.play();
		//	playing = true;
		//	// clock.restart();
		//}

		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			else if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::N) {
					music.play();
					std::ifstream file;
					file.open("Songs\\Team Nekokan - Can't Defeat Airman\\airman.osu");
					if (file.is_open())
					{
						string _x, _y, _time;
						int x, y, time;
						while (getline(file, _x, ',') &&
							getline(file, _y, ',') &&
							getline(file, _time, ','))
						{
							x = atoi(_x.c_str());
							y = atoi(_y.c_str());
							time = atoi(_time.c_str());

							HitObject object(time, x, y, texture, AR);
							objectQueue.push(object);

							string dummy;
							getline(file, dummy, '\n');
						}
						std::cout << "DONE INSERTS ALL OBJECT!" << endl;
						queued = true;
						clock.restart();
						/*start = 3660;*/
					}
					else {
						std::cout << "cannot open file";
					}
					file.close();

				}
				else if (e.key.code == sf::Keyboard::P && queued) {
					std::cout << objectQueue.front().getPostX() << " "
						<< objectQueue.front().getPostY() << " "
						<< objectQueue.front().getSpawnTime() << endl;
					objectQueue.pop();
				}
			}
			
		}
		
		if (!objectQueue.empty() /*&& playing*/) {
			if (elapsed.asMilliseconds() >= objectQueue.front().getSpawnTime() && elapsed.asMilliseconds() <= objectQueue.front().getHitTime()) {
				objToDrawQ.push(objectQueue.front());
				objectQueue.pop();
			}
		}

		if (!objToDrawQ.empty() /*&& playing*/) {
			HitObject object = objToDrawQ.front();
			
			if (elapsed.asMilliseconds() >= object.getHitTime() ) {
				objToDrawQ.pop();
				hitSound.play();
			}
		}

		window.clear();
		
		if (!objToDrawQ.empty() /*&& playing*/) {
			queue <HitObject> temp;
			sf::Text numb;
			numb.setFont(arial);
			numb.setColor(sf::Color::Red);
			int count = 1;
			while (!objToDrawQ.empty()) {
				window.draw(objToDrawQ.front().getSprite());
				
				numb.setString(to_string(count));
				numb.setPosition(objToDrawQ.front().getSprite().getPosition());
				window.draw(numb);
				count += 1;
				temp.push(objToDrawQ.front());
				objToDrawQ.pop();
			}
			objToDrawQ = temp;
		}
		window.draw(ms);

		window.display();
	}
	return 0;
}