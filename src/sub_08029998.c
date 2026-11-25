void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
void *sub_0805FAEC(s32, s32);

struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

/* Script command: play animation 9, install this script's command-handler table
 * at self+0x14, advance the step counter and its flag byte, dispatch the new
 * command's handler from that table, then restore the step counter. */
void sub_08029998(void *actor) {
    u8 *self = (u8 *)actor;
    u32 stepOffset;
    u8 *commandSlot;
    sub_08011368(*(void **)(self + 0x38), *(void **)(self + 0x3C) + 0x34, 9, 1);
    *(u32 *)(self + 0x14) = 0x0866DA64;
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepOffset = (s32)*(s16 *)(self + 0x22) * 2;
    commandSlot = self + 0x18;
    sub_080C31E0(self, *(void **)(*(u8 *)(commandSlot + stepOffset) * 4 + *(u32 *)(self + 0x14)));
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
}

/* Spawn a projectile from an origin point, offsetting its X by the sprite's
 * horizontal-flip direction and copying the origin's Y. */
void sub_08040B34(s32 unused, void *sprite, void *origin) {
    void *shot = sub_0805FAEC(D_02025FF0.v, 0x108);
    if (shot != NULL) {
        s32 facingOffset;
        if (*(u16 *)((u8 *)sprite + 2) & 0x10)
            facingOffset = 0x180000;
        else
            facingOffset = (s32)0xFFE80000;
        *(s32 *)((u8 *)shot + 0x4C) = *(s32 *)((u8 *)origin + 8) + facingOffset;
        *(s32 *)((u8 *)shot + 0x5C) = *(s32 *)((u8 *)origin + 0xC);
        *(u8 *)((u8 *)shot + 0x7C) = 0;
    }
}
