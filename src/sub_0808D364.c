struct R_0808D364 {
    u32 f00;
    u32 f04;
    u32 f08;
    u32 f0C;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1C;
    u32 f20;
    u8 _24[0x38 - 0x24];
    u8 f38;
    u8 _39[3];
    u8 f3C;
    u8 _3D;
    u8 f3E;
};

struct A_0808D364 {
    u8 _0[2];
    u16 f02;
    u8 _04[0x14 - 0x04];
    void *f14;
    u8 _18[0x22 - 0x18];
    u16 f22;
    void *f24;
    u8 _28[0x38 - 0x28];
    void *f38;
    struct R_0808D364 *f3C;
    u8 _40[0x6C - 0x40];
    void *f6C;
};

struct gCameraState {
    u8 _0[0x1460];
    s8 f1460;
    u8 _1461;
    s8 f1462;
    u8 _1463;
    s8 f1464;
    u8 _1465;
    s8 f1466;
    u8 _1467;
    s8 f1468;
    s8 f1469;
    s8 f146A;
};
extern struct gCameraState gCameraState;
extern vu32 D_040000D4[];

extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_0808D640(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_0808D454(void);

/* Initializes a scripted effect entity: sets up its graphics transfer
 * registers, allocates and seeds a transform/velocity record from the parent
 * position, publishes its angles to the shared angle table, then installs the
 * first-phase update callback. */
void sub_0808D364(struct A_0808D364 *entity) {
    u16 scaleValue = 0x7FFF;
    struct R_0808D364 *fx;
    struct gCameraState *angleTable;
    s32 zero;
    s32 angle;

    D_040000D4[0] = (u32)&scaleValue;
    D_040000D4[1] = 0x05000000;
    D_040000D4[2] = 0x80000001;
    (void)D_040000D4[2];

    allocWorkSlot(entity, 0, 0x40, 3);

    fx = entity->f6C;
    if (fx == NULL) {
        sub_080C31E0(entity, entity->f24);
        return;
    }

    fx->f00 = (u32)entity->f3C;
    fx->f08 = (u32)entity->f3C;
    fx->f04 = (u32)entity->f3C;
    fx->f10 = (u32)entity->f3C + 0x10000;
    fx->f0C = (u32)entity->f3C + 0x10000;
    fx->f14 = 0x4F0000;
    zero = 0;
    fx->f18 = zero;
    fx->f1C = 0x510000;
    fx->f20 = 0xA00000;
    fx->f3C = 1;
    fx->f3E = 1;
    sub_0808D640(fx);

    angleTable = &gCameraState;
    angle = *(s16 *)((u8 *)fx + 0x06);
    angleTable->f1460 = (s8)angle;
    angle = *(s16 *)((u8 *)fx + 0x16);
    angleTable->f1464 = (s8)angle;
    angle = *(s16 *)((u8 *)fx + 0x0E);
    angleTable->f1462 = (s8)angle;
    angle = *(s16 *)((u8 *)fx + 0x1E);
    angleTable->f1466 = (s8)angle;
    angleTable->f1468 = 0x31;
    angleTable->f1469 = 0x31;
    angleTable->f146A = fx->f38;

    entity->f02 = 0x800 | entity->f02;
    entity->f22 = zero;
    entity->f14 = sub_0808D454;
}
