struct S_02025FF0_37588 { u8 _0x000[0x174C]; u32 targetX; u32 targetY; };
extern struct S_02025FF0_37588 D_02025FF0;
s32 sub_08005910(s32, s32);
s32 sub_080113A8(s32, void *);
s32 sub_08037724(s32, void *);
void sub_080C31E4(void *, void *, s32);

/* Advances the entity's animation and its part; when the current script step
 * reaches value 8 it aims the part at the room's target point, clears the
 * step byte and restarts the script step. */
void sub_08037588(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animator;
    u8 *part;
    animator = work + 0x34;
    part = work + 0x48;
    sub_080113A8(sprite, animator);
    sub_08037724(sprite, part);
    if (*(u8 *)(((s16 *)((u8 *)arg0 + 0x22))[0] * 2 + (u8 *)arg0 + 0x19) == 8) {
        s32 dy = (s32)D_02025FF0.targetY - *(s32 *)(work + 0xC);
        s32 dx = (s32)D_02025FF0.targetX - *(s32 *)(work + 8);
        *(s32 *)(part + 4) = sub_08005910(dy, dx);
        *((s8 *)(((s16 *)((u8 *)arg0 + 0x22))[0] * 2 + (u8 *)arg0 + 0x19)) = 0;
        {
            s32 *scriptHandler = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptHandler);
        }
    }
}
