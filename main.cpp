#include <iostream>
#include <iomanip>

#include "fs.h"

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cout << "not enough args." << std::endl;
    }

    std::string drive = std::string(argv[1]);
    std::string command = std::string(argv[2]);

    if (command == "create") {
        auto _fs = fs::create(drive);
        _fs.save_state();
    }

    if (command == "ls") {
        auto _fs = fs::load(drive);
        std::cout << "attrs" << std::setw(15) << "length" << std::setw(15) << "name" << std::endl;
        for (const auto& file : _fs.files) {
            std::cout << file.is_hidden() << file.is_readonly() << file.is_system()
                      << std::setw(15)
                      << file.content.size()
                      << std::setw(17)
                      << file.name
                      << std::endl;
        }
    }

    if (command == "touch") {
        std::string filename = std::string(argv[3]);
        auto _fs = fs::load(drive);
        _fs.files.emplace_back(fs::file{ filename, 0x0, {} });
        _fs.save_state();
    }

    return 0;
}
