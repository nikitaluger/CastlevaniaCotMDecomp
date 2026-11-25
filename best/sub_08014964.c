struct S_02025FF0 { u8 _0x000[0x174C]; u32 v0; u32 v1; };
extern struct S_02025FF0 D_02025FF0;

s32 sub_08014964(s32 arg0) {
    s32 diff = D_02025FF0.v1 - arg0;
    if (diff > 0) {
        return 1;
    } else {
        if (diff < 0) {
            return -1;
        } else {
            return 0;
        }
    }
}
