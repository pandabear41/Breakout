#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

enum {
    TILE_TYPE_NONE = 0,

    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class Tile {
    public:
        int     tileID;
        int     typeID;
		
        Tile();
};

#endif // TILE_H_INCLUDED