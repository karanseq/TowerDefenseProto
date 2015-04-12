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

    void GeneratePath(CCPoint start, CCPoint end);
    void FillTheMatrix(int k, int x, int y);
    void TracePath(int k, int x, int y);
    void PrintMatrix();
	inline vector<CCPoint> GetEnemyPath() { return enemy_path_; }

    void update(float dt);

    CCTMXTiledMap* tiled_map_;
    CCTMXLayer* tile_layer_;

    int num_towers_;
    vector<Tower*> towers_;

    int num_enemy_start_points_;
    vector<CCPoint> enemy_start_points_;
    int num_enemy_end_points_;
    vector<CCPoint> enemy_end_points_;

    // Lee's play-things
    int matrix_[MAX_COLS][MAX_ROWS];
    vector<CCPoint> enemy_path_;
};

#endif // GAME_WORLD_H_
