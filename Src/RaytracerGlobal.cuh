#ifndef __RAYTRACERGLOBAL_H__
#define __RAYTRACERGLOBAL_H__

__global__ void init_kernel(int width, int height);
__global__ void raytracer_kernel(float3* pos, unsigned int width, unsigned int height);
__global__ void animate_kernel();

#endif