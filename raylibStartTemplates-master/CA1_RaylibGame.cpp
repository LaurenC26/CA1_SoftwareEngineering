#include "raylib.h"
//this command allows VSC to include the Raylib Libray. 


//struct is a collection of variables/functions/methods- this struct is to correct the ball within the Pong game. The void draw command allows the function to run continiously. 
struct Ball
{
	//float commands are calling a numeric value within the code.
	float x, y;
	float SpeedX, SpeedY;
	float radius;

	void Draw()
	{
//this code is drawing the ball and since we have defined the ball we just have to call the structs. 
			DrawCircle((int) x, y,(int) radius, GOLD);
	}
};
//the struct code for the paddle.
struct Paddle
{
//float commands are calling a numeric value within the code.
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{x - width/2, y -height/2, width, height};
	}
	void Draw()
	{
		//DrawRectangleGradientEx (GetRect(), LIME,LIME,RED,RED);
	DrawRectangleRec(GetRect(), GOLD); 
	//THE draw rectangle grad ex only needs the rec position and color.
	};
};


//The main function of the code.
int main(){
	//Window creating the window in vsc, gives the demensions and name. It also initializes a window.
	InitWindow(800, 450, "CyberPong");
	//set Window state makes sure that the refresh of the FPS stays inline with the computer refresh window rate.
	SetWindowState(FLAG_VSYNC_HINT);

	InitAudioDevice();
	
	Music music =
	LoadMusicStream("Resources/Music.wav");
	PlayMusicStream (music);

	Sound soundPong =LoadSound ("Resources/sound.rfx.wav");
	Sound winSound =LoadSound ("Resources/win.wav");

	Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
	bool scored = false;
	bool started = false;
// float type because they dont always have to be integers.
//.0f divides by a float
//struct to define the ball.
	Ball ball;
	//x position of ball.
	ball.x =GetScreenWidth()/2.0f;
	//y position of ball.
	ball.y=GetScreenHeight()/2.0f;
	//radius of ball.
	ball.radius =5;
	//speed on x-axis.
	ball.SpeedX =300;
	//speed on y-axis.
	ball.SpeedY =300;

//struct to define the left paddle.
	Paddle leftPaddle;
	//x position of the paddle.
	leftPaddle.x =50;
	//y position of the paddle.
	leftPaddle.y = GetScreenHeight()/2;
	//width and height of the paddle.
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	//Speed of the paddle.
	leftPaddle.speed = 500;

//struct to define the right ball.
	Paddle rightPaddle;
	//x position of the paddle.
	rightPaddle.x =GetScreenWidth() -50;
	//y position of the paddle.
	rightPaddle.y = GetScreenHeight()/2;
	//width and height of the paddle.
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	//Speed of the paddle.
	rightPaddle.speed = 500;


//defines the constant character of winner text.
	const char* winnerText = nullptr;

//Render loop so that the window will not close automatically.
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);

		scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
		//begins drawing
		//BeginDrawing();
		//draws a clear background
		//ClearBackground(BLACK);
//draws the fps rate if you hover it takes two arguments position x and y. X horizontal, y vertically. (0,0) 
//corresponds to the left of the box. origin is the top left and y goes down as the number gets bigger.

//could put the figues of the circle, but you can get the width of the screen and divide by 2 and same with height.
			//DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 5, WHITE);
//For the rectangle the height is not centred, the circle draws from the centre where rectangle draws from the top left, to fix this you substract half of the height to put it as the center.
			//DrawRectangle(50, GetScreenHeight()/2 - 50, 10, 100, WHITE);
//for width subtract 50 cuz we want to draw it 50 from the right but it draws from the left and not the center we also need to substract the width, it will make it so that the right of the right is 50 away from the width.
			//DrawRectangle (GetScreenWidth()-50 -10, GetScreenHeight()/2-50, 10, 100, WHITE);
			//DrawFPS(10,10);
//ends the drawing
		//EndDrawing();
//only drawn in one position, to move we have to replace the constants with variables, named floats above and changed the below of the drawing. 
while (!started){
	
		if (IsKeyPressed(KEY_SPACE))
		{
			started = true;
		}
		BeginDrawing();
			//draws a clear background//begins the rendering and creates a draw section.	
				ClearBackground(GetColor(0x052c46ff));
	//draws the fps rate if you hover it takes two arguments position x and y. X horizontal, y vertically. (0,0) 
	//corresponds to the left of the box. origin is the top left and y goes down as the number gets bigger.
	// NOTE: Texture is scaled twice its size
				DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

				// Draw midground image twice
				DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

				// Draw foreground image twice
				DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
				DrawFPS(10,10);
				
				DrawText ("CyberPong", GetScreenWidth() / 2, GetScreenHeight() / 2 -30, 60, YELLOW);
				//ends the drawing
			EndDrawing();
}

//put movement before drawing.
//ball slow need because of frame rate if multiplied by 1 it will be very slow, you multiply by a bigger number. Inputted Variables from the top and called by BallSpeedX
while(started){
	ball.x += ball.SpeedX * GetFrameTime();
	ball.y += ball.SpeedY * GetFrameTime();

	if (ball.y < 0)
	{
		ball.y= 0;
		ball.SpeedY *= -1;
	}

	//add logic to the ball to stop it moving off the screen.

	if (ball.y > GetScreenHeight())
	{ 
		//stops ball getting stuck in the bottom of the screen.
		ball.y =GetScreenHeight();
		// -1 reverses the ball.
		ball.SpeedY *= -1;
	}

	//this code means that if the position of the right paddle on the y axis is less than 50 then it will stay the same.
	if (rightPaddle.y < rightPaddle.height/2)
	{
		rightPaddle.y=rightPaddle.height/2;
	}

	//this is reverseing the above but it is getting the screen height of 800 and minusing 50.
	if (rightPaddle.y > GetScreenHeight() - rightPaddle.height/2)
	{
		rightPaddle.y= GetScreenHeight() - rightPaddle.height/2;
	}

	//this code means that if the position of the left paddle on the y axis is less than 50 then it will stay the same.
	if (leftPaddle.y < leftPaddle.height/2)
	{
		leftPaddle.y=leftPaddle.height/2;
	}

	//this is reverseing the above but it is getting the screen height of 800 and minusing 50.
	if (leftPaddle.y > GetScreenHeight() - leftPaddle.height/2)
	{
		leftPaddle.y= GetScreenHeight() - leftPaddle.height/2;
	}

	if(IsKeyDown(KEY_W))
	{
		leftPaddle.y -= leftPaddle.speed * GetFrameTime();
	}

	if(IsKeyDown(KEY_S))
	{
		leftPaddle.y += leftPaddle.speed * GetFrameTime();
	}

	if(IsKeyDown(KEY_UP))
	{
		rightPaddle.y -= rightPaddle.speed * GetFrameTime();
	}

	if(IsKeyDown(KEY_DOWN))
	{
		rightPaddle.y += rightPaddle.speed * GetFrameTime();
	}

		
	if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,leftPaddle.GetRect()))
	{
		if(ball.SpeedX < 0)
		{
		ball.SpeedX *= -1.1f;
		ball.SpeedY = (ball.y -leftPaddle.y) / (leftPaddle.height/2) * ball.SpeedX;
		PlaySound(soundPong);
		}
	}

		
	if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,rightPaddle.GetRect()))
	{
		if(ball.SpeedX> 0)
		{
		ball.SpeedX *= -1.1f;
		ball.SpeedY = (ball.y -rightPaddle.y) / (rightPaddle.height/2) * -ball.SpeedX;
		PlaySound(soundPong);
		}
	}


	if(ball.x<0)
	{
		winnerText = "Right Player Wins!";
		
		if (scored ==false){
			PlaySound(winSound);
		}
		scored = true;
	}


	if(ball.x > GetScreenWidth())
	{
		winnerText = "Left Player Wins!";
		if (scored ==false){
			PlaySound(winSound);
		}
		scored = true;
	}

	if (winnerText && IsKeyPressed(KEY_SPACE))
	{
		ball.x = GetScreenWidth() / 2;
		ball.y =GetScreenHeight() / 2;
		ball.SpeedX = 300;
		ball.SpeedY = 300;
		winnerText = nullptr;
		scored = false;
		StopSound(winSound);
	}

	BeginDrawing();
			//draws a clear background//begins the rendering and creates a draw section.	
				ClearBackground(GetColor(0x052c46ff));
	//draws the fps rate if you hover it takes two arguments position x and y. X horizontal, y vertically. (0,0) 
	//corresponds to the left of the box. origin is the top left and y goes down as the number gets bigger.
	// NOTE: Texture is scaled twice its size
				DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

				// Draw midground image twice
				DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

				// Draw foreground image twice
				DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

						
				
				ball.Draw();
				//it will continue to draw the ball as it did.
	//For the rectangle the height is not centred, the circle draws from the centre where rectangle draws from the top left, to fix this you substract half of the height to put it as the center.
				leftPaddle.Draw();
				rightPaddle.Draw();

				if (winnerText)
				{
					int textWidth = MeasureText(winnerText, 60);
					DrawText (winnerText, GetScreenWidth() / 2 -textWidth / 2, GetScreenHeight() / 2 -30, 60, YELLOW);		
				}

				//for width subtract 50 cuz we want to draw it 50 from the right but it draws from the left and not the center we also need to substract the width, it will make it so that the right of the right is 50 away from the width.
				//DrawRectangle (GetScreenWidth()/2 -50 -10, GetScreenHeight()/2-50, 10, 100, WHITE);
	//only drawn in one position, to move we have to replace the constants with variables. 
				DrawFPS(10,10);
	//ends the drawing
			EndDrawing();
	}
	}
  UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground);  // Unload foreground texture

	CloseAudioDevice();
//closes the window//de-initalizes the open window.
	CloseWindow ();
	return 0;
}