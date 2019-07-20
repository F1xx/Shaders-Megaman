#include "GamePCH.h"

#include "FloatingMineObject.h"
#include "FloatingPlayerObject.h"
#include "../Scenes/Scene.h"
#include <string>

FloatingPlayerObject::FloatingPlayerObject(Scene* pScene, std::string name, Transform transform, Mesh* pMesh, Material* pMaterial)
: FloatingObject( pScene, name, transform, pMesh, pMaterial )
{
    m_pController = nullptr;
}

FloatingPlayerObject::~FloatingPlayerObject()
{
}

void FloatingPlayerObject::SetController(PlayerController* pController)
{
    m_pController = pController;
}

void FloatingPlayerObject::Update(float deltatime)
{
    FloatingObject::Update( deltatime );

    int numattached = 0;

    // Check if we're colliding with any mines.
    for( int i=0; i<20; i++ )
    {
		std::string minename = "Mine" + std::to_string(i);
        FloatingMineObject* pMine = dynamic_cast<FloatingMineObject*>( m_pScene->GetGameObjectByName( minename.c_str() ) );
        assert( pMine != 0 );

        if( pMine != 0 )
        {
            // Check if we're touching the mine.
            bool touching = false;

            //TODO_Floating: Check if we're touching mine.  Assume the player and the mine each have a radius of 1.
			float radiisqrd = 2.0f;
			radiisqrd *= radiisqrd; //square it to avoid rooting
			vec3 pos = GetPosition();
			vec3 minepos = pMine->GetPosition();
			float distsqrd = ((minepos.x - pos.x) * (minepos.x - pos.x)) + ((minepos.y - pos.y) * (minepos.y - pos.y)) + ((minepos.z - pos.z) * (minepos.z - pos.z));

			if (distsqrd <= radiisqrd)
			{
				touching = true;
			}

            if( touching )
            {
                pMine->m_AttachedToPlayer = true;
				AttachedMines.push_back(pMine);
            }

            // Count the number of mines attached to us.
            if( pMine->m_AttachedToPlayer )
                numattached++;
        }
    }

    // Make all attached mines circle around us.
    int count = 0;
	float range = 5.0f;

    for( int i=0; i<20; i++ )
    {
		std::string minename = "Mine" + std::to_string(i);
        FloatingMineObject* pMine = dynamic_cast<FloatingMineObject*>( m_pScene->GetGameObjectByName( minename.c_str() ) );
        assert( pMine != 0 );

        if( pMine != 0 && pMine->m_AttachedToPlayer )
        {
            //TODO_Floating: Position the mine so it's circling us.
			//did it a different way because I have no idea how doing it here would work
			//didn't see the numattached variable lol
			count++;
        }
    }


	float reliefangle = 360.0f / AttachedMines.size();

	angle += deltatime * 60.0f;
	if (angle > 360)
	{
		angle = 0;
	}

	for (unsigned int j = 0; j < AttachedMines.size(); j++)
	{
		float thisradangle = DegreesToRadians(reliefangle * j + angle);

		vec3 newpos = GetPosition();

		vec2 orbit;

		orbit.x = cosf(thisradangle) * range;
		orbit.y = sinf(thisradangle) * range;

		newpos.x += orbit.x;
		newpos.z += orbit.y;

		newpos.y = AttachedMines[j]->GetPosition().y;


		AttachedMines[j]->SetPosition(newpos);
	}

    // Move faster depending how many mines we have.
    float speed = 3.0f + numattached;

    vec3 dir(0,0,0);

    if( m_pController->IsHeld_Up() )
        dir.z += 1;
    if( m_pController->IsHeld_Down() )
        dir.z -= 1;
    if( m_pController->IsHeld_Left() )
        dir.x -= 1;
    if( m_pController->IsHeld_Right() )
        dir.x += 1;

	dir = dir.Normalize(); //hamfisted but definitely won't be larger than 1 now

    //TODO_Floating: Make sure direction vector isn't longer than 1.
	if (dir.Length() > 1)
	{
		OutputMessage("Player moving too fast (%f, %f, %f)\n", dir.x, dir.y, dir.z);
	}

    m_Position += dir * speed * deltatime;
}

float FloatingPlayerObject::DegreesToRadians(float deg)
{
	return (deg / 180.0f) * PI;
}
