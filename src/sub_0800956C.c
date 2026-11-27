extern u32 gScriptStepCallbackTable;
void clearActorPool(void);
void decompressToVram(const void *src, void *dst);
void postDisplaySprite(s32 a, const void *src, void *dst, s32 c, s32 d);
u8 *sub_08001480(void *arg0, s32 idx);
s32 sub_08005F1C(void);
void sub_080C0574(void);
void sub_080C08D0(s32);
void sub_08005E80(s32);
typedef void (*Func2)(void *, void *);

struct B {
    u8 _0[0x125C];
    u32 f125C;
    u16 f1260;
    u16 f1262;
    u8 _1264[0x14];
    u32 f1278;
    u32 f127C;
    u8 _1280[0x20];
    u16 f12A0;
    u8 _12A2[0x3E];
    u16 f12E0;
    u8 _12E2[0x3E];
    u16 f1320;
};

/*
 * Loads/initializes a level scene: resets the global view state and graphics
 * mode, clears VRAM, DMA-copies in the scene's tiles and palettes, creates its
 * objects and finally invokes the setup callback in gScriptStepCallbackTable.
 */
void sub_0800956C(void *scene)
{
    struct B *world = (struct B *)0x02021E90;
    u32 zero;
    u16 fillWord;
    volatile u32 *dmaReg;
    u8 *obj;
    u8 *counter;
    u32 coordOff;
    u16 mode;
    world->f125C = 0;
    mode = *(volatile u16 *)0x03000830;
    mode &= 0xF0FF;
    zero = 0;
    *(volatile u16 *)0x03000830 = mode + zero;
    world->f1260 = 0xD8 << 8;
    world->f1320 = 0;
    world->f12E0 = 0;
    world->f12A0 = 0;
    world->f1262 = 0x88;
    coordOff = 0x1278;
    *((u32 *)((u8 *)world + coordOff + 4)) = 0;
    *((u32 *)((u8 *)world + coordOff)) = 0;
    clearActorPool();
    fillWord = 0;
    dmaReg = (volatile u32 *)0x040000D4;
    dmaReg[0] = (u32)&fillWord;
    dmaReg[1] = 0x06000000;
    dmaReg[2] = 0x8100C000;
    dmaReg[2];
    decompressToVram((void *)0x08634AC8, (void *)0x0600C000);
    decompressToVram((void *)0x086363FC, (void *)0x06000000);
    postDisplaySprite(1, (void *)0x086361BC, (void *)0x05000000, 0x200, 0x10);
    decompressToVram((void *)0x08635A70, (void *)0x06010000);
    postDisplaySprite(1, (void *)0x086363BC, (void *)0x050002A0, 0x40, 0x10);
    *(u8 *)((u8 *)scene + 0x5C) = 2;
    obj = sub_08001480(scene, 0x16);
    *(u8 *)(obj + 0x3C) = 0;
    obj = sub_08001480(scene, 0x16);
    *(u8 *)(obj + 0x3C) = 1;
    if (sub_08005F1C() == 0)
    {
        sub_080C0574();
        sub_080C08D0(0xC0000);
        sub_08005E80(1);
    }
    *(u32 *)((u8 *)scene + 4) = 0;
    { s16 objIndex = *(s16 *)((u8 *)scene + 0x22);
      u32 byteOffset = objIndex * 2;
      counter = (u8 *)(byteOffset + (u32)scene) + 0x19; }
    *counter = zero;
    ((Func2)gScriptStepCallbackTable)((u8 *)scene + 0x18, (u8 *)scene + 0x22);
}
