extern void sub_08011368(void *, void *, s32, s32);
extern void sub_08014DB4(void *, void *, u32, u32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_174C { u8 pad[0x174C]; u32 targetX; u32 targetY; };
extern struct S_02025FF0_174C D_02025FF0;

/* Play pose 8 while steering the entity's follow path toward the target point
 * stored at D_02025FF0+0x174C; once the path reports it has reached a limit,
 * clear the state counter and advance to the next handler from 0x08671BB0. */
void sub_08053598(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *anim = body + 0x34;
    u8 *motion = body + 0x48;
    sub_08011368((void *)sprite, anim, 8, 1);
    sub_08014DB4(body, body + 0x4C, D_02025FF0.targetX, D_02025FF0.targetY);
    if (*(u16 *)(motion + 0x1C) & 4) {
        s16 stateIndex = *(s16 *)(self + 0x22);
        s32 *handlerTable;
        *(u8 *)(self + stateIndex * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
