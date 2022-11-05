#include "raylib.h"
//this command allows VSC to include the Raylib Libray. 


//struct is a collection of variables/functions/methods- this struct is to correct the ball within the Pong game. The void draw command allows the function to run continiously. 
struct Ball
{
	//float commands are calling a numeric value within the code.
	float x, y;
	float SpeedX, SpeedY;
	float radius;
	
	//this code is drawing the ball and since we have defined the ball we just have to call the method. 
	void Draw(Color ballColor)
	{
			DrawCircle((int) x, y,(int) radius, ballColor);
	}

};


//the struct code for the paddle.
struct Paddle
{
//float commands are calling a numeric value within the code.
	float x, y;
	float speed;
	float width, height;

	//creating the rectangle parameters
	Rectangle GetRect()
	{
		return Rectangle{x - width/2, y -height/2, width, height};
	}

	//creating the draw function for the rectangle
	void Draw()
	{
		//DrawRectangleGradientEx (GetRect(), LIME,LIME,RED,RED);
		DrawRectangleRec(GetRect(), RAYWHITE); 
		//THE draw rectangle grad ex only needs the rec position and color.
	};
};


//The main function of the code.
int main(){
	//Window creating the window in vsc, gives the demensions and name. It also initializes a window.
	InitWindow(800, 450, "CyberPong");
	
	//set Window state makes sure that the refresh of the FPS stays inline with the computer refresh window rate.
	SetWindowState(FLAG_VSYNC_HINT);
	
	//initilizes audio
	InitAudioDevice();
	
	//defining music and resources
	Music music = LoadMusicStream("Resources/Music.wav");
	//playing that music on creation
	PlayMusicStream (music);
	
	//defining the sfx for the game
	Sound soundPong =LoadSound ("Resources/sound.rfx.wav");
	//defining the sfx for the game
	Sound winSound =LoadSound ("Resources/win.wav");
	
	//defining the location of the game textures background
	Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
	//defining the location of the game textures midground
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
	//defining the location of the game textures foreground
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

	//allowing for multiple colors of the game objects
	Color colors[] = {PINK, YELLOW, GREEN, BLUE, WHITE};
	//this variable stores the current position in the colors array
	int currentColorIndex = 0;

	//getting the length of the colors array
	int len = sizeof(colors) / sizeof(colors[0]);
	
	//float to control the background scrolling background
    float scrollingBack = 0.0f;
	//float to control the background scrolling midground
    float scrollingMid = 0.0f;
	//float to control the background scrolling foreground
    float scrollingFore = 0.0f;
	
	//bools to control the game loop
	bool scored = false;
	bool started = false;
	
	//creating a ball object from the struct created above
	Ball ball;
	//starting position of the ball x
	ball.x =GetScreenWidth()/2.0f;
	//starting position of the ball y
	ball.y=GetScreenHeight()/2.0f;
	
	//radius of ball.
	ball.radius =5;
	
	// starting speed of the ball x
	ball.SpeedX = 300;
	// starting speed of the ball y
	ball.SpeedY = 300;

	//creating left paddle object
	Paddle leftPaddle;
	//starting position of the paddle x
	leftPaddle.x = 50;
	//starting position of the paddle y
	leftPaddle.y = GetScreenHeight() / 2;
	
	//width of the paddle
	leftPaddle.width = 10;
	//height of the paddle
	leftPaddle.height = 100;
	
	//Speed of the paddle.
	leftPaddle.speed = 500;

	//struct to define the right paddle.
	Paddle rightPaddle;
	
	//starting position of the right paddle x
	rightPaddle.x = GetScreenWidth() - 50;
	//starting position of the right paddle y
	rightPaddle.y = GetScreenHeight() / 2;
	
	//width of the paddle
	rightPaddle.width = 10;
	//height of the paddle.
	rightPaddle.height = 100;
	
	//Speed of the paddle, half that of the player by default due to how the computer controller moves it
	rightPaddle.speed = 250;


	//defines all the text used in the game for ease of editing
	//text for title of the game
	const char* title = "CYBERPONG";
	//text for up instruction of the game
	const char* upInstruction = "Press W to move paddle up";
	//text for down instruction of the game
	const char* downInstruction = "Press S to move paddle up";
	//text for start instruction of the game
	const char* startInstruction = "Press the Spacebar to play";
	//text for winner of the game
	const char* winnerText = nullptr;
	//text for right player winner of the game
	const char* rightWinText = "Right Player Wins";
	//text for left player winner of the game
	const char* leftWinText = "Left Player Wins";
	//text for restarting the game
	const char* extraWinText = "Press the Spacebar to continue";
	
	//defines all the font sizes used for ease of updating
	//defines title font size
	int titleFontSize = 80;
	//defines large font size
	int largeFontSize = 60;
	//defines small font size
	int smallFontSize = 30;

	//Render loop so that the window will not close automatically.
	while (!WindowShouldClose())
	{
		//function to update the music player with the default scene music
		UpdateMusicStream(music);

		//updating the scrolling variables for the background
		scrollingBack -= 0.1f;
		//updating the scrolling variables for the midground
        scrollingMid -= 0.5f;
		//updating the scrolling variables for the foreground
        scrollingFore -= 1.0f;

        //if statement to reset the background texture for infinite scrolling background
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
		//if statement to reset the background texture for infinite scrolling midground
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
		//if statement to reset the background texture for infinite scrolling foreground
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
		
		//game will not start until this is triggered, allowing for a start menu
		if(started == false){
			//trigger to start game is pressing space
			if(IsKeyDown(KEY_SPACE))
			{
				started = true;
			}
		}

		//if the space bar has been pressed, this statement will be true, running the game
		if(started==true){

			//ball slow need because of frame rate if multiplied by 1 it will be very slow, you multiply by a bigger number. Inputted Variables from the top and called by BallSpeedX
			ball.x += ball.SpeedX * GetFrameTime();
			ball.y += ball.SpeedY * GetFrameTime();

			//prevents the ball from going off the screen and reverses it's Y speed, making it bounce
			//this is for the top of the screen
			if (ball.y < 0)
			{
				ball.y= 0;
				ball.SpeedY *= -1;
			}

			//this is for the bottom
			if (ball.y > GetScreenHeight())
			{ 
				//stops ball getting stuck in the bottom of the screen.
				ball.y = GetScreenHeight();
				// -1 reverses the ball speed.
				ball.SpeedY *= -1;
			}

			//stops the paddle from going off the edge of the screen
			//the paddle's position is at it's centre so an offset is used to stop it going partly off the edge before stopping
			//this is for the top of the screen
			if (rightPaddle.y < rightPaddle.height/2)
			{
				rightPaddle.y=rightPaddle.height/2;
			}

			//this is for the bottom
			if (rightPaddle.y > GetScreenHeight() - rightPaddle.height/2)
			{
				rightPaddle.y= GetScreenHeight() - rightPaddle.height/2;
			}

			//this is stoppoing the left paddle going off the screen. Same as above for the right paddle
			//this is for the top of the screen
			if (leftPaddle.y < leftPaddle.height/2)
			{
				leftPaddle.y=leftPaddle.height/2;
			}

			//this is for the bottom
			if (leftPaddle.y > GetScreenHeight() - leftPaddle.height/2)
			{
				leftPaddle.y= GetScreenHeight() - leftPaddle.height/2;
			}

			//User input for controlling the left paddle
			//if W is pressed the paddle will move by the set speed * the frame time so it moves consistently regardless of the FPS
			if(IsKeyDown(KEY_W))
			{
				leftPaddle.y -= leftPaddle.speed * GetFrameTime();
			}
			//if s is down it will move paddle down, with the same control for FPS above
			if(IsKeyDown(KEY_S))
			{
				leftPaddle.y += leftPaddle.speed * GetFrameTime();
			}

			//logic to control the computer controlled paddle
			//the paddle will only move when the ball is in the right half of the screen to make it more fair for the player
			if (ball.x > GetScreenWidth()/ 2 )
			{
				//this logic makes it so the paddle always moves towards the ball, 
				//This for moving it upwards
				if(ball.y < rightPaddle.y)
				{
					rightPaddle.y -= rightPaddle.speed * GetFrameTime();
				}

				//this for moving it downwards
				if(ball.y > rightPaddle.y)
				{
					rightPaddle.y += rightPaddle.speed * GetFrameTime();
				}
			}
			
			//checking the collision of the ball with the left paddle
			if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,leftPaddle.GetRect()))
			{	
				//if the balls position is colliding with the rectangle and it is moving towards the left paddle
				//this stops the below code from running multiple times if the ball is in contact for multiple frames
				if(ball.SpeedX < 0)
				{
					//increase the x speed to make the game progressively more difficult
					ball.SpeedX *= -1.1f;
					//this math makes the ball bounce off in a direction that looks correct 
					//and stops the chance of the y speed becoming 0 and the ball just bouncing perfectly back and forth between paddles
					ball.SpeedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.SpeedX;
					//play the sfx
					PlaySound(soundPong);

					//this updates the current position of in the color array and will be used when the ball is drawn
					//if the array hits the last color then it resets the position to allow infinite looping through the colors
					if (currentColorIndex == len-1){
						currentColorIndex = 0;
					}
					else
					{
						currentColorIndex += 1;
					}
				}
			}

			//this is the same as above for the ball with the right paddle
			if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,rightPaddle.GetRect()))
			{
				//if the balls position is colliding with the rectangle and it is moving towards the right paddle
				//this stops the below code from running multiple times if the ball is in contact for multiple frames
				if(ball.SpeedX> 0)
				{
					//increase the x speed to make the game progressively more difficult
					ball.SpeedX *= -1.1f;
					//this math makes the ball bounce off in a direction that looks correct 
					//and stops the chance of the y speed becoming 0 and the ball just bouncing perfectly back and forth between paddles
					ball.SpeedY = (ball.y -rightPaddle.y) / (rightPaddle.height/2) * -ball.SpeedX;
					//play the sfx
					PlaySound(soundPong);

					//this updates the current position of in the color array and will be used when the ball is drawn
					//if the array hits the last color then it resets the position to allow infinite looping through the colors
					if (currentColorIndex == len-1){
						currentColorIndex = 0;
					}
					else
					{
						currentColorIndex += 1;
					}
				}
			}

			//logic checking for a win condition
			//if the ball hits the left screen
			if(ball.x<0)
			{							
				//plays an sfx, using the bool so it only plays once
				if (scored ==false){
					PlaySound(winSound);
				}
				//upate a string that states the winner
				winnerText = rightWinText;
				//updating the bool so the win sound only plays once
				scored = true;
			}

			//win condition for the right side of the screen
			if(ball.x > GetScreenWidth())
			{
				//plays an sfx, using the bool so it only plays once
				if (scored ==false){
					PlaySound(winSound);
				}
				//upate a string that states the winner
				winnerText = leftWinText;
				//updating the bool so the win sound only plays once
				scored = true;
			}

			//logic to reset the game after a goal is scored
			//the winnerText string contains information and the player presses space the game resets
			//the winnerText is empty until a goal is scored so prevents the player resetting during play
			if (winnerText && IsKeyPressed(KEY_SPACE))
			{
				//resets the ball to its starting position and speed
				//ball position x
				ball.x = GetScreenWidth() / 2;
				//ball position y
				ball.y =GetScreenHeight() / 2;
				//ball speed x
				ball.SpeedX = 300;
				//ball position y
				ball.SpeedY = 300;

				//empties the winnerText string again
				winnerText = nullptr;

				//resets the bool for the game loop
				scored = false;

				//stops the winSound from playing if it still is
				StopSound(winSound);
			}
		}

		//rendering the game
		BeginDrawing();
			//draws a clear background//begins the rendering and creates a draw section.	
			ClearBackground(GetColor(0x052c46ff));
			
   			
			//draws the backgrounds twice for scrolling purposes
            DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

            // Draw midground image twice for scrolling purposes
            DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

            // Draw foreground image twice for scrolling purposes
            DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

			//the rendering while the game is running
			if(started == true){
				//draws the ball with the currently selected color in the colors array
				ball.Draw(colors[currentColorIndex]);

				//draws the left paddle	
				leftPaddle.Draw();
				//draws the right paddle	
				rightPaddle.Draw();

				//this logic displays text after a goal is scored
				if (winnerText)
				{					
					//displays the text of who winds and instructions to play again, both centred on the screen
					DrawText (winnerText, GetScreenWidth() / 2 -MeasureText(winnerText,largeFontSize) / 2, GetScreenHeight() / 2 -30, largeFontSize, RAYWHITE);
					//press space to start next round		
					DrawText (extraWinText, GetScreenWidth() / 2 - MeasureText(extraWinText, smallFontSize)/2, GetScreenHeight() / 2 +100, smallFontSize, RAYWHITE);
				}
			}
			//rendering for when the game first loads, before the player hits space on the start screen
			//draws all the text set at the top and centres it horizontally
			else{	
				//draws the title text and centres horizontally			
				DrawText (title, GetScreenWidth() / 2 - MeasureText(title, titleFontSize)/2, GetScreenHeight() / 2 - 100, titleFontSize, RAYWHITE);
				//draws the up instruction text and centres horizontally		
				DrawText (upInstruction, GetScreenWidth() / 2 - MeasureText(upInstruction,smallFontSize)/2, GetScreenHeight() / 2 + 50, smallFontSize, RAYWHITE);
				//draws the down instruction text and centres horizontally		
				DrawText (downInstruction, GetScreenWidth() / 2-MeasureText(downInstruction,smallFontSize)/2, GetScreenHeight() / 2 + 90, smallFontSize, RAYWHITE);
				//draws the start text and centres horizontally		
				DrawText (startInstruction, GetScreenWidth() / 2-MeasureText(startInstruction,smallFontSize)/2, GetScreenHeight() / 2 + 130, smallFontSize, RAYWHITE);			
			}
			
			//draws the fps rate if you hover it takes two arguments position x and y. X horizontal, y vertically. (0,0) 
			//corresponds to the left of the box. origin is the top left and y goes down as the number gets bigger.
			DrawFPS(10,10);
			//ends the drawing
		EndDrawing();
	
	}
	// Unload background texture
    UnloadTexture(background); 
	// Unload midground texture 
    UnloadTexture(midground);   
	// Unload foreground texture
    UnloadTexture(foreground);  

	//closes audio device
	CloseAudioDevice();
	//closes the window//de-initalizes the open window.
	CloseWindow ();
	return 0;
}