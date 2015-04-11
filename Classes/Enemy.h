/*
 * Enemy.h
 *
 *  Created on: Apr 11, 2015
 *      Author: Karan
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

class GameWorld;

class Enemy: public GameObject {
public:
	Enemy();
	virtual ~Enemy();

	static Enemy* create(GameWorld* game_world);

	virtual bool init(GameWorld* game_world);
	virtual void Update();

	list<int> path_indices_;
};

#endif /* ENEMY_H_ */
