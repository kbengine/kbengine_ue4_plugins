
#include "KBEnginePluginsPrivatePCH.h"
#include "Entity.h"

Entity::Entity():
	id_(0),
	className_(""),
	position_(),
	direction_(),
	isOnGround_(false),
	base_(NULL),
	cell_(NULL),
	inited_(false)
{
}

Entity::~Entity()
{
}
