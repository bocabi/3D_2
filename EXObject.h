#pragma once
class EXObject : public Object
{
public:
	MultiMesh* mesh;
	EXObject();
	virtual ~EXObject();
public:


	// Object을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void UIRender() override;

	virtual void Collision(Object* obj) override;

};

