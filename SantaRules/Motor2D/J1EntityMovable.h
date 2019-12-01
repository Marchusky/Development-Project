#ifndef __j1ENTITYMOVABLE_H__
#define __j1ENTITYMOVABLE_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;
struct current_state;

class j1EntityMovable : public j1Entity
{
public:

	enum class Current_State
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_LEFT_W,
		ST_LEFT_R,
		ST_RIGHT_W,
		ST_RIGHT_R,
		ST_JUMPING,
		ST_FALLING,
		ST_SLIDING,
		ST_CLIMBING,
		ST_DYING,
	};

public:
	j1EntityMovable(iPoint pos, ENTITY_TYPE type);

	virtual bool Awake();

	virtual bool Update(float dt, bool doLogic);

	virtual bool CleanUp();

	virtual void OnCollision(Collider* c1, Collider* c2);

public: //animations

	//Idle
	Animation		idle;
	//Walking
	Animation		walking;
	//Dying
	Animation		dying;

public:

	//Basic properties
	Current_State	EntityState;
	SDL_Rect		EntityRect;
	uint			lifePoints;
	iPoint			Size;

	//Position / Movement
	iPoint			CurrentPosition;
	float			velocity;
	SDL_Texture*	Graphics = nullptr;
	
	//Animation
	Animation*		EntityAnimation;
	SDL_Rect		rotating_animation;
	bool			flipped = false;

	//Texture
	SDL_Texture*	tex;
	SDL_Rect*		tex_rect;
	
	

};

#endif	__j1ENTITYMOVABLE_H__

