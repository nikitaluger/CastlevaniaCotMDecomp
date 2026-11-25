/* Update an entity's mover flags and state, spawn a requested effect, advance
 * its script, and write the mover's scroll-relative screen coordinates. */
extern s32 sub_08005E80(s32);
extern void sub_080113A8(void *, void *);
extern void sub_08011EE8(void *, s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern s32 sub_08016238(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct MoverState { u8 a; u8 flags; u8 pad[0x12]; u16 flags2; };
struct MoverFlags { u16 flags; };
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
void sub_08029E48(void *arg0) {
    void *workObj; void *mover; void *moverTarget; struct MoverFlags *mFlags; struct MoverState *state;
    workObj = *(void **)((u8 *)arg0 + 0x38);
    mover = *(void **)((u8 *)arg0 + 0x3C);
    moverTarget = (u8 *)mover + 0x34;
    mFlags = (struct MoverFlags *)mover;
    state = *(struct MoverState **)((u8 *)mover + 0x28);
    state->flags |= 5;
    if (sub_0805F9B4(*(s32 *)((u8 *)mover + 8), *(s32 *)((u8 *)mover + 0xC)) == 1) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        goto end;
    }
    if (sub_08016238(*(void **)((u8 *)mover + 0x28)) != 0) mFlags->flags |= 1;
    state = *(struct MoverState **)((u8 *)mover + 0x28);
    if (state->flags2 & 1) mFlags->flags |= 1;
    if (mFlags->flags & 1) {
        state = *(struct MoverState **)((u8 *)mover + 0x28);
        state->flags &= 0xFB;
        if (*((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x1A) != 1) {
            s32 *cmd;
            sub_08005E80(0x189);
            *((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x1B) = 0;
            cmd = (s32 *)0x08671BDC;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *cmd);
        }
    }
    if (sub_08013B5C(workObj, mover) != 0) goto else_branch;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0866DA80;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    {
        u8 *p = (u8 *)((s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        p[0x19] = p[0x19] + 1;
    }
    {
        s32 idx2 = (s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *q = (u8 *)arg0; u8 val;
        q += 0x18; q += idx2; val = *q;
        sub_080C31E0(arg0, *(s32 *)(*(u32 *)((u8 *)arg0 + 0x14) + (u32)(val * 4)));
    }
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    if (*(u16 *)((u8 *)arg0 + 2) & 0x8000) goto end;
    sub_080113A8(workObj, moverTarget);
    sub_08011EE8(mover, 0, 0);
else_branch:
    {
        struct MoverState *st2; u8 *pt; u8 *pb; u32 idx; u8 *p1; u8 *p2;
        st2 = *(struct MoverState **)((u8 *)mover + 0x28);
        st2->flags2 = 0;
        pt = D_02021E90; pb = D_02025FF0; pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        p1 = pt + 0x1278;
        *(u32 *)((u8 *)workObj + 0x14) = *(u32 *)((u8 *)mover + 8) - ((*(s32 *)(p1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        p2 = pt + 0x127C;
        *(u32 *)((u8 *)workObj + 0x18) = *(u32 *)((u8 *)mover + 0xC) - ((*(s32 *)(p2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
end:
    ;
}
