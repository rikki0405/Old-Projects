//
//  nRooms.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/03/24.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include "nRooms.h"

using namespace luabridge;

void nRooms::updateRoom(nRooms *rms, nRooms *newRms) {
    
    /* Not Yet Implemented */
    
}

void nRooms::loadZone(nRooms *rms, lua_State *L) {
    
    /* Force rms to a nullptr (just in case of garbage pointer data) */
    rms = nullptr;
    
    /* Open the lua file to get data from */
    const std::string fnRooms = "Rooms.lua";
    luaL_dofile(L, fnRooms.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    /* Error Checking */
    if (luaL_loadfile(L, fnRooms.c_str()) || lua_pcall(L, 0, 0, 0))
        std::cout << "Lua Error Generated!" << std::endl;
    
    /* LuaRefs */
    LuaRef luaRooms = getGlobal(L, "nRooms");
    
    for (int i = 1; i < luaRooms.length() + 1; i++) {
        LuaRef luaPos = luaRooms[i];
        LuaRef luaData = luaPos["data"];
        LuaRef roomName = luaPos["name"];
        
        LuaRef dataPos = luaData;
        LuaRef roomDesc = dataPos["description"];
        LuaRef roomLook = dataPos["look"];
        
        /* Create vector, push LuaRefs into vector, with error checking */
        std::vector<std::string> pushData;
        if (!roomName.isNil()) { pushData.push_back(roomName.cast<std::string>());
        } else { pushData.push_back("empty"); }
        if (!roomDesc.isNil()) {pushData.push_back(roomDesc.cast<std::string>());
        } else { pushData.push_back("empty"); }
        if (!roomLook.isNil()) {pushData.push_back(roomLook.cast<std::string>());
        } else { pushData.push_back("empty"); }
        
        /* Insert the zone */
        if (rms == nullptr) { zoneInsert(rms, nullptr, pushData);
        } else { zoneInsert(rms->root->current, rms->root, pushData); }
    }
    
    /* Now to set the exits - Loop Recursion */
    for (rms->current = rms->root; rms->current != nullptr; rms->current = rms->current->next)
        setExits(rms->current, L);
    
    /* Now, check our hard work. Run through the linked list and display our exits! */
    zoneDisplay(rms->root);
    
    std::cout << "Reached the end of loadZone - Congrats!" << std::endl;
}


void nRooms::zoneInsert(nRooms *&rms, nRooms *root, const std::vector<std::string> data) {
    if (rms == nullptr) {
        
        /* Create a new node */
        rms = new nRooms();
        
        /* Push data into newly created node */
        rms->rName = data.at(0);
        rms->rDesc = data.at(1);
        rms->rLook = data.at(2);
        
        /* Check the root pointer */
        if (root == nullptr) { rms->root = rms;
        } else { rms->root = root; }
        
        /* Debug Output */
        std::cout << "Zone Loading - Room Inserted: " << rms->rName << std::endl;
        
        if (rms->root != nullptr)
            std::cout << "Root pointing to: " << rms->root->rName << std::endl;
        
        rms->root->current = rms;
        
    } else {
        /* Move to next in the list*/
        zoneInsert(rms->next, root, data);
    }
}

void nRooms::zoneDisplay(nRooms *rms) {
    
    /* Debug Routine to show a node's exit pointers */
    
    const std::string dirExit[maxExits] {
        "North Exit: ",
        "East Exit: ",
        "South Exit: ",
        "West Exit: ",
        "Up Exit: ",
        "Down Exit: " };
    
    /* Run thru our list and show our exits! */
    std::cout << "Current Room: " << rms->rName << std::endl;
        
    /* Display exits */
    for (int j = 0; j < 5; j++) {
        if (rms->exits[j] != nullptr)
            std::cout << dirExit[j] << rms->exits[j]->rName << std::endl;
    }
    
    /* Move to the next in the list */
    if (rms->next != nullptr)
        zoneDisplay(rms->next);
    
}

void nRooms::setExits(nRooms *rms, lua_State *L) {
    
    /* 01 - Open rooms.lua */
    const std::string fnRooms = "Rooms.lua";
    luaL_dofile(L, fnRooms.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    /* Error Checking */
    if (luaL_loadfile(L, fnRooms.c_str()) || lua_pcall(L, 0, 0, 0))
        std::cout << "Lua Error Generated!" << std::endl;
    
    /* LuaRefs */
    LuaRef luaRooms = getGlobal(L, "nRooms");
    
    /* 02 - Find the room */
    for (int i = 1; i < luaRooms.length() + 1; i++) {
        /* LuaRefs */
        LuaRef rmsPos = luaRooms[i];
        LuaRef rmsName = rmsPos["name"];
        
        /* 03 - Find room in rooms.lua */
        if (rmsName.cast<std::string>() == rms->rName) {
            /* More LuaRefs */
            LuaRef rmsData = rmsPos["data"];
            LuaRef rmsNorth = rmsData["north"];
            LuaRef rmsEast = rmsData["east"];
            LuaRef rmsSouth = rmsData["south"];
            LuaRef rmsWest = rmsData["west"];
            LuaRef rmsUp = rmsData["up"];
            LuaRef rmsDown = rmsData["down"];
            
            /* 04 - Set up the exits */
            if(!rmsNorth.isNil())
                rms->exits[pNorth] = findRoom(rms->root, rmsNorth.cast<std::string>());
            if(!rmsEast.isNil())
                rms->exits[pEast] = findRoom(rms->root, rmsEast.cast<std::string>());
            if(!rmsSouth.isNil())
                rms->exits[pSouth] = findRoom(rms->root, rmsSouth.cast<std::string>());
            if(!rmsWest.isNil())
                rms->exits[pWest] = findRoom(rms->root, rmsWest.cast<std::string>());
            if(!rmsUp.isNil())
                rms->exits[pUp] = findRoom(rms->root, rmsUp.cast<std::string>());
            if(!rmsDown.isNil())
                rms->exits[pDown] = findRoom(rms->root, rmsDown.cast<std::string>());
            
            /* Found our value, break from loop */
            break;
        }
    }
}
