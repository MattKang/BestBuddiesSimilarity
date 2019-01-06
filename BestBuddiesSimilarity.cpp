//
// Created by Matt Kang on 2018-12-31.
//

#include "BestBuddiesSimilarity.h"

BBS::Matrix BBS::compute()
{
    const auto imageSize = image.size();
    const auto templateSize = templateImage.size();
    Matrix bbs = Matrix::zeros(image.rows, image.cols);

    return bbs;
}

BBS::Matrix BBS::compute(const Matrix &image, const Matrix &templateImage)
{
    setImage(image);
    setTemplate(templateImage);
    return compute();
}

BBS::Matrix BBS::getImage() const
{
    return image;
}

BBS::Matrix BBS::getTemplate() const
{
    return templateImage;
}

void BBS::setImage(const BBS::Matrix &imageIn)
{
    image = adjustImageSize(imageIn);
}

void BBS::setTemplate(const BBS::Matrix &imageIn)
{
    templateImage = adjustImageSize(imageIn);
}

BBS::Matrix BBS::adjustImageSize(const BBS::Matrix &image) const
{
    if (image.rows % pz || image.cols % pz)
        return Matrix::block(image, 0, 0, image.cols - image.cols % pz, image.rows - image.rows % pz);
    return image;
}

BBS::Matrix BBS::im2col(BBS::Matrix &src, int rowBlock, int colBlock, int rowStride, int colStride)
{
    const auto m = src.rows;
    const auto n = src.cols;
    const auto rowB = static_cast<int>(floor((m - rowBlock) / rowStride) + 1);
    const auto colB = static_cast<int>(floor((n - colBlock) / colStride) + 1);
    int dstrows = ((m - rowBlock) % rowStride != 0 ? rowB + 1 : rowB);
    int dstcols = ((n - colBlock) % colStride != 0 ? colB + 1 : colB);

    Matrix dst(rowBlock * colBlock, dstrows * dstcols);

    int colIndex = 0;
    int rowOffset;
    bool colbreak = false;
    bool rowbreak;
    int j = 0;
    int i;
    while (!colbreak) // Col iterator
    {
        if (j + colBlock > n - 1)
        {
            j = n - colBlock;
            colbreak = true;
        }
        rowbreak = false;
        i = 0;
        while (!rowbreak) // Row iterator
        {
            if (i + rowBlock > m - 1)
            {
                i = m - rowBlock;
                rowbreak = true;
            }
            rowOffset = 0;
            for (int jj = 0; jj < colBlock; jj++) // col iterator of sub-block
            {
                for (int ii = 0; ii < rowBlock; ii++) // row iterator of sub-block
                {
                    dst(jj * rowBlock + ii, colIndex) = src(i + ii, j + jj);
                }
            }
            colIndex += 1;
            i += rowStride;
        }
        j += colStride;
    }
    return dst;
}