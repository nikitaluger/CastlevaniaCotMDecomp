extern void sub_08003A6C(void *a, s32 b, void *c);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void sub_0808449C(void);
extern void sub_0808BBAC(s32, s32, s32);
extern u32 gMainObjTimerCallback;

/* Initializes an entity's visual state: clears its timers, installs the update
 * callback and data tables, sets its palette/OBJ attributes, then advances the
 * script step and dispatches the matching callback. */
void sub_080802E0(void *arg0) {
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
    *(void **)(entity + 0x24) = sub_0808449C;
    *(void **)(sprite + 0x24) = (void *)0x084ED990;
    sub_08003A6C(state + 0x20, 0, (void *)0x084EDA18);
    *(u32 *)(sprite + 0x14) = 0xC0 << 16;
    *(u32 *)(sprite + 0x18) = 0xFFD00000;
    *(u32 *)(actor + 0x10) = 0x80 << 1;
    *(vu16 *)0x05000000 = 0x1F;
    sub_0808BBAC(0x40, 1, 3);
    *(u32 *)(actor + 0x14) = 1;

    *(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
    {
        u32 *eventPtr = &gMainObjTimerCallback;
        u8 *stepBase = entity + 0x18;
        sub_080C31E4(stepBase, entity + 0x22, (void *)*eventPtr);
        {
            s16 step = *(s16 *)(entity + 0x22);
            (*(u8 *)(step * 2 + entity + 0x19))++;
            step = *(s16 *)(entity + 0x22);
            stepBase += step * 2;
            {
                u8 b = *stepBase;
                void **tbl = *(void ***)(entity + 0x14);
                sub_080C31E0(entity, tbl[b]);
            }
        }
    }
}
