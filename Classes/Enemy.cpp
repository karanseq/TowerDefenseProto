/*
 * Enemy.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: Karan
 */

#include "Enemy.h"

Enemy::Enemy()
{
	path_indices_.clear();
}

Enemy::~Enemy()
{}

Enemy* Enemy::create(GameWorld* game_world)
{
	Enemy* enemy = new Enemy();
	if(enemy && enemy->init(game_world))
	{
		enemy->autorelease();
		enemy->game_world_ = game_world;
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Enemy::init(GameWorld* game_world)
{
	if(!CCSprite::initWithFile("enemy.png"))
	{
		return false;
	}

	return true;
}

void Enemy::Update()
{

}
