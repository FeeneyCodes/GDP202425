#ifndef _CNameValuePair_HG_
#define _CNameValuePair_HG_

#include <string>
#include <vector>



class CNameValuePair
{
public:
	typedef struct fvec4
	{
		fvec4() : x(0.0f), y(0.0f), z(0.0), w(1.0f) {};
		float x, y, z, w;
	} fvec4;	
	CNameValuePair();
	CNameValuePair( const std::string &name );
	CNameValuePair( const std::string &name, fvec4 fVec4Value );
	CNameValuePair( const std::string &name, float fValue );
	CNameValuePair( const std::string &name, int iValue );
	CNameValuePair( const std::string &name, std::string sValue );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair childNVP3 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair &childNVP3, const CNameValuePair &childNVP4 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
					const CNameValuePair &childNVP6 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
					const CNameValuePair &childNVP6, const CNameValuePair &childNVP7 );
	CNameValuePair( const std::string &name, const CNameValuePair &childNVP0, const CNameValuePair &childNVP1, const CNameValuePair &childNVP2, 
		            const CNameValuePair &childNVP3, const CNameValuePair &childNVP4, const CNameValuePair &childNVP5, 
					const CNameValuePair &childNVP6, const CNameValuePair &childNVP7, const CNameValuePair &childNVP8 );

	void AddChild( const CNameValuePair &childNVP );
	bool bHadChildren(void);
	std::string name;
	// ** The values **
	fvec4 fvec4Value;		// Can also be used for one float
	int iValue;
	std::string sValue;
	// ****************
	void Reset(void);
	std::vector<CNameValuePair> vecChildNVPairs;
	// Helper function to scan through the children, looking for certain commands
	// Will only scan one level deep unless you tell it to (but is that a Good Idea?)
	// Will return after finding the first one. If you want to "beef this up", you could 
	//	emulate the STL find() and find_next() type methods which can take a starting iterator, which you can 
	//  pass the iterator in as a starting point
	bool ScanChildrenForName( std::string nameToFind, CNameValuePair &childNVP, bool bScanRecursively = false );
};




#endif 











//typedef struct fvec4
//{
//	fvec4() : x(0.0f), y(0.0f), z(0.0), w(1.0f) {};
//	float x, y, z, w;
//} fvec4;
//
//union TheDataTypes
//{
//	// VS work-around from: http://stackoverflow.com/questions/21968635/invalid-union-member
//	struct {
//		fvec4 fVec4;
//	};
//	float fValue;
//	bool bValue;
//	int iValue;
//	unsigned int uiValue;
//};
//
//class CNameValuePair
//{
//public:
//	enum enumTypeInUse
//	{
//		IS_A_STRING,
//		IS_A_VEC4,
//		IS_A_FLOAT,
//		IS_AN_INT,
//		IS_AN_UINT,
//		UNKNOWN_OR_NOT_SET
//	};