#include "CNameValuePair.h"

void CNameValuePair::Reset(void)
{
	this->fvec4Value.x = this->fvec4Value.y = this->fvec4Value.z = this->fvec4Value.w = 0.0f;
	this->sValue = "";
	this->iValue = 0;
	return;
}

CNameValuePair::CNameValuePair()
{
	this->Reset();
	return;
}

CNameValuePair::CNameValuePair( const std::string &name )
{
	this->Reset();
	this->name = name;
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, fvec4 fvec4Value )
{
	this->Reset();
	this->name = name;
	this->fvec4Value = fvec4Value;
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, float fValue )
{
	this->Reset();
	this->name = name;
	this->fvec4Value.x = fValue;
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, int iValue )
{
	this->Reset();
	this->name = name;
	this->iValue = iValue;
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, std::string sValue )
{
	this->Reset();
	this->name = name;
	this->sValue = sValue;
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair childNVP3 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair &childNVP3, const CNameValuePair &childNVP4 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	this->vecChildNVPairs.push_back( childNVP4 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	this->vecChildNVPairs.push_back( childNVP4 );
	this->vecChildNVPairs.push_back( childNVP5 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
				const CNameValuePair &childNVP6 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	this->vecChildNVPairs.push_back( childNVP4 );
	this->vecChildNVPairs.push_back( childNVP5 );
	this->vecChildNVPairs.push_back( childNVP6 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
				const CNameValuePair &childNVP6, const CNameValuePair &childNVP7 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	this->vecChildNVPairs.push_back( childNVP4 );
	this->vecChildNVPairs.push_back( childNVP5 );
	this->vecChildNVPairs.push_back( childNVP6 );
	this->vecChildNVPairs.push_back( childNVP7 );
	return;
}

CNameValuePair::CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		        const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
				const CNameValuePair &childNVP6, const CNameValuePair &childNVP7, const CNameValuePair &childNVP8 )
{
	this->Reset();
	this->vecChildNVPairs.push_back( childNVP0 );
	this->vecChildNVPairs.push_back( childNVP1 );
	this->vecChildNVPairs.push_back( childNVP2 );
	this->vecChildNVPairs.push_back( childNVP3 );
	this->vecChildNVPairs.push_back( childNVP4 );
	this->vecChildNVPairs.push_back( childNVP5 );
	this->vecChildNVPairs.push_back( childNVP6 );
	this->vecChildNVPairs.push_back( childNVP8 );
	return;
}

void CNameValuePair::AddChild( const CNameValuePair &childNVP )
{
	this->vecChildNVPairs.push_back( childNVP );
	return;
}

bool CNameValuePair::bHadChildren(void)
{
	return ( ! this->vecChildNVPairs.empty() );
}


bool CNameValuePair::ScanChildrenForName( std::string nameToFind, CNameValuePair &childNVP, bool bScanRecursively /*= false*/ )
{
	for ( std::vector<CNameValuePair>::iterator itChildNVPair = this->vecChildNVPairs.begin();
		  itChildNVPair != this->vecChildNVPairs.end(); itChildNVPair++ )
	{
		if ( itChildNVPair->name == nameToFind )
		{
			childNVP = (*itChildNVPair);
			return true;
		}
		// Scan children's children?
		if ( bScanRecursively )
		{
			if ( itChildNVPair->ScanChildrenForName( nameToFind, childNVP, bScanRecursively ) )
			{
				return true;
			}
		}// if ( bScanRecursively )
	}// for ( std::vector<CNameValuePair>::iterator itChildNVPair 

	// Sorry it didn't work out...
	return false;
}
