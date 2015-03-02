//
//  Parser.cpp
//  Lua_TextAdv
//
//  Created by Rikki Jones on 2015/02/13.
//  Copyright (c) 2015年 Rikki Jones. All rights reserved.
//

#include "Parser.h"

using namespace std;
using namespace luabridge;

// grabs the input from the player, shifts everything to lower case and splits the parse up
vector<string> preParse(const string& playerInput) { // playerInput comes in, parsed output goes out
    vector<string> parseInput; // our return vector
    string cWord; // word container
    for (auto c : playerInput) {  // check every character in strInput
        cWord += c;  // moves the char(c) over to a string container(cWord)
        if (isspace(c)) { // if the next character is a whitespace
            cWord = cWord.substr(0, cWord.size() - 1); // remove the last character of the string
            parseInput.push_back(cWord);  // copies the string-contained char into the vector
            cWord = "";  // clear the char-string container
        }
    }
    parseInput.push_back(cWord); // copy the last word into the vector stack
    
    return parseInput;
}

// takes the parsed vector from above, and removes prepositions, specified in an external lua file
vector<string> prepositionTemp(const vector<string>& refParse) {
    // lua stuff
    lua_State* L = luaL_newstate();
    const string filename = "language.lua";
    
    luaL_dofile(L, filename.c_str()); // loading this everytime a parse is executed
    luaL_openlibs(L);               // allows the lua file to be edited during runtime
    lua_pcall(L, 0, 0, 0);
    
    // error handling
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua Error Generated!" << endl; // script is not loaded
    }
    
    LuaRef ppGlobal = getGlobal(L, "Prepositions");
    LuaRef ppList = ppGlobal["List"];
    
    vector<string> vTemp, vDynamic;
    vDynamic = refParse; // copy over the refParse to vDynamic
    
    for (int i = 1; i < ppList.length() + 1; i++) {
        // load the current position preposition into the container
        LuaRef preposition = ppList[i];
        //cout << "Debug: " << preposition.cast<string>();
        
        // now loop the current preposition against the values of the parsed string in order of the vector
        for (int j = 0; j < vDynamic.size(); j++) {
            if ( vDynamic.at(j) != preposition.cast<string>()) {
                vTemp.push_back(vDynamic.at(j));
            }
        }
        
        vDynamic = vTemp;   // update vDynamic with vTemp values
        vTemp.clear();      //  and empty vTemp
    }
    
    return vDynamic; // updated vector with no prepositions is returned
}

int parse(const std::string pWord) {
    
    lua_State* L = luaL_newstate();
    const string filename = "language.lua";
    
    luaL_dofile(L, filename.c_str()); // loading this everytime a parse is executed
    luaL_openlibs(L);               // allows the lua file to be edited during runtime
    lua_pcall(L, 0, 0, 0);
    
    // error handling
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) { // checking if the script is loaded
        cout << "Lua Error Generated!" << endl; // script is not loaded
    }
    
    bool found = false; // if true, verb exists in the list
    LuaRef verbs = getGlobal(L, "verbs");
    
    int rtn;  // return container
    
    // container for the verb
    std::string fVerb;
    
    for (int i = 1; i < verbs.length() + 1; i++) {
        LuaRef verb = verbs[i];
        LuaRef synonyms = verb["synonyms"];
        LuaRef vCast = verb["main"];
            
        string sCast = vCast.cast<string>();
            
        // check the main entry
            
        if (pWord == sCast) { // should never be Nil
            fVerb = pWord;
            found = true;
            break;
        } else {
                
            // else, check the synonyms
            for (int j = 1; j < synonyms.length() + 1; j++) {
                LuaRef check = synonyms[j];
                string sCast2 = check.cast<string>();
                    
                if (!check.isNil()) {
                    if (pWord == sCast2) { // if a synonym match is found
                        fVerb = sCast; // assign it the main word, not the synonym
                        found = true;
                        break;
                    }
                }
            }
        }
        if (found)
            break;
    }
    
    if (!found)  { // didn't find the word
        rtn = 0;
        
        if (pWord == "quit" || pWord == "exit")
            rtn = 99;
    } else {
        // entry found, now the parse-tastic time
        
        // hard entry explicitly for "move"/"go"
        if (pWord == "go")
            rtn = 1;
        
    }
    return rtn;
}
