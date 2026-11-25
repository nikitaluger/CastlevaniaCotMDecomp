/* Spawns two child entities from a parent: def1/def2 describe each child and slot1/slot2
 * receive the created objects. The parent's spawn-state flag bit 4 selects one spawn
 * routine and bit 8 selects the other. */
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
extern void sub_080155CC(void *, s32, s16, s16, s16, s16);
extern void sub_0801569C(void *, s32, s16, s16, s16, s16);
inline int FlippedCoord(s32 fixed, s16 offset) { return (fixed >> 16) - offset; }
void sub_0801534C(struct SpawnerEntity *parent, struct SpawnDef *def1, struct SpawnDef *def2, s32 slot1, s32 slot2) {
  struct SpawnState *state = parent->spawnState; u16 flags; s32 xInt; s32 yInt; s32 modeB;
  if (def1 == 0) { state->flags = (state->flags & 0xFFF3) | 1; state->child = 0; }
  if (def2 == 0) { state->flags = (state->flags & 0xFFF3) | 1; state->child = 0; }
  flags = state->flags;
  if (flags & 4) {
    struct OriginFlags *origin = parent->origin; s32 x; s32 y;
    if (origin->flags & 0x10) { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = FlippedCoord(fixed, def1->xOffset); }
    else { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = (xInt = fixed >> 16) + def1->xOffset; }
    if (origin->flags & 0x20) { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = FlippedCoord(fixed, def1->yOffset); }
    else { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = (fixed >> 16) + def1->yOffset; }
    sub_080155CC(parent, slot1, x, y, def1->speedX, def1->speedY);
    if (origin->flags & 0x10) { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = FlippedCoord(fixed, def2->xOffset); }
    else { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = (fixed >> 16) + def2->xOffset; }
    if (origin->flags & 0x20) { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = FlippedCoord(fixed, def2->yOffset); }
    else { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = (fixed >> 16) + def2->yOffset; }
    sub_080155CC(parent, slot2, x, y, def2->speedX, def2->speedY);
  } else { do { modeB = flags & 8; } while (0); if (modeB) {
    struct OriginFlags *origin = parent->origin; s32 x; s32 y;
    if (origin->flags & 0x10) { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = FlippedCoord(fixed, def1->xOffset); }
    else { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } do { x = (fixed >> 16) + def1->xOffset; } while (0); }
    if (origin->flags & 0x20) { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = FlippedCoord(fixed, def1->yOffset); }
    else { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = (fixed >> 16) + def1->yOffset; }
    sub_0801569C(parent, slot1, x, y, def1->speedX, def1->speedY);
    if (origin->flags & 0x10) { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = FlippedCoord(fixed, def2->xOffset); }
    else { s32 fixed = state->x; if (fixed < 0) { fixed += 0xFFFF; } x = (fixed >> 16) + def2->xOffset; }
    if (origin->flags & 0x20) { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = FlippedCoord(fixed, def2->yOffset); }
    else { s32 fixed = state->y; if (fixed < 0) { fixed += 0xFFFF; } y = (yInt = fixed >> 16) + def2->yOffset; }
    sub_0801569C(parent, slot2, x, y, def2->speedX, def2->speedY);
    } }
}
