#include "Raytracer.h"

#include "RaytracerTypes.cuh"
#include "RaytracerGlobal.cuh"

#include <cuda_gl_interop.h>


Raytracer::Raytracer(GLRenderer* renderer, unsigned int priority) :
	DisplayableTask(priority), _buffer(nullptr), _vbo(GL_INVALID_VALUE)
{
	_renderer = renderer;
}

Raytracer::~Raytracer()
{
}

bool
Raytracer::Start()
{
	unsigned int width = _renderer->Width();
	unsigned int height = _renderer->Height();
	init_kernel<<<1,1>>>(width, height);
	if (cudaMalloc(&_buffer, width * height * sizeof(uchar4)) != cudaSuccess)
		return false;
	glGenBuffers(1, &_vbo);
	if (_vbo == GL_INVALID_VALUE)
		return false;
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	unsigned int size = width * height * sizeof(float3);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	cudaGLRegisterBufferObject(_vbo);
	return true;
}

void
Raytracer::Update()
{
	unsigned int width = _renderer->Width();
	unsigned int height = _renderer->Height();

	animate_kernel<<<1,1>>>();
	cudaThreadSynchronize();
	float3 *dptr;
    cudaGLMapBufferObject((void**)&dptr, _vbo);
	dim3 block(32, 16, 1);
	dim3 grid(width / block.x + 1, height / block.y + 1, 1);
	cudaThreadSynchronize();
	raytracer_kernel<<<grid,block>>>(dptr, width, height);
	cudaGLUnmapBufferObject(_vbo);
}

void
Raytracer::Display()
{
	unsigned int width = _renderer->Width();
	unsigned int height = _renderer->Height();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexPointer(2, GL_FLOAT, 12, 0);
	glColorPointer(4, GL_UNSIGNED_BYTE, 12, (GLvoid*)8);
    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_POINTS, 0, width * height);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
Raytracer::Stop()
{
	if (_buffer != nullptr)
		cudaFree(_buffer);
	if (_vbo != GL_INVALID_VALUE)
		glDeleteBuffers(1, &_vbo);
}