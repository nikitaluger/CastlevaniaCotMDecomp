extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Typed views of status fields in the linked work object. */
struct WorkFlags { u8 pad[0xEC]; u16 spriteFlags; };
struct WorkState { u8 pad[0xEE]; u8 subState; };
struct WorkMode  { u8 pad[0xEF]; u8 mode; };
struct WorkValue { u8 pad[0x114]; u32 value; };

/* Actor script step: initialise the linked work object's state fields (copying
 * one sprite attribute bit), clear its auxiliary fields, then advance the
 * script. */
void sub_080A7510(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    s32 *lit;
    u8 zero;
    ((struct WorkState *)work)->subState = 0;
    ((struct WorkMode *)work)->mode = 2;
    zero = 0;
    ((struct WorkFlags *)work)->spriteFlags = *(u16 *)(sprite + 2) & 0x10;
    ((struct WorkValue *)work)->value = 0x60;
    {
        u8 *fieldPtr = work + 0x148;
        *(u8 *)fieldPtr = zero;
        fieldPtr -= 0x20;
        *(s32 *)fieldPtr = 0;
        fieldPtr += 4;
        *(s32 *)fieldPtr = 0;
        fieldPtr += 8;
        *(s32 *)fieldPtr = 0;
    }
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    work = self;
    work += 0x18;
    sub_080C31E4(work, self + 0x22, *lit);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    work += (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)work * 4));
}
