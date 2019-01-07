//
// Created by Matt Kang on 2018-12-31.
//

#include "BestBuddiesSimilarity.h"

BBS::Image BBS::compute()
{
    Image bbs = Image::zeros(image.rows(), image.cols());
    std::vector<Matrix> imageRGB(static_cast<unsigned long>(image.channels()));
    cv::split(image, imageRGB);
    auto templateMat = im2col(templateCrop, pz, pz, pz, pz);
    auto imageMat = im2col(image, pz, pz, pz, pz);
    const auto N = templateMat.cols();

    constexpr float filterSigma = 0.6;
    const auto filter = cv::createGaussianFilter(image.type(), cv::Size(pz, pz), filterSigma);
    const auto kernel = cv::getGaussianKernel(pz, filterSigma);

    return bbs;
}

BBS::Image BBS::compute(const Image &image, const Image &templateImage)
{
    setImage(image);
    setTemplate(templateImage);
    return compute();
}

BBS::Image BBS::getImage() const noexcept { return image; }

BBS::Image BBS::getTemplate() const noexcept { return templateImage; }

BBS::Image BBS::getTemplateCrop() const noexcept { return templateCrop; }

void BBS::setImage(const Image &imageIn) { image = adjustImageSize(imageIn); }

void BBS::setImageBox(const std::vector<int> &boundingBox)
{
    imageCrop =
        adjustImageSize(image.block(boundingBox.at(0), boundingBox.at(1), boundingBox.at(2), boundingBox.at(3)));
    imageBox = boundingBox;
}

void BBS::setImageBox(const int x, const int y, const int width, const int height)
{
    setImageBox({x, y, width, height});
}

void BBS::setTemplate(const Image &imageIn) { templateImage = adjustImageSize(imageIn); }

void BBS::setTemplateBox(const std::vector<int> &boundingBox)
{
    templateCrop = adjustImageSize(templateImage.block(boundingBox.at(0),
                                                       boundingBox.at(1),
                                                       boundingBox.at(2),
                                                       boundingBox.at(3)));
    templateBox = boundingBox;
}

void BBS::setTemplateBox(const int x, const int y, const int width, const int height)
{
    setTemplateBox({x, y, width, height});
}

BBS::Image BBS::adjustImageSize(const Image &image) const
{
    if (image.rows() % pz || image.cols() % pz)
        return image.block(0, 0, image.cols() - image.cols() % pz, image.rows() - image.rows() % pz);
    return image;
}

BBS::Image BBS::im2col(Image &src, int rowBlock, int colBlock, int rowStride, int colStride)
{
    // SOURCE: https://sites.google.com/site/myvrdo/blog/eigenvsopencvim2col
    int m = src.rows();
    int n = src.cols();
    auto rowB = static_cast<int>(floor((m - rowBlock) / rowStride) + 1);
    auto colB = static_cast<int>(floor((n - colBlock) / colStride) + 1);
    int dstrows = ((m - rowBlock) % rowStride != 0 ? rowB + 1 : rowB);
    int dstcols = ((n - colBlock) % colStride != 0 ? colB + 1 : colB);

    Image dst(rowBlock * colBlock, dstrows * dstcols);

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
