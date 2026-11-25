/*
 * Actor script step: refresh a sprite attribute from the work state, set a
 * sprite flag when the actor's own flag byte is nonzero, and when the watched
 * sub-object signals clear, write two part fields, advance the script, then
 * switch the actor to the script's next state.
 */
extern void sub_080148D8(void *, void *);
extern s32 sub_080B9824(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

#define ATTR_FLAG  0x40
#define PART_VALUE 5

void sub_080B7C18(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);   /* reused below for the script address */
    u8 *workParts = work + 0x48;

    sub_080148D8(sprite, *(void **)(work + 0x08));
    if (*(u8 *)(self + 0x4C) != 0) {
        u8 *attr = (u8 *)(sprite + 0x2A);
        s32 attrValue = ATTR_FLAG | *attr;
        *attr = (u8)attrValue;
    }
    if (sub_080B9824(*(s32 *)(work + 0x48)) != 0) {
        u8 *partField = *(u8 **)(work + 0x28);
        u8 zero = 0;
        u8 five = PART_VALUE;
        *(partField + 1) = five;
        *(u8 *)(*(u32 *)(workParts + 0x04) + 1) = five;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = zero;
        {
            s32 *callbackTable = (s32 *)0x08671BB0;
            work = self + 0x18;
            sub_080C31E4(work, self + 0x22, *callbackTable);
        }
        ((u8 *)(self + (*(s16 *)(self + 0x22)) * 2))[0x19]++;
        work += (*(s16 *)(self + 0x22)) * 2;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)work * 4));
    }
}
