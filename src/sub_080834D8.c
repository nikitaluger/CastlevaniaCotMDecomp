extern void startEffectTimer(void *a, s32 b, void *c);
extern void spawnEntity(void *a, s32 b, s32 c, s32 d);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void releaseActorEffectParts(void);
extern void sub_0808BBAC(s32, s32, s32);
extern u32 gMainObjTimerCallbacks;

/* Sets up an entity's appearance (graphics/palette/animation) and its destruction
 * callback, then runs the first step of its script/behavior table. */
void sub_080834D8(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *stateBlock = *(u8 **)(self + 0x6C);
    u8 *state = stateBlock + 4;
    u8 *gfx = *(u8 **)(self + 0x38);

    *(u32 *)(state + 0x2C) = 0;
    *(u32 *)(state + 0x30) = 0;
    *(u32 *)(state + 0x34) = 0;
    *(u32 *)(state + 0x38) = 0;
    *(u32 *)(state + 0x3C) = 0;
    *(u32 *)(state + 0x18) = *(u32 *)(self + 0x24);
    *(void **)(self + 0x24) = releaseActorEffectParts;
    *(void **)(gfx + 0x24) = (void *)0x084FAC70;
    startEffectTimer(stateBlock + 0x20, 0, (void *)0x084FACFC);
    *(u32 *)(gfx + 0x14) = 0xFFC00000;
    *(u32 *)(gfx + 0x18) = 0xA0 << 15;
    spawnEntity(self, 0x77, 0xA, 0x12);
    *(u32 *)(state + 0x10) = 0x80 << 1;
    *(vu16 *)0x05000000 = 0;
    sub_0808BBAC(0x40, 1, 3);
    *(u32 *)(state + 0x14) = 1;

    *(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        u32 *pAnimStep = &gMainObjTimerCallbacks;
        u8 *stepBase = self + 0x18;
        sub_080C31E4(stepBase, self + 0x22, (void *)*pAnimStep);
        {
            s16 stepIdx = *(s16 *)(self + 0x22);
            (*(u8 *)(stepIdx * 2 + self + 0x19))++;
            stepIdx = *(s16 *)(self + 0x22);
            stepBase += stepIdx * 2;
            {
                u8 stepByte = *stepBase;
                void **handlerTable = *(void ***)(self + 0x14);
                sub_080C31E0(self, handlerTable[stepByte]);
            }
        }
    }
}
