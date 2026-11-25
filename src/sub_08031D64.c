/* Per-frame update for a scripted attack/effect: kills it when it leaves the play area,
 * tracks nearby targets and script flags (optionally firing an event), advances the
 * parent's script step to dispatch a callback, then repositions the sprite on screen. */
extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(s32, void *);
extern s32 sub_08016238(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct StateFlags { u16 flags; };
struct SpriteDefFlags { u8 flagsA; u8 flagsB; };
struct SpriteDefTimer { u8 _0[0x14]; u16 timer; };
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

void sub_08031D64(u8 *self)
{
    s32 sprite = *((s32 *)(self + 0x38));
    u8 *state = *((u8 **)(self + 0x3C));
    u8 *scratch = state + 0x34;
    u8 *spriteDef;
    spriteDef = *((u8 **)(state + 0x28));
    ((struct SpriteDefFlags *)spriteDef)->flagsB |= 5;
    if (sub_0805F9B4(*((s32 *)(state + 8)), *((s32 *)(state + 0xC))) == 1)
    {
        sub_080C31E0(self, *((void **)(self + 0x24)));
        return;
    }
    if (sub_08016238(*((void **)(state + 0x28))) != 0)
        ((struct StateFlags *)state)->flags |= 1;
    if (1 & ((struct SpriteDefTimer *)(*((u8 **)(state + 0x28))))->timer)
        ((struct StateFlags *)state)->flags |= 1;
    if (1 & (*((u16 *)state)))
    {
        if ((*((u8 *)((((u32)(*((s16 *)(self + 0x22)))) * 2) + (u32)self + 0x1A))) != 1)
        {
            s32 *callback;
            sub_08005E80(0x18A);
            *((u8 *)((((u32)(*((s16 *)(self + 0x22)))) * 2) + (u32)self + 0x1B)) = 0;
            callback = (s32 *)0x08671BDC;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *callback);
        }
    }
    if (sub_08013B5C(sprite, state) == 0)
    {
        s32 stepOff; u8 *script; u8 cmd; void **scriptTable; void *entry; u8 *stepPtr;
        *((void **)(self + 0x14)) = (void *)0x0866DCAC;
        *((u16 *)(self + 0x22)) = (u16)(*((u16 *)(self + 0x22)) + 1);
        stepPtr = (u8 *)((((u32)(*((s16 *)(self + 0x22)))) * 2) + (u32)self);
        *((u8 *)(stepPtr + 0x19)) = (u8)(*((u8 *)(stepPtr + 0x19)) + 1);
        stepOff = (*((s16 *)(self + 0x22))) * 2;
        script = self + 0x18;
        cmd = *(script + stepOff);
        scriptTable = *((void **)(self + 0x14));
        entry = scriptTable[cmd];
        sub_080C31E0(self, entry);
        *((u16 *)(self + 0x22)) = (u16)(*((u16 *)(self + 0x22)) - 1);
        if (((*((u16 *)(self + 2))) & 0x8000) == 0)
        {
            sub_080113A8(sprite, scratch);
            sub_0801165C(state, 0);
        }
        else goto done;
    }
    ((struct SpriteDefTimer *)(*((u8 **)(state + 0x28))))->timer = 0;
    {
        u8 *pt = D_02021E90;
        u8 *pb = D_02025FF0;
        u8 *base1;
        u8 *base2;
        u32 idx;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)state + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)state + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
done:
    ;
}
