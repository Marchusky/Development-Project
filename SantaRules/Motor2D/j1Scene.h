#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1EntityManager.h"
#include "j1EntityPlayer.h"

struct SDL_Texture;

enum ListOfMapNames
{
	FirstLevel,
	SecondLevel
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data) const;

public:
	p2List<p2SString*>	map_names;
	int					currentMap;
	float				transition_time;
	
	bool				to_end;
	bool				Map_1;			
	bool				Map_2;

private:
	SDL_Texture*		debug_tex;
	float				camera_speed_debugg;
	uint i = 0; // PF test
	uint j = 0; // PF test
};

#endif // __j1SCENE_H__