//
//  Player.h
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/02/27.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#ifndef __Lua_TextAdv_Engine__Player__
#define __Lua_TextAdv_Engine__Player__

#include <iostream>
#include <string>
#include <vector>
#include <LuaBridge.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "rooms.h"

using namespace luabridge;

struct Player {

    std::string name;
    int location;
    int test2;
    
    Player *root;
    
    void updatePlayer(Player *player, class location::locNode *node, const int location);
    void movePlayer(Player *player,  class location::locNode *node, const int location, const int direction);
    
};

#endif /* defined(__Lua_TextAdv_Engine__Player__) */
