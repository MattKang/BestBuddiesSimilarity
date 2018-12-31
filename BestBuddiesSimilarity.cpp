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

BBS::MatrixT BBS::compute(MatrixT imageIn, MatrixT templateImageIn)
{
    image = imageIn;
    templateImage = templateImageIn;
    return compute();
}

BBS::MatrixT BBS::getImage()
{
    return image;
}

BBS::MatrixT BBS::getTemplate()
{
    return templateImage;
}

void BBS::setImage(BBS::MatrixT imageIn)
{
    image = imageIn;
}

void BBS::setTemplate(BBS::MatrixT templateImageIn)
{
    templateImage = templateImageIn;
}