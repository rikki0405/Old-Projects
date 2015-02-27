-- Rooms.lua

-- Main
--  Directions:

-- 0 - North; 1 - East; 2 - South; 3 - West; 4 - Up; 5 - Down
-- Max Directions: 6  |  No Exit: -1

--Design1 = {

--{ -- Room 1
--name = "Warehouse",
--exit[0] = -1,           -- North Exit
--exit[1] = -1,           -- East Exit
--exit[2] = -1,           -- South Exit
--exit[3] = "Docks",      -- West Exit
--exit[4] = -1,           -- Upper Exit
--exit[5] = -1,           -- Lower Exit

--},

--{ -- Room 2
--name = "Docks",
--exit[0] = "Gates",      -- North
--exit[1] = "Warehouse",  -- East
--exit[2] = -1,           -- South
--exit[3] = -1,           -- West
--exit[4] = -1,           -- Up
--exit[6] = -1            -- Down
--}

--}

Design2 = {

    { -- Room 1
        name = "Warehouse",
        description = "A moderately sized warehouse, it seems to be inactive and everything is covered in dust",              -- what is displayed when the player moves into the room
        look = "You notice a layer of dust covering everything, with sunlight coming in through the windows",           -- when a player types in "look" (no object)
        west = "Docks"          -- to the west is the docks
    },

    { -- Room 2
        name = "Docks",
        east = "Warehouse",     -- to the east is the warehouse
        north = "Gates"        -- to the north is the gates

        -- conditions
       -- east_condition = ObjectRequired("Key")  -- Function Call implementation? Pointer?
    }
}
