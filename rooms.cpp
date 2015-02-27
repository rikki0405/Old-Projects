//
//  Rooms.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/02/27.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include "Rooms.h"

int loadRooms (int curRoom) {
    lua_State* L = luaL_newstate();
    const string filename = "rooms.lua";
    
    luaL_dofile(L, filename.c_str()); // loading this everytime a parse is executed
    luaL_openlibs(L);               // allows the lua file to be edited during runtime
    lua_pcall(L, 0, 0, 0);
    
    // error handling
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua Error Generated!" << endl; // script is not loaded
        return -1;
    }

    if (curRoom == 0) { // no room loaded, load default room
     
        
    }
    
    
    return 0;
}

void location::insert(locNode *&node, int vnum, std::string name, std::string description) {
 
    if (node == nullptr) { // current spot in the pointer list is empty
        node = new locNode(vnum, name, description);
    }
    else if (vnum < node->vnum)                             // if the list is longer than current position
        insert(node->next, vnum, name, description);   // move until it gets to the end
}

void location::assignExits(location *loc, int North, int East, int South, int West, int Up, int Down) {
    
    // not yet implemented
    
}

void location::description(locNode *&node, int location) {
    // this is for when "look" is invoked via parser
    if (node != nullptr) { // if the parsed referenced pointer isn't null
        cout << "node vnum : " << node->vnum <<  endl;
        cout << "node desc : " << node->description << endl;
        if (location > node->vnum)
            description(node->next, location);
        if (location < node->vnum)
            description(node->previous, location);
        cout << node->description << endl;
    };
    
}

void location::print(locNode *&node) {
    // this will print all results for the entire "tree"
    if (node != nullptr) {              // if current node isn't empty
        if (node->vnum != 1)            // if it isn't at the first spot
            print(node->previous);      // recursively move until it is
        cout << node->vnum << ": " << node->name << endl;
        print(node->next);
    }
}
