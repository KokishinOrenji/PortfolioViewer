#include "FilePriceRepository.h"
#include "../../PriceUtils.h"

void FilePriceRepository::LoadData() {
    std::ifstream file(filePath);
    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line) && !line.empty()) {
        std::vector<std::string> cols;
        boost::algorithm::split(cols, line, boost::is_any_of(","));
        if (cols.size() != 3) {
            std::stringstream error;
            error << "Incorrect number of columns in row  in " << filePath
                << ". Expected 3, actual " << cols.size() << ". Full text: " << line;
            std::cerr << error.str();
            continue;
        }
        auto dateFromFile = boost::gregorian::from_string(cols[0]);

        priceMap[cols[1]].emplace_back(dateFromFile, tryConvertToDouble(cols[2]));
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
