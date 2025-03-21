#include "CGameObjectManager.h"
#include <algorithm>

// Requires a CModelTypeManager to start (for loading the models)
CGameObjectManager::CGameObjectManager(IGameObjectBuilder* pGameObjectBuilder )
{
	this->m_pGameObjectBuilder = pGameObjectBuilder;
	return;
}

CGameObjectManager::~CGameObjectManager()
{
	// TODO: Get rid of all the objects

}

bool CGameObjectManager::AddGameObjectToWorld( 
	std::string type, 
	bool bTreatTypeAsMeshName, 
	unsigned int &objectID, std::string &error, 
	float scale /*=1.0f*/, bool bTreatScaleAsBoundingBoxSize /*=false*/ )
{
	// Use the game object builder to create the specific object
	CGameObject* pTempObject = 0;
	if ( ! this->m_pGameObjectBuilder->CreateGameObject( type, pTempObject, bTreatTypeAsMeshName, error, scale, bTreatScaleAsBoundingBoxSize ) )
	{
		// Can't create that type of object
		objectID = 0;
		return false;
	}

	// Tell the object about me (the mediator)
	IMediator* pTheMediator = this;
	pTempObject->SetMediator( pTheMediator );

	// Object created, so add it to the vector
	this->m_vec_pTheObjects.push_back( pTempObject );
	objectID = pTempObject->GetID();
	return true;
}

// Returns all the objects that we are to render
// Note that this returns a COPY of the internal vector (not a reference to it)
void CGameObjectManager::AppendListOfObjectsToRender( std::vector< CGameObject* > &vec_pGameObjects )
{
	// Don't clear the vector (it's append, not 'get')
	//std::copy( this->m_vec_pTheObjects.begin(), this->m_vec_pTheObjects.end(), vec_pGameObjects.begin() );
	for ( std::vector< CGameObject* >::iterator itpGO = this->m_vec_pTheObjects.begin();
		  itpGO != this->m_vec_pTheObjects.end(); itpGO++ )
	{
		CGameObject* pTempGameObject = (*itpGO);		// really for debugging so we can see it
		vec_pGameObjects.push_back( pTempGameObject );
	}

	return;
}

//CGameObject* findGameObjectByFriendlyName( std::string friendlyNameToFind )
//{
//	for ( std::vector< CGameObject* >::iterator itGO = ::g_vec_pTheObjects.begin();
//		  itGO != ::g_vec_pTheObjects.end(); itGO++ )
//	{
//		if ( (*itGO)->friendlyName == friendlyNameToFind )
//		{	// Found it
//			return (*itGO);
//		}
//	}
//	// Didn't find it
//	return 0;
//}

CGameObject* CGameObjectManager::FindGameObjectByFriendlyName( std::string friendlyNameToFind )
{
	for ( std::vector< CGameObject* >::iterator itGO = this->m_vec_pTheObjects.begin();
		  itGO != this->m_vec_pTheObjects.end(); itGO++ )
	{
		if ( (*itGO)->friendlyName == friendlyNameToFind )
		{	// Found it
			return (*itGO);
		}
	}
	// Didn't find it
	return 0;
}

// Original function I "stole" from
// (i.e. it works as a function, so copy and paste into the class)
//CGameObject* findGameObjectByID( unsigned int ID )
//{
//	for ( std::vector< CGameObject* >::iterator itGO = ::g_vec_pTheObjects.begin();
//		  itGO != ::g_vec_pTheObjects.end(); itGO++ )
//	{
//		if ( (*itGO)->GetID() == ID )
//		{	// Found it
//			return (*itGO);
//		}
//	}
//	// Didn't find it
//	return 0;
//}
CGameObject* CGameObjectManager::FindGameObjectByID( unsigned int IDToFind )
{
	for ( std::vector< CGameObject* >::iterator itGO = this->m_vec_pTheObjects.begin();
		  itGO != this->m_vec_pTheObjects.end(); itGO++ )
	{
		if ( (*itGO)->GetID() == IDToFind )
		{	// Found it
			return (*itGO);
		}
	}
	// Didn't find it
	return 0;
}


void CGameObjectManager::ShutDown(void)
{
	// Go through the objects and delete them
	for ( std::vector< CGameObject* >::iterator itChild = this->m_vec_pTheObjects.begin();
			itChild != this->m_vec_pTheObjects.end(); itChild++ )
	{
		// Pointer not zero (0)?
		CGameObject* pTempChildObject = (*itChild);
		if ( pTempChildObject != 0 )
		{
			// Recursively delete all children's children (and so on)
			pTempChildObject->DeleteChildren();
			// Now delete this child
			delete pTempChildObject;
		}
	}
	// Clear the vector, too
	this->m_vec_pTheObjects.clear();

	return;
}

