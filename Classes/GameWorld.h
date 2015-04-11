#ifndef GAME_WORLD_H_
#define GAME_WORLD_H_

#include "GameGlobals.h"

class Tower;

class GameWorld : public CCLayer
{
public:
	GameWorld();
	virtual ~GameWorld();

    static CCScene* scene();
    CREATE_FUNC(GameWorld);

    virtual bool init();

    void CreatePlayground();
    void CreateTowers();

    CCTMXTiledMap* tiled_map_;
    CCTMXLayer* tile_layer_;

    int num_towers_;
    vector<Tower*> towers_;
};

#endif // GAME_WORLD_H_
