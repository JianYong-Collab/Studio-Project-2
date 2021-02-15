#include "Assignment2.h"
#include "GL\glew.h"
#include "Utility.h"
#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"
#include "MeshBuilder.h"
#include"MatrixStack.h"
#include "LoadTGA.h"
#include <sstream>
#include "Enemy.h"
#include "Bullet.h"
#include <math.h>
Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	rotateAngle = 1;

	for (int i = 0; i < 100; i++)
	{
		BulletArray[i] = nullptr;
	}
	// Init VBO here
	//Set Background colour to blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Generate a default VAO for now
	glGenVertexArrays(1, m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID[0]);
	
	
	

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//rainbow_bk.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//rainbow_ft.tga");

	meshList[GEO_UP] = MeshBuilder::GenerateQuad("up",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_UP]->textureID = LoadTGA("Image//rainbow_up.tga");

	meshList[GEO_DOWN] = MeshBuilder::GenerateQuad("down",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_DOWN]->textureID = LoadTGA("Image//rainbow_dn.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//rainbow_lf.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right",
		Color(1, 1, 1), 1.0f, 1.0f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//rainbow_rt.tga");

	

	


	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	


	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] =
		glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] =
		glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	

	glUseProgram(m_programID);
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	/*light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 40, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 100.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);*/

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	camera.Init(Vector3(-400, 30,450), Vector3(0, 30, 450), Vector3(0, 1, 0));
	

	//camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));
	//An array of 3 vectors which represents 3 vertices 
}
void Assignment2::Update(double dt)
{
	camera.Update(dt);
	if (Application::IsKeyPressed(0x31)) // number 1
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32)) // number 2
	{
		glDisable(GL_CULL_FACE);

	}
	if (Application::IsKeyPressed(0x33)) // number 3
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (Application::IsKeyPressed(0x34)) // number 4
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	float LSPEED = 10.0f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('5'))
	{
		//to do: switch light type to POINT and pass the information to shader
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('8'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		light[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}


	fps = 1.0f / dt;
	//Mouse Inputs
	static bool bLButtonState = false;

	if (!bLButtonState && Application::IsMousePressed(0))
	{
		float BUTTON_LEFT = 86;
		float BUTTON_RIGHT = 106;
		float BUTTON_TOP = 64;
		float BUTTON_BOTTOM = 44;
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = (0, x / 10); //convert (0,800) to (0,80)
		float posY = (0, 108 - (y / 10)); //convert (600,0) to (0,60)
		std::cout << "posX:" << posX << " , posY:" << posY << std::endl;
		if (posX > BUTTON_LEFT && posX < BUTTON_RIGHT && posY >  BUTTON_BOTTOM && posY < BUTTON_TOP)
		{
			std::cout << "Hit!" << std::endl;
			//trigger user action or function
		}
		else
		{
			std::cout << "Miss!" << std::endl;
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
	for (int i = 0; i < 8; i++)
	{
		if (EnemyArray[i]->EnemyHp <= 0)
		{
			EnemyArray[i]->Alive = false;
		}
		if (EnemyArray[i]->Alive == false)
		{
			for (int e = 0; e < 8; e++)
			{
				ItemHitbox(26, 40, 26, EnemyArray[e]->EnemyPos.x, EnemyArray[e]->EnemyPos.y, EnemyArray[e]->EnemyPos.z, 1, e);
			}
		}
	}
	
	//
	
	
}



void Assignment2::Render()
{

	

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if(light[0].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	modelStack.LoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	RenderSkyBox();
	
	
	
}
void Assignment2::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void Assignment2::RenderSkyBox()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	/*modelStack.Scale(2, 2, 2);*/


	modelStack.PushMatrix();
	modelStack.Translate(-500 , 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 500 );
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -500);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(500 , 0,0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, -500 , 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_DOWN], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 500 , 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_UP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

}
void Assignment2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

//glDisable(GL_DEPTH_TEST);
glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
glUniform1i(m_parameters[U_LIGHTENABLED], 0);
glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, mesh->textureID);
glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
for (unsigned i = 0; i < text.length(); ++i)
{
	Mtx44 characterSpacing;
	characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	mesh->Render((unsigned)text[i] * 6, 6);
}
glBindTexture(GL_TEXTURE_2D, 0);
glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
//glEnable(GL_DEPTH_TEST);
}
void Assignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)

{

	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 192, 0, 108, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 1.0f, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
void Assignment2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 192, 0, 108, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);
	/*modelStack.Rotate(SwingSword,0,1,0);*/
	modelStack.Scale(sizex, sizey, 0);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void Assignment2::Hitbox(float length, float height, float width, float tlength, float theight, float twidth, float scale, int enemy, int bullet)
{
	if ((BulletArray[bullet]->BulletPos.x) < (((length * scale)) + tlength) && (BulletArray[bullet]->BulletPos.x) > (-((length * scale)) + tlength) && (BulletArray[bullet]->BulletPos.y) < (((height * scale)) + theight) && (BulletArray[bullet]->BulletPos.y) > (-((height * scale)) + theight) && (BulletArray[bullet]->BulletPos.z) < (((width * scale)) + twidth) && (BulletArray[bullet]->BulletPos.z) > (-((width * scale)) + twidth))
	{
		EnemyArray[enemy]->EnemyHp -= 1;
		std::cout << "Hit" << std::endl;
	}




}
void Assignment2::ItemHitbox(float length, float height, float width, float tlength, float theight, float twidth, float scale, int enemy)
{
	if ((camera.position.x) < (((length * scale)) + tlength) && (camera.position.x) > (-((length * scale)) + tlength) && (camera.position.y) < (((height * scale)) + theight) && (camera.position.y) > (-((height * scale)) + theight) && (camera.position.z) < (((width * scale)) + twidth) && (camera.position.z) > (-((width * scale)) + twidth))
	{
		EnemyArray[enemy]->NearItem = true;
	}
	else
		EnemyArray[enemy]->NearItem = false;
}
void Assignment2::TradingHitBox(float length, float height, float width, float tlength, float theight, float twidth, float scale)
{
	if ((camera.position.x) < (((length * scale)) + tlength) && (camera.position.x) > (-((length * scale)) + tlength) && (camera.position.y) < (((height * scale)) + theight) && (camera.position.y) > (-((height * scale)) + theight) && (camera.position.z) < (((width * scale)) + twidth) && (camera.position.z) > (-((width * scale)) + twidth))
	{
		NearVillager = true;
	}
	else
		NearVillager = false;
}
void Assignment2::Exit()
{
	glDeleteVertexArrays(1, m_vertexArrayID);
	glDeleteProgram(m_programID);
}



