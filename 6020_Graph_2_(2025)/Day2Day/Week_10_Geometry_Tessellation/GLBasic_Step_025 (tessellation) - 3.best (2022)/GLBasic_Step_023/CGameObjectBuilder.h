#ifndef _CGameObjectBuilder_HG_
#define _CGameObjectBuilder_HG_

// This class is reponsible for "building" various types of objects, 
//	based on existing types of "game objects"
//

#include "IGameObjectBuilder.h"
#include "CModelTypeManager.h"

class CGameObjectBuilder : public IGameObjectBuilder
{
public:
	CGameObjectBuilder(	CModelTypeManager* pModelTypeManager );
	// Sort of like an "abstract factory"

	// bTreatTypeAsMeshName == true, then the "type" is simply the mesh name
	virtual bool CreateGameObject( std::string type, 
	                               CGameObject* &pCreatedObject, 
								   bool bTreatTypeAsMeshName,
								   std::string &error, 
								   float scale /*= 1.0f*/, 
								   bool bTreatScaleAsBoundingBoxSize /*= false*/ );



private:
	CGameObjectBuilder() {};	// Can't call constructor so that we ensure there is a pointer to the ModelTypeManager (which is needed)

	bool m_CreateBasicObjectFromMesh( std::string meshName, CGameObject* &pCreatedObject, float scale, bool bTreatScaleAsBoundingBoxSize, std::string &error );
	
	// These are specific, more complex models.
	bool m_CreateBasicBunny( CGameObject* &pCreatedObject, std::string &error );
	bool m_CreateBunnyWithTieFighter( CGameObject* &pCreatedObject, std::string &error );
	bool m_CreateTieFighter( CGameObject* &pCreatedObject, std::string &error );
	//
	void CreateSwamOfCylons( CGameObject* &pCreatedObject );
	//void CreateSkateboardingBunny( CGameObject* &blah );

	bool m_CreateALight( CGameObject* &pCreatedObject, unsigned int LightID, std::string &error );

	CModelTypeManager* m_pModelTypeManager;

};

#endif
