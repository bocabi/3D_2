#include "DXUT.h"
#include "Collision.h"

Collision::Collision()
{
	timer = new CDXUTTimer;
	timer->Start();
}

Collision::~Collision()
{
	SAFE_DELETE(timer);
}

bool Collision::IsRayHitBound(Ray* ray, cBoundSphere* boundingbox, Transform* ts, Vec3* hitPos, Vec3* hitnormal)
{
	D3DXMATRIXA16 matWorld = ts->matW;
	Vec3 scalse = ts->Size;

	Vec3 center;
	float radius;
	Vec3 halfsize;

	D3DXVec3TransformCoord(&center, &boundingbox->localCenter, &matWorld);
	halfsize.x = boundingbox->halfSize.x * scalse.x;
	halfsize.y = boundingbox->halfSize.y * scalse.y;
	halfsize.z = boundingbox->halfSize.z * scalse.z;
	radius = D3DXVec3Length(&halfsize);
	Vec3 dirToCenter = center - ray->origin;
	float lengthsq = D3DXVec3LengthSq(&dirToCenter);
	float r2 = radius * radius;
	if (r2 > lengthsq)
	{
		return false;
	}
	float dot = D3DXVec3Dot(&dirToCenter, &ray->direction);
	if (dot <= 0.f)
	{
		return false;
	}

	float x2 = dot * dot;
	float d2 = lengthsq;
	float y2 = d2 - x2;
	if (y2 - r2)
	{
		return false;
	}
	if (hitPos != NULL)
	{
		d2 = r2;
		float x = sqrt(d2 - y2);
		*hitPos = ray->origin + (ray->direction * (dot - x));
		if (hitnormal)
		{
			*hitnormal = *hitnormal - center;
			D3DXVec3Normalize(hitnormal, hitnormal);
		}
	}
	return true;
}

bool Collision::IsRayHitBound(Ray* ray, BoundingBox* boundingbox, Transform* ts, Vec3* hitPos, Vec3* hitnormal)
{
	if (this->IsRayHitBound(ray, (cBoundSphere*)boundingbox, ts, NULL, NULL) == false)
	{
		return false;
	}
	D3DXMATRIXA16 matWorld = ts->GetMat();
	D3DXMATRIXA16 matInvMatrix;
	D3DXMatrixInverse(&matInvMatrix, NULL, &matWorld);
	Vec3 origin;
	D3DXVec3TransformCoord(&origin, &ray->origin, &matInvMatrix);
	Vec3 dir;
	D3DXVec3TransformNormal(&dir, &ray->direction, &matInvMatrix);

	Ray newRay;
	newRay.origin = origin;
	newRay.direction = dir;
	D3DXVECTOR3 Vertices[8];
	Vertices[0] = D3DXVECTOR3(boundingbox->LocalMinPos.x, boundingbox->LocalMinPos.y, boundingbox->LocalMinPos.z);
	Vertices[1] = D3DXVECTOR3(boundingbox->LocalMinPos.x, boundingbox->LocalMaxPos.y, boundingbox->LocalMinPos.z);
	Vertices[2] = D3DXVECTOR3(boundingbox->LocalMaxPos.x, boundingbox->LocalMaxPos.y, boundingbox->LocalMinPos.z);
	Vertices[3] = D3DXVECTOR3(boundingbox->LocalMaxPos.x, boundingbox->LocalMinPos.y, boundingbox->LocalMinPos.z);
	Vertices[4] = D3DXVECTOR3(boundingbox->LocalMinPos.x, boundingbox->LocalMinPos.y, boundingbox->LocalMaxPos.z);
	Vertices[5] = D3DXVECTOR3(boundingbox->LocalMinPos.x, boundingbox->LocalMaxPos.y, boundingbox->LocalMaxPos.z);
	Vertices[6] = D3DXVECTOR3(boundingbox->LocalMaxPos.x, boundingbox->LocalMaxPos.y, boundingbox->LocalMaxPos.z);
	Vertices[7] = D3DXVECTOR3(boundingbox->LocalMaxPos.x, boundingbox->LocalMinPos.y, boundingbox->LocalMaxPos.z);

	D3DXVECTOR3 hit;
	D3DXVECTOR3 min = boundingbox->LocalMinPos;
	D3DXVECTOR3 max = boundingbox->LocalMaxPos;
	D3DXPLANE planeBack;
	this->CreatePlane(&planeBack, Vertices + 0, Vertices + 1, Vertices + 2);
	if (this->IntersectRayToPlane(&hit, &newRay, &planeBack, false))
	{
		if (min.x <= hit.x && hit.x <= max.x &&
			min.y <= hit.y && hit.y <= max.y)
		{
			if (hitPos != NULL)
			{
				D3DXVec3TransformCoord(hitPos, &hit, &matWorld);
			}
			if (hitnormal != NULL)
			{
				//  *hitnormal = -ts->matW;
			}
		}
	}

	return false;
}

void Collision::CreatePlane(LPD3DXPLANE pOutPlane, const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2)
{
	D3DXVECTOR3 normal;
	D3DXVECTOR3 edge1 = *p1 - *p0;
	D3DXVECTOR3 edge2 = *p2 - *p0;
	D3DXVec3Cross(&normal, &edge1, &edge2);
	D3DXVec3Normalize(&normal, &normal);

	//평면의 노말 방향으로 원점까지의 최단 거리
	float dist = -D3DXVec3Dot(&normal, p0);

	//평면값 쓰자
	pOutPlane->a = normal.x;
	pOutPlane->b = normal.y;
	pOutPlane->c = normal.z;
	pOutPlane->d = dist;
}

float Collision::PlaneDot(const LPD3DXPLANE pPlane, const D3DXVECTOR3* point)
{
	D3DXVECTOR3 normal(pPlane->a, pPlane->b, pPlane->c);


	float distance = D3DXVec3Dot(&normal, point) + pPlane->d;


	return distance;
}

bool Collision::IntersectRayToPlane(D3DXVECTOR3* pOut, const LPRay pRay, const LPD3DXPLANE pPlane, bool bCheck2Side)
{
	D3DXVECTOR3 normal(pPlane->a, pPlane->b, pPlane->c);

	float dot2 = D3DXVec3Dot(&normal, &pRay->direction);//광선의 바향과 평면의 법선 방햐으이 각차의 cos값

	//그리드를 0,0,0 에서 보면 안 보이는 것과 같은 이치다.
	//반직선과 평면의 각도가 90 라는 얘기는 평행하다는 얘기.
   /* if (FLOATEQUAL(dot2, 0.f))
	{
		return false;
	}*/

	//반직선의 시작점에서 평면까지의 최단거리
	float dist = D3DXVec3Dot(&normal, &pRay->origin) + pPlane->d;

	//양면 체크를 안 한다면
	if (bCheck2Side == false)
	{
		//반직선의 시작 위치가 뒤에 있어도 실패
		if (dist < 0.f)
			return false;
	}

	//반직선방향으로 충돌지점까지의 거리
	float t = dist / -dot2;

	//레이 방향이 반대로 되어 있는 경우
	if (t < 0.f)
		return false;

	//충돌 위치
	*pOut = pRay->origin + (pRay->direction * t);

	return true;
}

bool Collision::IsOverlap(Transform* pTransA, Transform* pTransB)
{
	D3DXVECTOR3 centerA;
	float radiusA;
	D3DXVECTOR3 centerB;
	float radiusB;

	centerA = pTransA->Pos;
	centerB = pTransB->Pos;
	centerA.y = pTransA->Pos.y / 2;
	centerB.y = pTransB->Pos.y / 2;

	D3DXVECTOR3 dirTo = Vec3(centerB - centerA);
	float distPow2 = D3DXVec3LengthSq(&dirTo);
	cout << distPow2 << "DistPos\n";
	radiusA = pTransA->Radius / 2;
	radiusB = pTransB->Radius / 2;
	float sumRadiusPow2 = (radiusA)*pTransA->Size.x + (radiusB)*pTransB->Size.x;
	sumRadiusPow2 *= sumRadiusPow2;
	cout << sumRadiusPow2 << "sumRadius\n";

	if (distPow2 > sumRadiusPow2)
	{
		return false;
	}



	return true;
}

bool Collision::BoxColl(Transform* tsA, Transform* tsB)
{
	Vec3 centerA;
	Vec3 centerB;

	centerA = tsA->Pos;
	centerB = tsB->Pos ;
	centerA.y = tsA->Pos.y + (tsA->GetMesh->maxVec.y - tsA->GetMesh->minVec.y) * tsA->Size.y/2;
	centerB.y = tsB->Pos.y + (tsB->GetMesh->maxVec.y - tsB->GetMesh->minVec.y) * tsB->Size.y/2;
	RECT rt, rt1, rt2, rt3, rt4;
	if (tsA->timer->GetTime() <= 0.5)
	{
		rt1 = {
			LONG((centerA.x - ((tsA->GetMesh->maxVec.x - tsA->GetMesh->minVec.x) * tsA->Size.x)/2)),
			LONG((centerA.y + ((tsA->GetMesh->maxVec.y - tsA->GetMesh->minVec.y) * tsA->Size.y)/2 )) ,
			LONG((centerA.x + ((tsA->GetMesh->maxVec.x - tsA->GetMesh->minVec.x) * tsA->Size.x)/2)) ,
			LONG((centerA.y - ((tsA->GetMesh->maxVec.y - tsA->GetMesh->minVec.y) * tsA->Size.y)/2)) };
		rt2 = {
			LONG((centerB.x - ((tsB->GetMesh->maxVec.x - tsB->GetMesh->minVec.x) * tsB->Size.x)/2)) ,
			LONG((centerB.y + ((tsB->GetMesh->maxVec.y - tsB->GetMesh->minVec.y) * tsB->Size.y)/2 )),
			LONG((centerB.x + ((tsB->GetMesh->maxVec.x - tsB->GetMesh->minVec.x) * tsB->Size.x)/2)) ,
			LONG((centerB.y - ((tsB->GetMesh->maxVec.y - tsB->GetMesh->minVec.y) * tsB->Size.y)/2)) ,

		};
		rt3 =
		{
			LONG((centerA.z - ((tsA->GetMesh->maxVec.z - tsA->GetMesh->minVec.z) * tsA->Size.z)/2)),
			LONG((centerA.y + ((tsA->GetMesh->maxVec.y - tsA->GetMesh->minVec.y) * tsA->Size.y)/2 )) ,
			LONG((centerA.z + ((tsA->GetMesh->maxVec.z - tsA->GetMesh->minVec.z) * tsA->Size.z) /2)),
			LONG((centerA.y - ((tsA->GetMesh->maxVec.y - tsA->GetMesh->minVec.y) * tsA->Size.y) / 2))
		};
		rt4 =
		{
			LONG((centerB.z - ((tsB->GetMesh->maxVec.z - tsB->GetMesh->minVec.z) * tsB->Size.z)/2 )),
			LONG((centerB.y + ((tsB->GetMesh->maxVec.y - tsB->GetMesh->minVec.y) * tsB->Size.y) / 2)) ,
			LONG((centerB.z + ((tsB->GetMesh->maxVec.z - tsB->GetMesh->minVec.z) * tsB->Size.z)/2)) ,
			LONG((centerB.y - ((tsB->GetMesh->maxVec.y - tsB->GetMesh->minVec.y) * tsB->Size.y) / 2))
		};
		tsA->timer->Reset();

	}


	
	if (rt1.bottom<=rt2.top&rt1.left<=rt2.right&&rt1.right >= rt2.left&&rt2.bottom <= rt1.top)
		{
			if (rt3.left <= rt4.right&& rt3.right >= rt4.left)
			{
			return true;

			}
		}
		

	if (tsA->timer->GetTime() >= 0.5)
	{
		tsA->timer->Reset();

	}
	return false;
}
