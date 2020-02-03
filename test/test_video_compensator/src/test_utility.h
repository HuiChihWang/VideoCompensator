#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "jsoncpp/json/json.h"
#include "../../../libvideo_compensator/include/seq_compensator.h"

namespace fs = std::experimental::filesystem;
static const std::string strTestFolder{"D:\\myProject\\VideoCompensator\\test\\test_video_compensator\\data"};

namespace Ivs
{
inline std::vector<cv::Rect> LoadJsonMeta(const std::string& strFilePath)
{
    std::ifstream fInput{ strFilePath };
    Json::Value root;
    Json::Reader reader;
    std::vector<cv::Rect> vecRectObjects;

    if (reader.parse(fInput, root))
    {
        for (auto& obj : root)
        {
            cv::Rect rectObject;
            rectObject.x = obj["X"].asInt();
            rectObject.y = obj["Y"].asInt();
            rectObject.width = obj["Width"].asInt();
            rectObject.height = obj["Height"].asInt();
            vecRectObjects.emplace_back(rectObject);
        }
    }

    return std::move(vecRectObjects);
}

inline std::vector<TInputImageMeta> ReadImageMeta(const std::string& strTestFolder)
{
    std::vector<TInputImageMeta> vecSequenceInput;
    auto itFiles = fs::directory_iterator{ strTestFolder };

    for (auto& itFile : itFiles)
    {
        if (itFile.path().extension() == ".png")
        {
            TInputImageMeta tInput;
            auto pathFile = itFile.path();
            std::string strFileName = pathFile.stem().string();
            auto pathJsonFile = pathFile.parent_path() / fs::path{ strFileName + ".json" };

            tInput.matImage = cv::imread(itFile.path().string());
            tInput.vecObjRegions = LoadJsonMeta(pathJsonFile.string());

            for (auto& rect : tInput.vecObjRegions)
            {
                cv::rectangle(tInput.matImage, rect, { 255, 0, 0 });
            }

            vecSequenceInput.emplace_back(tInput);
        }
    }

    return std::move(vecSequenceInput);
}


}
