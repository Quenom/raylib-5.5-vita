#include <stdio.h>
#include <psp2/kernel/clib.h>
#include "raylib.h"

int _newlib_heap_size_user = 12 * 1024 * 1024;
int sceLibcHeapSize = 8 * 1024 * 1024;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 544;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Set MSAA 4X hint before windows creation

    InitWindow(screenWidth, screenHeight, "raylib audio example");

    InitAudioDevice();      // Initialize audio device


    Music music = LoadMusicStream("resources/country.mp3");
    Sound fxWav = LoadSound("resources/spring.wav");         // Load WAV audio file
    Sound fxOgg = LoadSound("resources/target.ogg");

    music.looping=false;
    float pitch = 1.0f;
    bool pause = false;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateMusicStream(music);
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        {
            sceClibPrintf("1 ");
            StopMusicStream(music);
            PlayMusicStream(music);
            pause = false;
            sceClibPrintf("done\n");
        }
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)){
            sceClibPrintf("2 ");
            pause = !pause;
            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
            sceClibPrintf("done\n");
        }
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
            sceClibPrintf("3 ");
            PlaySound(fxWav);
            sceClibPrintf("done\n");
        }
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
            sceClibPrintf("4 ");
            PlaySound(fxOgg);
            sceClibPrintf("done\n");
        }
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)){
            sceClibPrintf("5 ");
            pitch +=0.1f;
            SetSoundPitch(fxWav, pitch);
            SetSoundPitch(fxOgg, pitch);
            SetMusicPitch(music, pitch);
            sceClibPrintf("done\n");
        }
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
            sceClibPrintf("6 ");
            pitch -=0.1f;
            SetSoundPitch(fxWav, pitch);
            SetSoundPitch(fxOgg, pitch);
            SetMusicPitch(music, pitch);
            sceClibPrintf("done\n");
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Press square to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);
            DrawText("Press cross to PLAY the OGG sound!", 200, 220, 20, LIGHTGRAY);
            DrawText("Press trianle to PLAY/PAUSE the mp3!", 200, 240, 20, LIGHTGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadMusicStream(music);
    UnloadSound(fxWav);
    UnloadSound(fxOgg);
    CloseAudioDevice();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}