#ifndef _j1COLLISION_CPP_
#define _j1COLLISION_CPP_

#include "p2Log.h"
#include "p2list.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"

j1Collision::j1Collision()
{
	

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[WALL][WALL] = false;
	matrix[WALL][CLIMB_WALL] = false;
	matrix[WALL][BONUS] = false;
	matrix[WALL][PLAYER] = true;

	matrix[CLIMB_WALL][WALL] = false;
	matrix[CLIMB_WALL][CLIMB_WALL] = false;
	matrix[CLIMB_WALL][BONUS] = false;
	matrix[CLIMB_WALL][PLAYER] = true;

	matrix[BONUS][WALL] = false;
	matrix[BONUS][CLIMB_WALL] = false;
	matrix[BONUS][BONUS] = false;
	matrix[BONUS][PLAYER] = true;

	matrix[PLAYER][WALL] = true;
	matrix[PLAYER][CLIMB_WALL] = true;
	matrix[PLAYER][BONUS] = true;
	matrix[PLAYER][PLAYER] = false;
}

j1Collision::~j1Collision()
{}
 

bool j1Collision::Awake(pugi::xml_node& node)
{
	bool ret = true;

	name.create("collison"); //that's to fix the config file ids declaration inside player node

	return ret;
}

bool j1Collision::PostUpdate() //BIG ERROR HERE, CALLBACK ACCESSES WEIRD PLACES
{
	bool ret = true; 

	// Remove all colliders scheduled for deletion 
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	
	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;
		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true && matrix[c2->type][c1->type] && App->player->God_Mode != true)
			{
				App->player->OnCollision(c1, c2);
			}

		}
	}

	return ret;

	
}

void j1Collision::DebugDraw()
{
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		
		case PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		
		case CLIMB_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;

		case WALL: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

		case BONUS: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		} 
	}

}

bool j1Collision::canCollide_right(uint tile_id) //we get this id from the x and y value of the collider and with the function get()
{
	bool ret = true;
	if (App->map->Metadata->data[tile_id] != NULL)
	{
		if (App->map->Metadata->data[tile_id + 1] != NULL)
		{
			if (App->map->Metadata->data[tile_id + 1] == App->player->WALL_id 
				|| App->map->Metadata->data[tile_id + 1] == App->player->CLIMB_WALL_id)
			{
				ret = false;
			}
		}
	}
	return ret;
}
 bool j1Collision::canCollide_left(uint tile_id) //we get this id from the x and y value of the collider and with the function get()
{
	bool ret = true;
	if (App->map->Metadata->data[tile_id] != NULL)
	{
		if (App->map->Metadata->data[tile_id - 1] != NULL)
		{
			if (App->map->Metadata->data[tile_id - 1] == App->player->WALL_id ||
				App->map->Metadata->data[tile_id - 1] == App->player->CLIMB_WALL_id)
			{
				ret = false;
			}
		}
	}

	return ret;
}

bool j1Collision::canCollide_top(uint tile_id) //we get this id from the x and y value of the collider and with the function get()
{
	bool ret = true;
	if (App->map->Metadata->data[tile_id] != NULL)
	{
		if (App->map->Metadata->data[tile_id - App->map->Metadata->width] != NULL)
		{
			if (App->map->Metadata->data[tile_id - App->map->Metadata->width] == App->player->WALL_id ||
				App->map->Metadata->data[tile_id - App->map->Metadata->width] == App->player->CLIMB_WALL_id)
			{
				ret = false;
			}
		}
	}

	return ret;
}

bool j1Collision::canCollide_bottom(uint tile_id) //we get this id from the x and y value of the collider and with the function get()
{
	bool ret = true;
	if (App->map->Metadata->data[tile_id] != NULL)
	{
		if (App->map->Metadata->data[tile_id + App->map->Metadata->width] != NULL)
		{
			if (App->map->Metadata->data[tile_id + App->map->Metadata->width] == App->player->WALL_id ||
				App->map->Metadata->data[tile_id + App->map->Metadata->width] == App->player->CLIMB_WALL_id)
			{
				ret = false;
			}
		}
	}

	return ret;
}

// Called before quitting
bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}


Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret; 
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// Return true if there is an overlap
	// between argument "r" and property "rect"                                                                                                              

	if (((r.x + r.w) >= (rect.x)) && ((r.x) <= (rect.x + rect.w))
		&& ((r.y + r.h) >= (rect.y)) && ((r.y) <= (rect.y + rect.h)))
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------



#endif