/*
 * Script step: allocate the actor's work object of type 0x54 and abort the
 * script if that fails; otherwise clear the pose flags byte and dispatch the
 * next script step's handler.
 */
void allocWorkSlot(void *, s32, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct Work {
    u8 pad[0x48];
    u8 poseFlags;
};

void sub_0805B694(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *scriptEntry;
    s32 *stepCallback;
    struct Work *work;

    allocWorkSlot(arg0, 0, 0x54, 0);
    work = (struct Work *)*(u32 *)(self + 0x3C);
    if (work == NULL) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
        return;
    }
    work->poseFlags = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepCallback = (s32 *)0x08671BB0;
    scriptEntry = self + 0x18;
    sub_080C31E4(scriptEntry, self + 0x22, *stepCallback);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptEntry += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(arg0, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)scriptEntry * 4));
}
