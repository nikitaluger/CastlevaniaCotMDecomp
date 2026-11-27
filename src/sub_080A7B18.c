extern void *gScriptStepCallbackTable;
extern void *spawnBudgetedEffect(void *, s32);
extern s32 divideInt(s32, s32);
extern void sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Spawns a companion object for the entity, initializes its parent link and two
 * body counters, then advances the script to the next step. */
void sub_080A7B18(u8 *self) {
    s16 stepIdx;
    u8 *gfx;
    u8 *body;
    u8 *stepBase;
    void *child;

    gfx = *(u8 **)(self + 0x38);
    body = *(u8 **)(self + 0x3C);
    if (!(*(self + *(s16 *)(self + 0x22) * 2 + 0x19) & 2)) {
        *(u16 *)gfx = (*(u16 *)gfx & 0xFFF) | 0xE000;
    }
    child = spawnBudgetedEffect(self, 0x19F);
    *(void **)(body + 0x180) = child;
    if (child != 0) {
        *(s32 *)((u8 *)child + 0x4C) = self[0x4C];
        *(s32 *)(body + 0x14C) = -divideInt(*(s32 *)(body + 0xFC), 0xC);
        *(s32 *)(body + 0x150) = -divideInt(*(s32 *)(body + 0x100), 0xC);
        *(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            void **fnaddr = &gScriptStepCallbackTable;
            stepBase = self + 0x18;
            sub_080C31E4(stepBase, self + 0x22, (s32)*fnaddr);
        }
        *(self + *(s16 *)(self + 0x22) * 2 + 0x19) = *(self + *(s16 *)(self + 0x22) * 2 + 0x19) + 1;
        stepIdx = *(s16 *)(self + 0x22);
        stepBase += stepIdx * 2;
        sub_080C31E0((s32)self, *(s32 *)((u8)(*stepBase) * 4 + *(u32 *)(self + 0x14)));
    }
}
