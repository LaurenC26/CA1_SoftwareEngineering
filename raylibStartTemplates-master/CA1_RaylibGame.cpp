#include "raylib.h"
//includes the raylib library

//creates a main function
int main(){
//defines the window width and height.
 const int windowWidth{500};
 const int windowHeight{500};
//initializes a window
InitWindow(windowWidth,windowHeight,"Lauren's Game");
//sets the Frame rate of the project
SetTargetFPS(60);  
//render loop for the window.
	while(!WindowShouldClose()){
//begins the rendering and creates a draw section.	
BeginDrawing();
ClearBackground(WHITE); 
EndDrawing();
//ends the rendering
}
//de-initalizes the open window.
CloseWindow();
}