extern vu32 D_02025FF0;
extern vu32 D_08671BB0;

void *sub_0805FAEC(s32, s32);
void sub_080161F0(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
void sub_08011368(u32, void *, u32, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    u32 unk_0x3C;
};

struct SubObj {
    u8 pad_0x00[0x24];
    u32 unk_0x24;
    u32 unk_0x28;
    u8 pad_0x2C[0x34 - 0x2C];
    u8 unk_0x34;
};

struct ResultObj {
    u8 pad_0x00[0x4C];
    s16 unk_0x4C;
    u8 pad_0x4E[0x54 - 0x4E];
    s16 unk_0x54;
};

/* Per-frame object update: when the sub-object requests cleanup, run the
 * object-list cleanup, then dispatch this object's script handler at +0x24. */
void sub_08028918(struct MainObj *arg0) {
    struct SubObj *sub = (struct SubObj *)arg0->unk_0x3C;
    if (sub->unk_0x28 != 0) {
        sub_080161F0();
    }
    sub_080C31E0(arg0, sub->unk_0x24);
}
