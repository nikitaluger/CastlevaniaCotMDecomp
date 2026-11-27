extern void advanceAnimTrackByDelta(void *a, void *b, void *c);
extern void advanceMotion(void *a, s32 b);
extern void sub_080A1744(void *a, void *b);

struct FlipObj {
    u8 pad0[2];
    u16 flags;
};
struct Motion {
    u8 pad0[0x10];
    s32 velX;
};
struct DirectionEntry {
    u8 pad0[2];
    u16 dir;
};
struct DirectionTable {
    struct DirectionEntry *entries;
};
struct TrackState {
    u8 flags;
    u8 indexOffset;
    u8 pad2[6];
    struct DirectionTable *dirTable;
    u8 padC[2];
    s16 index;
};
struct FacingState {
    u8 pad0[0x14];
    u16 prevDir;
    u8 tableIndex;
    u8 changeCount;
};

struct D_02025FF0_t {
    u8 _0[0x1754];
    s32 field1754;
};
extern struct D_02025FF0_t gMainWorkspace;
extern void *D_0866FDEC[];

/* Updates an entity's facing direction and motion velocity from its movement
 * track: applies a speed delta (negated by the object's flip flag), zeroes the
 * velocity for the special directions 1 and 7, and tracks direction changes,
 * bumping a global counter and the change count when leaving those directions.
 */
s32 sub_080A17DC(struct FlipObj *entity, struct Motion *motion, struct TrackState *track, struct FacingState *facing, s32 magnitude)
{
    s32 signedSpeed;
    s32 changed;
    u16 direction;
    struct DirectionTable *table;

    signedSpeed = magnitude;
    changed = 0;
    advanceAnimTrackByDelta(entity, track, D_0866FDEC[facing->tableIndex]);
    table = track->dirTable;
    {
        s32 idx;
        idx = track->index + track->indexOffset;
        direction = table->entries[idx - 1].dir;
    }
    if (!(entity->flags & 0x10))
        signedSpeed = -signedSpeed;
    motion->velX = signedSpeed;
    if (direction == 1 || direction == 7)
        motion->velX = 0;
    if (direction != facing->prevDir)
    {
        if ((direction == 1 || direction == 7) && gMainWorkspace.field1754 <= 8)
            gMainWorkspace.field1754 = 9;
        if (facing->prevDir == 1 || facing->prevDir == 7)
        {
            changed = 1;
            facing->changeCount++;
            sub_080A1744(entity, motion);
        }
        facing->prevDir = direction;
    }
    advanceMotion(motion, 0);
    return changed;
}
