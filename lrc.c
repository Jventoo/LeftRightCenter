#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_AMOUNT 3

typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

const char *names[] = { "Happy", "Sleepy", "Sneezy", "Dopey", "Bashful",
  "Grumpy", "Doc", "Mirror Mirror", "Snow White", "Wicked Queen" };

//
// Returns the position of the player to the left.
//
// pos: The position of the current player.
// players : The number of players in the game.
//
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

//
// Returns the position of the player to the right .
//
// pos: The position of the current player .
// players : The number of players in the game .
//
uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}

//
// Transfer money from one player to another, update the balance array,
// and return whether to increment player count (did a player come back from $0?).
//
// from_pos: Position money is departing.
// to_pos: Position money is going.
// bals: Pointer to dynamic array where balances are stored.
//
bool transfer_money(uint32_t from_pos, uint32_t to_pos, uint32_t *bals) {
  (*(bals + from_pos))--;
  uint32_t startToBal = (*(bals + to_pos))++;
  printf("gives $1 to %s ", names[to_pos]);

  return (startToBal == 0);
}

int main(void) {
  uint32_t seed, num_players, pot = 0, current_player = 0;

  printf("Random Seed: ");
  int result = scanf("%d", &seed);
  if (result != 1) {
    printf("Bad Seed! Exiting...\n");
    return 1;
  }

  srand(seed);

  bool input_success = false;
  while (!input_success) {
    printf("How many players? ");
    scanf("%d", &num_players);

    if (num_players > 1 && num_players < 11) {
      input_success = true;
    } else {
      printf("Error! Must be an integer [2,10]!\n");
    }
  }

  // Default initialize player balances to defined STARTING_AMOUNT
  uint32_t *balances = calloc(num_players, sizeof(uint32_t));
  for (uint32_t i = 0; i < num_players; ++i) {
    *(balances + i) = STARTING_AMOUNT;
  }

  uint32_t players_left = num_players;
  while (players_left > 1) {
    uint32_t right_pos = right(current_player, num_players);
    uint32_t left_pos = left(current_player, num_players);

    // Number of die rolls = Max(StartAmt, Balance)
    uint32_t bal = *(balances + current_player);
    uint32_t die_rolls = (bal < STARTING_AMOUNT) ? bal : STARTING_AMOUNT;

    printf("%s rolls... ", names[current_player]);
    for (uint32_t i = 0; i < die_rolls; ++i) {
      enum faciem die_result = die[rand() % 6];

      switch (die_result) {
      case LEFT:
        if (transfer_money(current_player, left_pos, balances)) {
          ++players_left;
        }
        break;
      case RIGHT:
        if (transfer_money(current_player, right_pos, balances)) {
          ++players_left;
        }
        break;
      case CENTER:
        (*(balances + current_player))--;
        pot++;
        printf("puts $1 in the pot ");
        break;
      case PASS:
        printf("gets a pass ");
        break;
      default:
        printf("ERROR ");
      }
    }
    printf("\n");

    if (*(balances + current_player) == 0) {
      --players_left;
    }

    // Right player's turn if they're in, loop clockwise otherwise
    if (*(balances + right_pos) > 0) {
      current_player = right_pos;
    } else {
      uint32_t i = right_pos;
      bool found = false;
      while (!found) {
        i = right(i, num_players);
        if (*(balances + i) > 0) {
          found = true;
        }
      }

      current_player = i;
    }
  }

  // Print the win condition
  printf("%s wins the $%d pot with $%d left in the bank!\n",
      names[current_player], pot, *(balances + current_player));

  free(balances);
  return 0;
}
