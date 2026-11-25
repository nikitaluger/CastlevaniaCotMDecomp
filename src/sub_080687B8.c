struct UpdateObj {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 f22; u8 _24[0x14];
    u32 f38; u8 _3C[0x30]; u32 f6C;
};
struct PartState {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 f2C;
    u8 _2E[0x12]; u32 f40; u32 f44; u8 _48[4]; u32 f4C; u32 f50;
    u8 _54[0x64]; u32 fB8; u8 _BC[8]; u32 fC4;
};
struct S_02025FF0 { u8 _0[0x24]; u32 f24; u16 f28; };
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02025FF0 D_02025FF0;
extern struct S_02021E90 D_02021E90;
extern u8 D_02025368[];                     /* level/enemy data block */
extern u8 D_080E03A0[];                      /* per-state value/clamp table */
extern void *D_08671BD0;

extern s32 sub_0806C4B4(void *, void *);     /* select movement/camera mode */
extern void sub_0806C5EC(void *, void *, void *, void *); /* reset state block */
extern void sub_0806BA20(void *, void *, void *);
extern void sub_080694D8(void *, void *, void *);
extern void sub_0806926C(void *);
extern void sub_080693E0(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *); /* update state position */
extern void sub_0806A884(void *, void *);    /* clamp/adjust sprite position */
extern void sub_08003A6C(void *, s32, void *); /* initialise a control struct */
extern u16 sub_0806BCD8(void *, void *, void *, void *); /* choose a script action */
extern void sub_0806C6B0(void *, void *, void *, void *); /* main per-frame update */
extern s32 sub_08003740(void *, void *);     /* decrement a counter, dispatch when zero */
extern void sub_080C31E8(void *, void *, s32, void *); /* run a script handler */

/* Updates one part of a multi-part boss: applies a state-table value, handles its
   death/reset cue and script transitions, then runs the full per-frame update. */
void sub_080687B8(struct UpdateObj *obj) {
    struct PartState *stateHdr; struct PartState *state; s32 sprite; u8 *levelData; u8 *counter;
    stateHdr = (struct PartState *)((u8 *)obj->f6C + 4);
    sprite = obj->f38;
    state = stateHdr;
    levelData = (u8 *)0x02025368;
    if (sub_0806C4B4(state, state) != 0) return;
    sub_0806C5EC(obj, (void *)sprite, state, state);
    sub_0806BA20((void *)sprite, state, state);
    {
        u8 *tbl = D_080E03A0;
        u32 off = (2 * state->f44) * 44;
        s32 cur = state->f0C + *(u32 *)(tbl + off);
        u32 lim;
        state->f0C = cur;
        lim = *(u32 *)((u8 *)D_080E03A0 + off + 4);
        if (cur > (s32)lim) state->f0C = lim;
    }
    sub_080694D8((void *)sprite, state, state);
    if (D_02025FF0.f24 != 0) {
        if ((D_02025FF0.f28 & *(u16 *)(levelData + 0x3BC)) != 0) goto block8;
        goto block9;
    } else {
        if ((D_02021E90.f146C & *(u16 *)(levelData + 0x3BC)) == 0) goto block9;
    }
block8:
    sub_0806926C(stateHdr);
    *(u32 *)((u8 *)stateHdr + 0xB8) = 0;
    *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
    { void *fn = &D_08671BD0; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x2C, *(void **)fn); }
    goto merged;
block9:
    sub_080693E0(obj, (void *)sprite, stateHdr, state);
merged:
    D_0806AB04(obj, (void *)sprite, stateHdr, state);
    {
        s32 t = stateHdr->f40;
        counter = (u8 *)stateHdr + 0x28;
        if (t == 1) {
            stateHdr->f4C = 0;
            stateHdr->f50 = 0;
            if (obj->f18 == 0x2C) {
                *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
                { void *fn = &D_08671BD0; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x2B, *(void **)fn); }
                *(u32 *)((u8 *)state + 0x08) = 0;
            } else {
                sub_08003A6C(counter, 0, (void *)0x084FCA3C);
                *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
                { void *fn = &D_08671BD0; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x29, *(void **)fn); }
            }
        }
    }
    sub_0806A884((void *)sprite, state);
    stateHdr->fC4 = sub_0806BCD8(obj, (void *)sprite, stateHdr, state);
    if (stateHdr->fC4 != 0) {
        *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
        { void *fn = &D_08671BD0; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, stateHdr->fC4, *(void **)fn); }
    }
    sub_08003740(counter, (void *)sprite);
    sub_0806C6B0(obj, (void *)sprite, stateHdr, state);
}
