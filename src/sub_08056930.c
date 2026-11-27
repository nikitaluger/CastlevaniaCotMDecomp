extern s32 isOutsideCameraBounds(s32, s32);
extern void sub_08056DB0(void *, void *, void *, s32);
extern void sub_08056B58(void *, void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, u32);

struct Entry_080CFBF8 { s32 value; u8 _rest[0x20]; };
struct S_080CFBF8 { u8 _pad[0x18]; struct Entry_080CFBF8 entries[1]; };
extern struct S_080CFBF8 D_080CFBF8;

/* Homing projectile update: while it is in view, steer it with the per-state
 * angle table, optionally finish the step and dispatch the next one, then
 * advance its animation sequence. */
void sub_08056930(void *entity) {
    void *sprite;
    void *work;
    void *anim;
    void *state;
    u32 *scriptTable;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)work + 0x34;
    state = (u8 *)work + 0x48;
    if (isOutsideCameraBounds(*(s32 *)((u8 *)entity + 0x4C), *(s32 *)((u8 *)entity + 0x5C)) != 1) {
        sub_08056DB0(entity, work, state, D_080CFBF8.entries[*(u8 *)((u8 *)state + 9)].value);
        if (*(u8 *)((u8 *)entity + 0x6C) != 0) {
            *(u32 *)((u8 *)state + 0x10) = *(u32 *)((u8 *)work + 0xC);
            *(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = 0;
            scriptTable = (u32 *)0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptTable);
        }
        sub_08056B58(sprite, anim, state, 0xC, 8);
    }
}
