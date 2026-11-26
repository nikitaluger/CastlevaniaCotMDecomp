struct S_02025368 { u8 _pad1[0x8C]; s16 arr8C[1]; u8 _pad2[0x2D9 - 0x8E]; u8 field2D9; u8 _pad3[0x2DE - 0x2DA]; u16 field2DE; };
struct Obj { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; void *f10; u8 _pad14[2]; u16 f16; u16 f18; };
struct Outer { u8 _pad[0x3C]; struct Obj *obj; };
extern struct S_02025368 gGameStatus;
u16 sub_0806D62C(u16, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Set up a small display/status object from the global menu state, or, when
 * that state is already active, just restart the entity's script. */
void sub_0806E8B8(void *arg0) {
    struct Outer *outer;
    void *owner;
    struct S_02025368 *base;
    u8 stateFlag;
    u16 stateValue;
    s16 mode;
    s32 limit;

    outer = (struct Outer *)((u8 *)*(void **)((u8 *)arg0 + 0x6C) + 4);
    owner = *(void **)((u8 *)arg0 + 0x38);
    base = &gGameStatus;
    stateFlag = base->field2D9;

    if (stateFlag != 0) {
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *audioCmd = (s32 *)0x08671BD0;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 4, *audioCmd);
        }
        {
            u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *scriptData = (u8 *)arg0 + 0x18;
            u8 handlerId = *(scriptData + stepOffset);
            u8 **handlers = *(u8 **)((u8 *)arg0 + 0x14);
            sub_080C31E0(arg0, (s32)handlers[handlerId]);
        }
    } else {
        outer->obj->f1 = stateFlag;
        outer->obj->f2 = 2;
        outer->obj->f3 = 8;
        outer->obj->f4 = stateFlag;
        outer->obj->f6 = 0x0A;
        outer->obj->f8 = 2;
        outer->obj->fA = stateFlag;
        outer->obj->fC = stateFlag;
        stateValue = base->field2DE;
        mode = base->arr8C[0];
        limit = (mode == 1) ? 0x8D : 0x2D;
        outer->obj->fE = sub_0806D62C(stateValue, limit);
        outer->obj->f10 = owner;
        outer->obj->f16 = 0x0F;
        outer->obj->f18 = 0x10;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *audioCmd = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *audioCmd);
        }
        {
            u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *scriptData = (u8 *)arg0 + 0x18;
            u8 handlerId = *(scriptData + stepOffset);
            u8 **handlers = *(u8 **)((u8 *)arg0 + 0x14);
            sub_080C31E0(arg0, (s32)handlers[handlerId]);
        }
    }
}
