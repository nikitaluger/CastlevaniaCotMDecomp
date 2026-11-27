struct Z { u32 w; u8 b; };
extern s32 setAnimationFrame(s32, s32, s32, s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(s32);
extern s32 sub_080458CC(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Enemy idle update: play animation frame 0, tick the random idle-turn timer
 * (delay 60..90, sub_080149A4), and once the enemy is within reach of the
 * player either switch to script step 1 (enemy on the side the player faces)
 * or to script step 2 (the player is attacking it). Otherwise, on contact,
 * flip the sprite's facing and shake the state timer, then walk in the
 * direction the player is facing. */
void sub_08045574(void *self) {
    s32 *actor;
    u8 *motion;
    u8 *anim;
    u8 *state;
    s32 timer;
    s32 side;

    actor = *(s32 **)((u8 *)self + 0x38);
    motion = *(u8 **)((u8 *)self + 0x3C);
    anim = motion + 0x34;
    state = motion + 0x48;
    setAnimationFrame((s32)actor, (s32)anim, 0, 1);
    sub_080149A4((s32)actor, motion, state, 0x3C, 0x5A);
    timer = *(u16 *)(state + 2) - 1;
    *(u16 *)(state + 2) = timer;
    if ((s32)(timer << 16) <= 0) {
        *(u16 *)(state + 2) = 0x3C;
        if (absXFromFocus(*(s32 *)(motion + 8)) <= 0x380000 &&
            absYFromFocus(*(s32 *)(motion + 0xC)) <= 0x200000) {
            side = signOf(*(s32 *)(motion + 8));
            if (side == getSpriteFacingSign((s32)actor)) {
                {
                    struct Z z = {0, 0};
                    s16 scriptIndex;
                    s32 *scriptParam;
                    *(u16 *)(state + 4) = 0;
                    scriptIndex = *(s16 *)((u8 *)self + 0x22);
                    *((u8 *)self + scriptIndex * 2 + 0x19) = z.b;
                    scriptParam = (s32 *)0x08671BD0;
                    sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *scriptParam);
                }
                return;
            }
        }
    }
    if (sub_080458CC(self, actor) == 1) {
        {
            u8 zero;
            s16 scriptIndex;
            s32 *scriptParam;
            zero = 0;
            *(u16 *)(state + 4) = 0x5A;
            scriptIndex = *(s16 *)((u8 *)self + 0x22);
            *((u8 *)self + scriptIndex * 2 + 0x19) = zero;
            scriptParam = (s32 *)0x08671BD0;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *scriptParam);
        }
        return;
    }
    if ((*(u16 *)(motion + 2) & 3) != 0) {
        u16 flags;
        u16 t;
        flags = *(u16 *)((u8 *)actor + 2);
        flags ^= 0x10;
        *(u16 *)((u8 *)actor + 2) = flags;
        t = *(u16 *)(state + 0);
        t += 0x3C;
        *(u16 *)(state + 0) = t;
    }
    if (getSpriteFacingSign((s32)actor) > 0) {
        *(s32 *)(motion + 0x10) = 0x6000;
    } else {
        *(s32 *)(motion + 0x10) = (s32)0xFFFFA000;
    }
}
