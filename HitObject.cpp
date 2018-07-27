#include "HitObject.h"



HitObject::HitObject()
{
	hit_time = 0;
	postX = 0;
	postY = 0;
}

HitObject::HitObject(int _hit_time, int _postX, int _postY, sf::Texture &texture, double AR) 
{
	hit_time = _hit_time;
	int preempt = 0;
	if (AR < 5) {
		preempt = 1200 + 600 * (5 - AR) / 5;
	}
	else if (AR == 5) {
		preempt = 1200;
	}
	else {
		preempt = 1200 - 750 * (AR - 5) / 5;
	}
	spawn_time = hit_time - preempt;
	postX = _postX;
	postY = _postY;
	body.setTexture(texture);
	body.setPosition(postX, postY);
	// body.setColor(sf::Color(255, 255, 255, 0));
}

int HitObject::getPostX() 
{
	return postX;
}

int HitObject::getPostY() 
{
	return postY;
}

int HitObject::getSpawnTime() 
{
	return spawn_time;
}

int HitObject::getHitTime() {
	return hit_time;
}

void HitObject::move() {
	
}

sf::Sprite HitObject::getSprite() {
	return body;
}

HitObject::~HitObject()
{
}
