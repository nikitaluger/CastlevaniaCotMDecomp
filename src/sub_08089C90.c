extern u32 D_02025FF0[];
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct Sprite_89C90 { u8 pad[2]; u16 flags; };

/* Tick of a grounded actor while the global state is 0x11: raise the sprite's
 * 0x10 flag, clear the current script step and advance the script, then
 * refresh the sprite's screen offset from the mover's position. */
void sub_08089C90(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *moverPos = *(u8 **)(self + 0x6C) + 4;
    struct Sprite_89C90 *sprite = (struct Sprite_89C90 *)*(void **)(self + 0x38);
    u32 zero;
    if (D_02025FF0[5] == 0x11) {
        zero = 0;
        sprite->flags |= 0x10;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = zero;
        {
            s32 *stepTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
        }
    }
    sub_0806D588(sprite, moverPos);
}
