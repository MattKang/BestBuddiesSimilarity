//
// Created by Matt Kang on 2018-12-31.
//

#ifndef BESTBUDDIESSIMILARITY_H
#define BESTBUDDIESSIMILARITY_H

#include <opencv2/opencv.hpp>

class BBS
{
    template<typename ScalarT>
    class MatrixWrap : public cv::Mat_<ScalarT>
    {
        using MatrixBase = cv::Mat_<ScalarT>;
        using MatrixBase::MatrixBase;
    public:
        MatrixWrap() = default;
        MatrixWrap(const cv::MatExpr &matrix) : MatrixBase(matrix) {};

        static MatrixWrap block(const MatrixWrap &image, const int x, const int y, const int width, const int height)
        {
            return image(cv::Rect(x, y, width, height));
        }
        static MatrixWrap zeros(const int rows, const int cols) { return MatrixBase::zeros(rows, cols); }
    };
    using Matrix = cv::Mat;
    using Image = MatrixWrap<cv::Vec3b>;

public:
//    BBS() : pz(pzDefault), gamma(gammaDefault) {};
    BBS(const Image &imageIn,
        const Image &templateImageIn,
        const int pzIn = pzDefault,
        const float gammaIn = gammaDefault) : pz(pzIn), gamma(gammaIn)
    {
        setImage(imageIn);
        setTemplate(templateImageIn);
    }

    Image compute();
    Image compute(const Image &image, const Image &templateImage);
    Image getImage() const noexcept;
    Image getTemplate() const noexcept;
    void setImage(const Image &imageIn);
    void setTemplate(const Image &imageIn);

private:
    Image adjustImageSize(const Image &image) const;
    static Image im2col(Image &src, int rowBlock, int colBlock, int rowStride, int colStride);

    static constexpr int pzDefault = 3; // from literature
    static constexpr float gammaDefault = 2; // from literature
    int pz;
    float gamma;
    Image image, templateImage;
};

#endif //BESTBUDDIESSIMILARITY_H
