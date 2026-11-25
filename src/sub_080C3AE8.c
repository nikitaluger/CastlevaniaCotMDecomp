/* Text-line helper: writes `glyph` at the current cursor index and clears the
 * remaining halfwords up to the line's end/count slot pointed to by `end`. */
void sub_080C3AE8(u16 *line, s16 *end, u16 glyph)
{
    u16 *p = line + *end;
    *p = glyph;
    p++;
    if (p < (u16 *)end) {
        do {
            *p = 0;
            p++;
        } while (p < (u16 *)end);
    }
}
