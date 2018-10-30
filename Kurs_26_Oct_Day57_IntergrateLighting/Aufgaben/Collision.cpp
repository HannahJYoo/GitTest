#include "stdafx.h"
#include "Collision.h"

bool Collision::Intersect_AABB(D3DXVECTOR3 * A, D3DXMATRIX & ATransform, D3DXVECTOR3 * B, D3DXMATRIX & BTransform)
{
	D3DXVECTOR3 Amin = D3DXVECTOR3(INFINITY, INFINITY, INFINITY);
	D3DXVECTOR3 Amax = D3DXVECTOR3(-INFINITY, -INFINITY, -INFINITY);
	D3DXVECTOR3 Bmin = Amin;
	D3DXVECTOR3 Bmax = Amax;

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&A[i], &A[i], &ATransform);
		D3DXVec3TransformCoord(&B[i], &B[i], &BTransform);

		if (A[i].x < Amin.x)
			Amin.x = A[i].x;
		if (A[i].y < Amin.y)
			Amin.y = A[i].y;
		if (A[i].z < Amin.z)
			Amin.z = A[i].z;

		if (A[i].x > Amax.x)
			Amax.x = A[i].x;
		if (A[i].y > Amax.y)
			Amax.y = A[i].y;
		if (A[i].z > Amax.z)
			Amax.z = A[i].z;

		if (B[i].x < Bmin.x)
			Bmin.x = B[i].x;
		if (B[i].y < Bmin.y)
			Bmin.y = B[i].y;
		if (B[i].z < Bmin.z)
			Bmin.z = B[i].z;

		if (B[i].x > Bmax.x)
			Bmax.x = B[i].x;
		if (B[i].y > Bmax.y)
			Bmax.y = B[i].y;
		if (B[i].z > Bmax.z)
			Bmax.z = B[i].z;
	}

	if (Amax.x < Bmin.x || Amin.x > Bmax.x) return false;
	if (Amax.y < Bmin.y || Amin.y > Bmax.y) return false;
	if (Amax.z < Bmin.z || Amin.z > Bmax.z) return false;

	return true;
}
