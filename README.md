# Cube3D

A 3D graphical representation of a maze from a first-person perspective, inspired by the classic game Wolfenstein 3D. This project was developed as part of the 42 school curriculum. It utilizes the raycasting rendering technique to create the illusion of a three-dimensional space from a two-dimensional map.

 <!-- Replace with a link to a screenshot of your project -->

## Features

*   **Map Parsing**: Reads and validates `.cub` files containing map layouts, textures, and color configurations.
*   **3D Rendering**: Uses the Raycasting algorithm to render the game world.
*   **Player Controls**:
    *   Move forward (`W`), backward (`S`), and strafe left (`A`) and right (`D`).
    *   Rotate the camera with the left (`←`) and right (`→`) arrow keys.
*   **Texturing**: Applies different textures to walls based on their orientation (North, South, East, West).
*   **Floor and Ceiling**: Renders solid colors for the floor and ceiling.
*   **Error Handling**: Robust validation for map files and configurations.
*   **Graceful Exit**: Close the window or press `ESC` to exit the program cleanly, freeing all allocated resources.

## How It Works: The Raycasting Engine

Raycasting is a rendering technique that creates a 3D perspective from a 2D map. Instead of projecting a complex 3D world onto a 2D screen, it casts rays from the player's viewpoint for each vertical column of the screen to determine what is visible and how it should be drawn.

Our implementation follows these key steps for each frame:

1.  **Ray Calculation**: For every pixel column `x` on the screen, we calculate a ray's direction. This starts from the player's position (`player.x`, `player.y`) and extends outwards at an angle corresponding to that column. The field of view (FOV) determines the total angle covered by all rays.

2.  **Wall Detection (DDA Algorithm)**: We use a Digital Differential Analysis (DDA) algorithm to find the first wall the ray intersects.
    *   In `ft_oper_draw`, we initialize the ray's properties, including `delta_dist` (the distance the ray travels between grid lines) and `side_dist` (the distance to the first grid line).
    *   The `hit_wall` function then "steps" the ray through the grid, always advancing to the next nearest grid line (either horizontal or vertical) until it hits a map cell containing a wall (`'1'`). The `touch()` function is used for this check.

3.  **Distance Correction (Fixing the "Fisheye" Effect)**: Calculating the direct Euclidean distance from the player to the wall would create a "fisheye" lens distortion. To prevent this, we calculate the *perpendicular* distance. The `fixed_dist` function achieves this by multiplying the Euclidean distance by the cosine of the angle between the ray and the player's central view vector.

    ```c
    // From /home/belmiro/Cube3d/sources/raycasting.c
    float	fixed_dist(t_other_data *data, t_game *game)
    {
        float	delta_x;
        float	delta_y;
        float	angle;
        float	fix_dist;
    
        delta_x = data->ray_x - game->player.x;
        delta_y = data->ray_y - game->player.y;
        angle = atan2(delta_y, delta_x) - game->player.angle;
        fix_dist = distance(delta_x, delta_y) * cos(angle);
        return (fix_dist);
    }
    ```

4.  **Calculating Slice Height**: The corrected distance is then used to determine the height of the vertical wall slice to be drawn on the screen. The closer the wall, the taller the slice.

    ```c
    // From /home/belmiro/Cube3d/sources/utils2.c
    void	ft_init_var_cal(t_player *player, t_game *game, t_other_data *data)
    {
        // ...
        player->dist = fixed_dist(data, game);
        // ...
        player->height = (BLOCK / player->dist) * (WIDTH / 2);
        player->start_y = (HEIGHT - player->height) / 2;
        player->end = player->start_y + player->height;
    }
    ```

5.  **Texture Mapping**:
    *   We determine which wall face was hit (North, South, East, or West) based on which direction the DDA algorithm was stepping when it found the wall. This is handled in `ft_define_color`.
    *   We calculate the exact x-coordinate (`tex_x`) on the texture by finding the precise point of intersection on the wall.
    *   For each pixel in the vertical screen column, we calculate the corresponding y-coordinate (`tex_y`) on the texture and draw the pixel with the correct color from the loaded texture data.

This process is repeated for all screen columns, from left to right, to construct the final 3D image.

## Getting Started

### Prerequisites

*   A C compiler (like `gcc` or `clang`)
*   `make`
*   X11 libraries (required by the MiniLibX graphics library)

### Compilation

1.  Clone the repository:
    ```sh
    git clone <repository_url> cube3d
    cd cube3d
    ```

2.  Compile the project using the provided `Makefile`:
    ```sh
    make
    ```
    This will create the `cub3d` executable. Other available commands are `make clean`, `make fclean`, and `make re`.

### Running the Game

To run the game, provide a path to a valid `.cub` map file as an argument:

```sh
./cub3d maps/your_map.cub
```

### Controls

*   **W**: Move forward
*   **S**: Move backward
*   **A**: Strafe left
*   **D**: Strafe right
*   **← (Left Arrow)**: Rotate camera left
*   **→ (Right Arrow)**: Rotate camera right
*   **ESC**: Exit the game

## Map File Format (`.cub`)

The map file defines the game environment. It must contain the following elements, in any order, before the map grid itself:

*   **Texture Identifiers**:
    *   `NO ./path/to/north_texture.xpm`
    *   `SO ./path/to/south_texture.xpm`
    *   `WE ./path/to/west_texture.xpm`
    *   `EA ./path/to/east_texture.xpm`

*   **Color Identifiers**:
    *   `F R,G,B` (Floor color, e.g., `F 220,100,0`)
    *   `C R,G,B` (Ceiling color, e.g., `C 225,30,0`)

*   **The Map Grid**:
    *   Composed of `1` (walls), `0` (empty space), spaces, and a single player start position.
    *   Player start position is marked with `N`, `S`, `E`, or `W` for the initial orientation.
    *   The map must be "closed" or surrounded by walls (`1`). Any open spaces leading to the "void" will result in an error.

#### Example `map.cub`:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111111111
1000100000000001
10N0100100000001
1000000000000001
1111111111111111
```

## Project Structure

```
.
├── includes/         # Header files (.h)
├── sources/          # Source code files (.c)
├── libft/            # Custom C library
├── mlx/              # MiniLibX graphics library
├── textures/         # Example textures
├── maps/             # Example maps
└── Makefile          # Build rules
```