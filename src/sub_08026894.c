s32 sub_0800583C(s32);
s32 setAnimationFrame(s32, s32, s32, s32);
s32 sub_08026C7C(s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Entity update: switch the attached component to animation 9, every sixth
 * script-phase tick spawn a small effect at a jittered offset from the
 * component's position, and invoke the entity's +0x24 callback when the
 * animator's 0x2 flag is set. */
void sub_08026894(void *entity) {
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    u8 *component;
    s32 spawnX;

    component = *(u8 **)((u8 *)entity + 0x3C);
    setAnimationFrame(sprite, (s32)(component + 0x34), 9, 0);
    if (sub_080C389C(*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19), 6) == 1) {
        spawnX = sub_0800583C(0x40000) + *(s32 *)(component + 8);
        sub_08026C7C(spawnX, sub_0800583C(0x40000) + *(s32 *)(component + 0xC) + 0x100000, 0, 0xFFFF8000, (s32)*(s16 *)(component + 0x1C));
    }
    if (2 & *(u8 *)(component + 0x34)) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
