#include "UI.h"
#include "Tree.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <iostream>
#include <queue>
#include <cmath>
#include <chrono>

Vector2 offset_to_circle(Vector2 from, Vector2 to, float radius) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float distance = sqrt(dx * dx + dy * dy);
    float scale = radius / distance;
    return { from.x + dx * scale, from.y + dy * scale };
}

int count_letter(Node* node, char target) {
    if (!node) return 0;

    int count = (node->data == target) ? 1 : 0;
    count += count_letter(node->left, target);
    count += count_letter(node->right, target);

    return count;
}

void draw_tree_recursive(Node* node, Vector2 pos, float horizontalOffset, float verticalStep, int level, Tree& tree) {
    if (!node) return;

    float nodeRadius = 30; 
    int letterCount = count_letter(tree.getRoot(), node->data);
  
    Color nodeColor = (letterCount > 1) ? ORANGE : LIGHTGRAY;
    DrawCircleV(pos, nodeRadius, nodeColor);
    DrawCircleLinesV(pos, nodeRadius, BLACK);

    
    DrawText(TextFormat("%c", node->data), pos.x - 8, pos.y - 10, 18, BLACK);

    
    float dynamicOffset = horizontalOffset / (1.2f + level * 0.3f); 

    float minOffset = 60;

    if (dynamicOffset < minOffset) {
        dynamicOffset = minOffset;
    }

    if (node->left) {
        Vector2 leftPos = { pos.x - dynamicOffset, pos.y + verticalStep };
        Vector2 lineStart = offset_to_circle(pos, leftPos, nodeRadius);
        Vector2 lineEnd = offset_to_circle(leftPos, pos, nodeRadius);

        DrawLineV(lineStart, lineEnd, DARKGRAY);
        draw_tree_recursive(node->left, leftPos, dynamicOffset, verticalStep, level + 1, tree); 
    }

    if (node->right) {
        Vector2 rightPos = { pos.x + dynamicOffset, pos.y + verticalStep };
        Vector2 lineStart = offset_to_circle(pos, rightPos, nodeRadius);
        Vector2 lineEnd = offset_to_circle(rightPos, pos, nodeRadius);

        DrawLineV(lineStart, lineEnd, DARKGRAY); 
        draw_tree_recursive(node->right, rightPos, dynamicOffset, verticalStep, level + 1, tree); 
    }
}

void UI(Tree tree) 
{
    int screenWidth = 1920;
    int screenHeight = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "TreeWords");

    SetTargetFPS(60);

    if (IsWindowResized() && !IsWindowFullscreen())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }

    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
        int display = GetCurrentMonitor();

        if (IsWindowFullscreen())
        {
            SetWindowSize(screenWidth, screenHeight);
        }
        else
        {
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }
        ToggleFullscreen();
    }

	Programm Pg;
	
    const char* Text;

    Pg.SetInW(1);
    Pg.SetDeD(1);

    std::string Word;


    while(Pg.GetInW())
    {
        std::cin >> Word;
        Pg.SetInW(0);
    }
    
    tree.InsertString(Word);
    Text = Word.c_str();
     
    std::chrono::microseconds duration;
    std::chrono::microseconds duration_str;

	while(Pg.GetRun())
	{
		BeginDrawing();
	
		rlDrawRenderBatchActive();
		Matrix proj = MatrixOrtho(0, 1920, 1080, 0, -1, 1);
		rlSetMatrixProjection(proj);
	
		ClearBackground(WHITE);
		
        
        if (!Pg.GetInW())
        {
            DrawText(Text, 50, 50, 40, BLACK);
            Vector2 a(960, 200);
            draw_tree_recursive(tree.getRoot(), a, 300, 70, 0, tree);
        }

		
        if (IsKeyPressed(65)) 
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (auto i : Word)
            {
                
                if (count_letter(tree.getRoot(), i) > 1)
                {
                    while (count_letter(tree.getRoot(), i) > 0)
                       tree.Delete(i);
                }
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            auto start_str = std::chrono::high_resolution_clock::now();
            std::string result;

            for (char c : Word) 
            {
                if (result.find(c) == 0)
                    result += c;
            }
            
            auto end_str = std::chrono::high_resolution_clock::now();
            
            duration_str = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            Pg.SetDeD(0);

        
        }
        
        if (!Pg.GetDeD()) 
        {
            DrawText("Duration of deleting duplicates from tree:", 50, 100, 25, BLACK);
            DrawText(TextFormat("%i", duration.count()), 600, 100, 27, ORANGE);
            DrawText("Duration of deleting duplicates from string:", 50, 130, 25, BLACK);
            DrawText(TextFormat("%i", duration_str.count()), 600, 130, 27, ORANGE);
        }

        EndDrawing();
        
        if (IsKeyPressed(256))
        {
            Pg.SetRun(0);
            return; 
        }
    }


	
}