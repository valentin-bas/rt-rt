#ifndef __RAYTRACERTYPES_H__
#define __RAYTRACERTYPES_H__

#include "Math.h"

#define CRED 0
#define CGREEN 1
#define CBLUE 2

/* --------------- VECTORS -------------------- */

struct VECTOR3D{
	double x;
	double y;
	double z;
} ;


/* ----------------- VIEWPORT ----------------- */
struct VIEWPORT {
	int xvmin;
	int yvmin;
	int xvmax;
	int yvmax;
};


/* ------------------- PIXEL ------------------ */
struct PIXEL{
	int i;
	int j;
};

/* ---------------- SPHERE -------------------- */

struct SPHERE_INTERSECTION {
	double	lambda_in;
	double	lambda_out;
	VECTOR3D	normal;
	VECTOR3D point;
	bool	valid;
} ;

struct SPHERE {
	VECTOR3D center;
	double radius;
	double kd_rgb[3];
	double ks_rgb[3];
	double ka_rgb[3];
	double kr_rgb[3];
	double refraction_index;
	double shininess;
	bool mirror;
};


/* ------------------- RAY --------------------- */
struct RAY {
	VECTOR3D origin;
	VECTOR3D direction;
};


/* --------------- VECTOR BASIS ---------------- */
struct VEC_BASIS {
	VECTOR3D u;
	VECTOR3D v;
	VECTOR3D n;
};

union Color
{
	float c;
	uchar4 components;
};

__device__ void vec_sub (VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3);
__device__ void vec_add (VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3);
__device__ void vec_scale (double scale, VECTOR3D *v1, VECTOR3D *v2);
__device__ double dotproduct (VECTOR3D *v1, VECTOR3D *v2);
__device__ VECTOR3D crossProduct(VECTOR3D *v1, VECTOR3D *v2);
__device__ void normalize_vector (VECTOR3D *v);
__device__ void set_rgb_array(double* rgb_array, double cred, double cgreen, double cblue);

#endif