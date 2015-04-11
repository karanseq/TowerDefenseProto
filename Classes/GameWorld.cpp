#include "GameWorld.h"
#include "Tower.h"

GameWorld::GameWorld()
{
	tiled_map_ = NULL;
	tile_layer_ = NULL;
	num_towers_ = 0;
	towers_.clear();
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
    
    return true;
}

void GameWorld::CreatePlayground()
{
	tiled_map_ = CCTMXTiledMap::create("test.tmx");
	addChild(tiled_map_);
	tile_layer_ = tiled_map_->layerNamed("playground");
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
