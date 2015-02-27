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
#include "Rooms.h"

using namespace std;
using namespace luabridge;

// declarations from other scripts
vector<string> preParse(const string& playerInput);                 // Parser.cpp
vector<string> prepositionTemp(const vector<string>& refParse);     // Parser.cpp
struct Player;      // rooms.h
struct location;    // rooms.h

int luaTest() {
    lua_State* L = luaL_newstate();
    const string filename = "script.lua"; // the name of the file we will load (never change, keep const)
    
    luaL_dofile(L, filename.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua file not loaded!" << endl; // script is not loaded
        return -1; // end program due to no script loaded
    }
    
    LuaRef main = getGlobal(L, "testing");
    LuaRef s = main["testString"];
    LuaRef n = main["number"];
    LuaRef x = main["null"];
    
    int z = 1;
    if (x.isNil())
        z = -1;
    
    if (s.isNil() || n.isNil()) {  // if either string variable is nil
        cout << "Variable not found!" << endl;  // show error
        return 0; // and end execution
    }
    string luaString = s.cast<string>();
    int answer = n.cast<int>();
    cout << luaString << endl;
    cout << "And here's our number:" << answer << endl;
    cout << "Test outputting a nil field: " << z << endl;
    
    return 0;
}

int luaVectorTest() {
    lua_State* L = luaL_newstate();
    const string filename = "script.lua";
    
    luaL_dofile(L, filename.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua file not loaded!" << endl; // script is not loaded
        return -1; // end program due to no script loaded
    }
    
    // grab initial values to check reading from lua file is correct
    LuaRef main = getGlobal(L, "testing");
    LuaRef s = main["testString"];
    LuaRef n = main["number"];
    
    string testString = s.cast<string>();
    int testNumber = n.cast<int>();
    
    cout << "Test varibles: " << testString << endl;
    cout << "Test integer: " << testNumber << endl;
    
    LuaRef table = getGlobal(L, "table");
    
    string mainString = table["main"].cast<string>();
    cout << mainString << endl;
    
    LuaRef array = table["array"];
    
    for (int i = 1; i < array.length() + 1; i++) {
        LuaRef check = array[i];
        cout << check.cast<string>() << endl;
    }
    
    
    return 0;
}

int PrepositionRemovalTest() {
    
    bool running = true;
    string pInput, outParse, yesno;
    vector<string> outputParse;
    
    cout << "Prepositional Removal Parse Test\n" << endl;
    
    while (running) {
        cout << "Parse input: ";
        getline(cin, pInput);
        cout << endl;
        
        // Parse the input and remove the prepositions in one swift move
        outputParse = prepositionTemp(preParse(pInput));
        
        // now to arrange the output parse in a single string
        for (int i = 0; i < outputParse.size(); i++) {
            outParse += outputParse.at(i);
            outParse += " ";
        }
        outParse = outParse.substr(0, outParse.size() - 1); // removal of last whitespace
        
        // Print the output with prepositions removed
        cout << "Input: " << pInput << endl;
        cout << "Output: " << outParse << endl;
        
        outputParse.clear(); // empty the vector
        
        // ask to parse another input
        //cout << "\nParse another input? (Y/N): ";
        //cin >> yesno;
        //cout << endl;
        
       // if (yesno == "N" || yesno == "n")
            running = false;
        
    }
    
    return 0;
}

int nilname() {
    /*      This function will try and see how loading a stack within an lua table WITHOUT
            a stackname declared. Trial Function. If this works, apply the structure to ROOMS.LUA
     
                Function works! No problems encountered!
     */
    
    lua_State* L = luaL_newstate();
    const string filename = "script.lua";
    
    luaL_dofile(L, filename.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua file not loaded!" << endl; // script is not loaded
        return -1; // end program due to no script loaded
    }
    
    // grab initial values to check reading from lua file is correct
    LuaRef main = getGlobal(L, "nilname");

    for (int i = 1; i < main.length() + 1; i++) {
        LuaRef print = main[i];
        LuaRef out = print["main"];
        cout << i << " - " << out << endl;
    }

    
    return 0;
}

int playerTesting() {
    
    // variables
    //bool running = true; // false = game stops
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
    LuaRef Main = getGlobal(L, "Design2");
    
    // create a player and rooms structs
    Player newPlayer;
    location loc("");  // initial invocation
    
    cout << "Please type in your name: ";
    cin >> newPlayer.name;
    cout << endl << endl;
    
    // load the rooms and set player at room 1
    for (int i = 1; i < Main.length() + 1; i++) {
        cout << "loop test : " << i << endl;
        LuaRef rmsPos = Main[i];
        LuaRef name = rmsPos["name"];
        LuaRef desc = rmsPos["description"];
        if (!name.isNil()) {                          // check if it is empty
            locInfo1 = name.cast<string>();         // push the casted string to the stack
        } else {
            cout << "name container is nil" << endl;
        }
        if (!desc.isNil()) {                         // check if it is empty
            locInfo2 = desc.cast<string>();  // cast to string
        } else {
            cout << "**description container is nil**" << endl;
            locInfo2 = "An empty description container"; // load in an empty description
        }
        loc.insert(loc.root, i, locInfo1, locInfo2);
    }//*/
    newPlayer.location = 1; // sets the player's vnum location at 1
    
    cout << "Player Testing! Multi-lua script loading will be tested later!" << endl;
    cout << newPlayer.name << ", welcome to the world!" << endl;
    
    loc.print(loc.root);
    loc.description(loc.root, newPlayer.location);
    /*
    // start game loop
    while (running) {
        cout << "What would you like to do?" << endl;
        
        getline(cin, pInput);
        cout << endl;
        
        // Parse the input and remove the prepositions in one swift move
        outputParse = prepositionTemp(preParse(pInput));
        
        // now to arrange the output parse in a single string
        for (int i = 0; i < outputParse.size(); i++) {
            outParse += outputParse.at(i);
            outParse += " ";
        }
        outParse = outParse.substr(0, outParse.size() - 1); // removal of last whitespace
        
        // Print the output with prepositions removed
        cout << "Input: " << pInput << endl;
        cout << "Output: " << outParse << endl;
        
        outputParse.clear(); // empty the vector
        
    };//*/
    
    cout << "playerTesting ended!" << endl;
    cout << "Feb 27 2015 - Rikki Jones" << endl;
    
    return 0;
}

int main() {
    
//    luaTest();                        // passed!
//    luaVectorTest();                  // passed!
//    PrepositionRemovalTest();         // passed!
//    nilname();                        // passed!
//    stuff();
//    cout << "Binary Tree Inorder Print" << endl;

    playerTesting();
    
    return 0;
    
}
