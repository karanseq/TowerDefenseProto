#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "GameGlobals.h"

class GameWorld;

class GameObject : public CCSprite
{
public:
	GameObject() : game_world_(NULL),
//		type_(E_GAME_OBJECT_NONE),
		aabb_(CCRectZero),
		speed_(CCPointZero) {}

	virtual ~GameObject()
	{}

	virtual void SetAABB(CCRect aabb)
	{
		aabb_ = aabb;
	}

	inline CCRect GetAABB() { return aabb_; }
	virtual void SetSpeed(CCPoint speed) { speed_ = speed; }
	inline CCPoint GetSpeed() { return speed_; }

	virtual void Update()
	{
		aabb_.origin.x += speed_.x;
		aabb_.origin.y += speed_.y;
	}
//	virtual void CollisionResponse(int tile_col, int tile_row, ECollisionType collision_type) {}

protected:
	GameWorld* game_world_;
//	EGameObjectType type_;
	CCRect aabb_;
	CCPoint speed_;
};

#endif // GAME_OBJECT_H_
