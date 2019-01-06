//
// Created by Matt Kang on 2018-12-31.
//

#ifndef BESTBUDDIESSIMILARITY_H
#define BESTBUDDIESSIMILARITY_H

#include <opencv2/opencv.hpp>

class BBS
{
    using ScalarType = cv::Vec3b; // 3-channel (RGB) unsigned char
    using MatrixBase = cv::Mat_<ScalarType>;

    class Matrix : public MatrixBase
    {
        using MatrixBase::MatrixBase;
    public:
        Matrix() = default;
        Matrix(const cv::MatExpr &matrix) : MatrixBase(matrix) {};

        static Matrix block(const Matrix &image, const int x, const int y, const int width, const int height)
        {
            return image(cv::Rect(x, y, width, height));
        }
        static Matrix zeros(const int rows, const int cols) { return MatrixBase::zeros(rows, cols); }
    };

public:
    BBS() : pz(pzDefault), gamma(gammaDefault) {};
    BBS(const Matrix &imageIn,
        const Matrix &templateImageIn,
        const int pzIn = pzDefault,
        const float gammaIn = gammaDefault) : pz(pzIn), gamma(gammaIn)
    {
        setImage(imageIn);
        setTemplate(templateImageIn);
    }

    Matrix compute();
    Matrix compute(const Matrix &image, const Matrix &templateImage);
    Matrix getImage() const;
    Matrix getTemplate() const;
    void setImage(const Matrix &imageIn);
    void setTemplate(const Matrix &imageIn);

private:
    Matrix adjustImageSize(const Matrix &image) const;
    static Matrix im2col(Matrix &src, int rowBlock, int colBlock, int rowStride, int colStride);

    static constexpr int pzDefault = 3; // from literature
    static constexpr float gammaDefault = 2; // from literature
    int pz;
    float gamma;
    Matrix image, templateImage;
};

#endif //BESTBUDDIESSIMILARITY_H
