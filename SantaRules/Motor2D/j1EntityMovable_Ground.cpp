#ifndef __j1ENTITYMOVABLE_GROUND_CPP__
#define __j1ENTITYMOVABLE_GROUND_CPP__

#include "j1EntityMovable_Ground.h"
#include "J1EntityMovable.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1Render.h"

j1EntityMovable_ground::j1EntityMovable_ground(iPoint pos, ENTITY_TYPE type) : j1EntityMovable(pos, type)
{
	//create name
	//TODO: PUSHBACKS

	LOG("Loading EntityMovable_ground textures");
	//Graphics = App->tex->Load("Spritesheets/Enemies/Bugfly/Idle_Flying.png");

	EntityState = Current_State::ST_IDLE;
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
}

bool j1EntityMovable_ground::PreUpdate()
{
	//some kind of state machine that, instead of input keys, 
	//works with the pathfinder ins some way I still have to think of
	return true;
}

bool j1EntityMovable_ground::Update(float dt, bool doLogic)
{
	//TODO: state machine of the bat

	//PLAYER
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
	EntityCollider->SetPos(CurrentPosition.x, CurrentPosition.y);

	////ANIMATIONS
	//rotating_animation = EntityAnimation->GetCurrentFrame();
	//App->render->Blit(Graphics, CurrentPosition.x, CurrentPosition.y, &rotating_animation, flipped);

	return true;
}

void j1EntityMovable_ground::OnCollision(Collider* c1, Collider* c2)
{
	// TODO: Launch dead animation if hit from top
	// TODO: Go a few tiles backwards after hitting the player before trying to attack again 
}
#endif __j1ENTITYMOVABLE_GROUND_CPP__