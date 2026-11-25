struct S_02025368 { u8 _pad1[0x8C]; s16 arr8C[1]; u8 _pad2[0x2DE - 0x8E]; u16 field2DE; };
extern struct S_02025368 D_02025368;
struct Obj { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; void *f10; u8 _pad14[2]; u16 f16; u16 f18; };
struct Outer { u8 _pad[0x3C]; struct Obj *obj; };
u16 sub_0806D62C(u16, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Configure an object's graphics and animation parameters from the global
 * settings, then run the next step of its behavior script. */
void sub_0806F408(void *arg0) {
    struct Outer *gfxData;
    void *sprite;
    struct S_02025368 *params;
    u16 paramValue;
    s16 mode;
    s32 scaleLimit;

    gfxData = (struct Outer *)((u8 *)*(void **)((u8 *)arg0 + 0x6C) + 4);
    sprite = *(void **)((u8 *)arg0 + 0x38);
    params = &D_02025368;
    gfxData->obj->f1 = 0;
    gfxData->obj->f2 = 2;
    gfxData->obj->f3 = 8;
    gfxData->obj->f4 = 0;
    gfxData->obj->f6 = 4;
    gfxData->obj->f8 = 4;
    gfxData->obj->fA = 0;
    gfxData->obj->fC = 0;
    paramValue = params->field2DE;
    mode = params->arr8C[0];
    scaleLimit = (mode == 1) ? 0x64 : 0x3F;
    gfxData->obj->fE = sub_0806D62C(paramValue, scaleLimit);
    gfxData->obj->f10 = sprite;
    gfxData->obj->f16 = 0xF;
    gfxData->obj->f18 = 0x12;
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
    {
        s32 *table = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *table);
    }
    {
        u8 *script = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        script[0x19] = (u8)(script[0x19] + 1);
    }
    {
        s32 scriptOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *scriptBase = (u8 *)arg0 + 0x18;
        u8 opcode = *(scriptBase + scriptOffset);
        u8 **opcodeTable = *(u8 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, (s32)opcodeTable[opcode]);
    }
}
