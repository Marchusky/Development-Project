#ifndef __J1ENTITY__
#define __J1ENTITY__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;

enum class ENTITY_TYPE
{
	PLAYER,
	FLYING_ENEMY,
	WALKING_ENEMY,
	CASH_BAG,
	UNKNOWN_TYPE
};
class j1Entity : public j1Module
{
public:
	j1Entity(iPoint pos, ENTITY_TYPE type);

	virtual bool PreUpdate();

	virtual bool Update(float dt, bool doLogic);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	//save?

	//load?

	virtual bool Draw(iPoint pos, SDL_Rect rect, bool flip);

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual const Collider* GetCollider()
	{
		return EntityCollider;
	}

	virtual const iPoint GetPosition()
	{
		return StartingPosition;
	}

	virtual void SetTexture(SDL_Texture* texture)
	{
		EntityTexture = texture;
	}

protected:
	ENTITY_TYPE		Type;
	Collider*		EntityCollider;
	iPoint			StartingPosition;
	SDL_Texture*	EntityTexture;
	iPoint			sprite_size;

	friend class j1EntityManager;
};

#endif __J1ENTITY__