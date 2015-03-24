//
//  nRooms.h
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/03/24.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#ifndef __Lua_TextAdv_Engine__nRooms__
#define __Lua_TextAdv_Engine__nRooms__

#include <iostream>
#include <vector>
#include <LuaBridge.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "nPlayer.h"

/* Directions: North, East, South, West, Up, Down */
enum exitDir { pNorth, pEast, pSouth, pWest, pUp, pDown, maxExits };

class nRooms {
public:
    std::string rName;              // room name
    std::string rDesc;              // room description
    std::string rLook;              // room look return
    
    nRooms *current;                // current location
    nRooms *root;                   // Zone root for linked list
    nRooms *next;                   // Recursive calling from root
    nRooms *exits[maxExits];        // 6 pointer array for our exits
    
    /* Function to set Exit Pointers */
    nRooms *findRoom(nRooms *current, const std::string &roomName) {
        
        nRooms *ptr = nullptr;
        
        if (roomName == current->rName)
            ptr = current;
        
        /* Recursively search for the room */
        if (roomName != current->rName)
            if (current->next != nullptr)
                ptr = findRoom(current->next, roomName);
        
        return ptr;
    }
    
    /* Class Functions */
    void updateRoom(nRooms *rms, nRooms *newRms);
    void zoneInsert(nRooms *&rms, nRooms *root, const std::vector<std::string> data);
    void loadZone(nRooms *rms, lua_State *L);
    void zoneDisplay(nRooms *rms);
    void setExits(nRooms *rms, lua_State *L);
    
    };

#endif /* defined(__Lua_TextAdv_Engine__nRooms__) */
