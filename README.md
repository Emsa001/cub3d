# Cub3d - Our very first raycaster

Cub3d is one of the 42 core corricumul projects, and second graphical project using MLX library (again...)


#### A 3d game, how intresting?!

Creating everything from very beggining, learning exactly how first 3d games were created. This was definitly one of the most intresting project I did so far.
From handling threads for optimization to playing around with textures for our doors - I loved it all.


## Getting Started

1. **Clone the repository**:
    ```sh
    git clone https://github.com/Emsa001/cub3d
    cd cub3d
    ```

2. **Build the project**:
    ```sh
    make
    ```
    or
    ```sh
    make bonus
    ```

3. **Run the project**:
    ```sh
    ./cub3d
    ```

## All Features  

### HUD  

#### 🎮 Main Menu  
Obviously, this is a real game, and every REAL game needs to have its menu!  
![Map selector](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/select_map.gif)

#### ⚙️ Quality settings  
Obviously, this is a real game, and every REAL game needs... you know, quality settings.  
![Quality Settings](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/quality.gif)

#### 🗺️ Minimap  
Obviously, this is a real game, and... Minimap!  
![Minimap](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/minimap.gif)

---

### Player  

#### 🏃 Player Movement  
While testing our game, we often needed to walk to different locations. It was annoying and boring. So, we implemented this amazing movement system that includes running, sliding, and jumping! It's just sooo satisfying!  
![Player Movement](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/movement.gif)

---

### Map Parts  

#### 🚪 Portals (aka "Levels")  
We limited our maps to a maximum of 3 levels, but this can be changed in the code. Going through a portal takes you to the next level, and all textures change.  
![Portals](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/portals.gif)
![Open Portals](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/open_portals.gif)

#### 🚪 Doors  
Doors work only if they’re placed next to a wall (so they actually do something). Moreover, they can be placed and opened from all 4 sides.  
![Doors](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/doors.gif)

#### 🧱 Building and Destroying Blocks  
There's a building system! Isn't that cool? You can place blocks wherever you want—no need to align them to a grid. All placed blocks can be destroyed or moved.  
![Blocks](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/blocks.gif)

---

### Economy  

#### 💰 Generators  
Generators are the only actual 3D objects. They don’t always face the player.  
They’re used to earn money and can be upgraded in 4 different categories.  
Generators update every second and increase the player's balance.  
![Generators](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/generators.gif)

#### 🛒 Shop  
Here, you can spend money to earn more money, open portals to go to the next level, buy speed shoes, potions, or TORCHES.  
Torches are amazing! They actually light up the place and are visible from far, far away.  

![Math](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/math.gif)
![potions](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/potions.gif)

#### 🎲 Gambling  
We have permissions for that.  
![Gambling](https://github.com/Emsa001/cub3d_recordings/raw/refs/heads/main/gamble.gif)

## License
This project is licensed under the MIT License. See the [MIT](https://choosealicense.com/licenses/mit/) file for details.
