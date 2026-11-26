extern void sub_08003740(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern s16 sub_080C364C(s32, s32);

struct S_02025FF0 {
    u8 _0[0x10];
    u32 field10;
    u8 _1[0x14ED - 0x14];
    u8 field14ED;
    u8 _2[0x173A - 0x14EE];
    u8 field173A;
};

extern struct S_02025FF0 gMainWorkspace;

/*
 * Applies the entity's velocity, decrements its countdown, updates the scaled
 * animation values, and finishes the callback when time runs out or a global
 * state requires it.
 */
void sub_08080134(void *arg0) {
    void *entity = arg0;
    void *subObj = *(void **)((u8 *)entity + 0x6C);
    void *obj = (u8 *)subObj + 4;
    void *ctx = *(void **)((u8 *)entity + 0x38);

    if (sub_0806D518(entity, ctx, obj) == 0) {
        s32 previous;
        s32 countdown;
        *(s32 *)((u8 *)subObj + 0x04) += *(s32 *)((u8 *)obj + 0x08);
        *(s32 *)((u8 *)obj + 0x04) += *(s32 *)((u8 *)obj + 0x0C);
        previous = *(s32 *)((u8 *)obj + 0x10);
        countdown = previous - 0x0A;
        *(s32 *)((u8 *)obj + 0x10) = countdown;
        if (countdown <= 0) {
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
        *(s16 *)((u8 *)ctx + 0x04) = sub_080C364C(0xC8 << 7, countdown);
        *(s16 *)((u8 *)ctx + 0x06) = sub_080C364C(0xC8 << 7, *(s32 *)((u8 *)obj + 0x10));
        {
            void *target = *(void **)((u8 *)obj + 0x2C);
            s32 scaled4 = (s32)*(s16 *)((u8 *)ctx + 0x04);
            *(s16 *)((u8 *)target + 0x06) = sub_080C364C(0x80 << 5, scaled4);
            target = *(void **)((u8 *)obj + 0x2C);
            {
                s32 scaled6 = (s32)*(s16 *)((u8 *)ctx + 0x06);
                *(s16 *)((u8 *)target + 0x08) = sub_080C364C(0xB0 << 4, scaled6);
            }
        }
        sub_08003740((u8 *)subObj + 0x20, ctx);
        sub_0806D588(ctx, obj);
        if (gMainWorkspace.field173A == 0x1C ||
            (gMainWorkspace.field14ED == 0 && gMainWorkspace.field10 != 0)) {
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        }
    }
}
