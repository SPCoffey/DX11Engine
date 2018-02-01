#pragma once

#include "DXCore.h"
#include "Mesh.h"
#include "Entity.h"
#include "Emitter.h"
#include "SimpleShader.h"
#include "Camera.h"
#include "Lights.h"
#include "WICTextureLoader.h"
#include <DirectXMath.h>

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);
	void RenderParticles();

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:

	// Camera
	Camera* camera;

	// Texture
	ID3D11ShaderResourceView* crateTexture;
	ID3D11ShaderResourceView* ornamentTexture;
	ID3D11ShaderResourceView* lightIcon;

	// Particle stuff
	ID3D11ShaderResourceView* particleTexture;
	SimpleVertexShader* particleVS;
	SimplePixelShader* particlePS;
	ID3D11DepthStencilState* particleDepthState;
	ID3D11BlendState* particleBlendState;
	ID3D11BlendState* noBlendState;
	Emitter* emitter;

	// Sampler State
	ID3D11SamplerState* sampleState;
	D3D11_SAMPLER_DESC sampleDesc;

	// Materials
	Material* crateMat;
	Material* ornamentMat;

	// Meshes
	Mesh* cone;
	Mesh* cube;
	Mesh* cylinder;
	Mesh* helix;
	Mesh* sphere;
	Mesh* torus;

	// Lights
	DirectionalLight light;
	DirectionalLight lightTwo;

	// Entities
	std::vector<Entity*> entities;

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGeometry();
	void CreateEntities();

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;
};
