/* Script step: allocate six child objects, store their handles in the work
 * object, then advance to the next script step's handler. */
void *sub_080A0210(void);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct SpawnWork { u8 pad[0x48]; u32 children[6]; };

void sub_0809F614(u8 *self) {
    u8 *scriptEntry;
    s32 *stepCallback;
    struct SpawnWork *work;
    u32 *childSlot;
    u32 i;

    work = (struct SpawnWork *)*(u32 *)(self + 0x3C);
    i = 0;
    childSlot = work->children;
    do {
        *childSlot++ = sub_080A0210();
        i++;
    } while (i <= 5);
    *(u8 *)(self + 0x6C) = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepCallback = (s32 *)0x08671BB0;
    scriptEntry = self + 0x18;
    sub_080C31E4(scriptEntry, self + 0x22, *stepCallback);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptEntry += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)scriptEntry * 4));
}
