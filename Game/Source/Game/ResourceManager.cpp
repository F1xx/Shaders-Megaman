#include "GamePCH.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto object : m_pMeshes)
		delete object.second;

	for (auto object : m_pMaterials)
		delete object.second;

	for (auto object : m_pShaders)
		delete object.second;

	for (auto object : m_pTextures)
		delete object.second;

	for (auto object : m_pSheets)
		delete object.second;
}

Mesh* ResourceManager::AddMesh(std::string name, Mesh* pMesh)
{
	assert(m_pMeshes.find(name) == m_pMeshes.end());

	m_pMeshes[name] = pMesh;

	return pMesh;
}

void ResourceManager::AddShader(std::string name, ShaderProgram* pShader)
{
	assert(m_pShaders.find(name) == m_pShaders.end());

	m_pShaders[name] = pShader;
}

void ResourceManager::AddTexture(std::string name, Texture* pTexture)
{
	assert(m_pTextures.find(name) == m_pTextures.end());

	m_pTextures[name] = pTexture;
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
	assert(m_pMaterials.find(name) == m_pMaterials.end());

	m_pMaterials[name] = pMaterial;
}

void ResourceManager::AddSpriteSheet(std::string name, SpriteSheet* pSheet)
{
	assert(m_pSheets.find(name) == m_pSheets.end());

	m_pSheets[name] = pSheet;
}

Mesh* ResourceManager::GetMesh(std::string name)
{
	auto it = m_pMeshes.find(name);
	if (it == m_pMeshes.end())
		return nullptr;

	return it->second;
}

ShaderProgram* ResourceManager::GetShader(std::string name)
{
	auto it = m_pShaders.find(name);
	if (it == m_pShaders.end())
		return nullptr;

	return it->second;
}

Texture* ResourceManager::GetTexture(std::string name)
{
	auto it = m_pTextures.find(name);
	if (it == m_pTextures.end())
		return nullptr;

	return it->second;
}

Material* ResourceManager::GetMaterial(std::string name)
{
	auto it = m_pMaterials.find(name);
	if (it == m_pMaterials.end())
		return nullptr;

	return it->second;
}

SpriteSheet* ResourceManager::GetSpriteSheet(const std::string name)
{
	auto it = m_pSheets.find(name);
	if (it == m_pSheets.end())
		return nullptr;

	return it->second;
}
