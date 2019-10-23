#ifndef _j1COLLISION_CPP_
#define _j1COLLISION_CPP_
//
//#include "j1App.h"
//#include "j1Collision.h"
//
//j1Collision::j1Collision()
//{
///*
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//		colliders[i] = nullptr;
//
//	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
//	matrix[COLLIDER_WALL][COLLIDER_PLAYER1] = true;
//	matrix[COLLIDER_WALL][COLLIDER_PLAYER2] = true;
//	matrix[COLLIDER_WALL][COLLIDER_PLAYER1_PARTICLE] = true;
//	matrix[COLLIDER_WALL][COLLIDER_PLAYER2_PARTICLE] = true;
//
//	matrix[COLLIDER_PLAYER1][COLLIDER_WALL] = true;
//	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1] = false;
//	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER2] = true;
//	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1_PARTICLE] = false;
//	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER2_PARTICLE] = true;
//
//	matrix[COLLIDER_PLAYER2][COLLIDER_WALL] = true;
//	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER1] = true;
//	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2] = false;
//	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER1_PARTICLE] = true;
//	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2_PARTICLE] = false;
//
//	matrix[COLLIDER_PLAYER1_PARTICLE][COLLIDER_WALL] = true;
//	matrix[COLLIDER_PLAYER1_PARTICLE][COLLIDER_PLAYER1] = false;
//	matrix[COLLIDER_PLAYER1_PARTICLE][COLLIDER_PLAYER2] = true;
//	matrix[COLLIDER_PLAYER1_PARTICLE][COLLIDER_PLAYER1_PARTICLE] = false;
//	matrix[COLLIDER_PLAYER1_PARTICLE][COLLIDER_PLAYER2_PARTICLE] = false;
//
//	matrix[COLLIDER_PLAYER2_PARTICLE][COLLIDER_WALL] = true;
//	matrix[COLLIDER_PLAYER2_PARTICLE][COLLIDER_PLAYER1] = true;
//	matrix[COLLIDER_PLAYER2_PARTICLE][COLLIDER_PLAYER2] = false;
//	matrix[COLLIDER_PLAYER2_PARTICLE][COLLIDER_PLAYER1_PARTICLE] = false;
//	matrix[COLLIDER_PLAYER2_PARTICLE][COLLIDER_PLAYER2_PARTICLE] = false;*/
//}
//
//j1Collision::~j1Collision()
//{}
// 
//
//bool j1Collision::Awake(pugi::xml_node&)
//{
//	bool ret = true;
//	// Remove all colliders scheduled for deletion
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
//		{
//			delete colliders[i];
//			colliders[i] = nullptr;
//		}
//	}
//
//	return ret;
//
//}
//
//// Called before render is available
//bool j1Collision::Start()
//{
//	bool ret = true;
//	DebugDraw();
//
//	return ret;
//}
//
//bool j1Collision::PostUpdate()
//{
//	bool ret = true;
//	//// Calculate collisions
//	//Collider* c1;
//	//Collider* c2;
//
//	//for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	//{
//	//	// skip empty colliders
//	//	if (colliders[i] == nullptr)
//	//		continue;
//	//	c1 = colliders[i];
//
//	//	// avoid checking collisions already checked
//	//	for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
//	//	{
//	//		// skip empty colliders
//	//		if (colliders[k] == nullptr)
//	//			continue;
//
//	//		c2 = colliders[k];
//
//	//		if (c1->CheckCollision(c2->rect) == true)
//	//		{
//	//			if (matrix[c1->type][c2->type] && c1->callback)
//	//				App->charlotte->OnCollision(c1, c2);
//
//	//			if (matrix[c2->type][c1->type] && c2->callback)
//	//				App->charlotte->OnCollision(c2, c1);
//	//		}
//
//	//	}
//	//}
//	return ret;
//}
//
////De aquí en adelante peta por falta de los otros modulos.
//
//void j1Collision::DebugDraw()
//{
//	//
//	//if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
//	//	debug = !debug;
//
//	//if (debug == false)
//	//	return;
//
//	//Uint8 alpha = 80;
//	//for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	//{
//	//	if (colliders[i] == nullptr)
//	//		continue;
//
//	//	switch (colliders[i]->type)
//	//	{
//	//	case COLLIDER_NONE: // white
//	//		App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
//	//		break;
//	//	case COLLIDER_WALL: // blue
//	//		App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
//	//		break;
//	//	case COLLIDER_PLAYER1: // green
//	//		App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
//	//		break;
//	//	case COLLIDER_PLAYER2: // red
//	//		App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
//	//		break;
//	//	case COLLIDER_PLAYER1_PARTICLE: // yellow
//	//		App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
//	//		break;
//	//	case COLLIDER_PLAYER2_PARTICLE: // magenta
//	//		App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
//	//		break;
//	//	}
//	//}
//
//}
//// Called before quitting
//bool j1Collision::CleanUp()
//{
//	LOG("Freeing all colliders");
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] != nullptr)
//		{
//			delete colliders[i];
//			colliders[i] = nullptr;
//		}
//	}
//
//	return true;
//}
//
//Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
//{
//	Collider* ret = nullptr;
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] == nullptr)
//		{
//			ret = colliders[i] = new Collider(rect, type, callback);
//			break;
//		}
//	}
//
//	return ret;
//}
//
//// -----------------------------------------------------
//
//bool Collider::CheckCollision(const SDL_Rect& r) const
//{
//	// Return true if there is an overlap
//	// between argument "r" and property "rect"
//
//	if (((r.x + r.w) >= (rect.x)) && ((r.x) <= (rect.x + rect.w))
//		&& ((r.y + r.h) >= (rect.y)) && ((r.y) <= (rect.y + rect.h)))
//	{
//		return true;
//	}
//
//	return false;
//}
#endif