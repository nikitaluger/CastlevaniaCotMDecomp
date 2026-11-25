extern s32 sub_08003740(void *, void *);
extern s32 sub_08003A6C(void *, s32, void *);
extern s32 sub_0806D450(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct GlobalState_83A84 {
    u8 _pad0[0x10];
    u32 field10;
    u8 _pad1[0x14ED - 0x14];
    u8 byte14ED;
    u8 _pad2[0x173A - 0x14EE];
    u8 byte173A;
    u8 _pad3[0x18C2 - 0x173B];
    u16 word18C2;
};
extern struct GlobalState_83A84 D_02025FF0;
extern u8 D_084FACEC[];

/* Actor script step: handle special-area movement, tick the animation timer and
 * snap the sprite to the grid; on expiry play a cue and advance the script. */
void sub_08083A84(void *actor) {
    void *work;
    void *position;
    void *sprite;
    struct GlobalState_83A84 *globals;
    s32 timerResult;

    work = *(void **)((u8 *)actor + 0x6C);
    position = (u8 *)work + 4;
    sprite = *(void **)((u8 *)actor + 0x38);

    if (sub_0806D450(actor, sprite, position) > 0) {
        sub_080C31E0(actor, *(void **)((u8 *)actor + 0x24));
        return;
    }

    {
        void *linkData = *(void **)((u8 *)position + 0x4C);
        if (*(u8 *)((u8 *)linkData + 1) == *(u8 *)((u8 *)work + 0x54)) {
            *(s32 *)((u8 *)work + 4) = *(s32 *)((u8 *)linkData + 0xC);
            *(s32 *)((u8 *)position + 4) = *(s32 *)((u8 *)linkData + 0x10);
        }
    }

    globals = &D_02025FF0;
    *(u16 *)sprite = globals->word18C2;

    {
        void *timer = (u8 *)work + 0x20;
        timerResult = sub_08003740(timer, sprite);
        if (timerResult == 0) {
            s32 *scriptTable;
            timerResult = sub_08003A6C(timer, 0, D_084FACEC);
            *(u8 *)((u8 *)actor + (s32)(*(s16 *)((u8 *)actor + 0x22) * 2) + 0x19) = 0;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, *scriptTable);
            return;
        }
    }

    sub_0806D588(sprite, position);

    if (globals->byte173A == 0x1C || (globals->byte14ED == 0 && globals->field10 != 0)) {
        sub_080C31E0(actor, *(void **)((u8 *)actor + 0x24));
    }
}
