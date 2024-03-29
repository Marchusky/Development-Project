#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	// TODO 1: if origin or destination are not walkable, return -1
	bool ret = -1;

	if (IsWalkable(origin) != false && IsWalkable(destination) != false)
	{
		// TODO 2: Create two lists: open, close
		PathList open;
		PathList closed;

		PathNode pathNode_open(0, 0, origin, nullptr);
		//Add the origin tile to open
		open.list.add(pathNode_open);
		// Iterate while we have tiles in the open list
		while (open.list.count() != 0)
		{
			//LOG("1");
			// TODO 3: Move the lowest score cell from open list to the closed list
			p2List_item<PathNode>* lowestFNode = open.GetNodeLowestScore();
			open.list.del(open.GetNodeLowestScore());

			p2List_item<PathNode>* current = closed.list.add(lowestFNode->data);
			// TODO 4: If we just added the destination, we are done!
			if (current->data.pos == destination)
			{
				last_path.Clear();
				// Backtrack to create the final path

				for (const PathNode* node = &current->data; node != NULL; node = node->parent)
					last_path.PushBack(node->pos);
				// Use the Pathnode::parent and Flip() the path when you are finish
				last_path.Flip();
				LOG("Distance to destinaton of: %d", last_path.Count());
				ret = last_path.Count();
				break;
			}
			// TODO 5: Fill a list of all adjacent nodes
			PathList adjacent_nodes;
			current->data.FindWalkableAdjacents(adjacent_nodes);

			// TODO 6: Iterate adjancent nodes:
			p2List_item<PathNode>* nodeIt = adjacent_nodes.list.start;
			// ignore nodes in the closed list
			while (nodeIt != NULL)
			{
				//LOG("2");
				if (closed.Find(nodeIt->data.pos) == NULL)
				{
					// If it is NOT found, calculate its F and add it to the open list
					// If it is already in the open list, check if it is a better path (compare G)
					if (open.Find(nodeIt->data.pos) != NULL)
					{
						if (open.Find(nodeIt->data.pos)->data.g > nodeIt->data.g)
						{
							const PathNode* parent = open.Find(nodeIt->data.pos)->data.parent;
							parent = nodeIt->data.parent;
						}
						// If it is a better path, Update the parent

					}
					else
					{
						nodeIt->data.CalculateF(destination);
						open.list.add(nodeIt->data);
					}
				}
				nodeIt = nodeIt->next;
			}
			adjacent_nodes.list.clear();
		}
	}
	return ret;
}

