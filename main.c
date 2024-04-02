#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "kmeans.h"

#define K_CLUSTERS 10
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "K-means");

    int image_w = 200, image_h = 200;

    //--------------------------------------------------------------------------------------

    const char *img_path = "images/chrollo.jpg";
    Image image = LoadImage(img_path);
    Color dominant_colors[K_CLUSTERS];

    for (int i=0; i<K_CLUSTERS; i++) {
        dominant_colors[i] = BLACK;                 // default colors
    }

    Texture2D texture;

    if (!IsImageReady(image)) {
        printf("*****Image doesn't exist.*****\n");
    } else {

        ImageResize(&image, image_w, image_h);

        int n_points = image_w * image_h;
        Color *image_color_data = (Color *) malloc(n_points * sizeof(Color));
        for (int i=0; i<n_points; i++) {
            int row = (int) i / image_w;
            int col = (int) i % image_w;
            image_color_data[i] = GetImageColor(image, row, col);
        }
        getDominantColors(n_points, image_color_data, dominant_colors);
        free(image_color_data);

        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //----------------------------------------------------------------------------------
        ClearBackground(RAYWHITE);
        //----------------------------------------------------------------------------------
        if (IsTextureReady(texture)) {
            DrawTexture(texture, 0, 0, WHITE);
        }
        for (int i=0; i<K_CLUSTERS; i++) {
            DrawRectangle(i*50, SCREEN_HEIGHT-45, 45, 45, dominant_colors[i]);
        }
        //----------------------------------------------------------------------------------
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //----------------------------------------------------------------------------------
    UnloadTexture(texture);
    //----------------------------------------------------------------------------------
    CloseWindow();
    //----------------------------------------------------------------------------------
    return 0;
}
