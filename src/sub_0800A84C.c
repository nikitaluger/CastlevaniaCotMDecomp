/* Dialogue trigger: when the entity is allowed to speak, plays a cue and starts
 * one of two message sequences, clearing a buffer with DMA for the second. */
extern s32 sub_08005E80(s32);
extern void sub_08007FE0(void);
extern s32 sub_0800B8C4(void *, s32);
extern s32 sub_080103F0(u8);
extern void sub_080C31E8(void *, void *, s32, void *);
extern u8 D_02025FF0[];
extern u8 D_020278D0[];
extern volatile u32 D_040000D4[];
extern u32 D_08671BD8;

struct D02021E90 { u8 pad[0x146C]; u16 flag; };
extern struct D02021E90 D_02021E90;

struct A84C {
    u8 pad0[0x18];
    u32 msgArg0;
    u8 pad1[6];
    s16 msgIndex;
    u8 pad2[0x18];
    u32 dataPtr;
    u8 pad3[0x10];
    u8 id;
    u8 pad4[7];
    u8 flag58;
    u8 pad5[3];
    u8 flag5C;
};

void sub_0800A84C(struct A84C *self) {
    struct A84C *selfCopy = self;
    u8 *buf = (u8 *)self->dataPtr;
    s32 zero;
    u8 *entry;
    s32 check = sub_0800B8C4(self, 0);
    if (check == 0) {
        if (D_02021E90.flag & 1) {
            s32 choice = sub_080103F0(self->id);
            if (choice != 0) {
                sub_08005E80(0x15C);
                sub_08007FE0();
                D_02025FF0[8] = self->id;
                *(s32 *)D_020278D0 = 6;
                entry = (u8 *)((s32)self->msgIndex * 2 + (u32)self);
                *(u8 *)(entry + 0x17) = check;
                {
                    u32 *msgTable = &D_08671BD8;
                    sub_080C31E8(&self->msgArg0, &self->msgIndex, 0x11, (void *)*msgTable);
                }
            } else {
                sub_08005E80(0x157);
                self->flag58 = 0;
                self->flag5C = 0;
                zero = choice;
                D_040000D4[0] = (u32)&zero;
                D_040000D4[1] = (u32)buf + 0x600;
                D_040000D4[2] = 0x85000002;
                (void)D_040000D4[2];
                *(u8 *)(buf + 0x635) = 2;
                entry = (u8 *)((s32)self->msgIndex * 2 + (u32)self);
                *(u8 *)(entry + 0x17) = choice;
                {
                    u32 *msgTable = &D_08671BD8;
                    sub_080C31E8(&self->msgArg0, &self->msgIndex, 0x10, (void *)*msgTable);
                }
            }
        }
    }
}
