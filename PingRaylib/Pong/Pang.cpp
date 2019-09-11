/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

// Audio converter https://www.onlinevideoconverter.com/es/success
// audio cutter https://audiotrimmer.com/es/

#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

bool CanHitP1 =  false;
bool PlayPVP = false;
bool PlayPVE = false;
bool Play = false;
bool Victory = false;
bool P1Win = false;
Image texture;
Sound fxOgg;
Texture2D text;
Color Coloretes[7] = { { 230, 41, 55, 255 }, { 0, 121, 241, 255 }, { 0, 228, 48, 255 }, { 255, 161, 0, 255 }, { 253, 249, 0, 255 }, { 255, 109, 194, 255 }, { 200, 122, 255, 255 } };
struct Player
{
	Rectangle Rec;
	Color PlayerColor;
	int ChooseColor;
	int Puntos;
	int TotalScore;

}P1, P2;

struct Ball
{
	Vector2 Position;
	float StandarSpeed;
	float YDir;
	float XDir;
	Color BallColor;
	float Radius;
}Pelota;


void Win(int TextColor);

void Menu();
void PVP();
void PVE();

int main(void)
{
	// Inicializar Variables
	{
	P1.Rec.height = 80;
	P2.Rec.height = 80;
	P1.Rec.width = 20;
	P2.Rec.width = 20;
	P1.Rec.x = 20;
	P1.Rec.y = (float)screenHeight / 2;
	P2.Rec.x = 760;
	P2.Rec.y = (float)screenHeight / 2;
	P1.ChooseColor = 0;
	P2.ChooseColor = 1;
	P1.PlayerColor = Coloretes[P1.ChooseColor];
	P2.PlayerColor = Coloretes[P2.ChooseColor];
	Pelota.Position.x = (float)screenWidth / 2;
	Pelota.Position.y = (float)screenHeight / 2;
	Pelota.BallColor = RAYWHITE;
	Pelota.XDir = 1;
	Pelota.YDir = 1;
	Pelota.StandarSpeed = 5;
	Pelota.Radius = 12;
	P1.TotalScore = 0;
	P2.TotalScore = 0;
	}

	// Initialization
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
	InitAudioDevice(); 

	fxOgg = LoadSound("Sounds/Lightsaber Sound Effect HQ - HD-[AudioTrimmer.com].ogg");
	texture = LoadImage("IMG/LightSaber.jpg"); 
	ImageResize(&texture, 20, 80);
	text = LoadTextureFromImage(texture);

	Menu();
	SetTargetFPS(60);
	PVP();
	PVE();
	
	

	CloseWindow();

	return 0;
}


void Win(int TextColor)
{
	P1.Puntos = 0;
	P2.Puntos = 0;
	Pelota.Position.x = (float)screenWidth / 2;
	Pelota.Position.y = (float)screenHeight / 2;
	DrawText(TextFormat("VICTORY"), screenWidth/3, screenHeight/2, 60, Coloretes[TextColor]);
	DrawText(TextFormat("Total score:"), screenWidth / 3, screenHeight / 2 + 60, 15, RAYWHITE);
	DrawText(TextFormat("Player 1: %i", P1.TotalScore), screenWidth / 3, screenHeight / 2 + 75, 15, RAYWHITE);
	DrawText(TextFormat("Player 2: %i", P2.TotalScore), screenWidth / 3, screenHeight / 2 + 90, 15, RAYWHITE);
}

void Menu()
{
	Vector2 MousePos;
	while (!WindowShouldClose() && Play == false && Victory == false)
	{
		MousePos = GetMousePosition();
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawRectangle((screenWidth / 2) + 100, P1.Rec.y, P1.Rec.width, P1.Rec.height, P1.PlayerColor);
		DrawRectangle((screenWidth / 2) - 100, P2.Rec.y, P2.Rec.width, P2.Rec.height, P2.PlayerColor);
		DrawText("Player 2", (screenWidth / 2) - 120, (screenHeight / 7) * 5, 15, BLACK);
		DrawText("Player 1", (screenWidth / 2) + 80, (screenHeight / 7) * 5, 15, BLACK);
		DrawText("WASD", (screenWidth / 2) - 120, (screenHeight / 9) * 7, 15, BLACK);
		DrawText("Arrows", (screenWidth / 2) + 80, (screenHeight / 9) * 7, 15, BLACK);
		Rectangle BtnPVP = { screenWidth / 2 - 75, screenHeight / 3, 73, 30 };
		Rectangle BtnPVE = { screenWidth / 2 + 50, screenHeight / 3, 73, 30 };
		DrawRectangle(screenWidth / 2 - 75, screenHeight / 3, 73, 33, GOLD);
		DrawRectangle(screenWidth / 2 + 55, screenHeight / 3, 73, 33, GOLD);
		DrawText("PVP", screenWidth / 2 - 70, screenHeight / 3, 30, BLACK);
		DrawText("PVE", screenWidth / 2 + 60, screenHeight / 3, 30, BLACK);
		
		DrawTexture(text, (screenWidth / 2) + 100, P1.Rec.y, P1.PlayerColor);
		DrawTexture(text, (screenWidth / 2) - 100, P2.Rec.y, P2.PlayerColor);

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{

			if (MousePos.x > (screenWidth / 2) + 100 && MousePos.x <(screenWidth / 2) + 100 + P1.Rec.width && MousePos.y > P1.Rec.y && MousePos.y < P1.Rec.y + P1.Rec.height) {
				if (P1.ChooseColor < 6) {
					P1.ChooseColor = P1.ChooseColor + 1;
					if (P2.ChooseColor == P1.ChooseColor) {
						if (P1.ChooseColor < 6) {
							P1.ChooseColor = P1.ChooseColor + 1;
						}
						else {
							P1.ChooseColor = 0;
						}
					}
				}
				else {
					P1.ChooseColor = 0;
					if (P2.ChooseColor == P1.ChooseColor)
					{
						P1.ChooseColor = P1.ChooseColor + 1;
					}
				}
			}
			if (MousePos.x > (screenWidth / 2) - 100 && MousePos.x <(screenWidth / 2) - 100 + P2.Rec.width && MousePos.y > P2.Rec.y && MousePos.y < P2.Rec.y + P2.Rec.height) {
				if (P2.ChooseColor < 6) {
					P2.ChooseColor = P2.ChooseColor + 1;
					if (P2.ChooseColor == P1.ChooseColor) {
						if (P2.ChooseColor < 6) {
							P2.ChooseColor = P2.ChooseColor + 1;
						}
						else {
							P2.ChooseColor = 0;
						}
					}
				}
				else {
					P2.ChooseColor = 0;
					if (P2.ChooseColor == P1.ChooseColor)
					{
						P2.ChooseColor = P2.ChooseColor + 1;
					}
				}
			}
			P1.PlayerColor = Coloretes[P1.ChooseColor];
			P2.PlayerColor = Coloretes[P2.ChooseColor];

			if (CheckCollisionPointRec(MousePos, BtnPVP)) {
				PlayPVP = true;
				Play = true;
			}
			if (CheckCollisionPointRec(MousePos, BtnPVE)) {
				PlayPVE = true;
				Play = true;
			}
		}

		EndDrawing();

	}

}
void PVP() 
{
	bool PowerUpActive;
	int PowerUpX = GetRandomValue(10, screenWidth - 10);
	int PowerUpY = GetRandomValue(10, screenHeight - 10);
	while (!WindowShouldClose() && PlayPVP == true && Victory == false && Play == true)    // Detect window close button or ESC key
	{
		
		// Update
		//----------------------------------------------------------------------------------
		//Movment
		{
			if (P1.Rec.y > 0) {
				if (IsKeyDown(KEY_W)) P1.Rec.y -= 2.0f;
			}
			if (P1.Rec.y < screenHeight - P1.Rec.height) {
				if (IsKeyDown(KEY_S)) P1.Rec.y += 2.0f;
			}


			if (P2.Rec.y > 0) {
				if (IsKeyDown(KEY_UP)) P2.Rec.y -= 2.0f;
			}
			if (P2.Rec.y < screenHeight - P2.Rec.height) {
				if (IsKeyDown(KEY_DOWN)) P2.Rec.y += 2.0f;
			}

		}
		///////////////
		if (CheckCollisionCircleRec(Pelota.Position, Pelota.Radius, P1.Rec) && CanHitP1 == true)
		{
			if ((P1.Rec.y + (P1.Rec.height / 2)) > Pelota.Position.y) {
				PlaySound(fxOgg);
				Pelota.YDir = -1;
			}
			else {
				Pelota.YDir = 1;
				PlaySound(fxOgg);
			}
			Pelota.XDir = Pelota.XDir * -1;
			Pelota.BallColor = P2.PlayerColor;
			CanHitP1 = false;
		}
		if (CheckCollisionCircleRec(Pelota.Position, Pelota.Radius, P2.Rec) && CanHitP1 == false) {
			if ((P2.Rec.y + (P2.Rec.height / 2)) > Pelota.Position.y)
			{
				Pelota.YDir = -1;
				PlaySound(fxOgg);
			}
			else
			{
				Pelota.YDir = 1;
				PlaySound(fxOgg);
			}
			Pelota.XDir = Pelota.XDir * -1;
			Pelota.BallColor = P1.PlayerColor;
			CanHitP1 = true;
		}

		Pelota.Position.y += Pelota.YDir * Pelota.StandarSpeed;
		Pelota.Position.x += Pelota.XDir * Pelota.StandarSpeed;

		if (Pelota.Position.x < 0) {
			P2.Puntos++;
			Pelota.Position.x = (float)screenWidth / 2;
			Pelota.Position.y = (float)screenHeight / 2;
			Pelota.BallColor = RAYWHITE;
			if (P2.Puntos == 5)
			{
				P1Win = false;
				Victory = true;
				P2.TotalScore = P2.TotalScore + 1;
			}
		}
		if (Pelota.Position.x > screenWidth) {
			P1.Puntos++;
			Pelota.Position.x = (float)screenWidth / 2;
			Pelota.Position.y = (float)screenHeight / 2;
			Pelota.BallColor = RAYWHITE;
			if (P1.Puntos == 5)
			{
				P1.TotalScore = P1.TotalScore + 1;
				P1Win = true;
				Victory = true;
			}
		}
		if (Pelota.Position.y < 12) {
			Pelota.YDir = Pelota.YDir * -1;
		}
		if (Pelota.Position.y > screenHeight - 12) {
			Pelota.YDir = Pelota.YDir * -1;
		}

		while (!WindowShouldClose() && Victory == true)    // Detect window close button or ESC key
		{
			ClearBackground(BLACK);
			BeginDrawing();
			if (P1Win == true) {
				Win(P2.ChooseColor);
			}
			else {
				Win(P1.ChooseColor);
			}
			EndDrawing();

			if (IsKeyDown(KEY_ENTER))
			{
				Victory = false;

			}

		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);
		DrawCircle(Pelota.Position.x, Pelota.Position.y, 12, Pelota.BallColor);
		DrawRectangle(P1.Rec.x, P1.Rec.y, P1.Rec.width, P1.Rec.height, P2.PlayerColor);
		DrawRectangle(P2.Rec.x, P2.Rec.y, P2.Rec.width, P2.Rec.height, P1.PlayerColor);
		DrawText(TextFormat("Puntos: %i", P1.Puntos), 30, 20, 15, P2.PlayerColor);
		DrawText(TextFormat("Puntos: %i", P2.Puntos), 700, 20, 15, P1.PlayerColor);
		DrawTexture(text, P1.Rec.x, P1.Rec.y, P2.PlayerColor);
		DrawTexture(text, P2.Rec.x, P2.Rec.y, P1.PlayerColor);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
}
void PVE()
{
	while (!WindowShouldClose() && PlayPVE == true && Victory == false && Play == true)    // Detect window close button or ESC key
	{

		// Update
		//----------------------------------------------------------------------------------
		//Movment
		{
			if (P1.Rec.y > 0) {
				if (IsKeyDown(KEY_W)) P1.Rec.y -= 2.0f;
			}
			if (P1.Rec.y < screenHeight - P1.Rec.height) {
				if (IsKeyDown(KEY_S)) P1.Rec.y += 2.0f;
			}


			if (Pelota.Position.y < (P2.Rec.y + P2.Rec.height / 2))
			{
				if (P2.Rec.y > 0)
				{
					P2.Rec.y -= 2.0f;
				}
			}
			else
			{
				if (P2.Rec.y < screenHeight)
				{
					P2.Rec.y += 2.0f;
				}
				
			}
			
		}
		///////////////
		if (CheckCollisionCircleRec(Pelota.Position, Pelota.Radius, P1.Rec) && CanHitP1 == true)
		{
			if ((P1.Rec.y + (P1.Rec.height / 2)) > Pelota.Position.y) {
				Pelota.YDir = -1;
			}
			else {
				Pelota.YDir = 1;
			}
			Pelota.XDir = Pelota.XDir * -1;
			Pelota.BallColor = P2.PlayerColor;
			CanHitP1 = false;
		}
		if (CheckCollisionCircleRec(Pelota.Position, Pelota.Radius, P2.Rec) && CanHitP1 == false) {
			if ((P2.Rec.y + (P2.Rec.height / 2)) > Pelota.Position.y)
			{
				Pelota.YDir = -1;
			}
			else
			{
				Pelota.YDir = 1;
			}
			Pelota.XDir = Pelota.XDir * -1;
			Pelota.BallColor = P1.PlayerColor;
			CanHitP1 = true;
		}

		Pelota.Position.y += Pelota.YDir * Pelota.StandarSpeed;
		Pelota.Position.x += Pelota.XDir * Pelota.StandarSpeed;

		if (Pelota.Position.x < 0) {
			P2.Puntos++;
			Pelota.Position.x = (float)screenWidth / 2;
			Pelota.Position.y = (float)screenHeight / 2;
			Pelota.BallColor = RAYWHITE;
			if (P2.Puntos == 5)
			{
				P1Win = false;
				Victory = true;
				P2.TotalScore = P2.TotalScore + 1;
			}
		}
		if (Pelota.Position.x > screenWidth) {
			P1.Puntos++;
			Pelota.Position.x = (float)screenWidth / 2;
			Pelota.Position.y = (float)screenHeight / 2;
			Pelota.BallColor = RAYWHITE;
			if (P1.Puntos == 5)
			{
				P1.TotalScore = P1.TotalScore + 1;
				P1Win = true;
				Victory = true;
			}
		}
		if (Pelota.Position.y < 12) {
			Pelota.YDir = Pelota.YDir * -1;
		}
		if (Pelota.Position.y > screenHeight - 12) {
			Pelota.YDir = Pelota.YDir * -1;
		}
		while (!WindowShouldClose() && Victory == true)    // Detect window close button or ESC key
		{
			ClearBackground(BLACK);
			BeginDrawing();
			if (P1Win == true) {
				Win(P2.ChooseColor);
			}
			else {
				Win(P1.ChooseColor);
			}
			EndDrawing();

			if (IsKeyDown(KEY_ENTER))
			{
				Victory = false;

			}

		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);
		DrawCircle(Pelota.Position.x, Pelota.Position.y, 12, Pelota.BallColor);
		DrawRectangle(P1.Rec.x, P1.Rec.y, P1.Rec.width, P1.Rec.height, P2.PlayerColor);
		DrawRectangle(P2.Rec.x, P2.Rec.y, P2.Rec.width, P2.Rec.height, P1.PlayerColor);
		DrawText(TextFormat("Puntos: %i", P1.Puntos), 30, 20, 15, P2.PlayerColor);
		DrawText(TextFormat("Puntos: %i", P2.Puntos), 700, 20, 15, P1.PlayerColor);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}
}