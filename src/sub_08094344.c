void sub_0801604C(void *);
void sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);

extern u8 D_08100818[];
extern u8 D_081007D0[];

/* When the sprite is flagged as hit (flag bit 0 and mask 0x1000), switch the
 * entity's animation/state block (+0x34) to state 1, then refresh the
 * sprite's screen position from the entity's world position. */
void sub_08094344(void *arg0, void *arg1) {
    u8 *anim = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x34;
    if ((*(u16 *)((u8 *)arg1 + 2) & 1) && (*(u16 *)arg1 & 0x1000)) {
        *(s32 *)(anim + 8) = 1;
    }
    sub_0801604C(arg1);
}
