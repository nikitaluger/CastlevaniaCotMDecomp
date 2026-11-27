extern void *gScriptStepCallbacks;
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014990(void *);
extern void sub_0808E05C(s32, s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

static inline u32 low3(u8 v) { return v & 7; }

/* Advances a patrol position by a fixed step, spawns a particle on step 1,
 * and reverses the parent's facing flag at the range limit before dispatch. */
void sub_0803B828(void *entity) {
    void *parent;
    void *obj;
    void *animObj;
    s32 newPos;
    s32 zero;
    u32 stepKind;

    parent = *(void**)((u8*)entity + 0x38);
    obj = *(void**)((u8*)entity + 0x3C);
    animObj = (u8*)obj + 0x34;
    setAnimationFrame(parent, animObj, 5, 0);
    stepKind = low3(*((u8*)entity + *(s16*)((u8*)entity + 0x22)*2 + 0x19));
    if (stepKind == 1) {
        sub_0808E05C(*(s32*)((u8*)obj + 0x08), *(s32*)((u8*)obj + 0x0C), 1, 8);
    }
    if (sub_08014990(parent) < 0) {
        newPos = *(s32*)((u8*)obj + 0x10) + (0xC0 << 5);
        *(s32*)((u8*)obj + 0x10) = newPos;
        if (newPos >= 0) {
            setAnimationFrame(parent, animObj, 0, 1);
            {
                u16 flags = *(u16*)((u8*)parent + 0x02);
                flags ^= 0x10;
                zero = 0;
                *(u16*)((u8*)parent + 0x02) = flags;
            }
            *((u8*)entity + *(s16*)((u8*)entity + 0x22)*2 + 0x19) = zero;
            {
                u32 *pd = (u32 *)&gScriptStepCallbacks;
                sub_080C31E8((u8*)entity + 0x18, (u8*)entity + 0x22, 0, (s32)*pd);
            }
        }
    } else {
        newPos = *(s32*)((u8*)obj + 0x10) + (s32)0xFFFFE800;
        *(s32*)((u8*)obj + 0x10) = newPos;
        if (newPos <= 0) {
            setAnimationFrame(parent, animObj, 0, 1);
            {
                u16 flags = *(u16*)((u8*)parent + 0x02);
                flags ^= 0x10;
                zero = 0;
                *(u16*)((u8*)parent + 0x02) = flags;
            }
            *((u8*)entity + *(s16*)((u8*)entity + 0x22)*2 + 0x19) = zero;
            {
                u32 *pd = (u32 *)&gScriptStepCallbacks;
                sub_080C31E8((u8*)entity + 0x18, (u8*)entity + 0x22, 0, (s32)*pd);
            }
        }
    }
}
