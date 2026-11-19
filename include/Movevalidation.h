#pragma once

#include "board.h"
bool check_if_impeded_by_ally_piece(board* b, int current_index);

bool check_if_we_can_move_to_destination(board* b, int current_index);
