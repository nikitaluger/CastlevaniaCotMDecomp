/* Spawns a new object at a position taken from a table indexed by gMainWorkspace.idx,
 * initialises its state from the parent object, then fires the queued callbacks
 * and clears this object's effect state. */
struct Rec64 { u32 a; u32 b; u8 pad[0x38]; };
struct S_02025FF0_AC { u8 _0[0x18A8]; u8 idx; u8 _1[0x13]; u16 f; };
extern struct S_02025FF0_AC gMainWorkspace;
struct S_02021E90_AC { u8 _0[0x1278]; struct Rec64 recs[1]; };
extern struct S_02021E90_AC gCameraState;
extern u32 gMainObjTimerCallback;
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080B0934(s32, s32);
extern void sub_080ACE78(void *, void *, void *);
extern void sub_080ACEBC(void *, void *);
extern void sub_080B07EC(void);

void sub_080AC478(void *obj) {
    u8 *objBytes = obj;
    u8 *work = *(u8 **)(objBytes + 0x3C);
    u8 *work48 = 0x48 + work;
    u8 *posXPtr;
    u8 *posYPtr;
    u8 *child;
    u32 i;
    u32 *slotPtr;
    u32 slotObj;
    u32 *endFuncs;
    s16 idx;

    gMainWorkspace.f = 0;
    posXPtr = work + 0x234;
    *(u32 *)posXPtr = gCameraState.recs[gMainWorkspace.idx + 1].a + (0xF1 << 15);
    posYPtr = work + 0x238;
    *(u32 *)posYPtr = gCameraState.recs[gMainWorkspace.idx + 1].b + (0x9E << 14);
    *(u32 *)(work + 0xC8) = sub_080B0934(*(u32 *)posXPtr, *(u32 *)posYPtr);
    sub_080ACE78(objBytes, work, work + 0xC8);
    sub_080ACEBC(work + 0xC8, work + 0x98);
    sub_080B07EC();
    child = *(u8 **)(work48 + 0x50);
    sub_080C31E0(child, *(u32 *)(child + 0x24));
    child = *(u8 **)(work48 + 0x54);
    sub_080C31E0(child, *(u32 *)(child + 0x24));
    child = *(u8 **)(work48 + 0x58);
    sub_080C31E0(child, *(u32 *)(child + 0x24));
    i = 0;
    slotPtr = (u32 *)(work + 0xA4);
    do {
        slotObj = *slotPtr++;
        sub_080C31E0((void *)slotObj, *(u32 *)(slotObj + 0x24));
        i++;
    } while (i <= 1);
    child = *(u8 **)(work48 + 0x2C);
    sub_080C31E0(child, *(u32 *)(child + 0x24));
    *(u32 *)(objBytes + 0x04) = 0;
    idx = *(s16 *)(objBytes + 0x22);
    *(u8 *)(objBytes + idx * 2 + 0x19) = 0;
    endFuncs = (u32 *)0x08671BB0;
    sub_080C31E4(objBytes + 0x18, objBytes + 0x22, *endFuncs);
}
