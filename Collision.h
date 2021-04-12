#pragma once
#include "singleton.h"
class Collision :public singleton<Collision>
{
public:
	Collision();
	~Collision();
	bool IsRayHitBound(Ray* ray, cBoundSphere* boundingbox, Transform* ts, Vec3* hitPos, Vec3* hitnormal);
	CDXUTTimer* timer;
	bool IsRayHitBound(Ray* ray, BoundingBox* boundingbox, Transform* ts, Vec3* hitPos, Vec3* hitnormal);
	void CreatePlane(LPD3DXPLANE pOutPlane, const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2);
	float PlaneDot(const LPD3DXPLANE pPlane, const D3DXVECTOR3* point);
	bool IntersectRayToPlane(D3DXVECTOR3* pOut, const LPRay pRay, const LPD3DXPLANE pPlane, bool bCheck2Side = false);
	bool IsOverlap(Transform* pTransA, Transform* pTransB);
	bool BoxColl(Transform* tsA, Transform* tsB);
};
#define COLL Collision::GetInstance()
