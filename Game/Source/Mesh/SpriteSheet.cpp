#include "GamePCH.h"
#include "SpriteSheet.h"

//A container class for the details which add a texture to a mesh
SpriteSheet::SpriteSheet(std::string afilename, std::string aspritename)
{
	m_TextureID = 0;
	m_CurrentSprite = nullptr;

	m_Filename = afilename;
	SetFile("Data/" + m_Filename += ".png");

	LoadSprites();

	SetSprite(aspritename);
}

//Sets all attributes of the spritesheet, including changing sprite if on the same sheet
void SpriteSheet::SetSprite(std::string aspritename)
{
	for (int i = 0; i < (int)m_Sprites.size(); i++)
	{
		if (m_Sprites[i].name == aspritename)
		{
			m_CurrentSprite = &m_Sprites[i];
			break;
		}
	}
}

//returns a string holding the name of the currently active sprite
std::string SpriteSheet::GetSprite()
{
	return m_CurrentSprite->name;
}

//Called on creation of a spritesheet object. Loads all sprites from the file with JSON and stores them all internally for quick access
void SpriteSheet::LoadSprites()
{
	std::string str = SaveLoad::LoadFromFile(m_Filename + ".json");
	cJSON* Root = cJSON_Parse(str.c_str());

	float fileWidth = (float)cJSON_GetObjectItem(Root, "width")->valuedouble;
	float fileHeight = (float)cJSON_GetObjectItem(Root, "height")->valuedouble;

	//Load the player
	cJSON* obj = cJSON_GetObjectItem(Root, "Files");

	//loop through all of the sprites
	for (int i = 0; i < cJSON_GetArraySize(obj); i++)
	{
		//subitem = the current sprite
		cJSON * subitem = cJSON_GetArrayItem(obj, i);

		float x = (float)cJSON_GetObjectItem(subitem, "posx")->valuedouble;
		float y = (float)cJSON_GetObjectItem(subitem, "posy")->valuedouble;
		float w = (float)cJSON_GetObjectItem(subitem, "origw")->valuedouble;
		float h = (float)cJSON_GetObjectItem(subitem, "origh")->valuedouble;
		std::string name = cJSON_GetObjectItem(subitem, "filename")->valuestring;

		//push the info onto the vector
		m_Sprites.push_back(SpriteInfo(vec2(x / fileWidth, y / fileHeight), vec2(w / fileWidth, h / fileHeight), name));
	}

	//handle memory
	cJSON_Delete(Root);
}

//creates an animation set from 2 spritenames
// void SpriteSheet::CreateAnimation(std::string aFirstSprite, std::string aSecondSprite)
// {
// 	SpriteInfo* first = &m_Sprites[0];
// 	SpriteInfo* second = &m_Sprites[1];
// 
// 	//cycle through and set the right info
// 	for (int i = 0; i < (int)m_Sprites.size(); i++)
// 	{
// 		if (m_Sprites[i].name == aFirstSprite)
// 		{
// 			first = &m_Sprites[i];
// 		}
// 		else if (m_Sprites[i].name == aSecondSprite)
// 		{
// 			second = &m_Sprites[i];
// 		}
// 	}
// 
// 	//adds the animation vector to a bigger vector of structs of animations
// 	std::vector<SpriteInfo*>anims;
// 	anims.push_back(first);
// 	anims.push_back(second);
// 
// 	AnimationInfo animation = AnimationInfo(anims[0], anims[1]);
// 	m_Animations.push_back(animation);
// 	SetSprite(aFirstSprite);
// }
// 
// //this is the actual animation
// //When called will move the animation forward frame by frame.
// void SpriteSheet::NextAnimationFrame(Directions adirection)
// {
// 	int temp = m_Animations[adirection].currentframe;
// 	m_Animations[adirection].currentframe = m_Animations[adirection].nextframe;
// 	m_Animations[adirection].nextframe = temp;
// 
// 	SetSprite(m_Animations[adirection].Frames[m_Animations[adirection].currentframe]->name);
// }

//loads the file and sets the textureID to the new loaded file
void SpriteSheet::SetFile(const std::string afilename)
{
	m_TextureID = LoadTexture(afilename.c_str());
}
