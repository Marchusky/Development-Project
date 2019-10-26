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


j1Player::j1Player()
{
	name.create("player");
}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& node)
{
	bool ret = true;

	pugi::xml_node colliders = node.child("colliders");
	
	//MAGIC NUMBERS -- config is set up to be filled with them
	Initial_Pos.x = node.attribute("InitalPos_x").as_uint();
	Initial_Pos.y = node.attribute("InitalPos_y").as_uint();
	CurrentPosition = { Initial_Pos.x,Initial_Pos.y };
	PlayerVel_w = node.attribute("PlayerVel_w").as_float();
	PlayerVel_r = node.attribute("PlayerVel_r").as_float();
	Gravity = node.attribute("Gravity").as_float();
	Slide_distance = node.attribute("slide_distance").as_float();
	//--- main_Collider creation
	SDL_Rect main_rect;
	main_rect.w = colliders.child("main_collider").child("width").attribute("value").as_uint();
	main_rect.h = colliders.child("main_collider").child("height").attribute("value").as_uint();
	main_rect.x = colliders.child("main_collider").child("coordinate_x").attribute("value").as_uint();
	main_rect.y = colliders.child("main_collider").child("coordinate_y").attribute("value").as_uint();
	main_Collider = App->coll->AddCollider(main_rect, COLLIDER_TYPE::PLAYER, this);
	return ret;
}

bool  j1Player::Start()
{
	LOG("Loading player textures");
	Graphics = App->tex->Load("Spritesheets/Santa.png");

	Floor = CurrentPosition.y;
	PlayerState = ST_IDLE;

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
	//PlayerInput.F11_enabled = App->input->keyboard[SDL_SCANCODE_F11] == KEY_DOWN;

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
	if (God_Mode == false) //preguntar
	{
		PlayerInput.W_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
		PlayerInput.A_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
		PlayerInput.S_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
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

	//LAYER STATES
	return ret;
}


bool j1Player::Update(float dt)
{
	bool ret = true;

	//MOVEMENT PER STATES
	switch (PlayerState)
	{
	case ST_IDLE:
		LOG("IDLE");
		//CurrentAnimation = &idle; FALTA
		break;

	case ST_LEFT_W:
		LOG("WALKING LEFT");
		CurrentPosition.x -= PlayerVel_w;
		CurrentPosition.y; //needed?
		break;

	case ST_LEFT_R:
		LOG("RUNNING LEFT");
		CurrentPosition.x = PlayerVel_r;
		CurrentPosition.y; //needed?
		break;

	case ST_RIGHT_W:
		LOG("WALKING RIGHT");
		CurrentPosition.x += PlayerVel_r;
		CurrentPosition.y; //needed?
		break;

	case ST_RIGHT_R:
		LOG("RUNNING RIGHT");
		CurrentPosition.x += PlayerVel_r;
		CurrentPosition.y; //needed?
		break;

	case ST_JUMPING:
		LOG("JUMPING");
		//Jumping(); FALTA
		break;

	case ST_SLIDING:
		LOG("DASH");
		//Slide(); FALTA
		break;

	case ST_CLIMBING:
		LOG("DASH");
		//Climb(); FALTA
		break;

	case ST_DYING:
		LOG("DASH");
		//CurrentAnimation = &Death; FALTA
		break;
	}

	//SDL_Rect r = CurrentAnimation->GetCurrentFrame();
	//App->render->Blit(Graphics, CurrentPosition.x, CurrentPosition.y, &r, 1.0f, true);
	
	//DRAW PLAYER
	PlayerRect = { CurrentPosition.x, CurrentPosition.y, 1, 1 }; //medir a papa noel FALTA
	App->render->DrawQuad(PlayerRect, 255, 255, 0);

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