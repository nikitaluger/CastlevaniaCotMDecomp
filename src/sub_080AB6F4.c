s32 scaleByRandom(s32);
void sub_080AAC20(s32, s32, s32);
void setObjectAnimation(s32, s32, s32, s32);
void _call_via_r2(void *, void *, s32);
void _call_via_r3(void *, void *, s32, s32);
s32 sub_0801473C(s32, s32);
s32 sub_080A857C(s32, void *);

/* Spawn four objects of each of two kinds at random vertical offsets. */
void sub_080AAC58(void) {
    u32 i;
    s32 randOffset;
    for (i = 0; i < 4; i++) {
        randOffset = scaleByRandom(0x1B00000) + 0x280000;
        sub_080AAC20(0, randOffset, 0x200000);
    }
    for (i = 0; i < 4; i++) {
        randOffset = scaleByRandom(0x1B00000) + 0x280000;
        sub_080AAC20(1, randOffset, 0x200000);
    }
}

/* Play animation 9, set flags on the work extension and restart the script. */
void sub_080AB320(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *sprite = *(void **)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    u8 *extra = work + 0x48;
    setObjectAnimation((s32)sprite, (s32)anim, 9, 0);
    *(u8 *)(extra + 0x1C) = 4;
    *(u8 *)(extra + 0x10) = 1;
    *(u8 *)(extra + 0x11) = 1;
    *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
    {
        s32 *advanceCb = (s32 *)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}

/* At sub-step 0x70 play animation 2; at 0x78 reset the sub-step and advance
 * the script through the alternate callback table. */
void sub_080AB6F4(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x70) {
        setObjectAnimation(sprite, (s32)anim, 2, 0);
    }
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x78) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb = (s32 *)0x08671BD0;
            _call_via_r3(actor + 0x18, actor + 0x22, 0, *advanceCb);
        }
    }
}

/* Steer the work's velocity toward the player, reversing it when the sprite's
 * horizontal flip changes. */
void sub_080A88EC(s32 arg0, void *arg1, void *arg2) {
    s32 velocity;
    if (*(u16 *)((u8 *)arg2 + 0xA4) != (u16)(0x10 & *(u16 *)((u8 *)arg1 + 2))) {
        *(s32 *)((u8 *)arg2 + 0xA0) = 0 - *(s32 *)((u8 *)arg2 + 0xA0);
        *(u16 *)((u8 *)arg2 + 0xA4) = (u16)(0x10 & *(u16 *)((u8 *)arg1 + 2));
    }
    velocity = *(s32 *)((u8 *)arg2 + 0xA0);
    *(s32 *)((u8 *)arg2 + 0xA0) = *(s32 *)((u8 *)arg2 + 0xA0) + (sub_0801473C(velocity, sub_080A857C(arg0, arg2)) << 8);
}
