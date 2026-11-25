struct FlagInfo { u8 pad0[8]; u16 flagId; };
struct Controller { u16 flags; u16 pad2; struct FlagInfo *info; };
struct Entity {
    u8 pad0[0x24];
    void *callback;
    u8 pad28[0xAC - 0x28];
    struct Controller *controller;
};

extern void sub_08007E24(u16);
extern void sub_08062394(s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);

/* Set a flag on the entity's controller and record the flag id in the global
 * bitfield, then adjust the +0x38F counter: each of the three adjacent slots
 * at +0x306..+0x308 holding 0x0B adds one, but only store a new value while
 * the total stays <= 0x62. Finally trigger effects and fire the callback. */
void sub_0805EF08(struct Entity *entity)
{
    struct Controller *ctrl;
    u8 *state;
    u8 *counter;
    s32 origCount;
    s32 adjCount;

    state = (u8 *)0x02025368;
    ctrl = entity->controller;
    ctrl->flags |= 4;
    sub_08007E24(ctrl->info->flagId);

    counter = state + 0x38F;
    origCount = *counter;
    adjCount = origCount;
    if (*(state + 0x306) == 0x0B) {
        adjCount = (u8)(origCount + 1);
    }
    if (*(state + 0x307) == 0x0B) {
        adjCount = (u8)(adjCount + 1);
    }
    if (*(state + 0x308) == 0x0B) {
        adjCount = (u8)(adjCount + 1);
    }
    if ((u32)adjCount <= 0x62) {
        *counter = origCount + 1;
    }

    sub_08062394(1, 0x0B);
    sub_08005E80(0x77);
    sub_080C31E0(entity, entity->callback);
}
