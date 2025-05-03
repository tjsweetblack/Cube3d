/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-23 19:15:53 by joandre           #+#    #+#             */
/*   Updated: 2025-03-23 19:15:53 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIB_H
# include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> // For bool type
#include <string.h>  // For memset
#include <sys/time.h> // For time tracking (optional, using fixed step for simplicity)

// --- Constants ---
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 480
#define MAP_WIDTH 32
#define MAP_HEIGHT 30
#define CELL_SIZE 16
#define PLAYER_SIZE 4 // Radius for drawing player circle
#define RAY_HIT_SIZE 4 // Radius for drawing ray hit circle
#define MAX_RAY_DISTANCE 100.0f // Max distance for raycast in map units

// --- Colors (ARGB format for mlx) ---
#define COLOR_BLACK 0x00000000
#define COLOR_BLUE  0x000000FF // Solid Blue
#define COLOR_DARK_GREY 0x00A9A9A9 // Dark Grey
#define COLOR_WHITE 0x00FFFFFF
#define COLOR_RED   0x00FF0000
#define COLOR_GREEN 0x0000FF00
#define COLOR_YELLOW 0x00FFFF00

// --- Key Codes (These might vary depending on your system/keyboard) ---
// Common keys for Linux/macOS (check your mlx documentation if needed)
// Using standard X.org keycodes where possible, or common mappings
#define KEY_ESC 53 // Escape key to close window
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

// --- Mouse Button Codes ---
#define MOUSE_LEFT_CLICK 1
#define MOUSE_RIGHT_CLICK 2
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5

// --- MLX Event Codes ---
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define MOUSE_PRESS 4
#define MOUSE_RELEASE 5
#define MOUSE_MOVE 6
#define DESTROY_NOTIFY 17 // Window close event

// --- Struct Definitions ---
#define mapWidth 24
#define mapHeight 24
#define screenHeight 24 * 30
#define screenWidth 24 * 30
#define TILE_SIZE 30 // Define the size of each tile in pixels

// Simple vector structs
typedef struct {
    float x;
    float y;
} Vec2f;

typedef struct {
    int x;
    int y;
} Vec2i;

// Structure to hold MLX context and game state
typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *addr; // Pointer to image data
    int bits_per_pixel;
    int line_length;
    int endian;
    float pos_x;
    float pos_y;
    char direction;
    float move_speed;
    int (*map)[mapWidth]; // Corrected type: pointer to an array of mapWidth integers
    Vec2i map_size;
    Vec2i cell_size;

    Vec2f player_pos; // Player position in map units (float)
    Vec2f mouse_pos;  // Mouse position in window pixels
    Vec2f mouse_cell; // Mouse position in map cell units (float)

    // Raycasting results
    Vec2f ray_intersection;
    bool tile_found;
    float hit_distance;

    // Input state tracking
    bool keys_held[256]; // Simple array to track key presses (adjust size if needed)
    bool mouse_buttons_held[5]; // Track mouse button presses (1: Left, 2: Right)

} GameState;

#endif
