extern s32 sub_080110B4(s32, void *, s32, s32, s32, s32, s32);

struct TrackTable {
    s32 base;
    s32 field4;
    s32 field8;
};

struct TrackState {
    u8 flags;
    u8 indexOffset;
    u8 _pad[6];
    struct TrackTable *table;
    u8 _padC[2];
    s16 index;
    s32 field10;
};

/* Advance a movement track one step: pass the current direction-table entry
 * and the track's state on to the step routine sub_080110B4. */
void advanceAnimTrackByDelta(s32 entity, struct TrackState *track, s32 delta) {
    struct TrackTable *table;

    table = track->table;
    sub_080110B4(entity, track, table->base + track->index * 4, table->field4, table->field8, track->field10, delta);
}
