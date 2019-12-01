#ifndef __j1ENTITYPLAYER_CPP__
#define __j1ENTITYPLAYER_CPP__

#include "j1EntityMovable_Ground.h"
#include "j1EntityMovable.h"
#include "p2Point.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "Animation.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1Window.h"
#include "j1EntityPlayer.h"

j1EntityPlayer::j1EntityPlayer(iPoint pos, ENTITY_TYPE type) : j1EntityMovable_ground(pos, type)
{
	name.create("player");

	LOG("Loading player textures");
	EntityTexture = App->tex->Load("Spritesheets/Santa.png");

	//IDLE
	idle.PushBack({ 5,1,48,75 });
	idle.PushBack({ 135,1,48,75 });
	idle.PushBack({ 266,1,48,75 });
	idle.PushBack({ 395,1,48,75 });
	idle.PushBack({ 525,1,48,75 });
	idle.PushBack({ 655,1,48,75 });
	idle.PushBack({ 785,1,48,75 });
	idle.PushBack({ 915,1,48,75 });
	idle.PushBack({ 1045,1,48,75 });
	idle.PushBack({ 1175,1,48,75 });

	idle.PushBack({ 6,90,48,75 });
	idle.PushBack({ 136,90,48,75 });
	idle.PushBack({ 266,90,48,75 });
	/*idle.PushBack({ 395,90,48,75 });
	idle.PushBack({ 527,90,48,75 });
	idle.PushBack({ 659,90,48,75 });*/

	idle.speed = 0.25f;

	//WALKING

	walking.PushBack({ 5,219,48,75 });
	walking.PushBack({ 136,219,48,75 });
	walking.PushBack({ 268,219,48,75 });
	walking.PushBack({ 397,219,48,75 });
	walking.PushBack({ 525,219,48,75 });
	walking.PushBack({ 656,219,48,75 });
	walking.PushBack({ 785,219,48,75 });
	walking.PushBack({ 916,219,48,75 });
	walking.PushBack({ 1047,219,48,75 });
	walking.PushBack({ 1175,219,48,75 });

	walking.PushBack({ 6,308,48,75 });
	walking.PushBack({ 137,308,48,75 });
	walking.PushBack({ 266,308,48,75 });

	walking.speed = 0.3f;

	//RUNNING
	running.PushBack({ 3,457,48,75 });
	running.PushBack({ 133,457,48,75 });
	running.PushBack({ 263,457,48,75 });
	running.PushBack({ 394,457,48,75 });
	running.PushBack({ 523,457,48,75 });
	running.PushBack({ 654,457,48,75 });
	running.PushBack({ 781,457,48,75 });
	running.PushBack({ 908,457,48,75 });
	running.PushBack({ 1041,457,48,75 });
	running.PushBack({ 1174,457,48,75 });

	running.PushBack({ 3,547,48,75 });

	running.speed = 0.1f;

	//JUMPING
	jumping.PushBack({ 23,663,48,75 });
	jumping.PushBack({ 157,663,48,75 });
	/*jumping.PushBack({ 287,663,48,75 });
	jumping.PushBack({ 412,663,48,75 });
	jumping.PushBack({ 543,663,48,75 });
	jumping.PushBack({ 659,663,48,75 });
	jumping.PushBack({ 788,663,48,75 });
	jumping.PushBack({ 915,663,48,75 });
	jumping.PushBack({ 1047,663,48,75 });
	jumping.PushBack({ 1177,663,75 });

	jumping.PushBack({ 6,749,48,75 });
	jumping.PushBack({ 136,749,48,75 });
	jumping.PushBack({ 275,749,48,75 });
	jumping.PushBack({ 411,749,48,75 });
	jumping.PushBack({ 542,749,48,75 });
	jumping.PushBack({ 674,749,48,75 });*/

	jumping.speed = 0.1f;

	//SLIDING
	sliding.PushBack({ 3,881,76,75 });
	sliding.PushBack({ 133,881,76,75 });
	sliding.PushBack({ 264,881,76,75 });
	sliding.PushBack({ 422,881,76,75 });
	sliding.PushBack({ 523,881,76,75 });
	sliding.PushBack({ 651,881,76,75 });
	sliding.PushBack({ 781,881,76,75 });
	sliding.PushBack({ 913,881,76,75 });
	sliding.PushBack({ 1043,881,76,75 });
	sliding.PushBack({ 1174,881,76,75 });

	sliding.PushBack({ 3,971,76,75 });

	sliding.speed = 0.1f;

	//DYING
	dying.PushBack({ 6,1086,48,75 });
	dying.PushBack({ 66,1086,48,75 });
	dying.PushBack({ 122,1086,48,75 });
	dying.PushBack({ 175,1086,48,75 });
	dying.PushBack({ 258,1086,48,75 });
	dying.PushBack({ 342,1086,48,75 });
	dying.PushBack({ 426,1086,48,75 });
	dying.PushBack({ 594,1086,48,75 });
	dying.PushBack({ 680,1086,83,75 });
	dying.PushBack({ 760,1086,83,75 });

	dying.PushBack({ 6,1173,83,75 });
	dying.PushBack({ 66,1173,83,75 });
	dying.PushBack({ 122,1173,83,75 });
	dying.PushBack({ 175,1173,83,75 });
	dying.PushBack({ 225,1173,83,75 });
	dying.PushBack({ 276,1173,83,75 });
	dying.PushBack({ 276,1173,83,75 });

	dying.speed = 0.1f;

	
} 

bool j1EntityPlayer::Awake(pugi::xml_node& node)
{
	//Player loaded from xml (LOS NOMBRES DE LAS VARIABLES YA ESTÁN BIEN PUESTOS)
	pugi::xml_node colliders = node.child("player").child("colliders");
	pugi::xml_node player_stats = node.child("player").child("player_stats");

	Size.x = player_stats.child("charachter_width").attribute("value").as_uint();
	Size.y = player_stats.child("character_height").attribute("value").as_uint();
	StartingPosition.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
	StartingPosition.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
	CurrentPosition.x = StartingPosition.x;
	CurrentPosition.y = StartingPosition.y;
	velocity = player_stats.child("PlayerVel_w").attribute("value").as_uint();
	PlayerVel_r = player_stats.child("PlayerVel_r").attribute("value").as_uint();
	PlayerVel_Y = player_stats.child("PlayerVel_Y").attribute("value").as_uint();
	Gravity = player_stats.child("Gravity").attribute("value").as_float();
	FallingVel = player_stats.child("falling_velocity").attribute("value").as_float();
	Slide_distance = player_stats.child("slide_distance").attribute("value").as_uint();

	//--- main_Collider creation
	EntityRect.w = player_stats.child("character_width").attribute("value").as_uint();
	EntityRect.h = player_stats.child("character_height").attribute("value").as_uint();
	EntityRect.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
	EntityRect.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
	EntityCollider = App->coll->AddCollider(EntityRect, COLLIDER_TYPE::PLAYER);

	//--collider ID's
	WALL_id = colliders.child("tile_types").child("WALL").attribute("value").as_uint();
	CLIMB_WALL_id = colliders.child("tile_types").child("CLIMB_WALL").attribute("value").as_uint();
	BONUS_id = colliders.child("tile_types").child("BONUS").attribute("value").as_uint();


	

	EntityState = Current_State::ST_IDLE;
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };


	God_Mode = false;



	return true;
}


bool j1EntityPlayer::PreUpdate()
{
	On_Ground;
	if (On_Ground == false) {

		Falling = true;
	}

	if (Falling == true)
	{

		CurrentPosition.y += Gravity;
	}
	bool ret = true;
	//SHORTCUTS INPUTS--- 
	PlayerInput.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN;
	PlayerInput.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN;
	PlayerInput.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN;
	PlayerInput.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN;
	PlayerInput.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN;
	PlayerInput.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN;
	PlayerInput.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN;

	//GODMODE---
	if (God_Mode == false && PlayerInput.F8_enabled)
	{
		LOG("GOD MODE ACTIVATED");
		God_Mode = true;
	}
	else if (God_Mode == true && PlayerInput.F8_enabled)
	{
		LOG("GOD MODE DEACTIVATED");
		God_Mode = false;
	}
	if (God_Mode == false)
	{
		PlayerInput.W_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
		PlayerInput.A_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
		PlayerInput.S_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN;
		PlayerInput.D_enabled = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
		PlayerInput.Shift_enabled = App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_REPEAT;
		PlayerInput.Space_enabled = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_REPEAT;
	}
	else
	{
		PlayerInput.W_GOD_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
		PlayerInput.A_GOD_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
		PlayerInput.S_GOD_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
		PlayerInput.D_GOD_enabled = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	}

	//PLAYER STATES
	if (God_Mode == false)
	{
		CurrentPosition.y += Gravity;

		if (EntityState == Current_State::ST_IDLE)
		{
			if (PlayerInput.A_enabled)
			{
				EntityState = Current_State::ST_LEFT_W;
			}
			if (PlayerInput.D_enabled)
			{
				EntityState = Current_State::ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				
				EntityState = Current_State::ST_JUMPING;

				if (On_Ground == false) {
					EntityState = Current_State::ST_FALLING;
					LOG("JUMP NOT AVAILABLE");
				}
			}
			if (PlayerInput.Space_enabled) {

				On_Ground = false;
				CanJump = false;
				PlayerVel_Y = 50;
				EntityState = Current_State::ST_JUMPING;

			}
		}
		if (EntityState == Current_State::ST_LEFT_W)
		{
			if (!PlayerInput.A_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (PlayerInput.Shift_enabled)
			{
				EntityState = Current_State::ST_LEFT_R;
			}
			if (PlayerInput.D_enabled)
			{
				EntityState = Current_State::ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled &&  CanJump == true)
			{
				On_Ground = false;
				EntityState = Current_State::ST_JUMPING;
			}
		}
		if (EntityState == Current_State::ST_LEFT_R)
		{
			if (!PlayerInput.A_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (!PlayerInput.Shift_enabled)
			{
				EntityState = Current_State::ST_LEFT_W;
			}
			if (PlayerInput.D_enabled)
			{
				EntityState = Current_State::ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled && CanJump == true)
			{
				EntityState = Current_State::ST_JUMPING;
			}
			if (PlayerInput.S_enabled)
			{
				EntityState = Current_State::ST_SLIDING;
			}
		}
		if (EntityState == Current_State::ST_RIGHT_W)
		{
			if (!PlayerInput.D_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (PlayerInput.Shift_enabled)
			{
				EntityState = Current_State::ST_RIGHT_R;
			}
			if (PlayerInput.A_enabled)
			{
				EntityState = Current_State::ST_LEFT_W;
			}
			if (PlayerInput.Space_enabled && CanJump == true)
			{
				EntityState = Current_State::ST_JUMPING;
			}
		}
		if (EntityState == Current_State::ST_RIGHT_R)
		{
			if (!PlayerInput.D_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (!PlayerInput.Shift_enabled)
			{
				EntityState = Current_State::ST_RIGHT_W;
			}
			if (PlayerInput.A_enabled)
			{
				EntityState = Current_State::ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled && CanJump == true)
			{
				EntityState = Current_State::ST_JUMPING;
			}
			if (PlayerInput.S_enabled)
			{
				EntityState = Current_State::ST_SLIDING;
			}
		}
		if (EntityState == Current_State::ST_JUMPING)
		{
			/*if (PlayerInput.W_enabled)
			{
				EntityState = Current_State::ST_CLIMBING;
			}*/
		}
		if (EntityState == Current_State::ST_FALLING)
		{

		}
		if (EntityState == Current_State::ST_SLIDING)
		{
			if (!PlayerInput.S_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (PlayerInput.Space_enabled && CanJump == true)
			{
				EntityState = Current_State::ST_JUMPING;
			}
		}
		if (EntityState == Current_State::ST_CLIMBING)
		{
			if (!PlayerInput.W_enabled)
			{
				EntityState = Current_State::ST_IDLE;
			}
			if (PlayerInput.Space_enabled && CanJump == true)
			{
				EntityState = Current_State::ST_JUMPING;
			}
		}
		//NOT NEEDED IN THIS VERSION
		if (EntityState == Current_State::ST_DYING) {}
	}
	//GODMODE MOVEMENT
	else if (God_Mode == true)
	{
		if (PlayerInput.W_GOD_enabled)
		{
			CurrentPosition.y -= PlayerVel_r;
		}
		if (PlayerInput.A_GOD_enabled)
		{
			CurrentPosition.x -= PlayerVel_r;

		}
		if (PlayerInput.S_GOD_enabled)
		{
			CurrentPosition.y += PlayerVel_r;

		}
		if (PlayerInput.D_GOD_enabled)
		{
			CurrentPosition.x += PlayerVel_r;
		}
	}

	return ret;
}

bool j1EntityPlayer::Update(float dt, bool doLogic)
{
	bool ret = true;
	ActualizedPosition = CurrentPosition;

	//MOVEMENT THROUGH STATES
	switch (EntityState)
	{
	case Current_State::ST_IDLE:
		LOG("IDLE");
		if (EndJump == true) {
			EntityAnimation = &idle;
		}
		else {
			EntityAnimation = &jumping;
		}
		JumpTicks = true;
		break;

	case Current_State::ST_LEFT_W:
		LOG("WALKING LEFT");
		flipped = true;
		Movement();
		EntityAnimation = &walking;
		break;

	case Current_State::ST_LEFT_R:
		LOG("RUNNING LEFT");
		flipped = true;
		Movement();
		EntityAnimation = &running;
		break;

	case Current_State::ST_RIGHT_W:
		LOG("WALKING RIGHT");
		flipped = false;
		Movement();
		EntityAnimation = &walking;
		break;

	case Current_State::ST_RIGHT_R:
		LOG("RUNNING RIGHT");
		flipped = false;
		Movement();
		EntityAnimation = &running;
		break;

	case Current_State::ST_JUMPING:
		LOG("JUMPING");
		
		EntityAnimation = &jumping;
	
		EndJump = false;
		On_The_Ground();

		if (Jump_Ready == true) {
			MidAirUP = true;

			Jumping();
		}
		if (EndJump == true) {
			Current_State::ST_FALLING;
			EntityAnimation = &jumping;
		}
		break;

	case Current_State::ST_FALLING:
		LOG("FALLING");
		TouchingCollider = false;
		EntityAnimation = &jumping;

		break;

	case Current_State::ST_SLIDING:
		LOG("SLIDING");
		EntityAnimation = &sliding;
		break;

	case Current_State::ST_CLIMBING:
		LOG("CLIMBING");
		EntityAnimation = &climbing;
		break;

	case Current_State::ST_DYING:
		LOG("DYING");
		EntityAnimation = &dying;
		break;
	}

	//PLAYER
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
	EntityCollider->SetPos(CurrentPosition.x, CurrentPosition.y);

	//ANIMATIONS
	rotating_animation = EntityAnimation->GetCurrentFrame();
	//App->render->Blit(Graphics, CurrentPosition.x, CurrentPosition.y, &rotating_animation, flipped);
	if (flipped == false)
	{
		BlitEntities(rotating_animation, flipped, CurrentPosition.x, CurrentPosition.y);
	}
	else
	{
		BlitEntities(rotating_animation, flipped, CurrentPosition.x, CurrentPosition.y);
	}


	return true;
}

void j1EntityPlayer::On_The_Ground()
{
	//CHECK COLLISION
	CanJump = false;
	if (On_Ground == true) {

		Jump_Ready = true;

		LOG("ON GROUND TRUE");
	}
	else if (On_Ground == false) {

		Jump_Ready = false;

		LOG("ON GROUND FALSE");
	}
}

void j1EntityPlayer::Jumping() 
{
	CanJump = false;

	if (MidAirUP == true) {
		LOG("MID AIR TRUE");
		PlayerVel_Y -= Gravity * 0.75;

		if (PlayerInput.A_enabled) 
		{
			CurrentPosition.x -= 1.5*velocity;
		}

		if (PlayerInput.D_enabled) {
			CurrentPosition.x += 1.5*velocity;

			LOG("GOING RIGHT INSIDE JUMP");
		}

		if (PlayerVel_Y <= 0) {
			height = CurrentPosition.y;
			LOG("VELOCITY REACHED 0 at %f", height);
			MidAirUP = false;
		}

		CurrentPosition.y -= PlayerVel_Y / 2;
	}

	if (MidAirUP == false) {
		LOG("MID AIR UP == FALSE");


		if (PlayerInput.D_enabled) {
			FallLeft = true;
			FallRight = false;

		}
		if (PlayerInput.A_enabled) {
			FallRight = true;
			FallLeft = false;
		}

		if (On_Ground == true) {
			LOG("TO IDLE FROM JUMP");
			EndJump = true;
			PlayerVel_Y = TempVelY;
		}

		else {
			LOG("FALLING");
			CurrentPosition.y += PlayerVel_Y;
			++FallingVel;
			LOG("TIMES = %d", FallingVel);
		}
	}
}

void j1EntityPlayer::On_The_Air() {

	CanJump = false;
	if (On_Ground == true) {
		Jump_Ready = false;
	}
	else if (On_Ground == false) {
		Jump_Ready = true;
	}

}

void j1EntityPlayer::Movement() {

	if (PlayerInput.A_enabled && !TouchingCollider) {
		if (!PlayerInput.Shift_enabled)
		{
			CurrentPosition.x -= velocity;
		}
		else if (PlayerInput.Shift_enabled)
		{
			CurrentPosition.x -= PlayerVel_r;
		}
	}

	if (PlayerInput.D_enabled && !TouchingCollider) {
		if (!PlayerInput.Shift_enabled)
		{
			CurrentPosition.x += velocity;
		}
		else if (PlayerInput.Shift_enabled)
		{
			CurrentPosition.x += PlayerVel_r;
		}

	}

}

bool j1EntityPlayer::Load(pugi::xml_node& data) 
{

	CurrentPosition.x = data.child("scene1").child("playerPos").attribute("x").as_float();
	CurrentPosition.y = data.child("scene1").child("playerPos").attribute("y").as_float();

	return true;
}

bool j1EntityPlayer::Save(pugi::xml_node& data) const
{
	pugi::xml_node player = data.append_child("playerPos");

	player.append_attribute("x") = CurrentPosition.x;
	player.append_attribute("y") = CurrentPosition.y;

	return true;
}

void j1EntityPlayer::OnCollision(Collider* c1, Collider* c2)
{

	return;
}
#endif __j1ENTITYPLAYER_CPP__

