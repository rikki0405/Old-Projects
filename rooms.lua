-- Rooms.lua

Rooms = {

    { -- Room 1
        name = "Warehouse",
        description = "A moderately sized warehouse, it seems to be inactive and everything is covered in dust",              -- what is displayed when the player moves into the room
        look = "You notice a layer of dust covering everything, with sunlight coming in through the windows",           -- when a player types in "look" (no object)
        west = "Docks"          -- to the west is the docks
    },

    { -- Room 2
        name = "Docks",
        description = "The docks. This is one big shipping container yard.",
        east = "Warehouse",     -- to the east is the warehouse
        north = "Gates"        -- to the north is the gates

        -- conditions
       -- east_condition = ObjectRequired("Key")  -- Function Call implementation? Pointer?
    },
    
    { -- Room 3
        name = "Gates",
        description = "The gates to the shipping yard is blocked off by a security gate.",
        south = "Docks",
        north = "Streets"
    },
    
    { -- Room 4
        name = "Streets",
        description = "You glance down the street, yet see no activity in any direction",
        south = "Docks",
        west = "Cafe",
        east = "Pier"
    },
    
    { -- Room 5
        name = "Cafe",
        description = "A Cafe. At this time of night, it seems to be closed.",
        east = "Streets"
    },
    
    { -- Room 6
        name = "Pier",
        descripion = "A pier overlooking the ocean. You can see lights coming from within the Docks",
        west = "Streets"
    }
    
}
