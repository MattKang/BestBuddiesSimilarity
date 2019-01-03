//
// Created by Matt Kang on 2018-12-31.
//

#include "BestBuddiesSimilarity.h"

BBS::MatrixT BBS::compute()
{
    const auto imageSize = image.size();
    const auto templateSize = templateImage.size();
    MatrixT bbs = zeros(imageSize);

    return bbs;
}

BBS::MatrixT BBS::compute(MatrixT image, MatrixT templateImage)
{
    setImage(image);
    setTemplate(templateImage);
    return compute();
}

BBS::MatrixT BBS::getImage() const
{
    return image;
}

BBS::MatrixT BBS::getTemplate() const
{
    return templateImage;
}

void BBS::setImage(BBS::MatrixT imageIn)
{
    image = adjustImageSize(imageIn);
}

void BBS::setTemplate(BBS::MatrixT imageIn)
{
    templateImage = adjustImageSize(imageIn);
}

BBS::MatrixT BBS::adjustImageSize(const BBS::MatrixT &image) const
{
    const auto size = image.size();
    if (size.width % pz || size.height % pz)
        return crop(image, 0, 0, size.width - size.width % pz, size.height - size.height % pz);
    return image;
}
