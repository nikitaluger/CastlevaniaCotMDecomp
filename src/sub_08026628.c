extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_0801468C(u8 *, u32);
extern s32 sub_08014A04(u8 *, s32, s32, s32, s32);
extern void sub_08014B1C(u8 *, u8 *, s32, s32);
extern void sub_08026954(u8 *, u8 *);
extern s32 sub_080C31E0(s32, s32);
struct S_02025FF0_1728 { u8 _0[0x1728]; u32 worldX; u32 worldY; };
extern struct S_02025FF0_1728 D_02025FF0;

/* Updates a tracking entity: sets the target's animation state, combines the
 * shared world origin with local offsets, moves the tracked point when the
 * target is close enough, dispatches a message through the entity's table and
 * advances a phase counter. */
void sub_08026628(u8 *arg0) {
    u8 *targetObj;
    u8 *state;
    u8 *stateTail;
    u8 *ctrl;
    s32 posX;
    s32 posY;
    u8 *msgEntry;
    u8 msgIndex;
    s32 byteIndex;

    targetObj = *((u8 **)(arg0 + 0x38));
    state = *((u8 **)(arg0 + 0x3C));
    stateTail = state + 0x34;
    ctrl = state + 0x48;
    sub_08011368(targetObj, stateTail, 0, 1);
    posX = D_02025FF0.worldX + *((u32 *)(ctrl + 0x08));
    posY = D_02025FF0.worldY + *((u32 *)(ctrl + 0x0C));
    if (sub_08014A04(state, posX, posY, 0x80 << 13, 0x80 << 13) == 1) {
        sub_08026954(state + 0x50, state + 0x54);
    }
    sub_08014B1C(state, state + 0x7C, posX, posY);
    sub_0801468C(targetObj, *((u32 *)(ctrl + 0x38)));
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0866D9A0;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    ((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2)[0x19]++;
    byteIndex = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
    msgEntry = (u8 *)arg0;
    msgEntry += 0x18;
    msgEntry += byteIndex;
    msgIndex = *msgEntry;
    sub_080C31E0((s32)arg0, *(s32 *)((u32)(msgIndex * 4) + *(u32 *)((u8 *)arg0 + 0x14)));
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    *(u32 *)(ctrl + 0x18) = (*(u32 *)(ctrl + 0x18) + (0x80 << 4)) & 0xFFFF;
    sub_0801165C(state + 0xA8, 0);
}
