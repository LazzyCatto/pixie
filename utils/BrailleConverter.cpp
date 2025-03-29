#include <QDebug>

#include "BrailleConverter.h"

QString BrailleConverter::convertToBraille(const std::vector<std::vector<bool>>& pixelData) {
    QString brailleResult;
    size_t width = pixelData.size();
    size_t height = pixelData[0].size();
    for (size_t y = 0; y < height; y += kBrailleHeight) {
        for (size_t x = 0; x < width; x += kBrailleWidth) {
            std::vector<std::vector<bool>> chunk(kBrailleWidth, std::vector<bool>(kBrailleHeight, false));
            for (size_t dx = 0; dx < kBrailleWidth; ++dx) {
                for (size_t dy = 0; dy < kBrailleHeight; ++dy) {
                    if (x + dx < pixelData.size() && y + dy < pixelData[x + dx].size()) {
                        chunk[dx][dy] = pixelData[x + dx][y + dy];
                    }
                }
            }
            QString braille = ChunkToBrailleSymbol(chunk);
            brailleResult += braille;
        }
        brailleResult += "\n";
    }

    return brailleResult;
}

QString BrailleConverter::convertToBrailleColor(
    const std::vector<std::vector<bool>>& pixelData,
    const std::vector<std::vector<int>>& colorData,
    PaletteManager *paletteManager,
    QColor backgroundColor) {
    
    QString brailleResult = "<html><body>";
    QString backgroundcolorString = QString("rgb(%1, %2, %3)")
        .arg(backgroundColor.red())
        .arg(backgroundColor.green())
        .arg(backgroundColor.blue());
    size_t width = pixelData.size();
    size_t height = pixelData[0].size();
    for (size_t y = 0; y < height; y += kBrailleHeight) {
        for (size_t x = 0; x < width; x += kBrailleWidth) {
            std::vector<std::vector<bool>> chunk(kBrailleWidth, std::vector<bool>(kBrailleHeight, false));
            for (size_t dx = 0; dx < kBrailleWidth; ++dx) {
                for (size_t dy = 0; dy < kBrailleHeight; ++dy) {
                    if (x + dx < pixelData.size() && y + dy < pixelData[x + dx].size()) {
                        chunk[dx][dy] = pixelData[x + dx][y + dy];
                    }
                }
            }
            QString braille = ChunkToBrailleSymbol(chunk);
            QColor color = paletteManager->getColor(colorData[x / kBrailleWidth][y / kBrailleHeight]);
            QString colorString = QString("rgb(%1, %2, %3)")
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
            brailleResult += QString("<span style='background-color: %1; color: %2;'>%3</span>")
                .arg(backgroundcolorString)
                .arg(colorString)
                .arg(braille);
        }
        brailleResult += "<br>";
    }

    return brailleResult + "</body></html>";
}

QString BrailleConverter::ChunkToBrailleSymbol(const std::vector<std::vector<bool>>& chunk) {
    // Преобразование пикселя в соответствующий символ Braille
    uint unicode = kEmptyBrailleUnicode;
    unicode |= chunk[0][0];
    unicode |= chunk[0][1] << 1;
    unicode |= chunk[0][2] << 2;
    unicode |= chunk[1][0] << 3;
    unicode |= chunk[1][1] << 4;
    unicode |= chunk[1][2] << 5;
    unicode |= chunk[0][3] << 6;
    unicode |= chunk[1][3] << 7;

    return QString::fromUcs4(&unicode, 1);
}
