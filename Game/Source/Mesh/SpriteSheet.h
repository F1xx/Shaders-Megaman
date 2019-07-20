#pragma once

struct SpriteInfo
{
	SpriteInfo(vec2 aoffset, vec2 ascale, std::string aname) { offset = aoffset; scale = ascale; name = aname; }

	vec2 offset, scale;
	std::string name;
};

struct AnimationInfo
{
	AnimationInfo(SpriteInfo* aframe1, SpriteInfo* aframe2) { Frames.push_back(aframe1); Frames.push_back(aframe2); }

	std::vector<SpriteInfo*> Frames;
	int currentframe = 0;
	int nextframe = 1;
};

class SpriteSheet
{
public:
	SpriteSheet(std::string afilename, std::string aspritename);

	//void SetScale(vec2 ascale) { m_Scale = ascale; }
	vec2 GetScale() { return m_CurrentSprite->scale; }

	//void SetOffset(vec2 aoffset) { m_Offset = aoffset; }
	vec2 GetOffset() { return m_CurrentSprite->offset; }

	std::string GetFilename() { return m_Filename; }
	GLuint GetTextureID() { return m_TextureID; }

	void SetSprite(std::string aspritename);
	std::string GetSprite();
	void LoadSprites();

// 	void CreateAnimation(std::string aFirstSprite, std::string aSecondSprite);
// 	void NextAnimationFrame(Directions adirection);

private:

	void SetFile(std::string afilename);

	GLuint m_TextureID;
	std::string m_Filename;

	SpriteInfo* m_CurrentSprite;

	std::vector<AnimationInfo> m_Animations;

	std::vector<SpriteInfo> m_Sprites;
};