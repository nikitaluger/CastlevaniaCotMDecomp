struct B_080A1348 {
    u8 _0[4];
    u32 f4;
    u8 _8[0x16 - 0x8];
    u8 f16;
    u8 _17[0x18 - 0x17];
    u32 f18;
    u32 f1C;
};

struct C_080A1348 {
    u8 _0[0x60];
    u8 f60;
    u8 _61[3];
    u32 f64;
};

struct S_080A1348 { u8 _0[0x17]; u8 f17; u8 f18; u8 f19; };

struct A_080A1348 {
    u8 _0[0x22];
    s16 f22;
    u8 _24[0x38 - 0x24];
    void *f38;
    struct C_080A1348 *f3C;
};

extern void *D_08671BD8;

extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_08011528(void *, void *);
extern void sub_08098598(s32, void *, s32, void *);
extern void sub_080A2D98(u32);
extern void sub_080A2DA0(u32);
extern void sub_080C31E8(void *, void *, s32, void *);

/* Update the companion sprite, then handle the script step's timed events:
 * play sounds at steps 0x5A/0x78 and redirect the script from its control byte. */
void sub_080A1348(struct A_080A1348 *obj) {
    void *sprite = obj->f38;
    struct C_080A1348 *scriptState = obj->f3C;
    void *stateArg = (u8 *)scriptState + 0x34;
    struct B_080A1348 *control = (struct B_080A1348 *)((u8 *)scriptState + 0x48);
    u8 controlByte;
    u8 controlByte2;

    sub_080114DC(sprite, stateArg, 0, 1);
    sub_08011528(sprite, stateArg);

    if (((struct S_080A1348 *)((u8 *)obj + obj->f22 * 2))->f19 > 0x5A) {
        sub_08098598(0x170, (u8 *)scriptState + 0x60, 0xA, (u8 *)scriptState + 0x64);
    }
    if (((struct S_080A1348 *)((u8 *)obj + obj->f22 * 2))->f19 == 0x5A) {
        controlByte = control->f16;
        switch (controlByte) {
        case 0:
            control->f1C = 7;
            control->f18 = controlByte;
            sub_08098598(0x170, (u8 *)scriptState + 0x60, 0xA, (u8 *)scriptState + 0x64);
            sub_080A2D98(control->f4);
            break;
        case 1:
            sub_080A2DA0(control->f4);
            break;
        }
    }
    if (((struct S_080A1348 *)((u8 *)obj + obj->f22 * 2))->f19 == 0x78) {
        controlByte2 = control->f16;
        switch (controlByte2) {
        case 0:
            ((struct S_080A1348 *)((u8 *)obj + obj->f22 * 2))->f17 = controlByte2;
            {
                void **handlerAddr = &D_08671BD8;
                sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 2, *handlerAddr);
            }
            return;
        case 1:
            ((struct S_080A1348 *)((u8 *)obj + obj->f22 * 2))->f17 = 0;
            {
                void **handlerAddr = &D_08671BD8;
                sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 1, *handlerAddr);
            }
            break;
        }
    }
}
