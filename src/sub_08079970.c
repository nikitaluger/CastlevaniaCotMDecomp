/* Set up a scripted effect: clear its sub-object slots, install the cleanup
 * callback and sprite graphics, seed direction/velocity from global state,
 * then advance the script and dispatch its next opcode. */
struct S02025FF0_79970 {
    u8 _0[0x14EF];
    u8 f14EF;
    u8 _1[0x1728 - 0x14F0];
    u32 f1728;
    u32 f172C;
};
extern struct S02025FF0_79970 D_02025FF0;

extern void sub_08003A6C(void *, s32, void *);
extern void sub_0808449C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_08079970(void *arg0) {
    u8 *actor = *(u8 **)((u8 *)arg0 + 0x6C);
    u8 *state = actor + 4;
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    s32 zero = 0;
    u32 scriptOffset;

    *(u32 *)(state + 0x2C) = zero;
    *(u32 *)(state + 0x30) = zero;
    *(u32 *)(state + 0x34) = zero;
    *(u32 *)(state + 0x38) = zero;
    *(u32 *)(state + 0x3C) = zero;
    *(u32 *)(state + 0x18) = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0808449C;
    {
        struct S02025FF0_79970 *globals = &D_02025FF0;
        u8 kindByte = globals->f14EF;
        *(u8 *)(actor + 0x55) = kindByte;
        *(u32 *)(sprite + 0x24) = (u32)0x084DE7BC;
        sub_08003A6C(actor + 0x20, 0, (void *)0x084DE890);
        *(u32 *)(state + 0x54) = 0x1C;
        *(u32 *)(actor + 4) = globals->f1728;
        *(u32 *)(state + 4) = globals->f172C + (u32)0xFFEC0000;
    }
    *(u32 *)(state + 8) = (*(u16 *)(sprite + 2) & 0x10) ? (s32)0xFFFF0000 : 0x10000;
    *(u32 *)(state + 0x0C) = (u32)0xFFFC0000;
    {
        scriptOffset = (u32)(2 * (s16)*(u16 *)((u8 *)arg0 + 0x22));
        *((u8 *)(scriptOffset + (u32)arg0) + 0x19) = (u8)zero;
        {
            void **scriptTableArg = (void **)0x08671BB0;
            u8 *scriptPc = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptPc, (u8 *)arg0 + 0x22, (s32)*scriptTableArg);
            {
                u8 *stepPtr = (u8 *)(scriptOffset + (u32)arg0);
                scriptOffset = (u32)(2 * (s16)*(u16 *)((u8 *)arg0 + 0x22));
                stepPtr = (u8 *)(scriptOffset + (u32)arg0);
                stepPtr[0x19] = (u8)(stepPtr[0x19] + 1);
            }
            scriptPc += 2 * (s16)*(u16 *)((u8 *)arg0 + 0x22);
            {
                u8 opcode = *scriptPc;
                sub_080C31E0(arg0, *(s32 *)(*(u8 **)((u8 *)arg0 + 0x14) + 4 * opcode));
            }
        }
    }
}
