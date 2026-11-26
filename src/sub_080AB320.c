void setObjectAnimation(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Prepare the actor's sprite (work+0x34) with animation 9, set the display
 * flags in work+0x48, clear the current command slot and run the next
 * script command through table 0x08671BB0. */
void sub_080AB320(void *arg0) {
    u8 *obj = (u8 *)arg0;
    void *actor;
    u8 *base;
    u8 *anim;
    s32 zero;
    s32 *table;
    actor = *(void **)(obj + 0x38);
    base = *(u8 **)(obj + 0x3C);
    anim = base + 0x34;
    base = base + 0x48;
    setObjectAnimation(actor, anim, 9, 0);
    zero = 0;
    *(u8 *)(base + 0x1C) = 4;
    *(u8 *)(base + 0x10) = 1;
    *(u8 *)(base + 0x11) = 1;
    *(u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2 + 0x19) = zero;
    table = (s32 *)0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *table);
}
