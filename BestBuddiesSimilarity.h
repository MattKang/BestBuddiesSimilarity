//
// Created by Matt Kang on 2018-12-31.
//

#ifndef BESTBUDDIESSIMILARITY_H
#define BESTBUDDIESSIMILARITY_H

#include <opencv2/opencv.hpp>

class BBS
{
    using MatrixT = cv::Mat;

    static constexpr int pzDefault = 3; // from literature
    static constexpr float gammaDefault = 2; // from literature

public:
    BBS() : pz(3), gamma(2);

    MatrixT compute();
    MatrixT compute(MatrixT image, MatrixT templateImage);
    MatrixT getImage() const;
    MatrixT getTemplate() const;
    void setImage(MatrixT imageIn);
    void setTemplate(MatrixT templateImageIn);

private:
    template<typename... Ts>
    static MatrixT zeros(Ts &&... args)
    {
        return cv::Mat::zeros(std::forward<Ts>(args)..., CV_8U);
    }

    MatrixT image, templateImage;
    int pz;
    float gamma;
};

#endif //BESTBUDDIESSIMILARITY_H
