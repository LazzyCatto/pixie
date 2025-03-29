#ifndef BRAILLECONVERTER_H
#define BRAILLECONVERTER_H

#include <string>
#include <vector>

#include "../managers/PaletteManager.h"

const int kBrailleWidth = 2;
const int kBrailleHeight = 4;
const uint kEmptyBrailleUnicode = 0x2800;

class BrailleConverter {
public:
    static QString convertToBraille(
        const std::vector<std::vector<bool>>& pixelData,
        const std::vector<std::vector<int>>& colorData,
        PaletteManager *paletteManager);

private:
    static QString ChunkToBrailleSymbol(const std::vector<std::vector<bool>>& chunk);
};

#endif // BRAILLECONVERTER_H