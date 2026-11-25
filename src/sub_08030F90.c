extern s32 sub_08014990(void *);
extern void sub_0808DBB4(s32, s32, s32);

void sub_08030F90(void *entity, void *originObj, s32 effectIndex) {
    u8 *table;
    s32 tableOff;
    s32 dx;
    s32 dy;
    table = (u8*)0x080CEB78;
    tableOff = effectIndex * 8;
    dx = *(s32 *)(table + tableOff);
    table += 4;
    dy = *(s32 *)(table + tableOff);
    if (sub_08014990(entity) > 0) {
        dx = -dx;
    }
    sub_0808DBB4(((s32 *)originObj)[2] + dx, ((s32 *)originObj)[3] + dy, 8);
}
