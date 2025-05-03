#include "../include/lib.h"



int worldMap[mapHeight][mapWidth] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// --- Drawing Helper Functions (Corrected float handling) ---

void draw_vertical_line(GameState game, int x, float start_y, float end_y, int color)
{
    int y;
    float tmp;

    if (start_y > end_y)
    {
        tmp = start_y;
        start_y = end_y;
        end_y = tmp;
    }
    y = (int)start_y;
    while (y <= (int)end_y)
    {
        mlx_pixel_put(game.mlx, game.win, x, y, color);
        y++;
    }
}

void draw_vertical_direction_line(GameState game, int x, float start_y, float end_y, int color)
{
    int y;
    float tmp;

    if (start_y > end_y)
    {
        tmp = start_y;
        start_y = end_y;
        end_y = tmp;
    }
    y = (int)start_y;
    while (y <= (int)end_y)
    {
        mlx_pixel_put(game.mlx, game.win, x, y, color);
        y++;
    }
}

void draw_horizontal_line(GameState game, int y, float start_x, float end_x, int color)
{
    int x;
    float tmp;

    if (start_x > end_x)
    {
        tmp = start_x;
        start_x = end_x;
        end_x = tmp;
    }
    x = (int)start_x;
    while (x <= (int)end_x)
    {
        mlx_pixel_put(game.mlx, game.win, x, y, color);
        x++;
    }
}

void draw_horizontal_direction_line(GameState game, int y, float start_x, float end_x, int color)
{
    int x;
    float tmp;

    if (start_x > end_x)
    {
        tmp = start_x;
        start_x = end_x;
        end_x = tmp;
    }
    x = (int)start_x;
    while (x <= (int)end_x)
    {
        mlx_pixel_put(game.mlx, game.win, x, y, color);
        x++;
    }
}


// --- Game Drawing Functions ---

void draw_walls(GameState game){
    int x = 0;
    int y = 0;
    while (y < mapHeight)
    {
        x = 0; // Reset x for each row
        while( x < mapWidth){
            if (game.map[y][x] == 1) // Access map correctly: [row][column] or [y][x]
            {
                // Draw the wall image at the pixel coordinates corresponding to the map tile
                mlx_put_image_to_window(game.mlx, game.win, game.img, x * TILE_SIZE, y * TILE_SIZE);
            }
            x++;
        }
        y++;
    }
}

void draw_grid(GameState game)
{
    float x, y;

    for (x = 0; x <= screenWidth; x += TILE_SIZE)
    {
        draw_vertical_line(game, (int)x, 0, screenHeight, 0xFF0000); // Red, cast x to int
    }

    for (y = 0; y <= screenHeight; y += TILE_SIZE)
    {
        draw_horizontal_line(game, (int)y, 0, screenWidth, 0xFF0000); // Red, cast y to int
    }
}

void draw_circle(GameState game, int center_x, int center_y, int radius, int color) {
    int x;
    int  y;
    float distance;

    for (y = center_y - radius; y <= center_y + radius; y++) {
        for (x = center_x - radius; x <= center_x + radius; x++) {
            distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
            if (distance <= radius) {
                mlx_pixel_put(game.mlx, game.win, x, y, color);
            }
        }
    }
}

void draw_player(GameState game)
{
    int radius = (int)(TILE_SIZE / 6); // Player circle radius relative to tile size
    int color = 0x00FF00; // Green

    draw_circle(game, (int)game.pos_x, (int)game.pos_y, radius, color);
    // Drawing direction lines from player center
    
}

// --- Raycasting Function ---

void cast_ray(GameState *game)
{
    float rayPosX = game->pos_x;
    float rayPosY = game->pos_y;

    // Current cell of the ray
    int mapX = (int)(rayPosX / TILE_SIZE);
    int mapY = (int)(rayPosY / TILE_SIZE);

    // Step direction (either +1 or -1)
    int stepX = 0;
    int stepY = 0;

    // Hit point coordinates
    float hitX = rayPosX;
    float hitY = rayPosY;

    // Determine step direction based on player direction
    if (game->direction == 'N') {
        stepY = -1;
        stepX = 0; // Axis-aligned ray
        hitX = rayPosX; // X is constant
    } else if (game->direction == 'S') {
        stepY = 1;
        stepX = 0; // Axis-aligned ray
        hitX = rayPosX; // X is constant
    } else if (game->direction == 'E') {
        stepX = 1;
        stepY = 0; // Axis-aligned ray
        hitY = rayPosY; // Y is constant
    } else if (game->direction == 'W') {
        stepX = -1;
        stepY = 0; // Axis-aligned ray
        hitY = rayPosY; // Y is constant
    } else {
        // Should not happen with N, S, E, W directions, but good practice
        return;
    }

    // DDA loop
    while (mapX >= 0 && mapX < mapWidth && mapY >= 0 && mapY < mapHeight && game->map[mapY][mapX] == 0)
    {
        if (stepX != 0) // Horizontal ray (East or West)
        {
            mapX += stepX;
            // Calculate hitX at the edge of the next tile
            if (stepX == 1) // Moving East, hit is at the left edge of the wall tile
                hitX = mapX * TILE_SIZE;
            else // Moving West, hit is at the right edge of the wall tile
                hitX = (mapX + 1) * TILE_SIZE;
            // hitY remains rayPosY
        }
        else if (stepY != 0) // Vertical ray (North or South)
        {
            mapY += stepY;
             // Calculate hitY at the edge of the next tile
            if (stepY == 1) // Moving South, hit is at the top edge of the wall tile
                hitY = mapY * TILE_SIZE;
            else // Moving North, hit is at the bottom edge of the wall tile
                hitY = (mapY + 1) * TILE_SIZE;
            // hitX remains rayPosX
        }
    }

    // Draw a white circle at the hit point if a wall was hit within bounds
    if (mapX >= 0 && mapX < mapWidth && mapY >= 0 && mapY < mapHeight)
    {
         draw_circle(*game, (int)hitX, (int)hitY, (int)(TILE_SIZE / 10), 0xFFFFFF); // White circle, small radius
    }
    if(game->direction ==  'E'){
        draw_horizontal_direction_line(*game, (int)game->pos_y, (int)game->pos_x, hitX, 0x00FF00);
    }else if(game->direction ==  'W'){
        draw_horizontal_direction_line(*game, (int)game->pos_y, (int)game->pos_x, hitX, 0x00FF00);
    }else if(game->direction ==  'N'){
        draw_vertical_direction_line(*game, (int)game->pos_x, (int)game->pos_y, hitY, 0x00FF00);
    }else if(game->direction ==  'S'){
        draw_vertical_direction_line(*game, (int)game->pos_x, (int)game->pos_y, hitY, 0x00FF00);
    }
    game->hit_distance = sqrt(pow(hitX - game->pos_x, 2) + pow(hitY - game->pos_y, 2));
}


// --- Redraw Function ---

void redraw_game(GameState *game)
{
    mlx_clear_window(game->mlx, game->win);
    draw_grid(*game);
    draw_walls(*game); // draw walls using the loaded image
    draw_player(*game);
    cast_ray(game); // Cast and draw the ray/hit point
    draw_line();
}

// --- Event Handler ---

int move_player(int keycode, void *param)
{
    GameState *game = (GameState *)param;
    float new_pos_x = game->pos_x;
    float new_pos_y = game->pos_y;
    float move_step = game->move_speed; // Use moveSpeed from GameState

    // Basic WASD key codes (these might vary based on your system and mlx version)
    // Consider using X11 keysyms for better portability if available via <X11/keysym.h>
    // For example: XK_w, XK_a, XK_s, XK_d, XK_Escape
    int key_w = 13; // Common keycode for 'w' on some systems
    int key_a = 0;  // Common keycode for 'a' on some systems
    int key_s = 1;  // Common keycode for 's' on some systems
    int key_d = 2;  // Common keycode for 'd' on some systems
    int key_esc = 53; // Common keycode for ESC

    // Using common ASCII values as fallback/alternative key identifiers
    if (keycode == 'w' || keycode == 'W' || keycode == key_w){
        new_pos_y -= move_step;
        game->direction = 'N';
    } // Move up
    else if (keycode == 's' || keycode == 'S' || keycode == key_s){
        new_pos_y += move_step;
        game->direction = 'S';
    } // Move down
    else if (keycode == 'a' || keycode == 'A' || keycode == key_a){
        new_pos_x -= move_step;
        game->direction = 'W';
    } // Move left
    else if (keycode == 'd' || keycode == 'D' || keycode == key_d){
        new_pos_x += move_step;
        game->direction = 'E';
    } // Move right
    else if (keycode == key_esc) // ESC key to exit
    {
        if (game->img)
            mlx_destroy_image(game->mlx, game->img); // Destroy image when done
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        if (game->mlx)
             mlx_destroy_display(game->mlx); // Uncomment if needed and available
        exit(0);
    }

    // Collision detection
    // Calculate potential new map coordinates
    int map_x = (int)(new_pos_x / TILE_SIZE);
    int map_y = (int)(new_pos_y / TILE_SIZE);

    // Check if the potential new position is within map bounds and is not a wall
    // Ensure we don't access worldMap out of bounds
     if (map_x >= 0 && map_x < mapWidth && map_y >= 0 && map_y < mapHeight && game->map[map_y][map_x] == 0)
    {
        game->pos_x = new_pos_x;
        game->pos_y = new_pos_y;
    }


    // Redraw the game state
    redraw_game(game);
    return (0); // Event successfully handled
}

// --- Main Function ---

int main()
{
    GameState game;

    game.move_speed = TILE_SIZE / 4.0; // Use float division for smoother movement
    game.pos_x = 1.5 * TILE_SIZE; // Use TILE_SIZE
    game.pos_y = 1.5 * TILE_SIZE; // Use TILE_SIZE
    game.direction = 'E'; // Initialize direction
    game.map = worldMap;
    game.img = NULL; // Initialize image pointer to NULL

    printf("Game Map:\n");
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            printf("%d ", worldMap[y][x]);
        }
        printf("\n");
    }

    printf("\nMap Width: %d\n", mapWidth);
    printf("Map Height: %d\n", mapHeight);

    printf("Tile at (0,0): %d\n", worldMap[0][0]);
    printf("Tile at (5,2): %d\n", worldMap[5][2]);
    printf("ciel of 5.6: %f\n", floor(5.6));

    game.mlx = mlx_init();
    if (game.mlx == NULL)
    {
        printf("Error initializing mlx\n");
        return 1;
    }

    // Load the wall image ONCE during initialization
    int img_width; // Variables to store image dimensions (required by mlx_xpm_file_to_image)
    int img_height;
    // Adjust the path "./coin.xpm" if your image is elsewhere
    game.img = mlx_xpm_file_to_image(game.mlx, "./coin.xpm", &img_width, &img_height);
    if (game.img == NULL)
    {
        printf("Error loading wall image. Make sure coin.xpm is in the correct directory.\n");
        // Handle error: potentially destroy window/mlx and exit
        // No window yet, so just destroy mlx display if possible
        // mlx_destroy_display(game.mlx); // Uncomment if needed and available
        return 1;
    }
    // You might want to check if img_width and img_height match TILE_SIZE here
    if (img_width != TILE_SIZE || img_height != TILE_SIZE) {
        printf("Warning: Wall image dimensions (%dx%d) do not match TILE_SIZE (%dx%d).\n", img_width, img_height, TILE_SIZE, TILE_SIZE);
        // You might choose to exit or try to scale the image if mlx supports it
    }


    game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "Game");
    if (game.win == NULL)
    {
        printf("Error creating window\n");
        // Clean up loaded image if window creation fails
        if (game.img)
             mlx_destroy_image(game.mlx, game.img); // Destroy image when done
        // mlx_destroy_display(game.mlx); // Uncomment if needed and available
        return 1;
    }

    redraw_game(&game); // Initial draw

    mlx_hook(game.win, 02, 1L<<0, move_player, &game); // KeyPress event (X_EVENT_KEY_PRESS is 2)

    mlx_loop(game.mlx);

    // Proper cleanup after mlx_loop exits (e.g., on window close if hooked)
    // If using a hook for window close (event 17), this part might not be reached
    if (game.img)
        mlx_destroy_image(game.mlx, game.img); // Destroy image when done
    if (game.win)
        mlx_destroy_window(game.mlx, game.win);
    if (game.mlx)
        mlx_destroy_display(game.mlx); // Uncomment if needed and available

    return 0;
}