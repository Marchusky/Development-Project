#ifndef __j1ENTITYPLAYER_H__
#define __j1ENTITYPLAYER_H__

#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"
#include "j1EntityMovable_Ground.h"
#include "j1Input.h"

struct Player_Input
{
	//TODO://SHORTCUTS //player only
	bool F1_enabled;	//START LEVEL 1 (falta)
	bool F2_enabled;	//START LEVEL 2 (falta)
	bool F3_enabled;	//Restart level (falta)
	bool F5_enabled;	//Save game (falta)
	bool F6_enabled;	//Load game (falta)
	bool F7_enabled;	//Show Colliders (falta)
	bool F8_enabled;	//God Mode (falta)

	//PLAYER //player only
	bool W_enabled;		//Climb
	bool A_enabled;		//Left
	bool S_enabled;		//Slide (has to press a direction in order to slide)
	bool D_enabled;		//Right
	bool Shift_enabled;	//Run
	bool Space_enabled;	//Jump

	//GODMODE //player only
	bool W_GOD_enabled;		//Up
	bool A_GOD_enabled;		//Left
	bool S_GOD_enabled;		//Down
	bool D_GOD_enabled;		//Right
};

class j1EntityPlayer : public j1EntityMovable_ground
{
public:
	j1EntityPlayer(iPoint pos, ENTITY_TYPE type);

	bool Awake(pugi::xml_node& node);
	
	bool PreUpdate();

	bool Update(float dt, bool doLogic);

	void OnCollision(Collider* c1, Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	
	//PLAYER
	//iPoint			Size;				EntityMovable inherited property -- Size
	//SDL_Rect		PlayerRect;				EntityMovable inherited property -- EntityRect
	Player_Input	PlayerInput;
	//Current_State	PlayerState;			EntityMovable inherited property -- EntityState

	//POSITION
	//iPoint		CurrentPosition;		EntityMovable inherited property -- CurrentPosition
	//iPoint		StartingPosition;		Entity inherited property		 -- StartingPosition
	iPoint			ActualizedPosition;		//Needed in EntityMovable?
	//float			PlayerVel_w;			EntityMovable inherited property -- velocity
	float			PlayerVel_r;
	float			PlayerVel_Y;
	//SDL_Texture*	Graphics = nullptr;		EntityMovable inherited property -- Graphics (also set to nullptr)


	//ANIMATION
	//Draw diferents animations
	//Animation*	EntityAnimation;		EntityMovable inherited property -- EntityAnimation
	//SDL_Rect		rotating_animation;		EntityMovable inherited property -- rotating_animation
	//bool			flipped = false;		EntityMovable inherited property -- flipped (also set to false)
	//Idle---
	//Animation		idle;					EntityMovable inherited property -- idle
	//Walking---
	//Animation		walking;				EntityMovable inherited property -- walking
	//Running---
	Animation		running;
	//Sliding---
	Animation		sliding;
	float			Slide_distance;
	//Climbing---
	Animation		climbing;
	//Dying---
	//Animation		dying;					EntityMovable inherited property -- dying
	void Movement();

	//Jumping---
	Animation		jumping;				
	float			TempVelY;
	float			FallingVel;
	float			height;
	bool			On_Ground;
	float			Gravity; //10
	float			GravitySave;
	bool			Jump_Ready;
	bool			MidAirUP;
	bool			Falling;
	bool			EndJump;
	bool			CanJump = true;
	bool			TouchingCollider;
	bool			JumpTicks;
	bool			FallLeft;
	bool			FallRight;

	void			On_The_Air();
	void			On_The_Ground();
	void			Jumping();



	
	//SHORTCUTS
	bool God_Mode = false;

	//Colliders---
	//Collider*		PlayerCollider;			EntityMovable inherited property -- EntityCollider

	bool lateral_collision_left = false;
	bool lateral_collision_right = false;
	bool top_collision = false;
	bool bottom_collision = false;

	uint WALL_id;
	uint CLIMB_WALL_id;
	uint BONUS_id;
};
#endif __j1ENTITYPLAYER_H__
