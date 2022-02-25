#include <raylib.h>
#include <string>


const int window_width = 800;
const int window_height = 600;
const int font_size = 30;

int main(int argc, char* argv[]) {
	// use args to get rid of warnings
	if(argc == 0) return -1;
	if(std::string(argv[0]) == "") return -1;

	InitWindow(window_width, window_height, "GUI DEMO");
	SetTargetFPS(60);
	SetTraceLogLevel(LOG_DEBUG);



	while(!WindowShouldClose()) {
		// update code
		char fps_text[5];
		sprintf(fps_text, "%d", GetFPS());
		int fps_offset = MeasureText(fps_text, font_size);


		// draw code
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(fps_text, window_width - fps_offset, 0, font_size, RED);
		EndDrawing();
	}
}
