extern s32 sub_08005E80(s32);
extern void sub_080113A8(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_08013B5C(void *, void *);
extern s32 hitTestEntities(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct S28 { u8 a; u8 flag; u8 pad[0x12]; u16 flag2; };
struct P3C { u16 f0; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Per-frame update for one entity: tests collision and active state, handles
 * the death/recycle path through the state's jump table, then repositions the
 * sprite against the camera. */
void sub_0804D9CC(void *entity) {
    void *sprite;
    void *state;
    void *anim;
    struct P3C *stateFlags;
    struct S28 *fx;
    sprite = *(void **)((u8 *)entity + 0x38);
    state = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)state + 0x34;
    stateFlags = (struct P3C *)state;
    fx = *(struct S28 **)((u8 *)state + 0x28);
    fx->flag |= 5;
    if (sub_0805F9B4(*(s32 *)((u8 *)state + 8), *(s32 *)((u8 *)state + 0xC)) == 1) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        goto end;
    }
    if (hitTestEntities(*(void **)((u8 *)state + 0x28)) != 0) stateFlags->f0 |= 1;
    if ((*(struct S28 **)((u8 *)state + 0x28))->flag2 & 1) stateFlags->f0 |= 1;
    if (stateFlags->f0 & 1) {
        if (*((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1A) != 1) {
            s32 *callbackSlot;
            sub_08005E80(0x189);
            *((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1B) = 0;
            callbackSlot = (s32 *)0x08671BDC;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 1, *callbackSlot);
        }
    }
    if (sub_08013B5C(sprite, state) != 0) goto else_branch;
    *(u32 *)((u8 *)entity + 0x14) = 0x0866E518;
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
    {
        u8 *desc = (u8 *)((s16)(*(u16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
        desc[0x19] = desc[0x19] + 1;
    }
    {
        s32 slot = (s16)(*(u16 *)((u8 *)entity + 0x22)) * 2;
        u8 *q = (u8 *)entity; u8 which;
        q += 0x18; q += slot; which = *q;
        sub_080C31E0(entity, *(s32 *)(*(u32 *)((u8 *)entity + 0x14) + (u32)(which * 4)));
    }
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    if (*(u16 *)((u8 *)entity + 2) & 0x8000) goto end;
    sub_080113A8(sprite, anim);
    advanceMotion(state, 0);
else_branch:
    {
        struct S28 *fx2; u8 *camTable; u8 *camBase; u32 idx; u8 *colX; u8 *colY;
        fx2 = *(struct S28 **)((u8 *)state + 0x28);
        fx2->flag2 = 0;
        camTable = gCameraState; camBase = gMainWorkspace; camBase += 0x18A8;
        idx = ((u32)*camBase + 1) * 0x40;
        colX = camTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)state + 8) - ((*(s32 *)(colX + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*camBase + 1) * 0x40;
        colY = camTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)state + 0xC) - ((*(s32 *)(colY + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
end:
    ;
}
