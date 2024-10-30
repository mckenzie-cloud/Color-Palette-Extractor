#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "kmeans.h"

#define K_CLUSTERS 8
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define IMG_SIZE 200

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "K-means");

    int image_w = 200, image_h = 200;

    //--------------------------------------------------------------------------------------

    const char *img_path = "images/pic5.jpg";
    Image image = LoadImage(img_path);
    Image img_cpy = ImageCopy(image);

    Color dominant_colors[K_CLUSTERS];

    for (int i=0; i<K_CLUSTERS; i++) {
        dominant_colors[i] = BLACK;                 // default colors
    }

    Texture2D texture;

    if (!IsImageReady(image)) {
        printf("*****Image doesn't exist.*****\n");
    } else {

        ImageResize(&image, image_w, image_h);
        ImageResize(&img_cpy, IMG_SIZE, IMG_SIZE);

        int n_points = IMG_SIZE * IMG_SIZE;
        Color *image_color_data = (Color *) malloc(n_points * sizeof(Color));
        for (int i=0; i<n_points; i++) {
            int row = (int) i / IMG_SIZE;
            int col = (int) i % IMG_SIZE;
            image_color_data[i] = GetImageColor(img_cpy, row, col);
        }
        getDominantColors(n_points, image_color_data, dominant_colors, 8);
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
