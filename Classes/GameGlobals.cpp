#include "GameGlobals.h"

CCSize GameGlobals::screen_size_ = CCSizeZero;
int GameGlobals::level_number_ = 0;

void GameGlobals::Init()
{
	screen_size_ = CCDirector::sharedDirector()->getWinSize();
}
