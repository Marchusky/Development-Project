#ifndef __j1ENTITYMOVABLE_GROUND_H__
#define __j1ENTITYMOVABLE_GROUND_H__

#include "j1EntityMovable.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"


class j1EntityMovable_ground : public j1EntityMovable
{
public:
	j1EntityMovable_ground(iPoint pos, ENTITY_TYPE type);

	virtual bool PreUpdate();
	
	virtual bool Update(float dt, bool doLogic);

	virtual void OnCollision(Collider* c1, Collider* c2);

};
#endif __j1ENTITYMOVABLE_GROUND_H__

