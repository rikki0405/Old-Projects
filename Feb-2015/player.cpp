//
//  Player.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/02/27.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include "Player.h"

using namespace std;

void Player::updatePlayer (Player *player, class location::locNode *node, const int location) {
 
    // NYI
}

void Player::movePlayer (Player *player, class location::locNode *node, const int location, const int direction) {
    
    // Parse in the information from the parser and update the player in the new room
    
    // locate the correct locNode
    while (node->vnum != location) {
        if (node->vnum < location)
            node = node->next;
        if (node->vnum > location)
            node = node->previous;
    }
    
    // check the exit direction
    if (node->exits[direction] != -1) {
        cout << "You exit to the direction (LUA SCRIPT)" << endl;
        
        // assign the new exit direction to player
        player->location = node->exits[direction];
        
        // locate the new room node
        while (node->vnum != player->location) {
            if (node->vnum < player->location) {
                node = node->next; }
            if (node->vnum > player->location) {
                if (node->previous != nullptr) {
                    node = node->previous;
                } else { break; } // prevent endless loop
            }
        }
        
        // print some shiny new moving output to player
        cout << "You move to the " << node->name << ". (LUA SCRIPT)" << endl;
        cout << node->description << endl;
    } else {
        cout << "You don't move" << endl;
        
        // print the current room's description once again
        cout << node->description << endl;
    }
    
}
