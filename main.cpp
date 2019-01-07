#include <iostream>
#include <sstream>

#include <opencv2/opencv.hpp>

#include "BestBuddiesSimilarity.h"
#include "CLI11.hpp"

int parseArgs(int &argc,
              char **argv,
              std::vector<std::string> &imagePaths,
              std::vector<std::string> &templatePaths,
              std::vector<std::string> &boxPaths)
{
    CLI::App app("Best Buddies Similarity sandbox");
    app.get_formatter()->column_width(35);
    app.add_option("-i, --image", imagePaths, "Path to reference image")->required()->check(CLI::ExistingFile);
    const auto templateOption =
        app.add_option("-t, --template", templatePaths, "Path to template image")->required()->check(CLI::ExistingFile);
    app.add_option("-b, --bounding-box", boxPaths, "Path to bounding box for template image")->needs(templateOption);
    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::Error &e)
    {
        app.exit(e);
        return -1;
    }
    return 0;
}

template<typename ScalarT = double, typename CharT = char *>
std::vector<std::vector<ScalarT>> readValuesFromFile(const CharT &filePath, const char delimiter = ',')
{
    std::vector<std::vector<ScalarT>> values;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::vector<ScalarT> valuesInLine;
        std::string value;
        while (std::getline(lineStream, value, delimiter))
        {
            valuesInLine.emplace_back(std::stod(value));
        }
        values.push_back(valuesInLine);
    }
    return values;
}

int main(int argc, char **argv)
{
    // Parse arguments
    std::vector<std::string> imagePaths, templatePaths, boxPaths;
    if (parseArgs(argc, argv, imagePaths, templatePaths, boxPaths))
        return -1;

    for (size_t i = 0; i < imagePaths.size(); ++i)
    {
        // Read in images
        const auto image = cv::imread(imagePaths.at(i));
        auto templateImage = cv::imread(templatePaths.at(i));

        cv::imshow("", image);
        cv::waitKey();
        cv::imshow("", templateImage);
        cv::waitKey();

        auto bbs = BBS(image, templateImage);

        // Crop template image by bounding box
        if (!boxPaths.empty())
        {
            const auto boundingBox = readValuesFromFile<int>(boxPaths.at(i));
            bbs.setTemplateBox(boundingBox.at(0));
        }
        cv::imshow("", bbs.getTemplateCrop());
        cv::waitKey();
        cv::imshow("", bbs.compute());
        cv::waitKey();
    }

    return 0;
}