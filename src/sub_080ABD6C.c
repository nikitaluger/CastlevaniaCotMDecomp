extern void sub_0808BB54(void);
extern void copyPoseAttrs(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);

extern s32 gScriptStepCallbackTable;
extern u8 D_081021CC[];

struct S_03000830 {
    u8 _0[4];
    u16 field4;
    u16 field6;
};
extern struct S_03000830 gCrossfadeGfxState;

/* Update a scripted entity's step: track the step-phase counter in the shared
 * registers, and when it reaches 0x10 clear the parent flag, install the
 * special-action data, flag the child nodes and dispatch the script action. */
void sub_080ABD6C(void *entity)
{
    void *parent;
    void *component;
    void *extras;

    parent = *(void **)((u8 *)entity + 0x38);
    component = *(void **)((u8 *)entity + 0x3C);
    extras = (u8 *)component + 0x48;

    if ((*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) & 7) == 0) {
        *(u8 *)((u8 *)component + 0x95) += 1;
    }

    gCrossfadeGfxState.field4 = 0x3F40;

    if (((*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) & 7) != 0) || (*(u8 *)((u8 *)component + 0x95) > 8)) {
        gCrossfadeGfxState.field6 = *(u8 *)((u8 *)component + 0x95);
    } else {
        gCrossfadeGfxState.field6 = 8;
    }

    if (*(u8 *)((u8 *)extras + 0x4D) == 0x10) {
        s32 zero;
        u16 newFlags;
        u8 *stepPtr;
        s16 pcOffset;

        newFlags = *(u16 *)((u8 *)parent + 2) & 0xFBFF;
        zero = 0;
        *(u16 *)((u8 *)parent + 2) = newFlags;
        sub_0808BB54();
        *(u8 *)(*(u8 **)((u8 *)component + 0x28) + 1) = 5;
        copyPoseAttrs(*(void **)((u8 *)component + 0x28), D_081021CC);

        *(u8 *)(*(u8 **)((u8 *)extras + 0x50) + 0x4C) = 1;
        *(u8 *)(*(u8 **)((u8 *)extras + 0x54) + 0x50) = 1;
        *(u8 *)(*(u8 **)((u8 *)extras + 0x58) + 0x50) = 1;
        *(u8 *)(*(u8 **)((u8 *)extras + 0x5C) + 0x54) = 1;
        *(u8 *)(*(u8 **)((u8 *)extras + 0x60) + 0x54) = 1;

        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = (u8)zero;

        {
            s32 *p = &gScriptStepCallbackTable;
            stepPtr = (u8 *)entity + 0x18;
            sub_080C31E4(stepPtr, (u8 *)entity + 0x22, *p);
        }

        pcOffset = *(s16 *)((u8 *)entity + 0x22);
        *(u8 *)((u8 *)entity + pcOffset * 2 + 0x19) += 1;

        pcOffset = *(s16 *)((u8 *)entity + 0x22);
        stepPtr += pcOffset * 2;
        sub_080C31E0(entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + *stepPtr * 4));
    }
}
