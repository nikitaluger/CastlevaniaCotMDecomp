s32 sub_080A1904(void *, void *, void *);
void sub_080114DC(void *, void *, s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Hit-reaction step: once the work animation's status byte reports the end of
 * its frame sequence, knock the actor back 38 pixels along its facing
 * direction, restart animation 0 and advance the script with command 4. */
void sub_080A1210(void *entity) {
    void *sprite = *(void **)((u8 *)entity + 0x38);
    void *work = *(void **)((u8 *)entity + 0x3C);
    void *anim = (u8 *)work + 0x34;

    if (sub_080A1904(sprite, anim, (u8 *)work + 0x48) != 0) {
        s32 x = *(s32 *)((u8 *)work + 8);

        if (*(u16 *)((u8 *)sprite + 2) & 0x10) {
            *(s32 *)((u8 *)work + 8) = x + 0x260000;
        } else {
            *(s32 *)((u8 *)work + 8) = x + 0xFFDA0000;
        }
        sub_080114DC(sprite, anim, 0, 0);
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptCb = (s32 *)0x08671BD0;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 4, *scriptCb);
        }
    }
}
