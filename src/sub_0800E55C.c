void *createChildObject(void *, s32);
void sub_0800F4D4(u8, u8, s32);
void sub_0800F6BC(void);
extern u8 gMenuState[];
extern u8 gCameraState[];
extern volatile u32 D_040000D4[3];

typedef struct { u8 pad[0x48]; u32 object; } T_020278D0;

/* Allocate the status object, load its graphics, then zero two VRAM regions
 * selected by the current area's flag. */
void sub_0800E55C(void *parent) {
    void *object;
    s16 dmaFillWord;
    s16 zero;
    u32 t;

    object = createChildObject(parent, 0x1B);
    ((T_020278D0 *)gMenuState)->object = (u32)object;
    object = (u8 *)object + 0x3C;
    zero = 0;
    *(u8 *)object = 6;
    sub_0800F4D4(gMenuState[0xF9], gMenuState[0xFA], 0x84 << 2);
    sub_0800F6BC();
    dmaFillWord = zero;
    D_040000D4[0] = (u32)&dmaFillWord;
    {
        u32 stateBase = (u32)gCameraState;
        u32 colorOffset = 0x1262;
        t = (*(u16 *)(stateBase + colorOffset) & 0xC) << 12;
    }
    D_040000D4[1] = t + 0x06000040;
    D_040000D4[2] = 0x810007E0;
    (void)D_040000D4[2];
    dmaFillWord = zero;
    D_040000D4[0] = (u32)&dmaFillWord;
    D_040000D4[1] = t + 0x06000020;
    D_040000D4[2] = 0x81000010;
    (void)D_040000D4[2];
}
