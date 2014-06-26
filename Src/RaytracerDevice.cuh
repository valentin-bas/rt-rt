#ifndef __RAYTRACERDEVICE_H__
#define __RAYTRACERDEVICE_H__

#define NSPHERES 4
#define RADIUS 200
#define FOCALDIST 1000

extern __device__ double focal_distance;
extern __device__ VEC_BASIS camera_frame;
extern __device__ VECTOR3D view_point, static_view_point;
extern __device__ VIEWPORT viewport;
extern __device__ SPHERE sphere[NSPHERES];
extern __device__ VECTOR3D light;

__device__ void compute_ray(RAY* ray, VECTOR3D* view_point, VIEWPORT* viewport, PIXEL* pixel, VEC_BASIS* camera_frame, double distance);
__device__ bool sphere_intersection (RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION* intersection);
__device__ void intersection_normal(SPHERE *sphere, SPHERE_INTERSECTION* intersection, RAY* ray);
__device__ void compute_shadow_ray(RAY* ray, SPHERE_INTERSECTION* intersection, VECTOR3D* light);
__device__ double shadowColor(double ka, double amb_intensity);
__device__ double blinnphongColor(SPHERE_INTERSECTION *intersection, VECTOR3D* light, VECTOR3D* viewpoint,
								  double kd, double ks, double ka, double p, double intensity, double amb_intensity);

#endif