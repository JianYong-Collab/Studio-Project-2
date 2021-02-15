#ifndef SCENE_UI_H
#define SCENE_UI_H
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Scene.h"
#include "Application.h"
#include"Mesh.h"
#include <MatrixStack.h>
class Assignment2 : public Scene
{
public:
	Assignment2();
	~Assignment2();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	float rotateAngle;
	float translateX;
	float translateY;
	float scaleAll;
	float fps;
	float SwingSword = 0;
	int bulletcount = 0;
	float bulletrate = 0;
	bool ShootBullet = false;
	bool PlayerAttack = false;
	bool gameStart = false;
	float timer = 0;
	int count = 0;
	float turn = 0;
	float et = 0;
	int gold = 0;
	bool Trading = false;
	bool NearVillager = false;
	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_QUAD,
		GEO_CUBE,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE5,
		GEO_TORUS,
		GEO_CIRCLE,
		GEO_LIGHTBALL,
		GEO_SQUARE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_UP,
		GEO_DOWN,
		GEO_FRONT,
		GEO_BACK,
		GEO_MODEL1,
		GEO_TEXT,
		GEO_DirtBlock,
		GEO_TV,
		GEO_GROUNDMESH,
		GEO_TREE1,
		GEO_TREE2,
		GEO_HOUSE1,
		GEO_HOUSE2,
		GEO_ROADTILE,
		GEO_CROSSHAIR,
		GEO_NUT,
		GEO_BODY,
		GEO_CYLINDER,
		GEO_HAND,
		GEO_HEMISPHERE,
		GEO_ITEM,
		GEO_PICKUP,
		GEO_CEO,
		NUM_GEOMETRY,

	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
private:
	unsigned m_vertexArrayID[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
	Light light[2];
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkyBox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void Hitbox(float length, float height, float width, float tlength, float theight, float twidth, float scale, int enemy , int bullet);
	void ItemHitbox(float length, float height, float width, float tlength, float theight, float twidth, float scale, int enemy);
	void TradingHitBox(float length, float height, float width, float tlength, float theight, float twidth, float scale);
};

#endif