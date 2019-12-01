#ifndef __J1ENTITY_CPP__
#define __J1ENTITY_CPP__

#include "j1Entity.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"

j1Entity::j1Entity(iPoint pos, ENTITY_TYPE type) : StartingPosition(pos), Type(type), EntityTexture(nullptr), EntityCollider(nullptr)
{
	return;
}

bool j1Entity::PreUpdate()
{
	return true;
}

bool j1Entity::Update(float dt, bool doLogic)
{
	return true;
}

bool j1Entity::PostUpdate()
{
	return true;
}

bool j1Entity::CleanUp()
{
	return true;
}

bool j1Entity::Save(pugi::xml_node &)const
{
	return true;
}

bool j1Entity::Load(pugi::xml_node &)
{
	return true;
}

//bool j1Entity::Draw(iPoint pos, SDL_Rect rect, bool flip)
//{
//	bool ret = false;
//
//	if (ret = App->render->Blit(EntityTexture, pos.x, pos.y, &rect, flip) == 0)
//	{
//		LOG("Blit error: Entity Texture");
//	}
//
//	return ret;
//}

void j1Entity::BlitEntities(SDL_Rect r, bool flip, float x, float y)
{
	if (flip == false)
	{
		App->render->Blit(EntityTexture, x, y, &r, flip);
	}
	else
	{
		App->render->Blit(EntityTexture, x, y, &r, flip);
	}
}

void j1Entity::OnCollision(Collider* c1, Collider* c2) //collisions must be managed from the Entity manager
{
	return;
}

#endif __J1ENTITY_CPP__