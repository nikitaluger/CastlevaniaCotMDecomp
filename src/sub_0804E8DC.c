s32 sub_08005820(s32);
void setAnimationFrame(s32, void *, u16, u8);
void setSpriteFlip(void *, s32);
s32 sub_08014A04(void *, s32, s32, s32, s32);
void sub_08014B1C(void *, void *, s32, s32);
void sub_0804EA20(void *);
void *sub_0805FAEC(s32, s32);
extern u8 gMainWorkspace[];

/* Counts down a timer: on expiry in the right animation state it spawns
 * object 0x13E just above the entity with a fresh random delay, then updates
 * movement toward the player and applies collision resolution. */
void sub_0804E8DC(void *entity) {
    s32 parent = *(s32 *)((u8 *)entity + 0x38);
    void *obj = *(void **)((u8 *)entity + 0x3C);
    u8 *anim = (u8 *)obj + 0x34;
    u8 *state = (u8 *)obj + 0x48;
    u32 timer;

    setAnimationFrame(parent, anim, 0, 1);
    timer = *(u16 *)(state + 0x12);
    timer--;
    *(u16 *)(state + 0x12) = timer;
    if ((s32)(timer << 16) < 0) {
        if (*(u8 *)(anim + 1) == 4 && *(s32 *)(anim + 4) == 1) {
            void *spawned;
            u32 poolOffset = 0x1870;

            *(u16 *)(state + 0x12) = (u16)(sub_08005820(0x3D) + 0xB4);
            spawned = sub_0805FAEC(*(s32 *)(gMainWorkspace + poolOffset), 0x13E);
            if (spawned != NULL) {
                s32 x = *(s32 *)((u8 *)obj + 8);
                if (x < 0)
                    x += 0xFFFF;
                {
                    s32 xWord = x >> 16;
                    *(s16 *)((u8 *)spawned + 0x4C) = (s16)xWord;
                }
                {
                    s32 y = *(s32 *)((u8 *)obj + 0xC);
                    s32 yWord;
                    if (y < 0)
                        y += 0xFFFF;
                    yWord = (y >> 16) + 0x10;
                    *(s16 *)((u8 *)spawned + 0x54) = (s16)yWord;
                }
                *(s32 *)((u8 *)spawned + 0x5C) = 0;
                *(s32 *)((u8 *)spawned + 0x6C) = 0x10000;
            }
        }
    }
    if (sub_08014A04(obj, *(s32 *)(state + 8), *(s32 *)(state + 0xC), 0x80000, 0x80000) == 1) {
        sub_0804EA20(entity);
    }
    sub_08014B1C(obj, state + 0x14, *(s32 *)(state + 8), *(s32 *)(state + 0xC));
    setSpriteFlip((void *)parent, *(s32 *)(state + 0x18));
}
