struct S_080DEA88 { u8 _pad[0xE3 << 3]; s32 field; };
extern struct S_080DEA88 D_080DEA88;
extern s32 sub_0806C4B4(s32, s32);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AA64(void *, void *);
extern void sub_08003A6C(void *, s32, s32);
extern s32 sub_08003740(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Scripted entity update: if no special camera/position mode is active, reset
 * result state and scroll offsets, tick a timer; on expiry initialise a param
 * block, copy a field, clear the script slot and start the script, then run the
 * common post-update. */
void sub_080670D8(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *ctrl = *(u8 **)(entity + 0x6C);
    u8 *pos = ctrl + 4;
    void *mainObj = *(void **)(entity + 0x38);
    u8 *timer;
    s32 result;
    if (sub_0806C4B4((s32)pos, (s32)pos) == 0) {
        sub_0806C5EC(arg0, mainObj, pos, pos);
        sub_0806AA64(mainObj, pos);
        timer = ctrl + 0x2C;
        result = sub_08003740(timer, mainObj);
        if (result == 0) {
            sub_08003A6C(timer, 0, D_080DEA88.field);
            *(s32 *)(ctrl + (0x88 << 1)) = *(s32 *)(ctrl + (0x84 << 1));
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = result;
            {
                const u32 *lit = (const u32 *)0x08671BB0;
                sub_080C31E4(entity + 0x18, entity + 0x22, *lit);
            }
        }
        sub_0806C6B0(arg0, mainObj, pos, pos);
    }
}
