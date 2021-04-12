#include "DXUT.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::GetWorldBox(const Transform& cTrans, D3DXVECTOR3* outBoxPos)
{
	D3DXVECTOR3 Vertices[8];
	Vertices[0] = D3DXVECTOR3(this->LocalMinPos.x, this->LocalMinPos.y, this->LocalMinPos.z);
	Vertices[1] = D3DXVECTOR3(this->LocalMinPos.x, this->LocalMaxPos.y, this->LocalMinPos.z);
	Vertices[2] = D3DXVECTOR3(this->LocalMaxPos.x, this->LocalMaxPos.y, this->LocalMinPos.z);
	Vertices[3] = D3DXVECTOR3(this->LocalMaxPos.x, this->LocalMinPos.y, this->LocalMinPos.z);
	Vertices[4] = D3DXVECTOR3(this->LocalMinPos.x, this->LocalMinPos.y, this->LocalMaxPos.z);
	Vertices[5] = D3DXVECTOR3(this->LocalMinPos.x, this->LocalMaxPos.y, this->LocalMaxPos.z);
	Vertices[6] = D3DXVECTOR3(this->LocalMaxPos.x, this->LocalMaxPos.y, this->LocalMaxPos.z);
	Vertices[7] = D3DXVECTOR3(this->LocalMaxPos.x, this->LocalMinPos.y, this->LocalMaxPos.z);

	D3DXMATRIXA16 matFinal = cTrans.matW;
	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(outBoxPos + i, Vertices + i, &matFinal);
	}
}

void BoundingBox::GetWorldAABBMinMax(const Transform& cTrans, D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	D3DXVECTOR3 worldPos[8];
	GetWorldBox(cTrans, worldPos);

	//얻은 8개의 최대 최소를 구하자
	*min = worldPos[0];
	*max = worldPos[0];

	for (int i = 1; i < 8; i++) {

		if (min->x > worldPos[i].x) {
			min->x = worldPos[i].x;
		}
		else if (max->x < worldPos[i].x) {
			max->x = worldPos[i].x;
		}

		if (min->y > worldPos[i].y) {
			min->y = worldPos[i].y;
		}
		else if (max->y < worldPos[i].y) {
			max->y = worldPos[i].y;
		}

		if (min->z > worldPos[i].z) {
			min->z = worldPos[i].z;
		}
		else if (max->z < worldPos[i].z) {
			max->z = worldPos[i].z;
		}
	}
}

void BoundingBox::RenderGizmo(const Transform& ts)
{
	Vec3 worldPos[8];
	GetWorldBox(ts, worldPos);
	GIZMO_MGR->Line(worldPos[0], worldPos[1], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[1], worldPos[2], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[2], worldPos[3], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[3], worldPos[0], 0xff00ff00);

	GIZMO_MGR->Line(worldPos[4], worldPos[5], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[5], worldPos[6], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[6], worldPos[7], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[7], worldPos[4], 0xff00ff00);

	GIZMO_MGR->Line(worldPos[0], worldPos[4], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[1], worldPos[5], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[2], worldPos[6], 0xff00ff00);
	GIZMO_MGR->Line(worldPos[3], worldPos[7], 0xff00ff00);
	Vec3 min;
	Vec3 max;
	min = worldPos[0];
	max = worldPos[0];
	for (int i = 1; i < 8; i++)
	{
		if (min.x > worldPos[i].x) {
			min.x = worldPos[i].x;
		}
		else if (max.x < worldPos[i].x) {
			max.x = worldPos[i].x;
		}

		if (min.y > worldPos[i].y) {
			min.y = worldPos[i].y;
		}
		else if (max.y < worldPos[i].y) {
			max.y = worldPos[i].y;
		}

		if (min.z > worldPos[i].z) {
			min.z = worldPos[i].z;
		}
		else if (max.z < worldPos[i].z) {
			max.z = worldPos[i].z;
		}
	}
	GIZMO_MGR->AABBBox(min, max, 0xff008800);
}

cBoundSphere::cBoundSphere()
{
}

cBoundSphere::~cBoundSphere()
{
}

void cBoundSphere::GetWorldCenterRadius(const Transform& cTrans, D3DXVECTOR3* center, float* radius)
{
}

void cBoundSphere::RenderGizmo(const Transform& trans)
{
}
