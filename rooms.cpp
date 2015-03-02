//
//  Rooms.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/02/27.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include "Rooms.h"

void location::insert(locNode *&node, locNode *&pnode, int vnum, std::string name, std::string description) {
 
    if (node == nullptr) { // current spot in the pointer list is empty
        node = new locNode(pnode, vnum, name, description);
    }
    else if (vnum > node->vnum) {                           // if the list is longer than current position
        insert(node->next, node, vnum, name, description);   // move until it gets to the end
    }
}

void location::assignExits(locNode *loc, int vnum, int North, int East, int South, int West, int Up, int Down) {
    
    if (loc->vnum == vnum) {
    // set up the exits
    loc->exits[0] = North;
    loc->exits[1] = East;
    loc->exits[2] = South;
    loc->exits[3] = West;
    loc->exits[4] = Up;
    loc->exits[5] = Down;
    
    } else {  // move to the next pointer
        assignExits(loc->next, vnum, North, East, South, West, Up, Down);
    }
    
    
}

int location::roomVnum(locNode *node, const std::string roomName, const int found) {
    // Parse in the name of the room, search through the pointer list
    //  and return the vnum of the room list
    // This is for use with assign the vnum to the exits int array

    int vnum = found;
    
    if (node != nullptr)
        if (node->name == roomName)
            vnum = node->vnum;
    
    if (node != nullptr)
        if (vnum == 0) // we have not yet found our value
            if (node->name != roomName)
                vnum = roomVnum(node->next, roomName, 0);
    
    if (found != 0)     // we have found our exit value
        vnum = found;   // return this value
    
    return vnum;
}

void location::description(locNode *&node, int location) {
   
    if (node != nullptr) {
        if (location > node->vnum)
            description(node->next, location);
        if (location < node->vnum)
            description(node->previous, location);
        cout << node->description << endl;
    }
}

void location::description(locNode *&node, int location, bool debug) {
    // this is for when "look" is invoked via parser
    if (node != nullptr) { // if the parsed referenced pointer isn't null
        cout << "node vnum : " << node->vnum <<  endl;
        cout << "node desc : " << node->description << endl;
        cout << "north exit : " << node->exits[0] << endl;
        cout << "east exit : " << node->exits[1] << endl;
        cout << "south exit : " << node->exits[2] << endl;
        cout << "west exit : " << node->exits[3] << endl;
        cout << "up exit : " << node->exits[4] << endl;
        cout << "down exit : " << node->exits[5] << endl;
        if (location > node->vnum)
            description(node->next, location);
        if (location < node->vnum)
            description(node->previous, location);
        cout << node->description << endl;
    };
    
}

void location::print(locNode *&node) {
    // this will print all results for the entire "tree"
    // node will always point to the ROOT
    
    if (node != nullptr) {              // if current node isn't empty
        //if (node->vnum != 1)            // if it isn't at the first spot
        //    print(node->previous);      // recursively move until it is
        cout << node->vnum << ": " << node->name << endl;
        cout << node->description << endl;
        print(node->next);
    }
}
