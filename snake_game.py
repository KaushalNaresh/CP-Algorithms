from enum import Enum

class IllegalStateError(RuntimeError):
    pass

class GameState(Enum):

    DEATH_BY_COLLISION_WITH_BODY = "DEATH_BY_COLLISION_WITH_BODY"
    DEATH_BY_COLLISION_WITH_WALL = "DEATH_BY_COLLISION_WITH_WALL"
    WON = "WON"
    CONTINUE = "CONTINUE"

class SnakeGame:

    def __init__(self, rows, cols, snacks):
        self._rows = rows
        self._cols = cols
        self._grid = [[0 for _ in range(cols)] for _ in range(rows)]
        self._snake = [[0, 0]]
        self._food_left = len(snacks)

        for snack_r, snack_c in snacks:
            self._grid[snack_r][snack_c] = 1

    def _check_game_state(self):
        snake_head_r, snake_head_c = self._snake[-1]

        if snake_head_r < 0 or snake_head_r >= self._rows or snake_head_c < 0 or snake_head_c >= self._cols:
            return GameState.DEATH_BY_COLLISION_WITH_WALL
        if [snake_head_r, snake_head_c] in self._snake[:-1]:
            return GameState.DEATH_BY_COLLISION_WITH_BODY
        if self._food_left == 0:
            return GameState.WON
        else:
            return GameState.CONTINUE
        
    def _eat_food(self, r, c):

        if r >= 0 and r < self._rows and c >= 0 and c < self._cols and self._grid[r][c] == 1:
            self._food_left -= 1
            self._grid[r][c] = 0
            return True
        return False
    
    def _move_in_direction(self, r, c):

        self._snake.append([r, c])
        if not self._eat_food(r, c):
            self._snake.pop(0) 
    
    def move(self, direction):

        snake_head_r, snake_head_c = self._snake[-1]

        match direction:
            case "UP":
                new_r, new_c = snake_head_r-1, snake_head_c  
                self._move_in_direction(new_r, new_c) 
                return self._check_game_state()

            case "DOWN":
                new_r, new_c = snake_head_r+1, snake_head_c   
                self._move_in_direction(new_r, new_c) 
                return self._check_game_state()
            
            case "LEFT":
                new_r, new_c = snake_head_r, snake_head_c-1  
                self._move_in_direction(new_r, new_c) 
                return self._check_game_state()

            case "RIGHT":
                new_r, new_c = snake_head_r, snake_head_c+1  
                self._move_in_direction(new_r, new_c) 
                return self._check_game_state()
            
            case _:
                raise IllegalStateError(direction)

rows, cols = 5, 6
# 8 snacks total; the last one ([4,5]) is intentionally left uneaten
snacks = [
    [0,1],[0,2],[0,3],[0,4],  # grow along top row
    [2,4],[2,3],[2,2],        # grow again on row 2
    [4,5]                     # remains uneaten
]
snake_game = SnakeGame(rows, cols, snacks)
moves = [
    "RIGHT","RIGHT","RIGHT","RIGHT",  # eat 4 snacks on top row
    "DOWN","DOWN",                    # move to row 2 and eat [2,4]
    "LEFT","LEFT",                    # eat [2,3], [2,2]
    "UP","UP",                        # reposition (no food)
    "RIGHT",                          # reposition (no food)
    "DOWN",                           # reposition (no food)
    "LEFT"                            # COLLIDES with body at [1,2]
]

for direction in moves:
    try:
        game_state = snake_game.move(direction)
        print(direction, game_state, snake_game._snake)
        if game_state != GameState.CONTINUE:
            print(game_state)
            break
    except IllegalStateError as ex:
        print("Invalid direction", ex)