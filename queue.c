#include "queue.h"
#include "linked_list.h"
#include "tile_game.h"
#include <stdbool.h>

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
  size_t val = remove_from_head(&q->data);
  struct game_state state = deserialize(val);

  return state;
}

int number_of_moves(struct game_state start) {
  struct queue q = {.data = {.head = NULL}};
  uint64_t visited[1000000] = {0};
  int visited_count = 0;
  
  visited[visited_count++] = serialize(start);
  enqueue(&q, start);
  
  while (q.data.head != NULL) {
    struct game_state current = dequeue(&q);
    
    if (current.empty_row == 3 && current.empty_col == 3) {  // Solved state ish
      bool solved = true;
      for (int r = 0; r < 4 && solved; r++) {
        for (int c = 0; c < 4 && solved; c++) {
          if (r == 3 && c == 3) continue;
          if (current.tiles[r][c] != r * 4 + c + 1) { solved = false; }  // Acutally check that its solved
        }
      }
      if (solved) {
        free_list(q.data);
        return current.num_steps;
      }
    }
    
    struct game_state next_state;
    uint64_t serialized_next;
    
    // try all moves now, check if different, check if visited, queue if not visited and different
    next_state = current;
    move_up(&next_state);
    serialized_next = serialize(next_state);
    if (serialized_next != serialize(current)) {
      bool isNew = true;
      for (int i = 0; i < visited_count; i++) {
        if (visited[i] == serialized_next) {
          isNew = false;
          break;
        }
      }
      
      if (isNew) {
        visited[visited_count++] = serialized_next;
        enqueue(&q, next_state);
      }
    }
    
    next_state = current;
    move_down(&next_state);
    serialized_next = serialize(next_state);
    if (serialized_next != serialize(current)) {
      bool isNew = true;
      for (int i = 0; i < visited_count; i++) {
        if (visited[i] == serialized_next) {
          isNew = false;
          break;
        }
      }
      
      if (isNew) {
        visited[visited_count++] = serialized_next;
        enqueue(&q, next_state);
      }
    }
    
    next_state = current;
    move_left(&next_state);
    serialized_next = serialize(next_state);
    if (serialized_next != serialize(current)) {
      bool isNew = true;
      for (int i = 0; i < visited_count; i++) {
        if (visited[i] == serialized_next) {
          isNew = false;
          break;
        }
      }
      
      if (isNew) {
        visited[visited_count++] = serialized_next;
        enqueue(&q, next_state);
      }
    }
    
    next_state = current;
    move_right(&next_state);
    serialized_next = serialize(next_state);
    if (serialized_next != serialize(current)) {
      bool isNew = true;
      for (int i = 0; i < visited_count; i++) {
        if (visited[i] == serialized_next) {
          isNew = false;
          break;
        }
      }
      
      if (isNew) {
        visited[visited_count++] = serialized_next;
        enqueue(&q, next_state);
      }
    }
  }
  return -1;  // No solution!!
}
