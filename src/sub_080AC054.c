extern s32 sub_080ACCA4(s32, s32, void *, void *);
extern void sub_080AC9B4(u8, void *);
extern void sub_080C31E4(void *, void *, u32);

/* Effect-actor update: tick the animation table, apply action-byte flags, map the
 * body kind to a child direction flag, run two hit checks, and advance the
 * script when the second one succeeds. */
void sub_080AC054(u8 *arg0)
{
    u8 *gfx;
    u8 *work;
    u8 *body;
    s16 stepIdx;
    u8 action;
    u8 kind;

    gfx = *(u8 **)(arg0 + 0x38);
    work = *(u8 **)(arg0 + 0x3C);
    body = work + 0x48;

    sub_080AC9B4(work[0x244], work + 0x68);

    action = arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19];
    if (action == 8) {
        *(u8 *)(work + 0xC0) = 1;
    } else if (action == 0x30) {
        *(u8 *)(work + 0xC1) = 1;
    }

    kind = *(u8 *)(body + 0x79);
    if (kind == 1 || kind == 3) {
        *(u8 *)(*(s32 *)(body + 0x50) + 0x50) = 1;
    } else if (kind == 2) {
        *(u8 *)(*(s32 *)(body + 0x50) + 0x50) = kind;
    } else {
        *(u8 *)(*(s32 *)(body + 0x50) + 0x50) = 0;
    }

    body = body + 0x50;
    sub_080ACCA4(0, (s32)gfx, work, body);
    if (sub_080ACCA4(1, (s32)gfx, work, body) != 0) {
        stepIdx = *(s16 *)(arg0 + 0x22);
        arg0[stepIdx * 2 + 0x19] = 0;
        {
            u32 litbase = (u32)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *(u32 *)litbase);
        }
    }
}
