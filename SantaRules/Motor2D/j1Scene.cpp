#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "j1EntityPlayer.h"
#include "j1FadeToBlack.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	transition_time = config.child("transition_time").attribute("value").as_float();

	for (pugi::xml_node map = config.child("map_name"); map; map = map.next_sibling("map_name"))
	{
		p2SString* data = new p2SString;

		data->create(map.attribute("name").as_string());
		map_names.add(data);
	}

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	bool ret;

	to_end = false;
	Map_1 = true;
	Map_2 = false;

	ret = App->map->Load(map_names.start->data->GetString());
	LOG("Currenmt Level: %s", map_names.start->data->GetString());

	
	if (App->map->Load(map_names.start->data->GetString()) == true)		
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
		{
			App->pathfinding->SetMap(w, h, data);
		}

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/PathTile.png");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{	
	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	iPoint Player_pos = App->map->WorldToMap(App->manager->Player->CurrentPosition.x, App->manager->Player->CurrentPosition.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = Player_pos;
			origin_selected = true;
		}
	}

	/*if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
	{
		App->pathfinding->CreatePath((iPoint(0,0), iPoint(camera));
	}*/
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//camera movement with keys
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->render->camera.x += ceil(camera_speed_debugg * dt);	//As the value is multiplied by dt, camera movement will be adjusted to the framerate.  (100 * 0.033s (30fps), 100 * 0.066s (60fps)...)
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->render->camera.x -= ceil(camera_speed_debugg * dt);	//Ceil rounds up all the decimal values, returning the smallest integral value not less than the given value. 
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		App->render->camera.y += ceil(camera_speed_debugg * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		App->render->camera.y -= ceil(camera_speed_debugg * dt);
	}

	//Debugg keys
	if (App->manager->Player->PlayerInput.F1_enabled)			//Load First Level
	{
		App->fade->Fade_To_Black("map_1.tmx", transition_time);
	}
	if (App->manager->Player->PlayerInput.F2_enabled)			//Load Second Level
	{
		App->fade->Fade_To_Black("map_2.tmx",transition_time);
	}
	if (App->manager->Player->PlayerInput.F3_enabled)			//Restart Key
	{
		App->manager->Player->CurrentPosition.x = App->manager->Player->StartingPosition.x;
		App->manager->Player->CurrentPosition.y = App->manager->Player->StartingPosition.y;
	}
	if (App->manager->Player->PlayerInput.F5_enabled)			//Save Game Key
	{
		App->SaveGame("save_game.xml");
	}
	if (App->manager->Player->PlayerInput.F6_enabled)			//Load Game Key
	{
		App->LoadGame("save_game.xml");
	}


	uint win_height = 0;
	uint win_width = 0;
	App->win->GetWindowSize(win_width, win_height);

	App->render->camera.y = -(App->manager->Player->CurrentPosition.y - ((int)win_height/2));
	App->render->camera.x = -(App->manager->Player->CurrentPosition.x - ((int)win_width/2));
	App->map->Draw();
	App->coll->DebugDraw();

	//-------------------------------------------------------------------
	//Uncomment to show coordinates on title for debugg functions

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	/*p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());*/

	//-------------------------------------------------------------------

	// Debug pathfinding ------------------------------
	//int x, y; 
	i++; // test 
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);
	
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	if (i == 100 && j < path->Count())
	{
		iPoint pos = App->map->MapToWorld(path->At(j)->x, path->At(j)->y);
		App->manager->Player->CurrentPosition = pos;
		j++;
		i = 0;
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	App->coll->CleanUp();
	//App->manager->DestroyEntity(fffffffffff); //all entities destroyed
	App->map->CleanUp();
	if (App->manager->Player != nullptr)
	{
		App->manager->Player->CleanUp();
	}
	return true;
}

bool j1Scene::Save(pugi::xml_node& data) const
{
	data.append_child("currentMap").append_attribute("num") = currentMap;
	return true;
}

bool j1Scene::Load(pugi::xml_node& data)
{

	if (currentMap != data.child("currentMap").attribute("num").as_int())
	{
		LOG("Calling switch maps");
		currentMap = data.child("currentMap").attribute("num").as_int();
		App->map->SwitchMaps(map_names[data.child("currentMap").attribute("num").as_int()]);

	}
	return true;
}