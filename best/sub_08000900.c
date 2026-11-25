void sub_08000900(u8 *src, u8 *dst, u32 count)
{
    u8 *s = src;
    u32 n = count;
    u8 *p;
    u8 *q;
    u8 *dd;
    u32 r;

    if (n <= 3) {
        p = s;
        q = dst;
        if (n == 0) return;
        do { *q++ = *p++; n--; } while (n != 0);
        return;
    }

    dd = dst;
    p = s;
    {
        u32 a = (u32)p & 3;
        u32 b = (u32)dd & 3;
        if (a == b) {
            r = ((u32)(p + 4) & ~(u32)3) - (u32)p;
            n -= r;
            q = dd;
            if (r != 0) {
                do { *q++ = *p++; r--; } while (r != 0);
            }
            r = n >> 2;
            if (r != 0) {
                do { *(u32 *)q = *(u32 *)p; p += 4; q += 4; r--; } while (r != 0);
            }
            r = n & 3;
            if (r != 0) {
                do { *q++ = *p++; r--; } while (r != 0);
            }
            return;
        }
        if (((u32)p & 1) == ((u32)dd & 1)) {
            if (((u32)p & 1) != 0) {
                *dd = *p;
                s = p + 1;
                dd = dd + 1;
                n--;
            }
            r = n >> 1;
            p = s;
            q = dd;
            if (r != 0) {
                do { *(u16 *)q = *(u16 *)p; p += 2; q += 2; r--; } while (r != 0);
            }
            if (n & 1) { *q = *p; }
            return;
        }
        p = s;
        q = dst;
        if (n != 0) {
            do { *q++ = *p++; n--; } while (n != 0);
        }
    }
}
