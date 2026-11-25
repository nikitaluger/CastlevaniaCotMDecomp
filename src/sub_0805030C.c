/* Swap the two halfwords pointed to by a and b (used to shuffle drop slots). */
void sub_0805030C(u16 *a, u16 *b) {
    u16 tmp = *a;
    *a = *b;
    *b = tmp;
}
