#include "dice.h"

#include <nikola/nikola.h>

/// ----------------------------------------------------------------------
/// Dice functions

void dice_create(Dice* dice, const nikola::Vec3& start_pos, const nikola::ResourceID& skin) {
  // Dice init 
  nikola::memory_zero(dice, sizeof(Dice));

  nikola::transform_translate(dice->transform, start_pos);
  nikola::transform_scale(dice->transform, nikola::Vec3(1.0f));
  
  dice->skin_id = skin;
  dice->is_active = true;
}

void dice_throw(Dice& dice) {
  // @TODO (Dice): Expand upon this later to take in other 
  // multipliers into account when generating a value.
  dice.face_value = nikola::random_u32(1, 6);

  // @TODO (Dice): Also the dice should rotate from here... 
}

/// Dice functions
/// ----------------------------------------------------------------------
