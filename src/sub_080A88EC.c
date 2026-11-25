s32 sub_0801473C(s32, s32);
s32 sub_080A857C(s32, void *);

/* Keeps a work state's motion aimed at the player: when the source's facing
 * bit no longer matches the work's, reverse the work's velocity, then nudge
 * that velocity one fixed step toward the player-seeking heading. */
void sub_080A88EC(s32 actor, void *source, void *work) {
    u16 *facingPtr;
    s32 velocity;
    facingPtr = (u16 *)((u8 *)work + 0xA4);
    if (*facingPtr != (u16)(0x10 & *(vu16 *)((u8 *)source + 2))) {
        *(s32 *)((u8 *)work + 0xA0) = 0 - *(s32 *)((u8 *)work + 0xA0);
        *facingPtr = (u16)(0x10 & *(u16 *)((u8 *)source + 2));
    }
    velocity = *(s32 *)((u8 *)work + 0xA0);
    *(s32 *)((u8 *)work + 0xA0) = *(s32 *)((u8 *)work + 0xA0) + (sub_0801473C(velocity, sub_080A857C(actor, work)) << 8);
}
