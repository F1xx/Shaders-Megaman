#include "GamePCH.h"
#include "ContactListener.h"
#include "GameObjects/GameObject.h"

ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	GameObject* pObjA = (GameObject*)fixA->GetBody()->GetUserData();
	GameObject* pObjB = (GameObject*)fixB->GetBody()->GetUserData();

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	vec2 position = (worldManifold.points[0].x, worldManifold.points[0].y);
	vec2 normal = (worldManifold.normal.x, worldManifold.normal.y);

	if (pObjA && pObjB)
	{
		pObjA->BeginContact(fixB, position, normal);
		pObjB->BeginContact(fixA, position, normal * -1);
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	GameObject* pObjA = (GameObject*)fixA->GetBody()->GetUserData();
	GameObject* pObjB = (GameObject*)fixB->GetBody()->GetUserData();

	if (pObjA && pObjB)
	{
		pObjA->EndContact(pObjB);
		pObjB->EndContact(pObjA);
	}
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2ContactListener::PreSolve(contact, oldManifold);
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2ContactListener::PostSolve(contact, impulse);
}
