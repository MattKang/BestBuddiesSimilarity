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

void BBS::setImage(BBS::Matrix imageIn)
{
    image = adjustImageSize(imageIn);
}

void BBS::setTemplate(BBS::Matrix imageIn)
{
    templateImage = adjustImageSize(imageIn);
}

BBS::Matrix BBS::adjustImageSize(const BBS::Matrix &image) const
{
    if (image.rows % pz || image.cols % pz)
        return Matrix::crop(image, 0, 0, image.cols - image.cols % pz, image.rows - image.rows % pz);
    return image;
}
