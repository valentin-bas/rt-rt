#include "RaytracerTypes.cuh"
#include "RaytracerDevice.cuh"

__device__ double focal_distance;
__device__ VEC_BASIS camera_frame;
__device__ VECTOR3D view_point, static_view_point;
__device__ VIEWPORT viewport;
__device__ SPHERE sphere[NSPHERES];
__device__ VECTOR3D light;

__device__ void compute_ray(RAY* ray, VECTOR3D* view_point, VIEWPORT* viewport, PIXEL* pixel, VEC_BASIS* camera_frame, double distance)
{
	float u, v;
	VECTOR3D v1, v2, v3, v4, dir;
	
	
	// 1. calculate u and v coordinates of the pixels on the image plane:
	u = (double)(viewport->xvmin) + (double)(pixel->i) + 0.5 ;  
	v = (double)(viewport->yvmin) + (double)(pixel->j) + 0.5 ;  
	
	// 2. calculate ray direction
	vec_scale(-distance, &v1, &camera_frame->n);
	vec_scale(u, &v2, &camera_frame->u);
	vec_scale(v, &v3, &camera_frame->v);
	
	ray->origin.x = view_point->x;  
	ray->origin.y = view_point->y;
	ray->origin.z = view_point->z;
	
	vec_add(&v4, &v1, &v2);
	vec_add(&dir, &v4, &v3);
	normalize_vector(&dir);
	
	ray->direction.x = dir.x;
	ray->direction.y = dir.y;
	ray->direction.z = dir.z;
}

__device__ bool sphere_intersection (RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION* intersection)
{
	double discriminant;
	double A, B, C;
	double lambda1, lambda2;
	VECTOR3D temp;
	
	A = dotproduct(&ray->direction, &ray->direction);
	vec_sub(&temp, &ray->origin, &sphere->center);
	B = 2 * dotproduct(&temp, &ray->direction);
	vec_sub(&temp, &ray->origin, &sphere->center);
	C = dotproduct(&temp, &temp) - (sphere->radius * sphere->radius);
	discriminant = B*B - 4*A*C;
	if (discriminant >= 0)
	{
		lambda1 = (-B + sqrt(discriminant)) / (2*A);
		lambda2 = (-B - sqrt(discriminant)) / (2*A);
		// is the object visible from the eye (lambda1,2>0)
		if (lambda1>=0 && lambda2>=0)
		{
			if (lambda1 == lambda2)
				intersection->lambda_in = intersection->lambda_out = lambda1;
			else if (lambda1 < lambda2)
			{
				intersection->lambda_in  = lambda1;
				intersection->lambda_out = lambda2;
			}
			else
			{
				intersection->lambda_in  = lambda2;
				intersection->lambda_out = lambda1;
			}
			intersection->valid = true;
			return true;
		}
		else
		{
			intersection->valid = false;
			return false;
		}
	}
	else
	{
		intersection->valid = false;
		return false;
	}
}

__device__ void intersection_normal(SPHERE *sphere, SPHERE_INTERSECTION* intersection, RAY* ray)
{
	double lambda, scale;
	VECTOR3D v1, v2, point, normal;
	
	lambda = intersection->lambda_in;
	vec_scale(lambda, &v1, &ray->direction);
	vec_add(&point, &v1, &ray->origin);
	intersection->point.x = point.x;
	intersection->point.y = point.y;
	intersection->point.z = point.z;
	vec_sub(&v2, &point, &sphere->center);
	scale = 1.0 / sphere->radius;
	vec_scale(scale, &normal, &v2);
	normalize_vector(&normal);
	intersection->normal.x = normal.x;
	intersection->normal.y = normal.y;
	intersection->normal.z = normal.z;
}

__device__ void compute_shadow_ray(RAY* ray, SPHERE_INTERSECTION* intersection, VECTOR3D* light)
{
	VECTOR3D dir;
	
	// ray origin is in the intersection point
	ray->origin.x = intersection->point.x;
	ray->origin.y = intersection->point.y;
	ray->origin.z = intersection->point.z;
	// ray direction is from the intersection point towards the light:
	vec_sub(&dir, light, &intersection->point);
	normalize_vector(&dir);
	ray->direction.x = dir.x;
	ray->direction.y = dir.y;
	ray->direction.z = dir.z;
}

__device__ double shadowColor(double ka, double amb_intensity)
{
	
	return (ka * amb_intensity);	
}

__device__ double blinnphongColor(SPHERE_INTERSECTION *intersection, VECTOR3D* light, VECTOR3D* viewpoint,
								  double kd, double ks, double ka, double p, double intensity, double amb_intensity)
{
	
	double color_diffuse = 0.0; 
	double color_specular = 0.0;
	VECTOR3D l;
	VECTOR3D h;
	VECTOR3D v;

	// compute vector v :
	vec_sub(&v, viewpoint, &intersection->point);
	normalize_vector(&v);
	// compute vector l :
	vec_sub(&l, light, &intersection->point);
	normalize_vector(&l);
	// compute vector h:
	vec_add(&h, &v, &l);
	normalize_vector(&h);
	// compute the diffuse intensity:
	color_diffuse = kd * intensity * dotproduct(&l, &intersection->normal) ;
	if (color_diffuse < 0.0)
		color_diffuse = 0.0;
	// compute the specular intensity:
	color_specular = ks * intensity * pow (dotproduct(&h, &intersection->normal), p);
	if (color_specular < 0.0)
		color_specular = 0.0;
	return (color_diffuse + color_specular + (ka * amb_intensity));	
}