#pragma once

#include <nikola/nikola.h>

/// ----------------------------------------------------------------------
/// Consts

const nikola::u32 DICES_MAX = 6;

/// Consts
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// Dice 
struct Dice {
  nikola::Transform transform{};
  nikola::ResourceID skin_id{};

  nikola::u8 face_value = 0;
  bool is_active;
};
/// Dice 
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// Dice functions

void dice_create(Dice* dice, const nikola::Vec3& start_pos, const nikola::ResourceID& skin);

void dice_throw(Dice& dice);

/// Dice functions
/// ----------------------------------------------------------------------
