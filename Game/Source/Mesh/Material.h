#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;
class Texture;
class SpriteSheet;

class Material
{
protected:
	ShaderProgram* m_pShader;
	Texture* m_pTexture;
	SpriteSheet* m_pSpriteSheet;


public:
	Material(ShaderProgram* pShader, SpriteSheet* pSpriteSheet);
	Material(ShaderProgram* pShader, Texture* pTexture);
	virtual ~Material();

	ShaderProgram* GetShader() { return m_pShader; }
	Texture* GetTexture() { return m_pTexture; }
	SpriteSheet* GetSpriteSheet() { return m_pSpriteSheet; }
};

#endif //__Material_H__