#pragma once
class Object abstract
{
public:
	bool GravityOn = false;
	bool CollNow = false;
	Transform ts;
	string CollKind = "NULL";
	int Hp;
	string ObjTag = "NULL";
	bool Die = false;
public:
	Object() {}
	virtual ~Object() {}
	
public:
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void UIRender() PURE;
	virtual void Collision(Object * obj) PURE;
	bool ObjDie() {return Die;}
	void ObjDel() {Die = true;}
	void SetHp(int hp) { Hp = hp; }
	int GetHp()
	{
		return Hp;
	}
	void UpdatePos(Vec3 pos)
	{
		ts.SetPos(pos);
	};
};

