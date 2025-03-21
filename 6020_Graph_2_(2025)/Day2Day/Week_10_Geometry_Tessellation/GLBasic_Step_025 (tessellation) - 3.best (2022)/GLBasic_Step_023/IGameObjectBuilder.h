#ifndef _IGameObjectBuilder_HG_
#define _IGameObjectBuilder_HG_

// This is the interface to the IObjectBuilder class, which 
//	is reponsible for "building" various types of objects, 
//	based on existing types of "game objects"

// The idea is that you add the specific methods for certain objects
//	into the CObjectBuilder object, but not here.

#include <string>
#include "CGameObject.h"


class IGameObjectBuilder
{
public:
	virtual ~IGameObjectBuilder() {};

	// bTreatTypeAsMeshName == true, then the "type" is simply the mesh name
	// Scale of 1.0 means "don't scale mesh" if bTreatScaleAsBoundingBoxSize is false
	virtual bool CreateGameObject( std::string type, 
	                               CGameObject* &pCreatedObject, 
								   bool bTreatTypeAsMeshName,
								   std::string &error, 
								   float scale = 1.0f, 
								   bool bTreatScaleAsBoundingBoxSize = false ) = 0;

};

#endif 
