extern void sub_08001738(void *obj);
extern void *sub_08001480(void *parent, s32 kind);
extern void sub_080C31E4(void *stepData, void *stepIndex, s32 callback);
extern u32 D_02025FF0[];
extern s32 D_08671BB0;

struct S_03000830 { u8 pad[8]; u16 count; };
extern struct S_03000830 D_03000830;

/* Script step: frees three global objects and bumps a counter; once the gfx
 * counter reaches 0x10, snapshots the palette, creates a new kind-0x10 object
 * and advances the script. */
void sub_080075DC(void *arg0) {
    u8 *self = (u8 *)arg0;
    u32 obj1Off = 0x1854;
    u32 obj2Off = 0x1860;
    u32 obj3Off = 0x1894;
    u32 obj4Off = 0x1888;
    u32 gfxCount;

    sub_08001738(*(void **)((u8 *)D_02025FF0 + obj1Off));
    sub_08001738(*(void **)((u8 *)D_02025FF0 + obj2Off));
    *(u32 *)((u8 *)D_02025FF0 + obj3Off) += 1;
    sub_08001738(*(void **)((u8 *)D_02025FF0 + obj4Off));

    gfxCount = D_03000830.count + 2;
    D_03000830.count = (u16)gfxCount;
    if ((u16)gfxCount == 0x10) {
        u16 palette = *(u16 *)0x05000000;
        u32 palSlotOff = 0x1768;
        u32 newObjOff = 0x1884;
        *(u16 *)((u8 *)D_02025FF0 + palSlotOff) = palette;
        *(u32 *)((u8 *)D_02025FF0 + newObjOff) = (u32)sub_08001480(0, 0x10);
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        {
            s32 *scriptCb = &D_08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
        }
    }
}
