
#include "KBEnginePluginsPrivatePCH.h"
#include "Entity.h"

EntityFactory g_EntityFactory;
EntityDefMethodHandles g_EntityDefMethodHandles;

EntityCreator::EntityCreator(const FString& scriptName)
{
	g_EntityFactory.addEntityCreator(scriptName, this);
}

EntityCreator::~EntityCreator()
{
}

EntityDefMethodHandle::EntityDefMethodHandle(const FString& scriptName, const FString& defMethodName)
{
	g_EntityDefMethodHandles.add(scriptName, defMethodName, this);
}

EntityDefMethodHandle::~EntityDefMethodHandle()
{

}

EntityCreator* EntityFactory::addEntityCreator(const FString& scriptName, EntityCreator* pEntityCreator)
{
	creators.Add(scriptName, pEntityCreator);
	DEBUG_MSG("%s", *scriptName);
	return pEntityCreator;
}

EntityCreator* EntityFactory::findCreator(const FString& scriptName)
{
	EntityCreator** pCreator = g_EntityFactory.creators.Find(scriptName);
	if (pCreator == NULL)
	{
		return NULL;
	}

	return (*pCreator);
}

Entity* EntityFactory::create(const FString& scriptName)
{
	EntityCreator** pCreator = g_EntityFactory.creators.Find(scriptName);
	if (pCreator == NULL)
	{
		return NULL;
	}

	return (*pCreator)->create();
}

EntityDefMethodHandle* EntityDefMethodHandles::add(const FString& scriptName, const FString& defMethodName, EntityDefMethodHandle* pEntityDefMethodHandle)
{
	if (!defMethodHandles.Contains(scriptName))
		defMethodHandles.Add(scriptName, TMap<FString, EntityDefMethodHandle*>());

	TMap<FString, EntityDefMethodHandle*>* m = defMethodHandles.Find(scriptName);

	if (m->Contains(defMethodName))
	{
		ERROR_MSG("%s::%s exist!", *scriptName, *defMethodName);
		return NULL;
	}

	DEBUG_MSG("%s::%s", *scriptName, *defMethodName);
	m->Add(defMethodName, pEntityDefMethodHandle);
	return pEntityDefMethodHandle;
}

EntityDefMethodHandle* EntityDefMethodHandles::find(const FString& scriptName, const FString& defMethodName)
{
	TMap<FString, EntityDefMethodHandle*>* m = g_EntityDefMethodHandles.defMethodHandles.Find(scriptName);
	if (!m)
		return NULL;

	EntityDefMethodHandle** pEntityDefMethodHandle = m->Find(defMethodName);
	if (!pEntityDefMethodHandle)
		return NULL;

	return *pEntityDefMethodHandle;
}

Entity::Entity():
	id_(0),
	className_(TEXT("")),
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
