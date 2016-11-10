
#include "KBEnginePluginsPrivatePCH.h"
#include "ScriptModule.h"
#include "Method.h"
#include "Property.h"

ScriptModule::ScriptModule(const FString& moduleName):
	name(moduleName),
	usePropertyDescrAlias(false),
	useMethodDescrAlias(false),
	propertys(),
	idpropertys(),
	methods(),
	base_methods(),
	cell_methods(),
	idmethods(),
	idbase_methods(),
	idcell_methods()
{
	/*
	foreach(System.Reflection.Assembly ass in AppDomain.CurrentDomain.GetAssemblies())
	{
		script = ass.GetType("KBEngine." + modulename);
		if (script == null)
		{
			script = ass.GetType(modulename);
		}

		if (script != null)
			break;
	}

	if (script == null)
		Dbg.ERROR_MSG("can't load(KBEngine." + modulename + ")!");
	*/
}

ScriptModule::~ScriptModule()
{
}
