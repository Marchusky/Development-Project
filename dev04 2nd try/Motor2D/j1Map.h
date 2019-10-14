#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
struct Layer
{
	p2SString name;
	unsigned int width = 0u;
	unsigned int height = 0u;
	unsigned int* gid_list;

	// TODO 6: Short function to get the value of x, y

	inline uint Get(int x, int y) //const
	{
		return (y * width) + x;
	}

};

// ----------------------------------------------------
struct TileSet
{
	
	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;

	// TODO 7: Create a method that receives a tile id and returns it's Rect
	SDL_Rect GetTileRect(uint id)
	{
		SDL_Rect tile_rect;

		//first gid is the id number that has the first tile. We have to substract 
		//firstgid parameter to the id that is passed when the method is called so 
		//the id would be placed where it belongs into the actual array.
		uint tile_id = id - firstgid;

		//tilerect parameters:
		tile_rect.h = tile_height;
		tile_rect.w = tile_width;
		tile_rect.x = margin + ((tile_width + spacing) * (tile_id % num_tiles_width));
		tile_rect.y = margin + ((tile_height + spacing) * (tile_id / num_tiles_width));

		return tile_rect;
	}
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	// TODO 2: Add a list/array of layers to the map!
	p2List<Layer*>		layers;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	inline uint X_MapToWorld(uint x)
	{
		return (data.tile_width * x);
	}
	uint Y_MapToWorld(uint y)
	{
		return (data.tile_height * y);
	}

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single laye
	bool LoadLayer(pugi::xml_node& node, Layer* layer);

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__