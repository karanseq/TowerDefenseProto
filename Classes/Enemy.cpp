/*
 * Enemy.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: Karan
 */

#include "Enemy.h"
#include "GameWorld.h"

Enemy::Enemy()
{
	num_path_indices_ = 0;
	current_path_index_ = 0;
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

	game_world_ = game_world;
	path_indices_ = game_world_->GetEnemyPath();
	num_path_indices_ = path_indices_.size();
	
	setPosition(ccp(GET_X_FOR_COL(path_indices_[current_path_index_].x) + TILE_SIZE/2, GET_Y_FOR_ROW(path_indices_[current_path_index_].y, MAX_ROWS) + TILE_SIZE));

	return true;
}

void Enemy::Update()
{
	
}
