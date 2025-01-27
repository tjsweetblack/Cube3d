#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
//gcc main.c -o game -I minilibx-linux -L minilibx-linux -lmlx -lXext -lX11 -lm


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MINIMAP_SCALE 4 
#define MINIMAP_SIZE 96 

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05


#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307


typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;

    double  posX, posY;       // Player position
    double  dirX, dirY;       // Player direction vector
    double  planeX, planeY;   // Camera plane
} t_game;

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int floorColor = 0xCCCCCC; // Light gray for the floor
int ceilingColor = 0x87CEEB; // Sky blue for the ceiling



// Pixel manipulation
void put_pixel(t_game *game, int x, int y, int color) {
    char *dst;

    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void clear_image(t_game *game, int color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            put_pixel(game, x, y, color);
        }
    }
}

void draw_minimap(t_game *game) {
    int color;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            color = (worldMap[x][y] > 0) ? 0xFFFFFF : 0x000000; // White for walls, black for empty space
            for (int i = 0; i < MINIMAP_SCALE; i++) {
                for (int j = 0; j < MINIMAP_SCALE; j++) {
                    put_pixel(game, x * MINIMAP_SCALE + i, y * MINIMAP_SCALE + j, color);
                }
            }
        }
    }

    // Draw player position
    int playerX = (int)(game->posX * MINIMAP_SCALE);
    int playerY = (int)(game->posY * MINIMAP_SCALE);
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            put_pixel(game, playerX + i, playerY + j, 0xFF0000); // Red for player
        }
    }

    // Draw field of view (rays)
    for (double angle = -0.5; angle <= 0.5; angle += 0.1) { // Adjust angle range for FOV width
    double rayDirX = game->dirX + game->planeX * angle;
    double rayDirY = game->dirY + game->planeY * angle;

    double posX = game->posX;
    double posY = game->posY;

    while (1) { // Continue until the ray hits a wall
        posX += rayDirX * 0.1; // Step the ray forward
        posY += rayDirY * 0.1;

        // Check if the ray hits a wall
        if (worldMap[(int)posX][(int)posY] > 0) {
            break; // Stop the ray on wall hit
        }

        // Draw the ray on the minimap
        int rayX = (int)(posX * MINIMAP_SCALE);
        int rayY = (int)(posY * MINIMAP_SCALE);
        put_pixel(game, rayX, rayY, 0x00FF00); // Green for field of view
    }
}
}
// Raycasting function
void raycast(t_game *game) {
	//clear_image(game, 0x000000);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        int color = 0xFFFFFF;
        if (side == 1) color = color / 2;

        for (int y = drawStart; y < drawEnd; y++) {
            put_pixel(game, x, y, color);
        }
    }
}

void render_floor_and_ceiling(t_game *game) {
    for (int y = 0; y < SCREEN_HEIGHT / 2; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // Draw ceiling (top half of the screen)
            put_pixel(game, x, y, 0x87CEEB); // Sky blue
        }
    }

    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // Draw floor (bottom half of the screen)
            put_pixel(game, x, y, 0xCCCCCC); // Light gray
        }
    }
}

// Render loop
int render_scene(t_game *game) {
	mlx_clear_window(game->mlx, game->win);
	render_floor_and_ceiling(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

// Handle key presses
int key_press(int keycode, t_game *game) {
    if (keycode == KEY_W) {
        if (worldMap[(int)(game->posX + game->dirX * MOVE_SPEED)][(int)game->posY] == 0)
            game->posX += game->dirX * MOVE_SPEED;
        if (worldMap[(int)game->posX][(int)(game->posY + game->dirY * MOVE_SPEED)] == 0)
            game->posY += game->dirY * MOVE_SPEED;
    }
    if (keycode == KEY_S) {
        if (worldMap[(int)(game->posX - game->dirX * MOVE_SPEED)][(int)game->posY] == 0)
            game->posX -= game->dirX * MOVE_SPEED;
        if (worldMap[(int)game->posX][(int)(game->posY - game->dirY * MOVE_SPEED)] == 0)
            game->posY -= game->dirY * MOVE_SPEED;
    }
    if (keycode == KEY_D) {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-ROT_SPEED) - game->dirY * sin(-ROT_SPEED);
        game->dirY = oldDirX * sin(-ROT_SPEED) + game->dirY * cos(-ROT_SPEED);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-ROT_SPEED) - game->planeY * sin(-ROT_SPEED);
        game->planeY = oldPlaneX * sin(-ROT_SPEED) + game->planeY * cos(-ROT_SPEED);
    }
    if (keycode == KEY_A) {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(ROT_SPEED) - game->dirY * sin(ROT_SPEED);
        game->dirY = oldDirX * sin(ROT_SPEED) + game->dirY * cos(ROT_SPEED);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(ROT_SPEED) - game->planeY * sin(ROT_SPEED);
        game->planeY = oldPlaneX * sin(ROT_SPEED) + game->planeY * cos(ROT_SPEED);
    }
    if (keycode == KEY_ESC) {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return 0;
}

// Initialize game
void init_game(t_game *game) {
    game->posX = 22;
    game->posY = 12;
    game->dirX = -1;
    game->dirY = 0;
    game->planeX = 0;
    game->planeY = 0.66;

    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
}

int main() {
    t_game game;

    init_game(&game);
    mlx_loop_hook(game.mlx, render_scene, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_loop(game.mlx);

    return 0;
}