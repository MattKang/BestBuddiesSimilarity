//
// Created by Matt Kang on 2018-12-31.
//

#ifndef BESTBUDDIESSIMILARITY_H
#define BESTBUDDIESSIMILARITY_H

#include <array>
#include <opencv2/opencv.hpp>

class BBS
{
    // Define Matrix base class (recommended: OpenCV)
    template<typename ScalarT>
    using MatrixBase = cv::Mat_<ScalarT>;

    template<typename ScalarT>
    class MatrixWrap : public MatrixBase<ScalarT>
    {
        using MatrixBase = MatrixBase<ScalarT>; // for convenience
        using MatrixBase::MatrixBase; // inherit all base constructors

    public:
        MatrixWrap() = default;
        MatrixWrap(const cv::MatExpr &matrix) : MatrixBase(matrix) {}; // handles OpenCV's lazy evaluation

        MatrixWrap block(const int x, const int y, const int width, const int height) const
        {
            return MatrixBase(*this, cv::Rect(x, y, width, height));
        }
        int cols() const { return MatrixBase::cols; }
        int rows() const { return MatrixBase::rows; }
        auto width() const { return cols(); }
        auto height() const { return rows(); }
        static MatrixWrap zeros(const int rows, const int cols) { return MatrixBase::zeros(rows, cols); }
    };
    using Matrix = cv::Mat; // TODO Replace with something more general
    using Image = MatrixWrap<cv::Vec3b>; // 3-channel matrix

public:
//    BBS() : pz(pzDefault), gamma(gammaDefault) {};
    BBS(const Image &imageIn,
        const Image &templateImageIn,
        const int pzIn = pzDefault,
        const float gammaIn = gammaDefault)
        : pz(pzIn),
          gamma(gammaIn),
          imageBox{0, 0, imageIn.width(), imageIn.height()},
          templateBox{0, 0, templateImageIn.width(), templateImageIn.height()}, // TODO: valid after adjustImageSize()?
          templateCrop(templateImageIn)
    {
        setImage(imageIn);
        setTemplate(templateImageIn);
    }

    Image compute();
    Image compute(const Image &image, const Image &templateImage);
    Image getImage() const noexcept;
    Image getTemplate() const noexcept;
    Image getTemplateCrop() const noexcept;
    void setImage(const Image &imageIn);
    void setImageBox(const std::vector<int> &boundingBox);
    void setImageBox(const int x, const int y, const int width, const int height);
    void setTemplate(const Image &imageIn);
    void setTemplateBox(const std::vector<int> &boundingBox);
    void setTemplateBox(const int x, const int y, const int width, const int height);

private:
    Image adjustImageSize(const Image &image) const;
    static Image im2col(Image &src, int rowBlock, int colBlock, int rowStride, int colStride);

    static constexpr int pzDefault = 3; // from literature
    static constexpr float gammaDefault = 2; // from literature
    int pz;
    float gamma;
    Image image, templateImage, imageCrop, templateCrop;
    std::vector<int> imageBox, templateBox; // x, y, width, height
};

#endif //BESTBUDDIESSIMILARITY_H
