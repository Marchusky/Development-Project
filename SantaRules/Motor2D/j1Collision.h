#ifndef _j1COLLISION_H_
#define _j1COLLISION_H_

#define MAX_COLLIDERS 2000

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "j1Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	WALL,
	CLIMB_WALL,
	BONUS,
	PLAYER,
	ENEMY,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* calback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback) 
	{};

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}
	bool CheckCollision(const SDL_Rect& r) const;


	
};
class j1Collision : public j1Module
{
public:

	j1Collision();
	
	// Destructor
	virtual ~j1Collision();

	// Called before render is available
	bool Awake(pugi::xml_node& node);

	// Called before the first frame
	bool Update();

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	void DebugDraw();

	//--Check if collision from sides is possible--//
	bool canCollide_right(uint tile_gid);
	bool canCollide_top(uint tile_id);
	bool canCollide_bottom(uint tile_id);
	bool canCollide_left(uint tile_id);

 private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
	uint win_width;
	uint win_height;

};

#endif 