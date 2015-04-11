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
	range_[NUM_TOWER_UPGRADES] = {0.0f};
	physical_damage_[NUM_TOWER_UPGRADES] = {0.0f};
	magical_damage_[NUM_TOWER_UPGRADES] = {0.0f};
	speed_damage_[NUM_TOWER_UPGRADES] = {0.0f};
	speed_damage_duration_[NUM_TOWER_UPGRADES] = {0};
	fire_rate_[NUM_TOWER_UPGRADES] = {0.0f};
	cost_[NUM_TOWER_UPGRADES] = {0};

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
