/* Enemy/boss per-frame update: on the first trigger state, queue a delayed
 * graphics load and install its callback, then always tick that load and
 * align the sprite to its sub-object's 3D position. */
extern void startEffectTimer(void *, s32, const void *);
extern void stepDelayTimer(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, u32);

extern u32 gMainWorkspace[];
extern const void D_084FEC5C;
extern u32 gScriptStepCallbackTable[];

void sub_08088B58(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *subObj = *(u8 **)(self + 0x6C);
    u8 *position = subObj + 4;
    u8 *sprite = *(u8 **)(self + 0x38);

    if (gMainWorkspace[7] == 1) {
        u32 *cbTable;
        startEffectTimer(subObj + 0x20, 0, &D_084FEC5C);
        gMainWorkspace[7] = 2;
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        cbTable = gScriptStepCallbackTable;
        sub_080C31E4(self + 0x18, self + 0x22, cbTable[0]);
    }

    stepDelayTimer(subObj + 0x20, sprite);
    sub_0806D588(sprite, position);
}
