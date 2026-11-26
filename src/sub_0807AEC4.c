/* Spawns a companion object from the object pool and initializes its state,
 * callbacks and motion values; on allocation failure it just clears the old
 * object. Finally it advances the action byte and dispatches the next script
 * handler. */
extern void sub_08003A6C(void *, s32, void *);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080722E0(void *, u8);
extern void sub_0808449C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u32 D_084DB5E8;
extern u32 D_084DB794;
extern s32 gMainObjTimerCallback;

/* Buffer at state+4: +0x2C holds the spawned object (reloaded each use) */
struct SpawnBuf { u8 _0[0x2C]; u8 * volatile spawned; };
struct GlobalFlags { u8 _0[0x1510]; u8 flag1510; };
extern struct GlobalFlags gMainWorkspace;

void sub_0807AEC4(u8 *self) {
    s32 zero;
    s32 scaleConst;
    u8 *state = *(u8 **)(self + 0x6C);
    u8 *buf = state + 4;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *paramTable = gGameStatus;
    void *newObj;
    struct SpawnBuf *obj = (struct SpawnBuf *)buf;

    newObj = allocEffectPart();
    obj->spawned = newObj;
    if (newObj == NULL) {
        sub_0806D2D0(self);
        return;
    }
    zero = 0;
    *(u32 *)(buf + 0x30) = zero;
    *(u32 *)(buf + 0x34) = zero;
    *(u32 *)(buf + 0x38) = zero;
    *(u32 *)(buf + 0x3C) = zero;
    *(u8 *)(newObj + 1) = 1 & gMainWorkspace.flag1510;
    *(u8 *)(obj->spawned + 2) = 2;
    *(u8 *)(obj->spawned + 3) = 8;
    *(u16 *)(obj->spawned + 4) = *(u8 *)(paramTable + 0x304);
    *(u16 *)(obj->spawned + 6) = 4;
    *(u16 *)(obj->spawned + 8) = 4;
    *(u16 *)(obj->spawned + 0xA) = zero;
    *(u16 *)(obj->spawned + 0xC) = zero;
    *(u16 *)(obj->spawned + 0xE) = sub_0806D62C(*(u16 *)(paramTable + 0x2E2), 0x32);
    *(u16 *)(obj->spawned + 0x16) = 0x1E;
    *(u16 *)(obj->spawned + 0x18) = 0x59;
    {
        u8 *objCopy = obj->spawned;
        *(void **)(objCopy + 0x10) = gfx;
    }
    *(u32 *)(buf + 0x18) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(gfx + 0x24) = (u32)&D_084DB5E8;
    sub_08003A6C(state + 0x20, 0, &D_084DB794);
    *(u32 *)(state + 4) = *(u32 *)(self + 0x7C);
    *(u32 *)(buf + 4) = *(u32 *)(self + 0x8C);
    scaleConst = 0xA0 << 0xB;
    *(s32 *)(buf + 0x40) = scaleConst;
    {
        u32 srcValue = *(u32 *)(self + 0x9C);
        *(u8 *)(state + 0x48) = srcValue;
    }
    sub_080722E0(buf, *(u8 *)(state + 0x48));
    {
        s32 scaleFactor = *(s32 *)(buf + 0x40) >> 8;
        *(s32 *)(buf + 8) = (*(s32 *)(buf + 8) * scaleFactor) / 256;
        *(s32 *)(buf + 0xC) = (*(s32 *)(buf + 0xC) * scaleFactor) / 256;
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    {
        s32 *cbTable = &gMainObjTimerCallback;
        u8 *scriptPtr = self + 0x18;
        sub_080C31E4(scriptPtr, self + 0x22, *cbTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) + 1;
        scriptPtr += *(s16 *)(self + 0x22) * 2;
        {
            u8 cmdId = *scriptPtr;
            sub_080C31E0(self, *(s32 *)(cmdId * 4 + *(u32 *)(self + 0x14)));
        }
    }
}
