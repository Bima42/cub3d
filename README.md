# cub3d
The problematic was : re-create a Wolfenstein-3D like, using the MLX library. 
Only C was allowed.

## Install

```
git clone git@github.com:Bima42/cub3d.git
make
./cub3d map.cub
```

Note : Use W, A, S, D key to move. Use left and right arrow to rotate camera. Esc quit the game.

## Resume
At the beginning, we decided to treat parsing part before talk about raycasting etc
Then, we split works in two parts : initialisation part (graphics, mlx ...) and raycasting part

## Parsing
There is some important point to note :
- map file is .cub only
- this map file is strict :
	- begin by texture path (N, S, E, W)
	- then some rgb data for ceiling and floor
	- empty lines can be found between those datas
	- map architecture
- map :
	- must be surrounded by '1'
	- only one player spawn (N, S, E or W indicate player orientation)

Strategy use for map checking : for every rows and colums (x and y)
- start with skip white spaces
- then we have to hit a wall
- we skip all char except wall (1) until white space or \0
- if the char in pos - 1 is not a wall, it's an error
- the fact is if we hit a wall we have to found another one, walls works by pair. If the second wall was not hit, row (or column) is false

During this check, we extract the higher x and y to reformat_map, using white_spaces to reformat and put every lines ar the same length.

Last line is filled with \0.
	
## Raycasting
Transforming a limited form of data into a three-dimensional projection with the help of tracing rays from the view point into the viewing volume. 
Main principle :  rays can be cast and traced in groups based on certain geometric constraints.
A ray from the pixel through the camera is obtained and the intersection of all objects in the picture is computed.

We have to create a maze world that has the following geometric constraints:
- Walls are always at 90° angle with the floor.
- Walls are made of cubes that have the same size.
- Floor is always flat.
Need to define some attributes :
- Player/viewer’s height, player’s field of view (FOV), and player’s position.
- Projection plane’s dimension.
- Relationship between player and projection plane.
FOV of 60 is generally a good choice.
Player height reprensent half of window height.

The following illustrates steps:
- Based on the viewing angle, subtract 30 degrees (half of the FOV).
- Starting from column 0:
- Cast a ray.
- Trace the ray until it hits a wall.
- Record the distance to the wall (the distance = length of the ray).
- Add the angle increment so that the ray moves to the right
- Repeat step 2 and 3 for each subsequent column until all rays are cast.

This figure show a really good method to understand how checking horizontal and vertical intersections.

![Horizontal_check](/assets/horizontal_check.png)

![Vertical_check](/assets/vertical_check.png)

When horizontal and vertical intersections are merged, you have to check the lowest distance between player and wall using Pythagore theorem.
Now you know which side of the wall you have to drawn.

This way will show distortion called "fish-eye".
To remove the viewing distortion : ```correct_dist = distorted_dist * cos(angle);```

## Sources
- https://permadi.com/1996/05/ray-casting-tutorial-3/#CREATING%20A%20WORLD
- https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/
