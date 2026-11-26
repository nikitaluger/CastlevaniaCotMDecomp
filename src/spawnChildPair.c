/* Spawn two children of a parent entity. def1/def2 describe each child (speed and
 * position offsets) and slot1/slot2 are the slots to store them in. The parent's
 * spawn-state word selects the type-A helper (bit 2) or the type-B helper (bit 3);
 * its origin word mirrors a child's offset when X (bit 4) or Y (bit 5) is flagged.
 * A null definition cancels the corresponding pending spawn. */
struct SpawnState {
    u16 flags;
    u8 _pad2[6];
    s32 x;
    s32 y;
    u8 _pad10[8];
    s32 child;
};
struct OriginFlags {
    u8 _pad0[2];
    u16 flags;
};
struct SpawnDef {
    u8 _pad0[6];
    s16 speedX;
    s16 speedY;
    s16 xOffset;
    s16 yOffset;
};
struct SpawnerEntity {
    u8 _pad0[0x38];
    struct OriginFlags *origin;
    struct SpawnState *spawnState;
};
extern void spawnChildA(void *, s32, s16, s16, s16, s16);
extern void spawnChildB(void *, s32, s16, s16, s16, s16);
inline int flippedCoord(s32 fixed, s16 offset) { return (fixed >> 16) - offset; }
void spawnChildPair(struct SpawnerEntity *parent, struct SpawnDef *def1, struct SpawnDef *def2, s32 slot1, s32 slot2) {
  struct SpawnState *state = parent->spawnState; u16 flags; s32 xWhole; s32 yWhole; s32 useChildB;
  if (def1 == 0) { state->flags = (state->flags & SPAWN_STATE_CLEAR_CHILDREN) | SPAWN_STATE_ACTIVE; state->child = 0; }
  if (def2 == 0) { state->flags = (state->flags & SPAWN_STATE_CLEAR_CHILDREN) | SPAWN_STATE_ACTIVE; state->child = 0; }
  flags = state->flags;
  if (flags & SPAWN_STATE_CHILD_A) {
    struct OriginFlags *origin = parent->origin; s32 childX; s32 childY;
    if (origin->flags & ORIGIN_FLIP_X) { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = flippedCoord(fixedPos, def1->xOffset); }
    else { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = (xWhole = fixedPos >> 16) + def1->xOffset; }
    if (origin->flags & ORIGIN_FLIP_Y) { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = flippedCoord(fixedPos, def1->yOffset); }
    else { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = (fixedPos >> 16) + def1->yOffset; }
    spawnChildA(parent, slot1, childX, childY, def1->speedX, def1->speedY);
    if (origin->flags & ORIGIN_FLIP_X) { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = flippedCoord(fixedPos, def2->xOffset); }
    else { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = (fixedPos >> 16) + def2->xOffset; }
    if (origin->flags & ORIGIN_FLIP_Y) { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = flippedCoord(fixedPos, def2->yOffset); }
    else { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = (fixedPos >> 16) + def2->yOffset; }
    spawnChildA(parent, slot2, childX, childY, def2->speedX, def2->speedY);
  } else { do { useChildB = flags & SPAWN_STATE_CHILD_B; } while (0); if (useChildB) {
    struct OriginFlags *origin = parent->origin; s32 childX; s32 childY;
    if (origin->flags & ORIGIN_FLIP_X) { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = flippedCoord(fixedPos, def1->xOffset); }
    else { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } do { childX = (fixedPos >> 16) + def1->xOffset; } while (0); }
    if (origin->flags & ORIGIN_FLIP_Y) { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = flippedCoord(fixedPos, def1->yOffset); }
    else { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = (fixedPos >> 16) + def1->yOffset; }
    spawnChildB(parent, slot1, childX, childY, def1->speedX, def1->speedY);
    if (origin->flags & ORIGIN_FLIP_X) { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = flippedCoord(fixedPos, def2->xOffset); }
    else { s32 fixedPos = state->x; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childX = (fixedPos >> 16) + def2->xOffset; }
    if (origin->flags & ORIGIN_FLIP_Y) { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = flippedCoord(fixedPos, def2->yOffset); }
    else { s32 fixedPos = state->y; if (fixedPos < 0) { fixedPos += FIXED_TRUNC_BIAS; } childY = (yWhole = fixedPos >> 16) + def2->yOffset; }
    spawnChildB(parent, slot2, childX, childY, def2->speedX, def2->speedY);
    } }
}
