struct A_0808DCCC {
    u8 _0[2];
    u16 f02;
    u8 _04[0x14 - 0x04];
    void *f14;
    u8 _18[0x22 - 0x18];
    u16 f22;
    void *f24;
    u8 _28[0x38 - 0x28];
    void *f38;
    s32 f3C;
    u8 _40[0x6C - 0x40];
    u16 f6C;
    u8 _6E[0x74 - 0x6E];
    u8 f74;
};

struct R_0808DCCC {
    u16 f00;
    u16 f02;
    u8 _04[0x1C - 0x04];
    u32 f1C;
};

struct T_0808DCCC { u32 w[4]; };
extern struct T_0808DCCC D_08100208;
extern u8 D_081001FC[];

struct S_02025FF0 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;

extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, s32, u8 *);
extern void setAnimationFrame(void *, s32, s16, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_0808DDB0(void);

/*
 * Graphics setup for an entity: allocates a graphics object from the pool,
 * initializes it from the entity's animation index and style/flag bits, then
 * installs and runs the position-update callback.
 */
void sub_0808DCCC(struct A_0808DCCC *self) {
    struct T_0808DCCC angleTable = D_08100208;
    struct R_0808DCCC *gfx = allocSpriteObject();
    s32 animIndex;
    void *callback;

    if (gfx == NULL) {
        sub_080C31E0(self, self->f24);
        return;
    }
    self->f38 = gfx;
    allocWorkSlot(self, 0, 0x14, 0);
    animIndex = self->f3C;
    if (animIndex == 0) {
        sub_080C31E0(self, self->f24);
        return;
    }

    initSpriteGraphics(gfx, animIndex, D_081001FC);
    setAnimationFrame(gfx, animIndex, ((s16 *)angleTable.w)[self->f74 * 2], 0);

    switch (self->f6C & 0x30) {
    case 0x10:
        gfx->f02 = 0x10 | gfx->f02;
        break;
    case 0x20:
        gfx->f02 = 0x20 | gfx->f02;
        break;
    case 0x30:
        gfx->f02 = gfx->f02 | 0x30;
        break;
    }

    gfx->f1C = (self->f6C & 0xF) | 0x80000000;
    gfx->f00 = gfx->f00 | gMainWorkspace.f18C2;
    self->f02 = 0x800 | self->f02;
    callback = sub_0808DDB0;
    self->f14 = callback;
    self->f22 = 1;
    sub_080C31E0(self, callback);
}
