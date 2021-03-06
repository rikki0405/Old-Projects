-- language.lua
-- this will contain the prepositions and verbs that will be allowable within the game

Prepositions = {
    -- prepositions will be dropped out of the parsed sentences
    List = { "a", "an", "by", "in", "on", "the" }
    
    -- will add more if required
}

verbs = {
    -- verbs are validated words allowed to contain meaning
    -- each will have a base meaning, with synonymous words following
    
    { -- 3/2 starting verb parse testing with this begins
        main = "go",
        synonyms = { "move" }
    },
    
    {
        main = "grab", -- below synonyms will return this meaning when parsed against objects
        synonyms = { "take", "pick", "nab", "pinch" }
    }, -- comma after braces IS REQUIRED!
    
    {
        main = "look",
        synonyms = { "peer", "gaze", "glance" }
    },

    {
        main = "use",
        synonyms = { "tsukau" } -- don't test with empty just yet...
    } -- no comma here as it is the last table value
}

Linkers = { -- words that make it take another object (Verb-Object-(with)-Object): (use-key-WITH-door)
    List = { "with" }
}
