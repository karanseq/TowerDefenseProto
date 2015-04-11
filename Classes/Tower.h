/*
 * Tower.h
 *
 *  Created on: Apr 11, 2015
 *      Author: Karan
 */

#ifndef TOWER_H_
#define TOWER_H_

#include "GameObject.h"

class GameWorld;
class Enemy;

class Tower: public GameObject {
public:
	Tower();
	virtual ~Tower();

	static Tower* create(GameWorld* game_world, CCPoint position);

	virtual bool init(GameWorld* game_world, CCPoint position);
	virtual void Update();

	inline void SetRange(float range[NUM_TOWER_UPGRADES]) { std::copy(range, range + NUM_TOWER_UPGRADES, range_); }
	inline float* GetRange() { return range_; }

	inline void SetPhysicalDamage(float physical_damage[NUM_TOWER_UPGRADES]) { std::copy(physical_damage, physical_damage + NUM_TOWER_UPGRADES, physical_damage_); }
	inline float* GetPhysicalDamage() { return physical_damage_; }

	inline void SetMagicalDamage(float magical_damage[NUM_TOWER_UPGRADES]) { std::copy(magical_damage, magical_damage + NUM_TOWER_UPGRADES, magical_damage_); }
	inline float* GetMagicalDamage() { return magical_damage_; }

	inline void SetSpeedDamage(float speed_damage[NUM_TOWER_UPGRADES]) { std::copy(speed_damage, speed_damage + NUM_TOWER_UPGRADES, speed_damage_); }
	inline float* GetSpeedDamage() { return speed_damage_; }

	inline void SetSpeedDamageDuration(float speed_damage_duration[NUM_TOWER_UPGRADES]) { std::copy(speed_damage_duration, speed_damage_duration + NUM_TOWER_UPGRADES, speed_damage_duration_); }
	inline int* GetSpeedDamageDuration() { return speed_damage_duration_; }

	inline void SetFireRate(float fire_rate[NUM_TOWER_UPGRADES]) { std::copy(fire_rate, fire_rate + NUM_TOWER_UPGRADES, fire_rate_); }
	inline float* GetFireRate() { return fire_rate_; }

	inline void SetCost(float cost[NUM_TOWER_UPGRADES]) { std::copy(cost, cost + NUM_TOWER_UPGRADES, cost_); }
	inline int* GetCost() { return cost_; }

protected:
	float range_[NUM_TOWER_UPGRADES];
	float physical_damage_[NUM_TOWER_UPGRADES];
	float magical_damage_[NUM_TOWER_UPGRADES];
	float speed_damage_[NUM_TOWER_UPGRADES];
	int speed_damage_duration_[NUM_TOWER_UPGRADES];
	float fire_rate_[NUM_TOWER_UPGRADES];
	int cost_[NUM_TOWER_UPGRADES];

	int current_level_;
	Enemy* target_;
};

#endif /* TOWER_H_ */
