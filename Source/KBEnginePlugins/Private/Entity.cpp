
#include "KBEnginePluginsPrivatePCH.h"
#include "Entity.h"

EntityFactory g_EntityFactory;
EntitySetMethodHandles g_EntitySetMethodHandles;

EntityCreator::EntityCreator(const FString& scriptName)
{
	g_EntityFactory.addEntityCreator(scriptName, this);
}

EntityCreator::~EntityCreator()
{
}

EntitySetMethodHandle::EntitySetMethodHandle(const FString& scriptName, const FString& setMethodName)
{
	g_EntitySetMethodHandles.add(scriptName, setMethodName, this);
}

EntitySetMethodHandle::~EntitySetMethodHandle()
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

EntitySetMethodHandle* EntitySetMethodHandles::add(const FString& scriptName, const FString& setMethodName, EntitySetMethodHandle* pEntitySetMethodHandle)
{
	if (!setMethodHandles.Contains(scriptName))
		setMethodHandles.Add(scriptName, TMap<FString, EntitySetMethodHandle*>());

	TMap<FString, EntitySetMethodHandle*>* m = setMethodHandles.Find(scriptName);

	if (m->Contains(setMethodName))
	{
		ERROR_MSG("%s::%s exist!", *scriptName, *setMethodName);
		return NULL;
	}

	DEBUG_MSG("%s::%s", *scriptName, *setMethodName);
	m->Add(setMethodName, pEntitySetMethodHandle);
	return pEntitySetMethodHandle;
}

EntitySetMethodHandle* EntitySetMethodHandles::find(const FString& scriptName, const FString& setMethodName)
{
	TMap<FString, EntitySetMethodHandle*>* m = g_EntitySetMethodHandles.setMethodHandles.Find(scriptName);
	if (!m)
		return NULL;

	EntitySetMethodHandle** pEntitySetMethodHandle = m->Find(setMethodName);
	if (!pEntitySetMethodHandle)
		return NULL;

	return *pEntitySetMethodHandle;
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
