#include <raylib.h>

constexpr int window_width{1200};
constexpr int window_height{1000};
constexpr int cell_size{5};
constexpr int num_rows{window_width/cell_size};
constexpr int num_columns{window_height/cell_size};
int active_cells{0};
int current_rule{1};

Color dft = DARKBLUE;
Color act_cellcolor = WHITE;
Color text_color = YELLOW;
Color bg_text_color = RED;
bool background_mode{false};

int grid[num_rows][num_columns];

void Reset() {
  for (int r{0}; r < num_rows; r++) {
    for (int c{0}; c < num_columns; c++) {
      grid[r][c] = GetRandomValue(0, 1);
      if (grid[r][c] == 1)
        active_cells += 1;
    }
  }
}

void Draw(){
    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){
            DrawRectangle(r * cell_size, c * cell_size, cell_size, cell_size, (grid[r][c] == 1) ? act_cellcolor : dft);
        }
    }


}

int CountNeighbours(int r, int c){
    int count{0};
    int range{1};
    int neighborR;
    int neighborC;

    for(int dr{-range}; dr <= range; dr++){
        for(int dc{-range}; dc <= range; dc++){
            if(dr == 0 && dc == 0)continue;
            neighborR = (r + dr + num_rows) % num_rows;
            neighborC = (c + dc + num_columns) % num_columns;
            count += grid[neighborR][neighborC];
        }
    }
    return count;
}

void Update(){
    int tempgrid[num_rows][num_columns];

    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){

            int neighbours = CountNeighbours(r,c);

            if(current_rule==1){ //Default rule
                if(neighbours == 3)tempgrid[r][c] = 1;
                else if(neighbours == 2)tempgrid[r][c] = grid[r][c];
                else tempgrid[r][c] = 0;
            }

            else if(current_rule==2){ //High Life
                if(neighbours == 3 || neighbours == 6)tempgrid[r][c] = 1;
                else if(neighbours == 2)tempgrid[r][c] = grid[r][c];
                else tempgrid[r][c] = 0;
            }
            else if(current_rule==3){ //Seeds
                if(neighbours==2)tempgrid[r][c] = 1;
                else tempgrid[r][c]=0;
            }
            else if(current_rule==4){ //Life without death
                if(grid[r][c]==1)tempgrid[r][c]=1;
                else if(neighbours==3)tempgrid[r][c]=1;
                else tempgrid[r][c]=0;
            }
            else if(current_rule==5){
                if(grid[r][c]==1){
                    if(neighbours == 3 || neighbours == 4 || neighbours == 6 || neighbours == 7 || neighbours == 8)tempgrid[r][c] = 1;
                    else tempgrid[r][c] = 0;
                }
                else{
                    if(neighbours == 3 || neighbours == 6 || neighbours == 7 || neighbours == 8){
                        tempgrid[r][c] = 1;
                    }
                    else tempgrid[r][c] = 0;
                }
            }



        }
    }
    active_cells = 0;
    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){
            grid[r][c] = tempgrid[r][c];
            if(grid[r][c] == 1) active_cells+=1;
        }
    }
}


int main(){
    InitWindow(window_width, window_height, "game of life");
    SetTargetFPS(30);

    Reset();

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_R))Reset();
        if(IsKeyPressed(KEY_B))background_mode=!background_mode;
        if(!background_mode){
            for(int i{1}; i <= 5; i++){
                if(IsKeyPressed(KEY_ZERO + i))current_rule = i;
            }
        }

        BeginDrawing();
        ClearBackground(dft);

        Update();
        Draw();

        DrawText(TextFormat("Active Cells:%i",active_cells), 20, 20, 20, text_color);
        if(background_mode){
            DrawText("Background Mode", 20, 60, 25, bg_text_color);
            if(IsKeyPressed(KEY_ONE)){dft=DARKBLUE;act_cellcolor=WHITE;bg_text_color=RED;text_color=YELLOW;}
            if(IsKeyPressed(KEY_TWO)){dft=DARKBROWN;act_cellcolor=RED;bg_text_color=RED;text_color=YELLOW;}
            if(IsKeyPressed(KEY_THREE)){dft=DARKPURPLE;act_cellcolor=YELLOW;bg_text_color=RAYWHITE;text_color=RAYWHITE;}
            if(IsKeyPressed(KEY_FOUR)){dft=RAYWHITE;act_cellcolor=DARKGREEN;bg_text_color=BLACK;text_color=BLACK;}
        }
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}
