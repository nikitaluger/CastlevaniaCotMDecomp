extern void startEffectTimer(void *a, s32 b, void *c);
extern void sub_0808BBAC(s32 a, s32 b, s32 c);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void releaseActorEffectParts(void);

extern u8 D_084F0914[];
extern u8 D_084F0BB4[];
extern u32 gScriptStepCallbackTable;

/* Initializes a multi-part entity: clears its five sub-object slots, installs
 * the cleanup callback and sprite graphics, queues a palette effect, then runs
 * and advances one step of its script. */
void sub_08080EB0(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *state = *(u8 **)(entity + 0x6C);
    u8 *actor = state + 4;
    u8 *sprite = *(u8 **)(entity + 0x38);

    *(u32 *)(actor + 0x2C) = 0;
    *(u32 *)(actor + 0x30) = 0;
    *(u32 *)(actor + 0x34) = 0;
    *(u32 *)(actor + 0x38) = 0;
    *(u32 *)(actor + 0x3C) = 0;
    *(u32 *)(actor + 0x18) = *(u32 *)(entity + 0x24);
    *(void **)(entity + 0x24) = releaseActorEffectParts;
    {
        u32 zero = 0;
        *(u16 *)(sprite + 0x04) = (u16)(0x1000 | zero);
        *(u16 *)(sprite + 0x06) = 0x1000;
        *(void **)(sprite + 0x24) = D_084F0914;
        startEffectTimer(state + 0x20, 0, D_084F0BB4);
        *(u32 *)(sprite + 0x14) = 0x00780000;
        *(u32 *)(sprite + 0x18) = 0x00500000;
        *(u32 *)(actor + 0x10) = 0x100;
        *(vu16 *)0x05000000 = 0x3E0;
        sub_0808BBAC(0x40, 1, 3);
        *(u32 *)(actor + 0x14) = 1;
        *(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = (u8)zero;
    }
    {
        u32 *eventTable = &gScriptStepCallbackTable;
        u8 *scriptStep = entity + 0x18;
        sub_080C31E4(scriptStep, entity + 0x22, (void *)*eventTable);
        {
            s16 step = *(s16 *)(entity + 0x22);
            (*(u8 *)(step * 2 + entity + 0x19))++;
            step = *(s16 *)(entity + 0x22);
            scriptStep += step * 2;
            {
                u8 b = *scriptStep;
                void **tbl = *(void ***)(entity + 0x14);
                sub_080C31E0(entity, tbl[b]);
            }
        }
    }
}
