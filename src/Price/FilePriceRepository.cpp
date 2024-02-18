#include "FilePriceRepository.h"

void FilePriceRepository::LoadData() {
    std::ifstream file(filePath);
    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> cols;
        boost::algorithm::split(cols, line, boost::is_any_of(","));
        if (cols.size() != 3) {
            throw std::runtime_error("Incorrect number of columns in file: " + filePath);
        }
        auto dateFromFile = boost::gregorian::from_string(cols[0]);
        auto price = std::make_shared<Price>(dateFromFile, std::stod(cols[2]));

        priceMap[cols[1]].push_back(price);
    }
}

std::shared_ptr<FilePriceRepository> FilePriceRepository::GetInstance(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    static std::unordered_map<std::string, std::shared_ptr<FilePriceRepository>> instance;
    if (instance.find(filePath) == instance.end())
    {
        auto filePathRepo = std::make_shared<FilePriceRepository>(filePath);
        filePathRepo->LoadData();
        instance[filePath] = filePathRepo;
    }
    return instance[filePath];
}

// Initialize the static mutex
std::mutex FilePriceRepository::instanceMutex;

