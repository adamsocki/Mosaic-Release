




#include "structs.cpp"

MyData *Data = NULL;
#include "LoadSprites.cpp"
#include "EntityManager.cpp"

Sprite lemonSprite;
OBJMesh stallMesh = {};
Sprite stallTexture;
real32 rotation = {};

void MyInit() {
    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData *)Game->myData;

    LoadSprites();
    InitializeEntityManager();
    InitializeEntityBuffers();

    
    // All sprites must be png files
    // You provide the path to the png like "directory/to/my/file/file_name.png"
    // In this case I have put the pngs inside the "data" directory.
    LoadSprite(&Data->sprite, "data/galaga_ship.png");
    LoadSprite(&Data->sprite2, "data/van_gogh.png");
    LoadSprite(&stallTexture, "data/stallTexture.png");

    LoadSprite(&lemonSprite, "data/bad_lemon.png");

    LoadSoundClip("data/sfx/flute_breathy_c4.wav", &Data->sound);

    //TinyObject();
    stallMesh = LoadOBJModel("data/stall.obj");

    InitOBJMesh(&stallMesh);

}


vec2 position = V2(4, 0);

vec2 scale = V2(1, 1);

void MyGameUpdate() {
    // This sets the background color. 
    ClearColor(RGB(0.0f, 0.0f, 0.0f));


    if (InputHeld(Keyboard, Input_UpArrow)) {
        position.y += 2 * Game->deltaTime;
    }

    // position in pixels
    vec2 mousePos = Input->mousePosNormSigned;
    mousePos.x =-mousePos.x * 8;
    mousePos.y = mousePos.y * 4.5f;

    //DrawRect(V2(-2, -2), scale, RGB(0, 1, 1));

    //DrawRect(V2(-2, -2), scale, V4(0.0f, 1.0f, 1.0f, 0.5f));

    //DrawCoolRect(V2(0, 0), V2(1, 1), 0, RGB(0.0f, 0.3f, 0.3f));


    if (InputPressed(Keyboard, Input_Space)) {
        PlaySound(&Game->audioPlayer, Data->sound, 1.0f, true);
    }
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 28.0f;
    real32 rotationSpeed = 0.4f;

    if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;

    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraPosition.x += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraPosition.x -= cameraSpeed * Game->deltaTime;

    }
    
    // scale.x -= 0.2f * Game->deltaTime;
    // scale.y -= 0.2f * Game->deltaTime;
    // once scale goes negative we will have inverted the shape,
    // it will continue to grow.

    //position.y -= 2 * Game->deltaTime;

    // things are drawn in the order you call the functions.
    // The latest draw call will be on top of all previous, and so on.

    // (0, 0) is center of the screen
    // increasing values of y move up
    // We have negative coordinates
    // The width of our screen is 16 (-8 to 8) (left to right)
    // The height of our screen is 9 (-4.5 to 4.5) (bottom to top)

    // version that doesnt take an angle.    
    rotation += (1.0f) * Game->deltaTime;
    DrawOBJModel(&stallMesh, V3(0), V3(10.0f, 10.0f, 10.0f), rotation, RGB(1.0f, 0.3f, 0.3f), &stallTexture);
    DrawSprite(V2(0), V2(4, 4), DegToRad(0), &Data->sprite2);

    /*DrawSprite(mousePos, V2(0.5f, 0.5f), &lemonSprite);
    DrawRect(V2(0, 0), V2(1, 1), RGB(1.0f, 0.3f, 0.3f));
    DrawSprite(position, V2(0.5f, 0.5f), &Data->sprite);
    DrawSprite(mousePos, V2(0.5f, 0.5f), &Data->sprites.testSprite);*/
}
