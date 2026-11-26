struct S02025FF0 {
    u8 _0[0x14ED];
    u8 f14ED;
    u8 _1[0x14EF - 0x14EE];
    u8 f14EF;
    u8 _2[0x14FC - 0x14F0];
    u32 f14FC;
    u32 f1500;
    u8 _3[0x150C - 0x1504];
    u32 f150C;
    u8 f1510;
    u8 _4[0x1514 - 0x1511];
    u32 f1514;
    u8 _5[0x18BE - 0x1518];
    u16 f18BE;
};
extern struct S02025FF0 gMainWorkspace;

struct S02025368 { u32 data[1]; };
extern struct S02025368 gGameStatus;

struct SObj {
    u8 _0[0xCC];
    u16 fCC;
    u8 _1[(0x96 << 1) - 0xCE];
    u8 *f12C;
};

extern void sub_0806D930(u32 *);
extern s32 sub_080C364C(s32, s32);

/* Reset the shared result flags, recompute the stats block, then derive a
 * result code from the current mode and store a masked copy on the object. */
void sub_0806C5EC(s32 unused0, s32 unused1, struct SObj *obj) {
    u32 *state = gGameStatus.data;
    struct S02025FF0 *flags = &gMainWorkspace;
    u8 *modeFlag, *resultFlag;
    u32 *result;

    modeFlag = &flags->f14ED;
    flags->f14EF = *modeFlag;
    flags->f14FC = 0;
    flags->f1500 = 0;
    result = &flags->f150C;
    *result = 0;
    flags->f18BE = 0;
    obj->fCC = 0;
    resultFlag = &flags->f1510;
    *resultFlag = 0xFF;
    flags->f1514 = 0;
    sub_0806D930(&state[0xB1]);
    {
        u8 mode = *modeFlag;
        switch (mode) {
        case 0xA6:
            *result = sub_080C364C(state[0xB3], 0x50000);
            break;
        case 0xA9:
            *resultFlag = 0;
            break;
        }
    }
    obj->f12C[1] = 5 & gMainWorkspace.f1510;
}
