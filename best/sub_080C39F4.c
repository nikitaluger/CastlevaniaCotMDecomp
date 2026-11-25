void sub_080C39F4(u8 *arg0, s16 *arg1) {
    u8 *end;
    u32 off;
    u8 *p;
    
    off = (u32)(*arg1) * 2 + 2;
    end = arg0 + off;
    
    if (end < (u8 *)arg1) {
        p = end;
        *(u16 *)p = *(u16 *)p + 1;
        p += 2;
        if (p < (u8 *)arg1) {
            do {
                *(u16 *)p = 0;
                p += 2;
            } while (p < (u8 *)arg1);
        }
    }
}
