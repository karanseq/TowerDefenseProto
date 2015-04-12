#include "GameWorld.h"
#include "Tower.h"

GameWorld::GameWorld()
{
	tiled_map_ = NULL;
	tile_layer_ = NULL;
	num_towers_ = 0;
	towers_.clear();
	num_enemy_start_points_ = 0;
	enemy_start_points_.clear();
	num_enemy_end_points_ = 0;
	enemy_end_points_.clear();
	memset(matrix_, 0, sizeof(matrix_));
	enemy_path_.clear();
}

GameWorld::~GameWorld()
{}

CCScene* GameWorld::scene()
{
    CCScene *scene = CCScene::create();
    GameWorld *layer = GameWorld::create();
    scene->addChild(layer);
    return scene;
}

bool GameWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CreatePlayground();
    CreateTowers();

    // select a random start & end point for a given enemy's path
    int random_index = (int)(CCRANDOM_0_1() * num_enemy_start_points_);
    CCPoint enemy_start = enemy_start_points_[random_index];
    CCLOG("Selected enemy start point-%d:%f  %f", random_index, enemy_start.x, enemy_start.y);

    random_index = (int)(CCRANDOM_0_1() * num_enemy_end_points_);
	CCPoint enemy_end = enemy_end_points_[random_index];
    CCLOG("Selected enemy end point-%d:%f  %f", random_index, enemy_end.x, enemy_end.y);

    GeneratePath(enemy_start, enemy_end);
    
    return true;
}

void GameWorld::CreatePlayground()
{
	tiled_map_ = CCTMXTiledMap::create("test.tmx");
	addChild(tiled_map_);
	tile_layer_ = tiled_map_->layerNamed("playground");

	CCTMXObjectGroup* object_group = tiled_map_->objectGroupNamed("objects");
	CCArray* objects = object_group->getObjects();
	int num_objects = objects->count();

	for(int i = 0; i < num_objects; ++i)
	{
		CCDictionary* object = (CCDictionary*)(objects->objectAtIndex(i));

		// create the Hero at this spawning point
		if(strcmp(object->valueForKey("name")->getCString(), "enemy_start") == 0)
		{
			// create tower here
			++ num_enemy_start_points_;
			enemy_start_points_.push_back(ccp(GET_COL_FOR_X(object->valueForKey("x")->floatValue() - 1) - 1, GET_ROW_FOR_Y(object->valueForKey("y")->floatValue(), MAX_ROWS) - 1));
		}
		else if(strcmp(object->valueForKey("name")->getCString(), "enemy_end") == 0)
		{
			// create tower here
			++ num_enemy_end_points_;
			enemy_end_points_.push_back(ccp(GET_COL_FOR_X(object->valueForKey("x")->floatValue()) - 1, GET_ROW_FOR_Y(object->valueForKey("y")->floatValue(), MAX_ROWS) - 1));
		}
	}
}

void GameWorld::CreateTowers()
{
	CCTMXObjectGroup* object_group = tiled_map_->objectGroupNamed("objects");
	CCArray* objects = object_group->getObjects();
	int num_objects = objects->count();

	for(int i = 0; i < num_objects; ++i)
	{
		CCDictionary* object = (CCDictionary*)(objects->objectAtIndex(i));

		// create the Hero at this spawning point
		if(strcmp(object->valueForKey("name")->getCString(), "tower") == 0)
		{
			// create tower here
			Tower* tower = Tower::create(this, ccp(object->valueForKey("x")->floatValue(), object->valueForKey("y")->floatValue()));
			addChild(tower, E_LAYER_HERO);
			towers_.push_back(tower);
		}
	}
}

void GameWorld::GeneratePath(CCPoint start, CCPoint end)
{
	// fill the matrix with data
	for(int i = 0; i < MAX_COLS; ++i)
	{
		for(int j = 0; j < MAX_ROWS; ++j)
		{
			if(tile_layer_->tileGIDAt(ccp(i, j)) == 3)		// 2 is the GID for an enemy walkable tile
				matrix_[i][j] = 99;
			else
				matrix_[i][j] = -1;
		}
	}

	// run Lee's algorithm
	matrix_[(int)start.x][(int)start.y] = 0;
	FillTheMatrix(0, (int)start.x, (int)start.y);
	PrintMatrix();

	// trace the path
	CCLOG("About to call TracePath with k=%d  x=%d  y=%d", matrix_[(int)end.x][(int)end.y], (int)end.x, (int)end.y);
	TracePath(matrix_[(int)end.x][(int)end.y], (int)end.x, (int)end.y);
	CCLOG("Path has length:%d", enemy_path_.size());
//	for(int i = 0; i < enemy_path_.size(); ++i)
//	{
//		CCLOG("%f, %f", enemy_path_[i].x, enemy_path_[i].y);
//	}
}

void GameWorld::FillTheMatrix(int k, int x, int y)
{
	// DOWN
	if(x+1 < MAX_COLS)
	{
		if(matrix_[x+1][y] > k+1)
		{
			matrix_[x+1][y] = k+1;
			FillTheMatrix(k+1, x+1, y);
		}
	}

	// UP
	if(x-1 >= 0)
	{
		if(matrix_[x-1][y] > k+1)
		{
			matrix_[x-1][y] = k+1;
			FillTheMatrix(k+1, x-1, y);
		}
	}

	// RIGHT
	if(y+1 < MAX_ROWS)
	{
		if(matrix_[x][y+1] > k+1)
		{
			matrix_[x][y+1] = k+1;
			FillTheMatrix(k+1, x, y+1);
		}
	}

	// LEFT
	if(y-1 >= 0)
	{
		if(matrix_[x][y-1] > k+1)
		{
			matrix_[x][y-1] = k+1;
			FillTheMatrix(k+1, x, y-1);
		}
	}
}

void GameWorld::TracePath(int k, int x, int y)
{
	// DOWN
	if(x+1 < MAX_COLS)
	{
		if(matrix_[x+1][y] == k-1)
		{
			matrix_[x+1][y] = 99;
			enemy_path_.push_back(ccp(x+1, y));
			TracePath(k-1, x+1, y);
		}
	}

	// UP
	if(x-1 >= 0)
	{
		if(matrix_[x-1][y] == k-1)
		{
			matrix_[x-1][y] = 99;
			enemy_path_.push_back(ccp(x-1, y));
			TracePath(k-1, x-1, y);
		}
	}

	// RIGHT
	if(y+1 < MAX_ROWS)
	{
		if(matrix_[x][y+1] == k-1)
		{
			matrix_[x][y+1] = 99;
			enemy_path_.push_back(ccp(x, y+1));
			TracePath(k-1, x, y+1);
		}
	}

	// LEFT
	if(y-1 >= 0)
	{
		if(matrix_[x][y-1] == k-1)
		{
			matrix_[x][y-1] = 99;
			enemy_path_.push_back(ccp(x, y-1));
			TracePath(k-1, x, y-1);
		}
	}
}

void GameWorld::PrintMatrix()
{
	CCLOG("****************************");
	for(int i = 0; i < MAX_COLS; ++i)
	{
		string row = "";
		for(int j = 0; j < MAX_ROWS; ++j)
		{
			char buf[8] = {0};
			sprintf(buf, "%d ", matrix_[i][j]);
			row = row + buf;
		}
		CCLOG("%s", row.c_str());
	}
}

void GameWorld::update(float dt)
{}
