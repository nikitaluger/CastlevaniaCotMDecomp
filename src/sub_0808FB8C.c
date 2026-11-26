extern void sub_0801604C(void *);

/* If the command descriptor's flag words report bits 2/1 and bit 2, mark the
 * entity's state as changed at +0x14, then apply the descriptor. */
void sub_0808FB8C(void *entity, void *cmd)
{
    void *state = *(void **)((s8 *)entity + 0x3C);
    if ((6 & *(u16 *)((s8 *)cmd + 2)) && (4 & *(u16 *)cmd)) {
        *(u16 *)((s8 *)state + 0x14) = 1;
    }
    sub_0801604C(cmd);
}

extern u8 gMainWorkspace[];

/* True when the global 16.16 position (the player) lies within 32 px
 * horizontally and 48 px vertically of the entity's point at +0x0C/+0x10. */
s32 sub_0808FBB4(void *entity)
{
    void *state = *(void **)((s8 *)entity + 0x3C);
    s32 pointX = *(s32 *)((s8 *)state + 0x0C);
    s32 pointY = *(s32 *)((s8 *)state + 0x10);
    if (*(u32 *)(gMainWorkspace + 0x1728) >= pointX + 0xFFE00000 &&
        *(u32 *)(gMainWorkspace + 0x1728) <= pointX + 0x200000 &&
        *(u32 *)(gMainWorkspace + 0x172C) >= pointY + 0xFFD00000 &&
        *(u32 *)(gMainWorkspace + 0x172C) <= pointY + 0x300000) {
        return 1;
    }
    return 0;
}

extern void sub_080C31E8(void *, void *, s32, s32);

/* Command script step: once the state's completion flag at +0x18 (bit 1) is
 * set, clear its frame counter at +0x14 and the script flag byte, then advance
 * the command script. */
void sub_0808FB30(void *entity)
{
    void *state = *(void **)((s8 *)entity + 0x3C);
    if (2 & *(u8 *)((s8 *)state + 0x18)) {
        *(u16 *)((s8 *)state + 0x14) = 0;
        *(u8 *)((s8 *)entity + (s32)(s16)((u16 *)entity)[0x11] * 2 + 0x19) = 0;
        sub_080C31E8((s8 *)entity + 0x18, (s8 *)entity + 0x22, 1, *(u32 *)0x08671BD0);
    }
}

extern void sub_080C31E4(void *, void *, s32);

/* Command script step: once the state's completion flag at +0x18 (bit 1) is
 * set, clear the sub-object's flag byte at +1 and the script flag byte, then
 * advance the command script. */
void sub_0808FA90(void *entity)
{
    void *state = *(void **)((s8 *)entity + 0x3C);
    if (2 & *(u8 *)((s8 *)state + 0x18)) {
        *(u8 *)(*(u32 *)((s8 *)state + 4) + 1) = 0;
        *(u8 *)((s8 *)entity + (s32)(s16)((u16 *)entity)[0x11] * 2 + 0x19) = 0;
        sub_080C31E4((s8 *)entity + 0x18, (s8 *)entity + 0x22, *(u32 *)0x08671BB0);
    }
}
