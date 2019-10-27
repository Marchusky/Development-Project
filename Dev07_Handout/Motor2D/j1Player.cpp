#include "p2Point.h"
#include "p2Log.h"
#include "j1Module.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "Animation.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Collision.h"


j1Player::j1Player() : j1Module()
{
	name.create("player");

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
	//idle.PushBack({ 395,90,48,75 });
	//idle.PushBack({ 527,90,48,75 });
	//idle.PushBack({ 659,90,48,75 });

	idle.speed = 0.25f;

	//WALKING

	walking.PushBack({ 5,219,48,75 });
	walking.PushBack({ 134,219,48,75 });
	walking.PushBack({ 263,219,48,75 });
	walking.PushBack({ 391,219,48,75 });
	walking.PushBack({ 517,219,48,75 });
	walking.PushBack({ 646,219,48,75 });
	walking.PushBack({ 774,219,48,75 });
	walking.PushBack({ 903,219,48,75 });
	walking.PushBack({ 1031,219,48,75 });
	walking.PushBack({ 1154,219,48,75 });

	walking.PushBack({ 6,308,48,75 });
	walking.PushBack({ 134,308,48,75 });
	walking.PushBack({ 263,308,48,75 });

	walking.speed = 0.1f;

	//RUNNING
	running.PushBack({ 3,457,48,75 });
	running.PushBack({ 134,457,48,75 });
	running.PushBack({ 168,457,48,75 });
	running.PushBack({ 248,457,48,75 });
	running.PushBack({ 331,457,48,75 });
	running.PushBack({ 415,457,48,75 });
	running.PushBack({ 496,457,48,75 });
	running.PushBack({ 566,457,48,75 });
	running.PushBack({ 640,457,48,75 });
	running.PushBack({ 717,457,48,75 });
	 
	running.PushBack({ 3,219,48,75 });

	running.speed = 0.1f;

	//JUMPING
	jumping.PushBack({ 23,663,48,75 });
	jumping.PushBack({ 108,663,48,75 });
	jumping.PushBack({ 192,663,48,75 });
	jumping.PushBack({ 271,663,48,75 });
	jumping.PushBack({ 345,663,48,75 });
	jumping.PushBack({ 410,663,48,75 });
	jumping.PushBack({ 473,663,48,75 });
	jumping.PushBack({ 537,663,48,75 });
	jumping.PushBack({ 601,663,48,75 });
	jumping.PushBack({ 664,663,48,75 });

	jumping.PushBack({ 6,749,48,75 });
	jumping.PushBack({ 69,749,48,75 });
	jumping.PushBack({ 141,749,48,75 });
	jumping.PushBack({ 219,749,48,75 });
	jumping.PushBack({ 302,749,48,75 });
	jumping.PushBack({ 385,749,48,75 });
	
	jumping.speed = 0.1f;

	//SLIDING
	sliding.PushBack({ 3,881,76,75 });
	sliding.PushBack({ 57,881,76,75 });
	sliding.PushBack({ 110,881,76,75 });
	sliding.PushBack({ 163,881,76,75 });
	sliding.PushBack({ 215,881,76,75 });
	sliding.PushBack({ 267,881,76,75 });
	sliding.PushBack({ 319,881,76,75 });
	sliding.PushBack({ 372,881,76,75 });
	sliding.PushBack({ 425,881,76,75 });
	sliding.PushBack({ 479,881,76,75 });

	sliding.PushBack({ 3,971,76,75 });

	sliding.speed = 0.1f;

	//DYING
	dying.PushBack({ 6,1173,48,75 });
	dying.PushBack({ 66,1173,48,75 });
	dying.PushBack({ 122,1173,48,75 });
	dying.PushBack({ 175,1173,48,75 });
	dying.PushBack({ 258,1173,48,75 });
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

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& node)
{
	bool ret = true;

	pugi::xml_node colliders = node.child("colliders");
	pugi::xml_node player_stats = node.child("player_stats");

	
	//MAGIC NUMBERS -- config is set up to be filled with them
	Size.x = player_stats.child("charachter_width").attribute("value").as_uint();
	Size.y = player_stats.child("character_height").attribute("value").as_uint();
	Initial_Pos.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
	Initial_Pos.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
	CurrentPosition.x = Initial_Pos.x;
	CurrentPosition.y = Initial_Pos.y;
	PlayerVel_w = player_stats.child("PlayerVel_w").attribute("value").as_uint();
	PlayerVel_r = player_stats.child("PlayerVel_r").attribute("value").as_uint();
	Gravity = player_stats.child("Gravity").attribute("value").as_float();
	Slide_distance = player_stats.child("slide_distance").attribute("value").as_uint();
	//--- main_Collider creation
	PlayerRect.w = player_stats.child("character_width").attribute("value").as_uint();
	PlayerRect.h = player_stats.child("character_height").attribute("value").as_uint();
	PlayerRect.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
	PlayerRect.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
	PlayerCollider = App->coll->AddCollider(PlayerRect, COLLIDER_TYPE::PLAYER);

	//--collider ID's
	WALL_id = colliders.child("tile_types").child("WALL").attribute("value").as_uint();
	CLIMB_WALL_id = colliders.child("tile_types").child("CLIMB_WALL").attribute("value").as_uint();
	BONUS_id = colliders.child("tile_types").child("BONUS").attribute("value").as_uint();

	return ret;
}

bool  j1Player::Start()
{
	LOG("Loading player textures");
	Graphics = App->tex->Load("Spritesheets/Santa.png");

	PlayerState = ST_IDLE;
	PlayerRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };

	God_Mode = false;
	return true;
}

bool j1Player::PreUpdate()
{
	bool ret = true;
	//SHORTCUTS INPUTS
	PlayerInput.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN;
	PlayerInput.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN;
	PlayerInput.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN;
	PlayerInput.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN;
	PlayerInput.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN;
	PlayerInput.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN;
	PlayerInput.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN;


	//RESET CURRENT LEVEL
	if (PlayerInput.F3_enabled)
	{
		CurrentPosition.x = StartingPosition.x;
		CurrentPosition.y = StartingPosition.y;
		//FALTA CAMERA RESET
	}


	//GODMODE
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
		PlayerCollider->to_delete = true;
		PlayerInput.W_GOD_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
		PlayerInput.A_GOD_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
		PlayerInput.S_GOD_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
		PlayerInput.D_GOD_enabled = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	}

	//PLAYER STATES
	if (God_Mode == false)
	{
		if (PlayerState == ST_IDLE)
		{
			if (PlayerInput.A_enabled)
			{
				LOG("A pressed");
				PlayerState = ST_LEFT_W;
			}
			if (PlayerInput.D_enabled)
			{
				PlayerState = ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
		}
		if (PlayerState == ST_LEFT_W)
		{
			if (!PlayerInput.A_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (PlayerInput.Shift_enabled)
			{
				PlayerState = ST_LEFT_R;
			}
			if (PlayerInput.D_enabled)
			{
				PlayerState = ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
		}
		if (PlayerState == ST_LEFT_R)
		{
			if (!PlayerInput.A_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (!PlayerInput.Shift_enabled)
			{
				PlayerState = ST_LEFT_W;
			}
			if (PlayerInput.D_enabled)
			{
				PlayerState = ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
			if (PlayerInput.S_enabled)
			{
				PlayerState = ST_SLIDING;
			}
		}
		if (PlayerState == ST_RIGHT_W)
		{
			if (!PlayerInput.D_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (PlayerInput.Shift_enabled)
			{
				PlayerState = ST_RIGHT_R;
			}
			if (PlayerInput.A_enabled)
			{
				PlayerState = ST_LEFT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
		}
		if (PlayerState == ST_RIGHT_R)
		{
			if (!PlayerInput.D_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (!PlayerInput.Shift_enabled)
			{
				PlayerState = ST_RIGHT_W;
			}
			if (PlayerInput.A_enabled)
			{
				PlayerState = ST_RIGHT_W;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
			if (PlayerInput.S_enabled)
			{
				PlayerState = ST_SLIDING;
			}
		}
		if (PlayerState == ST_JUMPING)
		{
			if (PlayerInput.W_enabled)
			{
				PlayerState = ST_CLIMBING;
			}
		}
		if (PlayerState == ST_SLIDING)
		{
			if (!PlayerInput.S_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
		}
		if (PlayerState == ST_CLIMBING)
		{
			if (!PlayerInput.W_enabled)
			{
				PlayerState = ST_IDLE;
			}
			if (PlayerInput.Space_enabled)
			{
				PlayerState = ST_JUMPING;
			}
		}
		//NOT NEEDED IN THIS VERSION
		if(PlayerState == ST_DYING){}
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


bool j1Player::Update(float dt)
{
	bool ret = true;
	ActualizedPosition = CurrentPosition;

	//MOVEMENT THROUGH STATES
	switch (PlayerState)
	{
	case ST_IDLE:
		LOG("IDLE");
		current_animation = &idle; 
		break;

	case ST_LEFT_W:
		LOG("WALKING LEFT");
		flipped = true;
		CurrentPosition.x -= PlayerVel_w;
		current_animation = &walking;
		break;

	case ST_LEFT_R:
		LOG("RUNNING LEFT");
		flipped = true;
		CurrentPosition.x -= PlayerVel_r;
		current_animation = &running;
		break;

	case ST_RIGHT_W:
		LOG("WALKING RIGHT");
		flipped = false;
		CurrentPosition.x += PlayerVel_w;
		current_animation = &walking;
		break;

	case ST_RIGHT_R:
		LOG("RUNNING RIGHT");
		flipped = false;
		CurrentPosition.x += PlayerVel_r;   
		current_animation = &running;
		break;

	case ST_JUMPING:
		LOG("JUMPING");

		current_animation = &jumping;
		//FALTA
		break;

	case ST_SLIDING:
		LOG("SLIDING");
		current_animation = &sliding;
		break;

	case ST_CLIMBING:
		LOG("CLIMBING");
		current_animation = &climbing;
		break;

	case ST_DYING:
		LOG("DYING");
		current_animation = &dying;
		break;
	}

	//PLAYER
	PlayerRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
	PlayerCollider->SetPos(CurrentPosition.x, CurrentPosition.y);


	//ANIMATIONS
	rotating_animation = current_animation->GetCurrentFrame();
	App->render->Blit(Graphics, CurrentPosition.x, CurrentPosition.y, &rotating_animation, flipped);

	

	return true;
}


bool j1Player::PostUpdate()
{


	return true;
}


bool j1Player::CleanUp()
{

	LOG("Unloading Player");

	App->tex->UnLoad(Graphics);

	return true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	LOG("thx");
}

void j1Player::grounded()
{
	jump_available = false;
	if (in_land == true)
	{
		jump_available = true;
	}
	else
	{
		jump_available = false;
	}
}

void j1Player::jump()
{
	if (mid_air);
}