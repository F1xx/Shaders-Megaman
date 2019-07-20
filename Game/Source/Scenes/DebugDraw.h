#pragma once
#include "Box2D/Common/b2Draw.h"
class Camera;
class Material;

class DebugDraw : public b2Draw
{
public:
	DebugDraw();
	~DebugDraw();


	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	virtual void DrawTransform(const b2Transform& xf) override;
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

	virtual void SetCamera(Camera* cam);
	virtual void SetMaterial(Material* mat);

private:
	Camera* m_pCamera;
	Material* m_pMaterial;
};