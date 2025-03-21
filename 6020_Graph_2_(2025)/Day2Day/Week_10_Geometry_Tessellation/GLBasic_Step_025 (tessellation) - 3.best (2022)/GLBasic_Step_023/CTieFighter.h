#ifndef _CTieFighter_HG_
#define _

class CTieFighter : public CGameObject
{
public:
	// One method to rule them all!!!
	virtual void ReceiveMessage( CNameValuePair NVPair );
	

	// TieFighter had:
	void FlyAway();
};


class CBunny : public CGameObject
{
public:
	// One method to rule them all!!!
	virtual void ReceiveMessage( CNameValuePair NVPair );

	// Bunny had:
	void HotAway();
};