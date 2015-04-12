/*
 * Tower.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: Karan
 */

#include "Tower.h"
#include "GameWorld.h"

Tower::Tower()
{
	memset(range_, 0, sizeof(range_));
	memset(physical_damage_, 0, sizeof(physical_damage_));
	memset(magical_damage_, 0, sizeof(magical_damage_));
	memset(speed_damage_, 0, sizeof(speed_damage_));
	memset(speed_damage_duration_, 0, sizeof(speed_damage_duration_));
	memset(fire_rate_, 0, sizeof(fire_rate_));
	memset(cost_, 0, sizeof(cost_));

	current_level_ = 0;
}

Tower::~Tower()
{}

Tower* Tower::create(GameWorld* game_world, CCPoint position)
{
	Tower* tower = new Tower();
	if(tower && tower->init(game_world, position))
	{
		tower->autorelease();
		tower->game_world_ = game_world;
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return NULL;
}

bool Tower::init(GameWorld* game_world, CCPoint position)
{
	if(!CCSprite::initWithFile("tower.png"))
	{
		return false;
	}

	setPosition(position);

	return true;
}

void Tower::Update()
{}
