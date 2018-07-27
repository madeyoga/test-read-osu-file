#pragma once
#include <SFML\Graphics.hpp>

class HitObject
{
private:
	int hit_time;
	int spawn_time;
	int postX;
	int postY;
	sf::Sprite body;
	sf::Texture bodyTexture;
public:
	HitObject();
	HitObject(int _hit_time, int _postX, int _postY, sf::Texture &texture, double AR);
	int getSpawnTime();
	int getHitTime();
	int getPostX();
	int getPostY();
	void move();
	sf::Sprite getSprite();
	~HitObject();
};

