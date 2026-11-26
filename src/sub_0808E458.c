struct A {
    u8 _0[2]; u16 flags; u8 _04[0x14 - 0x04]; void *callback;
    u8 _18[0x22 - 0x18]; u16 state16; void *altCallback;
    u8 _28[0x38 - 0x28]; void *object; s32 objectId;
    u8 _40[0x6C - 0x40]; u16 modeFlags;
    u8 _6E[0x7C - 0x6E]; u8 tableIndex;
};
struct R { u16 flags; u16 flags2; u8 _04[0x1C - 0x04]; u32 state; };
struct T2 { u32 w[2]; };
extern struct T2 D_08100250;
extern u8 D_08100244[];
struct S_02025FF0 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern struct R *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, s32, u8 *);
extern void setAnimationFrame(void *, s32, s16, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_0808E544(void);

/* Allocate and configure an object for this entity, then hand control to the
 * entity's update callback. */
void sub_0808E458(struct A *arg) {
    struct T2 paramTable = D_08100250;
    struct R *res = allocSpriteObject();
    s32 objectId;
    void *fp;

    if (res == NULL) { sub_080C31E0(arg, arg->altCallback); return; }
    arg->object = res;
    allocWorkSlot(arg, 0, 0x14, 0);
    objectId = arg->objectId;
    if (objectId == 0) { sub_080C31E0(arg, arg->altCallback); return; }

    initSpriteGraphics(res, objectId, D_08100244);
    setAnimationFrame(res, objectId, ((s16 *)paramTable.w)[arg->tableIndex * 2], 0);

    switch (arg->modeFlags & 0x30) {
    case 0x10: res->flags2 = 0x10 | res->flags2; break;
    case 0x20: res->flags2 = 0x20 | res->flags2; break;
    case 0x30: res->flags2 = res->flags2 | 0x30; break;
    }

    res->state = (arg->modeFlags & 0xF) | 0x80000000;
    res->flags = res->flags | gMainWorkspace.f18C2;
    res->flags2 = res->flags2 | 0x400;
    arg->flags = 0x800 | arg->flags;
    fp = sub_0808E544;
    arg->callback = fp;
    arg->state16 = 1;
    sub_080C31E0(arg, fp);
}
