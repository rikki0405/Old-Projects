//
//  main.cpp - Main.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/03/24
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include <LuaBridge.h>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

/* New Classes for pointerDrivenPlayerTesting() */
#include "nRooms.h"
#include "nPlayer.h"
#include "nParser.h"

int zoneTesting() {
    /* 24-Mar-2015: Testing Begins */
    
    /* nRooms zone testing */
    
    lua_State *L = luaL_newstate();
    
    /* Class Entities */
    nRooms newRoom;
    
    /* Zone Load Test */
    newRoom.loadZone(newRoom.current, L);
    
    return 0;
}

int main() {

    zoneTesting();
    
    return 0;
    
}
