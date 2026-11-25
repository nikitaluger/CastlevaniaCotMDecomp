extern u8 D_02025368[];                    /* level/enemy data block */
extern u8 D_080E03A0[];                     /* per-state value/clamp table (0x58-byte rows) */
extern void *D_08671BC0;
extern void *D_08671BD0;
extern void *D_08671BD8;

struct S_02025FF0 { u8 _0[0x24]; u32 f24; u16 f28; };
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02025FF0 D_02025FF0;
extern struct S_02021E90 D_02021E90;

struct PartState {                          /* state block at header+4 */
    u8 _0[8]; s32 f8; s32 fC; u8 _10[0x40-0x10]; s32 f40; s32 f44;
    u8 _48[4]; s32 f4C; s32 f50; s32 f54;
};

extern s32 sub_0806C4B4(void *, void *);    /* select movement/camera mode */
extern void sub_0806C5EC(void *, void *, void *, void *); /* reset state block */
extern void sub_0806AB04(void *, void *, void *, void *); /* update state block position */
extern void sub_08005E80(s32);              /* play a sound effect */
extern void sub_0806E114(void *, s32, s32, s32); /* spawn a related object */
extern void sub_0806A884(void *, void *);   /* clamp/adjust sprite position */
extern s32 sub_08003740(void *, void *);    /* decrement a counter, dispatch when zero */
extern void sub_0806A7AC(void *, void *, s32); /* switch the state block to a new mode */
extern void sub_0806C6B0(void *, void *, void *, void *); /* main per-frame update */
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

/* Updates a multi-part boss/effect: applies a state-table value to the part, handles
   its death/reset cue and step-script transitions, then runs the full per-frame update. */
void sub_08066D1C(u8 *obj) {
    u8 *counter;
    u8 *header = *(u8 **)(obj + 0x6C);
    u8 *statePtr = header + 4;
    u8 *sprite = (u8 *)*(s32 *)(obj + 0x38);
    u8 *state = statePtr;
    s32 result = sub_0806C4B4(state, state);
    s32 base, idx;
    s32 counterResult;
    u8 *bt = (u8 *)0x02025368;

    if (result != 0) return;

    sub_0806C5EC(obj, sprite, state, state);
    base = 0x080E03A0;
    idx = ((struct PartState *)state)->f44 * 0x58;
    ((struct PartState *)state)->fC = ((struct PartState *)state)->fC + *(s32 *)(base + idx);
    base += 4;
    {
        s32 lim = *(s32 *)(base + idx);
        if (((struct PartState *)state)->fC > lim) ((struct PartState *)state)->fC = lim;
    }
    sub_0806AB04(obj, sprite, state, state);
    if (((struct PartState *)state)->f40 == 1) {
        sub_08005E80(0x67);
        ((struct PartState *)state)->f4C = result;
        ((struct PartState *)state)->f50 = result;
        ((struct PartState *)state)->f54 = result;
        ((struct PartState *)state)->f8 = result;
        sub_0806E114(obj, 9, *(s32 *)(header + 4), *(s32 *)(state + 4));
        *(u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj + 0x19) = (u8)result;
        { s32 *g = (s32 *)0x08671BD0; sub_080C31E8(obj + 0x18, obj + 0x22, 2, *g); }
    }
    sub_0806A884(sprite, state);
    counter = header + 0x2C;
    counterResult = sub_08003740(counter, sprite);
    if (counterResult == 0) {
        s32 *pc = (s32 *)(header + 0xBC);
        result = *pc - 1;
        *pc = result;
        if (result != 0) {
            *(u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj + 0x19) = (u8)counterResult;
            { s32 *g = (s32 *)0x08671BC0; sub_080C31E4(obj + 0x18, obj + 0x22, *g); }
        } else {
            sub_0806A7AC(sprite, state, 0x10);
            sub_08003740(counter, sprite);
            *(u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj + 0x17) = (u8)result;
            { s32 *g = (s32 *)0x08671BD8; sub_080C31E8(obj + 0x18, obj + 0x22, 3, *g); }
        }
    }
    if (D_02025FF0.f24 != 0) {
        if ((D_02025FF0.f28 & *(u16 *)(bt + 0x3BE)) != 0) goto block;
        goto skip;
    } else {
        if ((D_02021E90.f146C & *(u16 *)(bt + 0x3BE)) == 0) goto skip;
    }
block:
    sub_0806A7AC(sprite, statePtr, 0x10);
    sub_08003740(statePtr + 0x28, sprite);
    *(u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj + 0x17) = 0;
    { s32 *g = (s32 *)0x08671BD8; sub_080C31E8(obj + 0x18, obj + 0x22, 3, *g); }
skip:
    sub_0806C6B0(obj, sprite, statePtr, state);
}
