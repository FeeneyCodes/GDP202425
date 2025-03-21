#ifndef _CGameObjectManager_HG_
#define _CGameObjectManager_HG_

// This class is responsible for creating the various "game objects"
//	that exist in the "world" (or scene). 
// It also deals with intercommunication as a "mediator" 
// 
// Note that it's NOT responsible for:
// * loading the object mesh from files
// * loading the meshes into the buffers on the GPU
// * assembling objects
// * physics simualtion, etc.

#include "CGameObject.h"
#include "IGameObjectBuilder.h"

// Make this thing a mediator, too
#include "IMediator.h"

class CGameObjectManager : public IMediator
{
public:

	// From the IMediator interface
	// (The game objects use this to "call back" to the mediator
	virtual void SendMessageToMediator( CNameValuePair theMessage );

	//void SetModelTypeManager( CModelTypeManager* pModelTypeManager );
	//void SetGameObjectBuilder( IGameObjectBuilder* pGameObjectBuilder );
	//bool bIsItReadyToGo(void);

	// Requires a CModelTypeManager to start (for loading the models)
	CGameObjectManager(IGameObjectBuilder* pGameObjectBuilder );
	~CGameObjectManager();

	CGameObject* FindGameObjectByFriendlyName( std::string friendlyNameToFind );
	CGameObject* FindGameObjectByID( unsigned int IDToFind );

	bool AddGameObjectToWorld( std::string type, bool bTreatTypeAsMeshName, unsigned int &objectID, 
		                       std::string &error, float scale = 1.0f, bool bTreatScaleAsBoundingBoxSize = false );

	// Returns all the objects that we are to render
	// Note that this returns a COPY of the internal vector (not a reference to it)
	void AppendListOfObjectsToRender( std::vector< CGameObject* > &vec_pGameObjects );

	void ShutDown(void);

private:
	CGameObjectManager() {};	// Needs a CModelTypeManager so can't call default constructor

	IGameObjectBuilder* m_pGameObjectBuilder;		// For creating models
	std::vector< CGameObject* > m_vec_pTheObjects;
};

#endif
