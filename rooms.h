//
//  Rooms.h - new Rooms class
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/02/27.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#ifndef __Lua_TextAdv_Engine__Rooms__
#define __Lua_TextAdv_Engine__Rooms__

#include <iostream>
#include <vector>
#include <string>
#include <LuaBridge.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std;

enum exits { dNORTH, dEAST, dSOUTH, dWEST, dUP, dDOWN, dMAX };

class location {
public:
    class locNode {
    public:
        int vnum;                   // room ID
        std::string name;           // room name
        std::string description;    // description
        
        locNode *previous;
        locNode *next;
        
        locNode (std::string data) { // empty data fill
            vnum = 0;
            name = data;
            description = data;
            previous = nullptr;
            next = nullptr;
        };
        
        locNode (int x, std::string y, std::string z) {
            vnum = x;
            name = y;
            description = z;
            previous = nullptr;
            next = nullptr;
        }
    };
    locNode *root;
    
    location (std::string data) { // initial invocation
        
        root = new locNode(data);
    };
    
    // assign exits isnt implemented yet...
    void assignExits(location *rms, int North, int East, int South, int West, int Up, int Down);
    void insert(locNode *&node, int vnum, string name, string description);
    void description(locNode *&node, int location);
    void print(locNode *&node);
};

#endif /* defined(__Lua_TextAdv_Engine__newRooms__) */
