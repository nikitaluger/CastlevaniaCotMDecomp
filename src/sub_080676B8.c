struct S_080DEA88 { u8 _pad[0xE3 << 3]; s32 field; };
extern struct S_080DEA88 D_080DEA88;
extern s32 syncViewPosition(s32, s32);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AA64(void *, void *);
extern void startEffectTimer(void *, s32, s32);
extern s32 stepDelayTimer(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *spawnEntity(void *, s32, s32, s32);
extern s32 sub_0808D330();
extern void sub_080C31E4(void *, void *, s32);

/*
 * Updates an entity: refreshes its world position, advances a periodic spawn
 * counter, and when the effect-list check passes re-initialises its effect
 * timer and copies the animation state before running the main entity update.
 */
void sub_080676B8(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *subObj = *(u8 **)(entity + 0x6C);
    u8 *obj = subObj + 4;
    u8 *pos;
    void *ctx = *(void **)(entity + 0x38);
    s32 count;
    pos = obj;
    if (syncViewPosition((s32)pos, (s32)pos) == 0) {
        resetActionResultState(entity, ctx, pos, pos);
        sub_0806AA64(ctx, pos);
        subObj += 0xBC;
        count = *(s32 *)subObj + 1;
        *(s32 *)subObj = count;
        if (count <= 0x70 && (count & 7) == 0) {
            u8 *spawned = spawnEntity(entity, 0x2A, 0xA, 0x12);
            if (spawned != 0) {
                *(s32 *)(spawned + 0x7C) = *(s32 *)subObj;
            }
        }
        subObj = obj + 0x28;
        stepDelayTimer(subObj, ctx);
        if (sub_0808D330() != 0) {
            startEffectTimer(subObj, 0, D_080DEA88.field);
            *(s32 *)(obj + (0x86 << 1)) = *(s32 *)(obj + (0x82 << 1));
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
            {
                const u32 *effectIds = (const u32 *)0x08671BB0;
                sub_080C31E4(entity + 0x18, entity + 0x22, *effectIds);
            }
        }
        sub_0806C6B0(entity, ctx, obj, pos);
    }
}
