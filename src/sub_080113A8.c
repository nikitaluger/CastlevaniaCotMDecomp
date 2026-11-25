void sub_08010DF8(void *entity, void *track, s32 entry);

struct FrameTable {
    s32 base;
    s32 field4;
    s32 field8;
};

/* Animation track state: flags +0, frame index +1, frame duration +2, frame
 * timer +4, frame table +8, current table entry +0xE. */
struct AnimTrack {
    u8 flags;
    u8 index;
    u8 _pad[6];
    struct FrameTable *table;
    u8 _padC[2];
    s16 frame;
    s32 field10;
};

/* Step an animation track: hand sub_08010DF8 the entity, the track state and
 * the track's current frame entry (table base + frame * 4). */
void sub_080113A8(void *entity, struct AnimTrack *track) {
    struct FrameTable *table;

    table = track->table;
    sub_08010DF8(entity, track, table->base + track->frame * 4);
}
