#pragma once

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX
};

enum class MeshType : unsigned char
{
	Sprite,
	UI,
	Static,
	Animation
};

enum class BufferType : unsigned char
{
	Vertex,
	Index
};

enum class ShaderType : unsigned char
{
	Graphic,
	Compute
};

enum class ComponentType : unsigned char
{
	Scene,
	Object
};

enum class SceneComponentType : unsigned char
{
	Sprite
};

enum class EShaderBufferType : unsigned char
{
	Vertex = 0x1,
	Pixel = 0x2,
	Domain = 0x4,
	Hull = 0x8,
	Geometry = 0x10,
	Compute = 0x20,
	Graphic = Vertex | Pixel | Domain | Hull | Geometry,
	All = Vertex | Pixel | Domain | Hull | Geometry | Compute
};

enum class ECameraType : unsigned char
{
	Camera2D,
	Camera3D,
	CameraUI
};
