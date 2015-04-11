#ifndef GAME_GLOBALS_H_
#define GAME_GLOBALS_H_

// Global includes go here
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
// Global includes end here

// Helper macros
#define SCREEN_SIZE GameGlobals::screen_size_
#define SOUND_ENGINE CocosDenshion::SimpleAudioEngine::sharedEngine()

#define TILE_SIZE 32

#define GET_X_FOR_COL(col) ( (col) * TILE_SIZE )
#define GET_Y_FOR_ROW(row, h) ( ( (h) - (row) ) * TILE_SIZE )
#define GET_COL_FOR_X(x) ( floor( (x) / TILE_SIZE ) )
#define GET_ROW_FOR_Y(y, h) ( (h) - ceil( (y) / TILE_SIZE ) )

#define NUM_TOWER_UPGRADES 3

// enum used for proper z-ordering
enum EZorder
{
	E_LAYER_BACKGROUND = 0,
	E_LAYER_ENEMIES = 2,
	E_LAYER_PLATFORMS = 3,
	E_LAYER_HERO = 4,
	E_LAYER_HUD = 6,
	E_LAYER_POPUP = 8,
};

// Helper class containing only static members
class GameGlobals
{
private:
	GameGlobals();
	~GameGlobals();

public:
	// initialise common global data here
	// called when application finishes launching
	static void Init();
	// load initial/all game data here

	static CCSize screen_size_;
	static int level_number_;
};

#endif // GAME_GLOBALS_H_
