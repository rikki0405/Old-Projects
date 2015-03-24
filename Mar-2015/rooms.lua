-- Rooms.lua
--
--  File Structure Details will be documented later, you should be able to see what is what though...
--  Make sure your exit direction names MATCHES a room name PERFECTLY (case sensitive)

nRooms = {
{   name = "Staff Room",
    data = {
        description = "A staff room",
        look = "You see no teachers in the staff room",
        east = "2F Hallway West"
    }
},
{   name = "2F Hallway West",
    data = {
        description = "Room 2",
        look = "Room 2 look",
        north = "2F West Stairwell",
        east = "2F Hallway Central",
        south = "Principal’s Office",
        west = "Staff Room"
    }
},
{   name = "2F Hallway Central",
    data = {
        description = "Room 3",
        look = "Room 3 look",
        east = "2F Hallway East",
        west = "2F Hallway West"
    }
},
{   name = "2F Hallway East",
    data = {
        description = "Room 4",
        look = "Room 4 look",
        north = "2F East Stairwell",
        east = "Home Economics Classroom",
        south = "Library",
        west = "2F Hallway Central"
    }
},
{   name = "Home Economics Classroom",
    data = {
        description = "Room 5",
        look = "Room 5 look",
        west = "2F Hallway East"
    }
},
{   name = "2F West Stairwell",
    data = {
        description = "",
        look = "",
        south = "2F Hallway West",
        west = "2F Entrance",
        up = "3F West Stairwell",
        down = "1F West Stairwell"
    }
},
{   name = "2F East Stairwell",
    data = {
        description = "",
        look = "",
        south = "2F Hallway East",
        up = "3F East Stairwell",
        down = "1F East Stairwell"
    }
},
{   name = "Principal’s Office",
    data = {
        description = "",
        look = "",
        north = "2F Hallway West"
    }
},
{   name = "2F Entrance",
    data = {
        description = "",
        look = "",
        east = "2F West Stairwell"
    }
},
{   name = "School Courtyard",
    data = {
        description = "",
        look = "",
        up = "2F Entrance"
    }
},
{   name = "Library",
    data = {
        description = "",
        look = "",
        north = "2F Hallway East"
    }
},
{   name = "3F West Stairwell",
    data = {
        description = "",
        look = "",
        south = "3F Hallway West"
    }
},
{   name = "3F East Stairwell",
    data = {
        description = "",
        look = "",
        south = "3F Hallway East"
    }
},
{   name = "3F Hallway West",
    data = {
        description = "",
        look = "",
        north = "3F West Stairwell",
        east = "3F Hallway Central"
    }
},
{   name = "3F Hallway Central",
    data = {
        description = "",
        look = "",
        east = "3F Hallway East",
        west = "3F Hallway West"
    }
},
{   name = "3F Hallway East",
    data = {
        description = "",
        look = "",
        north = "3F East Stairwell",
        west = "3F Hallway Central"
    }
},
{   name = "1F West Stairwell",
    data = {
        description = "",
        look = "",
        south = "1F Hallway West",
        up = "2F West Stairwell"
    }
},
{   name = "1F East Stairwell",
    data = {
        description = "",
        look = "",
        south = "1F Hallway East",
        up = "2F East Stairwell"
    }
},
{   name = "1F Hallway West",
    data = {
        description = "",
        look = "",
        north = "1F West Stairwell",
        east = "1F Hallway Central"
    }
},
{   name = "1F Hallway Central",
    data = {
        description = "",
        look = "",
        east = "1F Hallway East",
        west = "1F Hallway West"
    }
},
{   name = "1F Hallway East",
    data = {
        description = "",
        look = "",
        north = "1F East Stairwell",
        west = "1F Hallway Central"
    }
}

}
