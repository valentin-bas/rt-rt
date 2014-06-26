#include "RaytracerTypes.cuh"

__device__ void vec_sub (VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3) {

	v1->x = v2->x - v3->x;
	v1->y = v2->y - v3->y;
	v1->z = v2->z - v3->z;
}

__device__ void vec_add (VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3) {
	
	v1->x = v2->x + v3->x;
	v1->y = v2->y + v3->y;
	v1->z = v2->z + v3->z;
}

__device__ void vec_scale (double scale, VECTOR3D *v1, VECTOR3D *v2) {
	
	v1->x = scale * v2->x;
	v1->y = scale * v2->y;
	v1->z = scale * v2->z;
}

__device__ double dotproduct (VECTOR3D *v1, VECTOR3D *v2) {
	
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

__device__ VECTOR3D crossProduct(VECTOR3D *v1, VECTOR3D *v2) {
	VECTOR3D temp;
	temp.x =   ( (v1->y * v2->z) - (v1->z * v2->y) );
	temp.y = - ( (v1->x * v2->z) - (v1->z * v2->x) );
	temp.z =   ( (v1->x * v2->y) - (v1->y * v2->x) );
	return temp;
}


__device__ void normalize_vector (VECTOR3D *v) {
	
	double magnitude;
	
	// 1. calculate the magnitude (lerngth):
	magnitude = sqrt( dotproduct(v, v) );
	
	// 2. normalize the vector:
	v->x = v->x / magnitude;
	v->y = v->y / magnitude;
	v->z = v->z / magnitude;
}

__device__ void set_rgb_array(double* rgb_array, double cred, double cgreen, double cblue)
{
	rgb_array[CRED] = cred;
	rgb_array[CGREEN] = cgreen;
	rgb_array[CBLUE] = cblue;
}