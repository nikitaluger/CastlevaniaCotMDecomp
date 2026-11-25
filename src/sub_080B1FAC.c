extern void sub_080113A8(void *a, void *b);
extern void sub_080146D0(void *a, s32 b, s32 c);
extern void sub_0801165C(void *a, s32 b);
extern s32 sub_08005910(s32 a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);

/* Shared globals at 0x02025FF0: a target world position used by movement
 * script steps (x at 0x174C, y at 0x1750). */
struct WorldTarget {
    u8 _0x000[0x174C];
    u32 targetX;
    u32 targetY;
};
extern struct WorldTarget D_02025FF0;

/* Movement script step: animate the linked body, count down a remaining-distance
 * value, drive the body's velocity from its heading and speed and integrate its
 * position, then when the counter reaches zero aim toward the shared target and
 * advance the script. */
void sub_080B1FAC(u8 *arg0)
{
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *body = *(u8 **)(arg0 + 0x3C);

    sub_080113A8(sprite, body + 0x34);

    *(s32 *)(arg0 + 0x6C) += 0xFFFFF800;
    if (*(s32 *)(arg0 + 0x6C) < 0)
        *(s32 *)(arg0 + 0x6C) = 0;

    sub_080146D0(body, *(s32 *)(arg0 + 0x7C), *(s32 *)(arg0 + 0x6C));
    sub_0801165C(body, 0);

    if (*(s32 *)(arg0 + 0x6C) == 0) {
        s32 deltaY = (s32)D_02025FF0.targetY - *(s32 *)(body + 0x0C);
        s32 deltaX = (s32)D_02025FF0.targetX - *(s32 *)(body + 0x08);
        *(s32 *)(arg0 + 0x7C) = sub_08005910(deltaY, deltaX);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit);
        }
    }
}
