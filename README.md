# 🎮 Cub3D

![Score](https://img.shields.io/badge/Score-125%2F125-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![42](https://img.shields.io/badge/42-Project-black)
![Team](https://img.shields.io/badge/Team-2_people-orange)

## 📌 Project Goal

**Cub3D** is a first-person 3D game engine written in C, inspired by **Wolfenstein 3D** — the grandfather of all FPS games. Using the **MiniLibX** library and a technique called **raycasting**, a 2D map is rendered in real time as a 3D perspective view, with textured walls, sprites, doors, and a dynamic UI.

---

## 🧠 Key Concepts

### Raycasting
Raycasting is a rendering technique that simulates 3D by casting one ray per vertical screen column from the player's position. For each ray:
1. Calculate the direction based on the player's angle and FOV
2. Step through the 2D map grid using **DDA (Digital Differential Analysis)** until a wall is hit
3. Compute the distance to the wall → determine the height of the vertical slice to draw
4. Sample the correct pixel from the wall texture (based on where the ray hit)

The result is a full frame rendered column by column — no actual 3D geometry, just math.

### DDA Algorithm
The **Digital Differential Analysis** algorithm efficiently steps a ray through a grid cell by cell, always jumping to the next horizontal or vertical grid line — whichever is closer. It avoids floating-point stepping and is fast enough for real-time rendering.

### Wall Textures
Each wall face (North, South, East, West) has its own **XPM texture**. When a ray hits a wall, the x-coordinate of the hit point determines which column of the texture to sample. The texture column is then stretched or compressed to the wall slice height.

### Sprites & Z-Buffer
Sprites are 2D objects (enemies, items) that always face the player. Rendering them correctly requires:
- **Distance sorting**: draw sprites from farthest to nearest
- **Z-buffer**: store the distance of each wall column so sprites behind walls are clipped correctly — without it, sprites would appear through walls

### Camera Plane & FOV
The player has a **position**, a **direction vector**, and a **camera plane** perpendicular to the direction. The ratio between the camera plane length and direction length defines the FOV. Rotating the player rotates both vectors simultaneously.

### Map Validation
The `.cub` map file must be fully parsed and validated before rendering:
- The map must be **enclosed** by walls on all sides (no open edges)
- Texture paths and floor/ceiling RGB colors must be present and valid
- Only valid characters (`0`, `1`, `N/S/E/W`, `2-5` for sprites, `D` for doors) are allowed

### MiniLibX
Same windowing library as fract-ol — pixel buffer writing, event hooks, image blitting. See fract-ol notes for the core MiniLibX API.

---

## 🚀 Usage

### Compilation
```bash
make        # mandatory
make bonus  # with sprites, doors, mouse rotation
```

### Running
```bash
./cub3D map.cub
```

### Map Format (`.cub`)
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 50,50,50

111111
100001
1000N1
100001
111111
```

- `1` = Wall, `0` = Empty space
- `N/S/E/W` = Player start position and initial direction
- **Bonus**: `2–5` = Sprites, `D` = Door

### Controls

| Input | Action |
|---|---|
| `W` `A` `S` `D` | Move forward / backward / strafe left / right |
| `←` `→` | Rotate camera |
| Mouse | Rotate camera (bonus) |
| `Q` / `E` | Decrease / increase mouse sensitivity |
| `O` | Open door |
| `ESC` | Exit cleanly |

---

## 🏗️ Implementation Logic

### Overall Architecture
```
main()
 ├── Parse .cub file
 │    ├── Read texture paths + floor/ceiling colors
 │    └── Read and validate map grid
 ├── Init MiniLibX (window + image buffer)
 ├── Init player (position, direction, camera plane)
 ├── mlx_loop_hook → render_frame()
 │    ├── For each screen column x:
 │    │    ├── Compute ray direction
 │    │    ├── DDA → find wall hit + distance
 │    │    ├── Compute wall slice height
 │    │    ├── Sample texture column
 │    │    └── Draw floor + wall + ceiling slice
 │    ├── Sort + draw sprites (Z-buffer)
 │    └── mlx_put_image_to_window
 ├── mlx_hook → keyboard + mouse events
 └── mlx_loop()
```

### Render Pipeline per Frame
1. Clear the image buffer
2. Draw **ceiling** (top half) and **floor** (bottom half) with flat colors
3. Cast one ray per column → draw textured wall slices
4. Sort sprites by distance → draw each sprite column, clipped by Z-buffer
5. Overlay UI (score, progress bar)
6. Blit to window

---

## ⚠️ Common Mistakes & Tricky Points

- **Map validation — enclosed check**: the most error-prone part. A common approach is flood-fill from the player position — if it reaches the map boundary, the map is not closed. Check all 4 directions including diagonal adjacency.
- **Fisheye effect**: using the raw Euclidean distance to the wall instead of the **perpendicular distance** causes walls to appear curved. Always use the perpendicular distance (project onto the camera direction).
- **Texture coordinate calculation**: the x-offset within a texture depends on whether the ray hit a vertical or horizontal wall face, and the exact fractional hit position. Getting this wrong produces smeared or flipped textures.
- **Sprite Z-clipping**: without a proper Z-buffer, sprites will bleed through walls. Store the wall distance for every column and skip sprite pixels whose column distance is farther than the wall.
- **Rotation matrix**: rotating the direction and camera plane vectors requires applying a 2D rotation matrix simultaneously to both — applying them separately introduces drift.
- **Player starting inside a wall**: validate the player's starting cell is `0` during map parsing.

---

## ✅ Evaluation Checklist

- [ ] Window opens and renders the map correctly
- [ ] All 4 wall faces show different textures (N/S/E/W)
- [ ] Movement and rotation work smoothly
- [ ] Map validation rejects unclosed maps and invalid characters
- [ ] Floor and ceiling colors render correctly
- [ ] `ESC` and window close button exit cleanly, no leaks
- [ ] **Bonus**: sprites render correctly and are clipped by walls (Z-buffer)
- [ ] **Bonus**: doors open with `O`
- [ ] **Bonus**: mouse rotation works

---

## 🛠️ Useful Debug Commands

```bash
# Memory leaks
valgrind --leak-check=full ./cub3D map.cub

# Test invalid maps
./cub3D unclosed_map.cub     # should print error
./cub3D no_player.cub        # should print error
./cub3D bad_texture.cub      # should print error

# Test minimal valid map
./cub3D pink_pony_club.cub
```
