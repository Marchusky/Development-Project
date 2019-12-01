#include "p2Point.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Window.h"
#include "j1Map.h"


#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"

j1FadeToBlack::j1FadeToBlack()
{

}

j1FadeToBlack:: ~j1FadeToBlack() 
{

}

bool j1FadeToBlack::Awake(pugi::xml_node&)
{
	screen = { 0, 0, App->win->width*App->win->scale, App->win->height*App->win->scale };
	return true;
}

bool j1FadeToBlack::Start()
{
	LOG("Preparing FadeToBlack");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool j1FadeToBlack::Update(float dt)
{
	if (current_step == fade_step::none)
	{
		return true;
	}

	uint now = SDL_GetTicks() - start_time;
	float normalized = 1.0f < ((float)now / (float)total_time) ? 1.0f : ((float)now / (float)total_time);


	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time) //Point where the screen is totally black, and the new map is loaded.
		{
			App->map->ChangeMap(map_name);							//Here the map is changed

			total_time += total_time;
			start_time = SDL_GetTicks();
			fading = false;
			current_step = fade_step::fade_from_black;
		}
	}
	break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
		{
			current_step = fade_step::none;
		}

	}
	break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

bool j1FadeToBlack::Fade_To_Black(const char* mapname, float time)
{
	bool ret = false;

	map_name = mapname;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;
	}

	return ret;
}