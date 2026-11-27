/* Per-frame camera/scroll update for an entity: skip when a special camera mode
 * owns the position, otherwise reset and constrain the scroll position, post an
 * idle effect, fire a timed effect when its counter expires, then run the final
 * camera update. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, u16, s32);
extern s32 gScriptStepCallbacks;
extern s32 gMenuScriptCallback;

void sub_08067934(u8 *entity) {
    u8 *cam = *(u8 **)(entity + 0x6C);
    u8 *pos = cam + 4;
    u8 *view = *(u8 **)(entity + 0x38);
    if (syncViewPosition(pos, pos) == 0) {
        resetActionResultState(entity, view, pos, pos);
        sub_0806AB04(entity, view, pos, pos);
        if (*(s32 *)(pos + 0x40) == 0) {
            *(s32 *)(pos + 0x4C) = 1;
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
            {
                s32 *effectData = &gScriptStepCallbacks;
                u8 *p18 = entity;
                u8 *p22 = entity;
                p18 += 0x18;
                p22 += 0x22;
                sub_080C31E8(p18, p22, 2, *effectData);
            }
        }
        sub_0806D588(view, pos);
        sub_0806A884(view, pos);
        if (stepDelayTimer(cam + 0x2C, view) == 0) {
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x17) = 0;
            {
                u8 *p18 = entity;
                u8 *p22 = entity;
                s32 *tailEffectData = &gMenuScriptCallback;
                u16 effectKind;
                p18 += 0x18;
                p22 += 0x22;
                effectKind = sub_08065CC8(entity, view, pos, pos);
                sub_080C31E8(p18, p22, effectKind, *tailEffectData);
            }
        }
        sub_0806C6B0(entity, view, pos, pos);
    }
}
