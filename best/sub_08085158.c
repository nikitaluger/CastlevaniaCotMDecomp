extern u32 sub_08061C78(void);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_0806D77C(s32, s32);
extern void sub_08086E28(void);
extern void playSound(s32);
extern s32 sub_080C3824(s32, s32);

struct S25FF0 {
    u8 _0[0x14ED]; u8 f14ED; u8 _14EE[6];
    u32 f14F4; u8 _14F8[4]; u32 f14FC, f1500; s16 f1504, f1506;
    u32 f1508; u8 _150C[0x180C-0x150C]; u32 f180C, f1810, f1814;
};
extern struct S25FF0 gMainWorkspace;
struct S25368 { u8 _0[0x2CC]; u32 f2CC, f2D0; u8 _2D4[0x300-0x2D4]; u32 f300; };
extern struct S25368 gGameStatus;
struct Arg1 { u8 _0[0x44]; u32 f44; u8 _48[0x9C-0x48]; u32 f9C, fA0; u8 _A4[0xB8-0xA4]; u32 fB8; };
struct Obj { u8 _0[0x7C]; u16 f7C; };

void sub_08085158(s32 arg0, struct Arg1 *arg1, s32 arg2) {
    u32 r6;
u32 __repair_result_r6;
    void *o;
    u32 t_1;
    u32 t_2;
    
    u32 off;
    u8 cmd;
    struct S25368 *p68 = &gGameStatus;
    u8 temp;

    gMainWorkspace.f1814 = 0;
    off = 0x14ED;
    temp = *(u8 *)((u8 *)&gMainWorkspace + off);
    cmd = temp;
    switch (cmd) {
    case 0x23:
        if (gMainWorkspace.f1506 == 0) return;
        o = sub_0806D2A0(arg0, 0x34, 0xA, 0x12);
        if (o != NULL) ((struct Obj *)o)->f7C = 0;
        sub_08086E28();
        return;
    case 0x24:
    case 0x28:
        __repair_result_r6 = sub_08061C78();
        if (__repair_result_r6 <= arg1->fB8) return;
        o = sub_0806D2A0(arg0, 0x34, 0xA, 0x12);
        if (o != NULL) ((struct Obj *)o)->f7C = 0;
        sub_08086E28();
        arg1->fB8 = __repair_result_r6;
        return;
    case 0x26:
        if (gMainWorkspace.f1504 == 0) return;
        o = sub_0806D2A0(arg0, 0x34, 0xA, 0x12);
        if (o != NULL) ((struct Obj *)o)->f7C = 0;
        sub_08086E28();
        return;
    case 0x27:
        if ((s32)p68->f2CC < (s32)p68->f2D0) {
            t_1 = (arg1->fB8 + 1) & 0x3F;
            arg1->fB8 = t_1;
            if (t_1 == 0) {
                o = sub_0806D2A0(arg0, 0x34, 0xA, 0x12);
                if (o != NULL) ((struct Obj *)o)->f7C = 0;
                sub_08086E28();
            }
        } else {
            arg1->fB8 = 0;
        }
        return;
    case 0x33:
        if (gMainWorkspace.f14FC != 0) {
            t_2 = gMainWorkspace.f14F4 + 1;
            gMainWorkspace.f14F4 = t_2;
            if (t_2 > 0x3B) {
                gMainWorkspace.f14F4 = 0;
                sub_0806D77C(arg2, 1);
                sub_08086E28();
            }
        }
        return;
    case 0x35:
        arg1->f44 = 3;
        gMainWorkspace.f1814 = 1;
        sub_08086E28();
        return;
    case 0x36:
        if ((s32)arg1->fB8 <= 0) {
            arg1->fB8 = 0xC;
            sub_0806D2A0(arg0, 0x38, 0xA, 0x12);
            sub_08086E28();
            playSound(0xD8);
        }
        arg1->fB8--;
        return;
    case 0x3A:
        arg1->f9C = 2;
        arg1->fA0 = 2;
        gMainWorkspace.f1810 = 1;
        gMainWorkspace.f180C = 0;
        return;
    case 0xA1:
        arg2 = gMainWorkspace.f14F4;
        if (arg2 != 0) {
            arg2--;
            gMainWorkspace.f14F4 = arg2;
            if ((arg2 <= 0x1FF) && !(arg2 & 3)) {
                sub_0806D2A0(arg0, 0x29, 0xA, 0x12);
            }
        }
        return;
    case 0xA3:
        r6 = p68->f300;
        if (r6 > (u32)gMainWorkspace.f1508) {
            p68->f300 = r6 + sub_080C3824(r6 - gMainWorkspace.f1508, 5);
            o = sub_0806D2A0(arg0, 0x34, 0xA, 0x12);
            if (o != NULL) {
                ((struct Obj *)o)->f7C = 0;
            }
            sub_08086E28();
        }
        return;
    }
}
