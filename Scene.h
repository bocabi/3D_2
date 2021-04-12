#pragma once
class Scene abstract
{
public :
	Scene() {};
	virtual ~Scene() {};
public:
	virtual void init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void UIRender() PURE;
	virtual void Release() PURE;
};

