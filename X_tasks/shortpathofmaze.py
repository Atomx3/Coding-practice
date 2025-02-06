def find_shortest_path(maze):
    # Find the entrance and exit coordinates
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if maze[i][j] == 'S':
                start_x, start_y = i, j
            elif maze[i][j] == 'T':
                target_x, target_y = i, j

    # Initialize a queue for BFS
    queue = [(start_x, start_y)]

    # Initialize a visited set to keep track of visited points
    visited = set()
    visited.add((start_x, start_y))

    # Initialize a dictionary to store the parent of each point
    parent = {}

    # Define possible moves (up, down, left, right)
    moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    # Perform BFS
    while queue:
        x, y = queue.pop(0)
        for dx, dy in moves:
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < len(maze) and 0 <= new_y < len(maze[0]) and maze[new_x][new_y] == '.' and (new_x, new_y) not in visited:
                queue.append((new_x, new_y))
                visited.add((new_x, new_y))
                parent[(new_x, new_y)] = (x, y)  # Update parent dictionary

    # Reconstruct the path from exit to entrance
    path = []
    curr_x, curr_y = target_x, target_y
    while (curr_x, curr_y) != (start_x, start_y):
        path.append((curr_x, curr_y))
        curr_x, curr_y = parent[(curr_x, curr_y)]

    # Reverse the path to get the correct order
    path.reverse()

    # Convert path to 2D array of integers
    path_array = [[0] * len(maze[0]) for _ in range(len(maze))]
    for x, y in path:
        path_array[x][y] = 1

    return path_array

# Example maze
maze = [
    ['S', '.', '.', '.', '#', '.', '.'],
    ['#', '#', '.', '#', '.', '#', '.'],
    ['.', '.', '.', '.', '.', '.', '.'],
    ['.', '#', '#', '#', '#', '#', '.'],
    ['.', '.', '.', '.', '.', '.', '.'],
    ['.', '#', '#', '#', '#', '#', '.'],
    ['.', '.', '.', '.', '.', '.', 'T']
]

# Find the shortest path
shortest_path = find_shortest_path(maze)

# Print the path
for row in shortest_path:
    print(row)
