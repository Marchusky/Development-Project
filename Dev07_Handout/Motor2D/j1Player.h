#ifndef _j1PLAYER_H_
#define _j1PLAYER_H_

#include "j1Module.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Point.h"
#include "Animation.h"



struct SDL_Texture;
struct Animation;
struct Collider;

struct Player_Input
{
	//SHORTCUTS
	bool F1_enabled;	//START LEVEL 1 (falta)
	bool F2_enabled;	//START LEVEL 2 (falta)
	bool F3_enabled;	//Restart level (falta)
	bool F5_enabled;	//Save game (falta)
	bool F6_enabled;	//Load game (falta)
	bool F7_enabled;	//Show Colliders (falta)
	bool F8_enabled;	//God Mode (falta)
	bool F11_enabled;	//FOCUS CAMERA ON THE  PLAYER}; (falta). needed?

	//PLAYER
	bool W_enabled;		//Climb
	bool A_enabled;		//Left
	bool S_enabled;		//Slide (has to press a direction in order to slide)
	bool D_enabled;		//Right
	bool Shift_enabled;	//Run
	bool Space_enabled;	//Jump

	//GODMODE
	bool W_GOD_enabled;		//Up
	bool A_GOD_enabled;		//Left
	bool S_GOD_enabled;		//Down
	bool D_GOD_enabled;		//Right
};
enum Current_State
{
	ST_UNKNOWN,
	ST_IDLE,
	ST_LEFT_W,
	ST_LEFT_R,
	ST_RIGHT_W,
	ST_RIGHT_R,
	ST_JUMPING,
	ST_SLIDING,
	ST_CLIMBING,
	ST_DYING,
};

class j1Player : public j1Module
{
private:

	iPoint Initial_Pos;

public:
	//AUDIO

	//SHORTCUTS
	bool God_Mode = false;

	//TESTING - TEMPORAL
	float Floor = CurrentPosition.y; //Movement

	j1Player();

	virtual ~j1Player();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//PLAYER
	Player_Input	PlayerInput;
	Current_State	PlayerState;
	SDL_Rect		PlayerRect;

	//POSITION
	iPoint			CurrentPosition;
	iPoint			StartingPosition;
	float			PlayerVel_w;
	float			PlayerVel_r;
	SDL_Texture*	Graphics = nullptr;

	//Idle
	Animation		idle;

	//Walking
	Animation		walking;

	//Running
	Animation		running;

	//Jumping
	Animation		jumping;
	float			Gravity;

	//Sliding
	Animation		sliding;
	float			Slide_distance;
	//Climbing
	Animation		climbing;

	//Dying
	Animation		dying;

public:

	Collider*		main_Collider;
	uint			main_x;
	uint			main_y;
};

#endif