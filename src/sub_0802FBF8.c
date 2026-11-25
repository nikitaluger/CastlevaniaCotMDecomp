extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BB0[];

/* Script step for two linked actors: when the first one's flag 8 is set, set
 * flag 0x10 on both and run a handler; otherwise, when both have flag 0x1000,
 * advance the script step and dispatch its handler. */
void sub_0802FBF8(u8 *self)
{
    u32 flag8;
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *links = state + 0x48;
    u8 *actorA = *(u8 **)(state + 0x48);
    u16 *actorAFlags = (u16 *)(actorA + 0x6C);
    u16 flagsA = *actorAFlags;
    u32 mask;
    u32 combined;
    u16 *actorBFlags;
    u8 *stepData;
    s32 *scriptEvent;

    flag8 = (u16)(flagsA & 8);
    if (flag8 != 0)
    {
        mask = 0x10;
        combined = flagsA | mask;
        do { *actorAFlags = combined; actorBFlags = (u16 *)(*(u8 **)(links + 4) + 0x6C); } while (0);
        mask |= *actorBFlags;
        *actorBFlags = mask;
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }
    if ((*(u16 *)(actorA + 2) & 0x1000) != 0 && (*(u16 *)(*(u8 **)(links + 4) + 2) & 0x1000) != 0)
    {
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = flag8;
        scriptEvent = D_08671BB0;
        stepData = self + 0x18;
        sub_080C31E4(stepData, self + 0x22, *scriptEvent);
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) += 1;
        stepData += (*(s16 *)(self + 0x22)) * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + (*stepData) * 4));
    }
}
