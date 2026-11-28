struct Z { u32 w; u8 b; };
extern s32 setAnimationFrame(s32, s32, s32, s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_080426E8(void *self) {
    s32 *actor;
    u8 *motion;
    u8 *anim;
    u8 *state;
    s32 timer;
    s32 facing;
    u16 t;

    actor = *(s32 **)((u8 *)self + 0x38);
    motion = *(u8 **)((u8 *)self + 0x3C);
    anim = motion + 0x34;
    state = motion + 0x48;
    sub_080149A4((s32)actor, motion, state, 0xB4, 0xF0);
    setAnimationFrame((s32)actor, (s32)anim, 0, 1);
    timer = *(u16 *)(state + 2) - 1;
    *(u16 *)(state + 2) = timer;
    if ((s32)(timer << 16) < 0) {
        *(u16 *)(state + 2) = *(u16 *)(*(u8 **)(state + 0x10) + 8);
        if (absXFromFocus(*(s32 *)(motion + 8)) <= (s32)*(u32 *)(*(u8 **)(state + 0x10)) &&
            absYFromFocus(*(s32 *)(motion + 0xC) - 0x100000) <= 0x300000) {
            facing = getSpriteFacingSign((s32)actor);
            if (facing == signOf(*(s32 *)(motion + 8))) {
                struct Z z = {0, 0};
                s16 scriptIndex;
                s32 *scriptParam;
                scriptIndex = *(s16 *)((u8 *)self + 0x22);
                *((u8 *)self + scriptIndex * 2 + 0x19) = z.b;
                scriptParam = (s32 *)0x08671BD0;
                sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *scriptParam);
                return;
            }
        }
    }
    if ((*(u16 *)(motion + 2) & 3) != 0) {
        u16 flags = *(u16 *)((u8 *)actor + 2);
        flags ^= 0x10;
        *(u16 *)((u8 *)actor + 2) = flags;
        t = *(u16 *)(state + 0);
        t += 0x3C;
        *(u16 *)(state + 0) = t;
    }
    if (getSpriteFacingSign((s32)actor) > 0) {
        *(s32 *)(motion + 0x10) = 0xA0 << 6;
    } else {
        *(s32 *)(motion + 0x10) = -0x2800;
    }
}
