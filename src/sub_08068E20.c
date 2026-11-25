/* Runs one step of a character action: applies the shared position/state updates, picks the
 * animation sequence from the global flags, cancels the action when it fails, then advances
 * the sequence timer and updates the action state. */
struct Arg0 {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 f22; u8 _24[0x14];
    u32 f38; u8 _3C[0x30]; u32 f6C;
};
struct ActionState {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 f2C;
    u8 _2E[0x12]; u32 f40; u32 f44; u8 _48[4]; u32 f4C; u32 f50;
    u8 _54[0x64]; u32 fB8; u8 _BC[8]; u32 fC4; u8 _C8[4]; u16 fCC;
};
struct S_02025FF0 { u8 _0[0x24]; u32 f24; u16 f28; u8 _2A[0x14C3]; u8 f14ED; };
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02025FF0 D_02025FF0;
extern struct S_02021E90 D_02021E90;
extern u8 D_02025368[];
extern void *D_08671BD0;

extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806926C(void *);
extern s32 sub_080693E0(void *, void *, void *, void *);
extern s32 sub_080694D8(void *, void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C49C(void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);

void sub_08068E20(struct Arg0 *actor) {
    struct ActionState *stateAlias; struct ActionState *state; s32 a; u8 *flagBase; u8 *sequence; s32 choice; s32 direction;
    state = (struct ActionState *)((u8 *)actor->f6C + 4);
    a = actor->f38;
    stateAlias = state;
    flagBase = (u8 *)0x02025368;
    if (sub_0806C4B4(stateAlias, stateAlias) != 0) return;
    sub_0806C5EC(actor, (void *)a, stateAlias, stateAlias);
    if (D_02025FF0.f24 != 0) {
        if ((D_02025FF0.f28 & *(u16 *)(flagBase + 0x3BC)) != 0) goto block8;
        goto block9;
    } else {
        if ((D_02021E90.f146C & *(u16 *)(flagBase + 0x3BC)) == 0) goto block9;
    }
block8:
    sub_0806926C(state);
    *(u32 *)((u8 *)stateAlias + 0x08) = 0;
    *(u32 *)((u8 *)state + 0xB8) = 0;
    *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
    { void *fn = &D_08671BD0; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x2B, *(void **)fn); }
    sequence = (u8 *)state + 0x28;
    goto tail;
block9:
    choice = sub_080693E0(actor, (void *)a, state, stateAlias);
    sequence = (u8 *)state + 0x28;
    if (choice != 0) goto tail;
    direction = sub_080694D8((void *)a, state, stateAlias);
    if (direction == 0) {
        sub_08003A6C(sequence, 0, (void *)0x084FCA3C);
        *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &D_08671BD0; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x29, *(void **)fn); }
    } else {
        state->fCC |= 0x0C;
    }
tail:
    D_0806AB04(actor, (void *)a, state, stateAlias);
    if (state->f40 == 0 && state->f4C == 0) {
        state->f4C = 1;
        sub_08003A6C(sequence, 0, (void *)0x084FCA84);
        *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &D_08671BD0; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x28, *(void **)fn); }
    }
    sub_0806A884((void *)a, stateAlias);
    state->fC4 = sub_0806BCD8(actor, (void *)a, state, stateAlias);
    if (state->fC4 != 0) {
        *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &D_08671BD0; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, state->fC4, *(void **)fn); }
    }
    if (D_02025FF0.f14ED == 0) {
        if (actor->f18 == 0x2A) {
            sub_0806C49C((void *)a, state);
            *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
            { void *fn = &D_08671BD0; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 4, *(void **)fn); }
        }
    }
    sub_08003740(sequence, (void *)a);
    sub_0806C6B0(actor, (void *)a, state, stateAlias);
}
