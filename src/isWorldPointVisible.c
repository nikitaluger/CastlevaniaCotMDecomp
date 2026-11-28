/* Visibility test for a 16.16 fixed-point world point. Translate it by the
 * camera position, project it onto the three view-space axes with the 8.8
 * view matrix, then reject it when it falls outside the perspective volume. */
s32 isWorldPointVisible(s32 worldX, s32 worldY, s32 worldZ)
{
    s32 dx, dy, viewX, viewY, viewZ;
    s32 product, product2;

    product = worldX - gCameraPosX;
    if (product < 0) product += FIXED_TRUNC_BIAS;
    dx = product >> 16;

    product = worldY - gCameraPosY;
    if (product < 0) product += FIXED_TRUNC_BIAS;
    dy = product >> 16;

    product = worldZ - gCameraPosZ;
    if (product < 0) product += FIXED_TRUNC_BIAS;
    worldZ = product >> 16;

    product = dx * gViewMatrixXX + dy * gViewMatrixXY + worldZ * gViewMatrixXZ;
    if (product < 0) product += VIEW_TRUNC_BIAS;
    viewX = product >> 8;

    if ((u32)(viewX - 0x80) > 0xF80) return 0;

    product2 = dx * gViewMatrixYX + dy * gViewMatrixYY + worldZ * gViewMatrixYZ;
    if (product2 < 0) product2 += VIEW_TRUNC_BIAS;
    viewY = product2 >> 8;

    product = dx * gViewMatrixZX + dy * gViewMatrixZY + worldZ * gViewMatrixZZ;
    if (product < 0) product += VIEW_TRUNC_BIAS;
    viewZ = product >> 8;

    product = -(((((viewX << 1) + viewX) << 3) - viewX) << 3);
    if (product < 0) product += VIEW_TRUNC_BIAS;
    if (viewY <= product >> 8) return 0;

    product = 0xB8 * viewX;
    if (product < 0) product += VIEW_TRUNC_BIAS;
    if (viewY >= product >> 8) return 0;

    product = 0 - (viewX * 0x90);
    if (product < 0) product += VIEW_TRUNC_BIAS;
    if (viewZ <= product >> 8) return 0;
    if (viewZ > 0x8F) return 0;

    return 1;
}
