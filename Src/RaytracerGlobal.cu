#include "RaytracerTypes.cuh"
#include "RaytracerDevice.cuh"

__global__ void init_kernel(int width, int height)
{
	viewport.xvmin = -width / 2;
	viewport.yvmin = -height / 2;
	viewport.xvmax = width / 2;
	viewport.yvmax = height / 2;
	camera_frame.u.x = 1.0;
	camera_frame.u.y = 0.0;
	camera_frame.u.z = 0.0;
	camera_frame.v.x = 0.0;
	camera_frame.v.y = 1.0;
	camera_frame.v.z = 0.0;
	camera_frame.n.x = 0.0;
	camera_frame.n.y = 0.0;
	camera_frame.n.z = 1.0;
	view_point.x = (viewport.xvmax - viewport.xvmin) / 2.0 ;
	view_point.y = (viewport.yvmax - viewport.yvmin) / 2.0 ;
	view_point.z = 0.0;
	static_view_point=view_point;
	focal_distance = FOCALDIST;
	//SCENE
	light.x = view_point.x - 1300;
	light.y = view_point.y + 1300;
	light.z = view_point.z - 300;
	sphere[0].radius = RADIUS/1.5;
	sphere[0].center.x  = view_point.x - (RADIUS+30);
	sphere[0].center.y  = view_point.y ;
	sphere[0].center.z  = view_point.z - focal_distance - (2*RADIUS+20);
	set_rgb_array(sphere[0].kd_rgb, 0.0, 0.0, 0.8);
	set_rgb_array(sphere[0].ks_rgb, 1.0, 1.0, 1.0);
	set_rgb_array(sphere[0].ka_rgb, 0.0, 0.0, 0.2);
	set_rgb_array(sphere[0].kr_rgb, 0.0, 0.0, 0.0);
	sphere[0].shininess = 100.0;
	sphere[0].refraction_index=1.52;
	sphere[0].mirror = false;
	sphere[1].radius = RADIUS/1.2;
	sphere[1].center.x  = view_point.x + 0;
	sphere[1].center.y  = view_point.y + 50;
	sphere[1].center.z  = view_point.z - focal_distance - (3*RADIUS+20);
	set_rgb_array(sphere[1].kd_rgb, 0.0, 0.8, 0.0);
	set_rgb_array(sphere[1].ks_rgb, 0.5, 0.5, 0.5);
	set_rgb_array(sphere[1].ka_rgb, 0.0, 0.2, 0.0);
	set_rgb_array(sphere[1].kr_rgb, 0.5, 0.5, 0.5);
	sphere[1].shininess = 10.0;
	sphere[1].refraction_index=1.52;
	sphere[1].mirror = false;
	sphere[2].radius = RADIUS;
	sphere[2].center.x  = view_point.x + (2*RADIUS+30);
	sphere[2].center.y  = view_point.y + 100;
	sphere[2].center.z  = view_point.z - focal_distance - (4*RADIUS+20);
	set_rgb_array(sphere[2].kd_rgb, 0.8, 0.0, 0.0);
	set_rgb_array(sphere[2].ks_rgb, 0.7, 0.7, 0.7);
	set_rgb_array(sphere[2].ka_rgb, 0.2, 0.0, 0.0);
	set_rgb_array(sphere[2].kr_rgb, 0.3, 0.3, 0.3);
	sphere[2].shininess = 100.0;
	sphere[2].refraction_index=1.52;
	sphere[2].mirror = false;
	sphere[3].radius = 100*RADIUS;
	sphere[3].center.x  = view_point.x ;
	sphere[3].center.y  = view_point.y - 100*RADIUS-130;
	sphere[3].center.z  = view_point.z - focal_distance - (4*RADIUS+20);
	set_rgb_array(sphere[3].kd_rgb, 0.2, 0.2, 0.2);
	set_rgb_array(sphere[3].ks_rgb, 0.8, 0.8, 0.5);
	set_rgb_array(sphere[3].ka_rgb, 0.0, 0.0, 0.0);
	set_rgb_array(sphere[3].kr_rgb, 0.2, 0.2, 0.5);
	sphere[3].shininess = 100.0;
	sphere[3].refraction_index=1.52;
	sphere[3].mirror = true;
};

__global__ void raytracer_kernel(float3* pos, unsigned int width, unsigned int height)
{
	unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int j = blockIdx.y * blockDim.y + threadIdx.y;

	if (i>= width || j>= height)
		return;

	RAY ray, shadow_ray;
	PIXEL pixel;
	int hitIdx = -1;
	double current_lambda = 0x7fefffffffffffff;
	SPHERE_INTERSECTION intersection, current_intersection;

	pixel.i = i;
	pixel.j = j;
	compute_ray(&ray, &view_point, &viewport, &pixel, &camera_frame, focal_distance);
	for (int k=0; k < NSPHERES; k++)
	{
		if (sphere_intersection(&ray, &sphere[k], &intersection))
		{
			intersection_normal(&sphere[k], &intersection, &ray);
			if (intersection.lambda_in < current_lambda)
			{
				current_lambda=intersection.lambda_in;
				hitIdx=k;
				current_intersection=intersection;
			}
		}
	}

	SPHERE_INTERSECTION shadow_ray_intersection;
	double theta;
	double red, green, blue;
	bool shadow = false;
	Color color;

	if (hitIdx > -1)
	{
		compute_shadow_ray(&shadow_ray, &current_intersection , &light);
		theta = dotproduct(&(shadow_ray.direction), &(current_intersection.normal));
		for (int l=0; l < NSPHERES; l++)
		{
			if (l != hitIdx)
			{
				if (sphere_intersection(&shadow_ray, &sphere[l], &shadow_ray_intersection) && (theta > 0.0))
					shadow=true;
			}
		}
		red=green=blue=0;
		if (shadow)
		{
			red += shadowColor(sphere[hitIdx].ka_rgb[CRED], 1.0);
			green += shadowColor(sphere[hitIdx].ka_rgb[CGREEN], 1.0);
			blue += shadowColor(sphere[hitIdx].ka_rgb[CBLUE], 1.0);
		}
		else
		{
			SPHERE* s = &sphere[hitIdx];
			red += blinnphongColor(&current_intersection, &light, &view_point,
								   s->kd_rgb[CRED], s->ks_rgb[CRED], s->ka_rgb[CRED],
								   s->shininess, 1.0, 1.0);
			green += blinnphongColor(&current_intersection, &light, &view_point,
								   s->kd_rgb[CGREEN], s->ks_rgb[CGREEN], s->ka_rgb[CGREEN],
								   s->shininess, 1.0, 1.0);
			blue += blinnphongColor(&current_intersection, &light, &view_point,
								   s->kd_rgb[CBLUE], s->ks_rgb[CBLUE], s->ka_rgb[CBLUE],
								   s->shininess, 1.0, 1.0);
		}
		if (red>1.0)
			red=1.0;
		if (green>1.0)
			green=1.0;
		if (blue>1.0)
			blue=1.0;
		//double* colorTmp = sphere[intersection_object].kd_rgb;
		//color.components = make_uchar4(colorTmp[0] * 255, colorTmp[1] * 255, colorTmp[2] * 255, 1);
		color.components = make_uchar4(red * 255, green * 255, blue * 255, 1);
	}
	else
		color.components = make_uchar4(0, 0, 0, 1);
	pos[j * width + i] = make_float3(i, j, color.c);
}

__device__ float timer=0.0f;

__global__ void animate_kernel()
{
	sphere[0].center.y=view_point.y+sinf(timer)*100;
	sphere[1].center.y=view_point.y+50+sinf(2*timer)*100;
	sphere[2].center.y=view_point.y+100+sinf(1.5*timer)*100;
	timer+=0.02f;
}