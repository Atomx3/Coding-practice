#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// Define constants for different click results and board states
#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

// Define the board structure
struct _board_t {
  int ** board; // 2D array representing the board
  int width; // Width of the board
  int height; // Height of the board
  int totalMines; // Total number of mines on the board
};

typedef struct _board_t board_t;

// Function to add a random mine to the board
void addRandomMine(board_t * b) {
  int x;
  int y;
  // We could have a board too small for the number of mines that we request.
  // Try w*h*10 times before we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while(b->board[y][x] == HAS_MINE); // Ensure the mine is placed in an empty spot
  b->board[y][x] = HAS_MINE;
}

// Function to create and initialize the board
board_t * makeBoard(int w, int h, int numMines) {
  board_t * b = malloc(sizeof(*b)); // Allocate memory for the board structure
  if (b == NULL) {
    fprintf(stderr, "Failed to allocate memory for board structure\n");
    exit(EXIT_FAILURE);
  }
  b->width = w; // Set the width of the board
  b->height = h; // Set the height of the board
  b->totalMines = numMines; // Set the total number of mines
  b->board = malloc(h * sizeof(*(b->board))); // Allocate memory for the rows
  if (b->board == NULL) {
    fprintf(stderr, "Failed to allocate memory for board rows\n");
    free(b);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < h; i++) {
    b->board[i] = malloc(w * sizeof(*(b->board[i]))); // Allocate memory for the columns
    if (b->board[i] == NULL) {
      fprintf(stderr, "Failed to allocate memory for board columns\n");
      for (int j = 0; j < i; j++) {
        free(b->board[j]); // Free previously allocated rows in case of failure
      }
      free(b->board);
      free(b);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < w; j++) {
      b->board[i][j] = UNKNOWN; // Initialize all cells to UNKNOWN
    }
  }
  for (int i = 0; i < numMines; i++) {
    addRandomMine(b); // Add mines to the board
  }
  return b; // Return the initialized board
}


// Function to print the current state of the board
void printBoard(board_t * b) {    
  int found = 0;
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y % 100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == KNOWN_MINE) {
        printf("*");
        found++;
      } else if (b->board[y][x] < 0) {
        printf("?");
      } else if (b->board[y][x] == 0) {
        printf(" ");
      } else {
        printf("%d", b->board[y][x]);
      }
    }
    printf("\n");
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");

  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\nFound %d of %d mines\n", found, b->totalMines);
}

// Function to count the number of mines around a given cell
int countMines(board_t * b, int x, int y) {
  int count = 0;
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (IS_MINE(b->board[ny][nx])) {
          count++; // Increment count if a mine is found
        }
      }
    }
  }
  return count; // Return the total count of mines around the cell
}


// Function to handle a click on the board
int click(board_t * b, int x, int y) {
  if (x < 0 || x >= b->width || y < 0 || y >= b->height) {
    return CLICK_INVALID;
  }
  if (b->board[y][x] == KNOWN_MINE) {
    return CLICK_KNOWN_MINE;
  }
  if (b->board[y][x] == HAS_MINE) {
    return CLICK_LOSE;
  }
  if (b->board[y][x] != UNKNOWN) {
    return CLICK_CONTINUE;
  }

  b->board[y][x] = countMines(b, x, y);
  return CLICK_CONTINUE;
}

// Function to check if the player has won the game
int checkWin(board_t * b) {
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == UNKNOWN) {
        return 0; // Return 0 if any cell is still UNKNOWN
      }
    }
  }
  return 1; // Return 1 if all cells are revealed
}


// Function to free the memory allocated for the board
void freeBoard(board_t * b) {
  for (int i = 0; i < b->height; i++) {
    free(b->board[i]); // Free each row
  }
  free(b->board); // Free the array of rows
  free(b); // Free the board structure
}


// Function to read an integer from the input
int readInt(char ** linep, size_t * lineszp) {
  if (getline(linep, lineszp, stdin) == -1) {
    fprintf(stderr, "End of file from keyboard reading a number. Quitting\n");
    exit(EXIT_FAILURE);
  }
  char * endptr = NULL;
  long int x = strtol(*linep, &endptr, 10);
  if (endptr == *linep) {
    fprintf(stderr, "You did not enter any valid number\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (*endptr != '\n') {
    fprintf(stderr, "Input was not entirely a number (junk at end)\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (x > INT_MAX) {
    fprintf(stderr, "%ld is too big for an int!\n", x);
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  return x;
}

// Function to reveal cells around a given cell
void doReveal(board_t * b, int x, int y, int revealMines) {
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (revealMines) {
          assert(b->board[ny][nx] != UNKNOWN);
          if (b->board[ny][nx] == HAS_MINE) {
            b->board[ny][nx] = KNOWN_MINE;
          }
        } else {
          assert(b->board[ny][nx] != HAS_MINE);
          if (b->board[ny][nx] == UNKNOWN) {
            b->board[ny][nx] = countMines(b, nx, ny);
          }
        }
      }
    }
  }
}

// Function to reveal cells if certain conditions are met
int maybeReveal(board_t * b, int x, int y) {
  int unknownSquares = 0;
  int knownMines = 0;
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (b->board[ny][nx] == UNKNOWN || b->board[ny][nx] == HAS_MINE) {
          unknownSquares++;
        } else if (b->board[ny][nx] == KNOWN_MINE) {
          knownMines++;
        }
      }
    }
  }
  assert(knownMines + unknownSquares >= b->board[y][x]);
  assert(knownMines <= b->board[y][x]);
  if (unknownSquares > 0) {
    int revealMines = (knownMines + unknownSquares == b->board[y][x]);
    int allKnown = knownMines == b->board[y][x];
    if (revealMines || allKnown) {
      assert(!revealMines || !allKnown);
      doReveal(b, x, y, revealMines);
      return 1;
    }
  }
  return 0;
}

// Function to determine known mines on the board
void determineKnownMines(board_t * b) {
  int foundMore = 0;
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] >= 0) {
        foundMore = maybeReveal(b, x, y) || foundMore;
      }
    }
  }
  if (foundMore) {
    determineKnownMines(b);
  }
}

// Function to reveal all mines on the board
void revealMines(board_t * b) {
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == HAS_MINE) {
        b->board[y][x] = KNOWN_MINE;
      }
    }
  }
}

  // Function to handle a player's turn
int playTurn(board_t * b, char ** linep, size_t *lineszp) {
  printf("Current board:\n");
  printBoard(b);
  printf("x coordinate:\n");
  int x = readInt(linep, lineszp);
  printf("y coordinate:\n");
  int y = readInt(linep, lineszp);
  int result = click(b, x, y);
  determineKnownMines(b);
  if (result == CLICK_LOSE) {
    printf("Oh no! That square had a mine. You lose!\n");
    revealMines(b);
    printBoard(b);
    return 1;
  } else if (result == CLICK_INVALID) {
    printf("That is not a valid square, please try again\n");
  } else if (result == CLICK_KNOWN_MINE) {
    printf("You already know there is a mine there!\n");
  } else if (checkWin(b)) {
    printBoard(b);
    printf("You win!\n");
    return 1;
  }
  return 0;
}

// Main function to run the Minesweeper game
int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: minesweeper width height numMines\n");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int numMines = atoi(argv[3]);
  if (width <= 0 || height <= 0 || numMines <= 0) {
    fprintf(stderr, "Width, height, and numMines must all be positive ints\n");
    return EXIT_FAILURE;
  }
  char * line = NULL;
  size_t linesz = 0;

  do {
    board_t * b = makeBoard(width, height, numMines);
    int gameOver = 0;
    while (!gameOver) {
      gameOver = playTurn(b, &line, &linesz);
    }
    freeBoard(b);
    do {
      printf("Do you want to play again?\n");
    } while (getline(&line, &linesz, stdin) == -1);
  } while (line[0] == 'Y' || line[0] == 'y');
  free(line);
  return EXIT_SUCCESS;
}
