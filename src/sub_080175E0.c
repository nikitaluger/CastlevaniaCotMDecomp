void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, u32);

/* Count the control timer down; when it expires, play the owner's animation,
 * clear the current script byte and advance the command stream. */
void sub_080175E0(void *arg0) {
    u8 *control;
    s32 timer;
    s32 commandIndex;
    s32 *handlerTable;
    void *owner;

    control = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x48;
    timer = *(u16 *)(control + 0x16) - 1;
    *(u16 *)(control + 0x16) = timer;
    if ((timer << 16) < 0) {
        owner = *(void **)((u8 *)arg0 + 0x30);
        if (owner != NULL) {
            sub_080C31E0(owner, *(void **)((u8 *)owner + 0x24));
        }
        commandIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + commandIndex * 2 + 0x17) = 0;
        handlerTable = (s32 *)0x08671BD8;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 4, *handlerTable);
    }
}

extern u8 D_02025FF0[];
s32 sub_0801491C(s32 arg0) {
    u8 *b = D_02025FF0;
    s32 v = *(s32 *)(b + 0x1750) - arg0;
    if (v < 0) v = -v;
    return v;
}

s32 sub_08014900(s32 arg0) {
    u8 *b = D_02025FF0;
    s32 v = *(s32 *)(b + 0x174C) - arg0;
    if (v < 0) v = -v;
    return v;
}

s32 sub_08014938(s32);
inline u16 inline_fn(u16 *arg0) { return *arg0; }
void sub_080148D8(void *arg0, s32 arg1) {
    u16 var_r0;
    if (sub_08014938(arg1) > 0) {
        var_r0 = 0x10 | inline_fn((u16 *)((s8 *)arg0 + 2));
    } else {
        var_r0 = 0xFFEF & inline_fn((u16 *)((s8 *)arg0 + 2));
    }
    *((u16 *)((s8 *)arg0 + 2)) = var_r0;
}
