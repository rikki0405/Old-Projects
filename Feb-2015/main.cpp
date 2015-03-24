//
//  main.cpp - Main.cpp
//  Lua_TextAdv_Engine
//
//  Created by Rikki Jones on 2015/01
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

#include "player.h"
#include "rooms.h"

using namespace std;
using namespace luabridge;

// declarations from other scripts
vector<string> preParse(const string& playerInput);                 // Parser.cpp
vector<string> prepositionTemp(const vector<string>& refParse);     // Parser.cpp
int parse(const std::string pWord);                                 // Parser.cpp
struct Player;      // rooms.h
struct location;    // rooms.h

int playerTesting() {
    
    // variables
    bool running = true; // false = game stops
    string pInput, outParse, yesno, locInfo1, locInfo2;
    vector<string> outputParse;
    
    // lua load
    lua_State* L = luaL_newstate(); // don't need a new to invoke a new state after this
    
    // lua script names
    const string fnScript = "script.lua";
    const string fnRooms = "rooms.lua";
    const string fnLang = "language.lua";
    
    luaL_dofile(L, fnRooms.c_str()); // loading this everytime a parse is executed
    luaL_openlibs(L);               // allows the lua file to be edited during runtime
    lua_pcall(L, 0, 0, 0);
    
    // error handling
    if (luaL_loadfile(L, fnRooms.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua Error Generated!" << endl; // script is not loaded
        return -1;
    }
    
    // set up LuaRefs
    LuaRef Main = getGlobal(L, "Rooms");
    
    // create a player and rooms structs
    Player newPlayer;
    location loc("");  // initial invocation
    
    cout << "Please type in your name: ";
    cin >> newPlayer.name;
    cout << endl << endl;
    
    // load the rooms and set player at room 1
    for (int i = 1; i < Main.length() + 1; i++) {
        
        // LuaRef List!
        LuaRef rmsPos = Main[i];
        LuaRef name = rmsPos["name"];
        LuaRef desc = rmsPos["description"];
        
        if (!name.isNil()) //{                              // check if it is empty
            locInfo1 = name.cast<string>();                 // push the casted string to the stack
       /* } else {
            cout << "name container is nil" << endl;  }*/
        
        if (!desc.isNil()) {                                // check if it is empty
            locInfo2 = desc.cast<string>();                 // cast to string
        } else {
            locInfo2 = "An empty description container";    // load in an empty description
        }
        
        
        loc.insert(loc.root, loc.root, i, locInfo1, locInfo2);
    }//*/
    
    // Load in the directions
    for (int i = 1; i < Main.length() + 1; i++) {
        
        LuaRef rmsPos = Main[i];
        LuaRef vnum = rmsPos["vnum"];
        
        // Set directions up
        LuaRef north = rmsPos["north"];
        LuaRef east = rmsPos["east"];
        LuaRef south = rmsPos["south"];
        LuaRef west = rmsPos["west"];
        LuaRef up = rmsPos["up"];
        LuaRef down = rmsPos["down"];
        
        // int containers
        int iN, iE, iS, iW, iU, iD;
        
        // Load Exit Directions
        if (!north.isNil()) {
            iN = loc.roomVnum(loc.root, north.cast<string>(), 0);
        } else { iN = -1; }
        if (!east.isNil()) {
            iE = loc.roomVnum(loc.root, east.cast<string>(), 0);
        } else { iE = -1; }
        if (!south.isNil()) {
            iS = loc.roomVnum(loc.root, south.cast<string>(), 0);
        } else { iS = -1; }
        if (!west.isNil()) {
            iW = loc.roomVnum(loc.root, west.cast<string>(), 0);
        } else { iW = -1; }
        if (!up.isNil()) {
            iU = loc.roomVnum(loc.root, up.cast<string>(), 0);
        } else { iU = -1; }
        if (!down.isNil()) {
            iD = loc.roomVnum(loc.root, down.cast<string>(), 0);
        } else { iD = -1; }
     
        // now, set up the exits to the room
        loc.assignExits(loc.root, i, iN, iE, iS, iW, iU, iD);
        
    }
    
    newPlayer.location = 1; // sets the player's vnum location at 1
    
    cout << "Player Testing! Multi-lua script loading will be tested later!" << endl;
    cout << newPlayer.name << ", welcome to the world!" << endl;
    
    loc.description(loc.root, newPlayer.location);
    
    // start game loop
    while (running) {
        cout << "What would you like to do?" << endl;
        
        getline(cin, pInput);
        cout << endl;
        
        if (pInput != "") {
            outputParse = prepositionTemp(preParse(pInput)); // split parse and remove prepositions
        
            switch (parse(outputParse.at(0))) {  // parse the verb
                case 0:
                    // NYI
                    break;
                case 99: // player entered "exit" or "quit" (lua script these)
                    running = false;
                    break;
                case 1: // 1 = move/go
                    // sort the directions
                    int dir = -1;
                    if (outputParse.at(1) == "north")
                        dir = 0;
                    if (outputParse.at(1) == "east")
                        dir = 1;
                    if (outputParse.at(1) == "south")
                        dir = 2;
                    if (outputParse.at(1) == "west")
                        dir = 3;
                    if (outputParse.at(1) == "up")
                        dir = 4;
                    if (outputParse.at(1) == "down")
                        dir = 5;
                
                    if (dir != -1)
                        newPlayer.movePlayer(&newPlayer, loc.root, newPlayer.location, dir);
                
                    break;
                    
                
            }
        
            // now to arrange the output parse in a single string
            for (int i = 0; i < outputParse.size(); i++) {
                outParse += outputParse.at(i);
                outParse += " ";
            }
            outParse = outParse.substr(0, outParse.size() - 1); // removal of last whitespace
        
            outParse.clear();       // empty the output parse string
            outputParse.clear();    // empty the vector
        }
        
    };//*/
    
    cout << "playerTesting ended!" << endl;
    cout << "Start Date: 27 Feb 2015 - Rikki Jones" << endl;
    cout << "End Date: 02 Mar 2015 - Rikki Jones" << endl;
    
    return 0;
}

int main() {

    playerTesting();                    // moving around the world - passed!
    
    return 0;
    
}
