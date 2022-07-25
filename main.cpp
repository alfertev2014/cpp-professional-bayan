#include <boost/program_options.hpp>

#include <iostream>
#include <vector>
#include <string>

namespace po = boost::program_options;

int main(int argc, char * argv[]) {

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("exclude", po::value<std::vector<std::string>>()->multitoken(), "Paths to exclude from scanning.")
        ("include", po::value<std::vector<std::string>>()->multitoken(), "Paths to include into scanning.")
        ("depth", po::value<std::uint32_t>()->default_value(0), "Directories scanning depth.")
        ("min-file-size", po::value<std::size_t>()->default_value(1), "Minimum size of files for scanning")
        ("file-name-masks", po::value<std::vector<std::string>>()->multitoken())
        ("block-size,S", po::value<std::size_t>()->default_value(4096))
        ("hash-algorithm,H", po::value<std::string>()->default_value(std::string{"crc32"}))
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (vm.count("include")) {
        auto includes = vm["include"].as<std::vector<std::string>>();
        std::cout << "includes: " << std::endl;
        for (auto &include : includes) {
            std::cout << include << std::endl;
        }
    } else {
        std::cout << "Paths for scanning was not set.\n";
        return -1;
    }

    if (vm.count("exclude")) {
        auto excludes = vm["exclude"].as<std::vector<std::string>>();
        std::cout << "excludes: " << std::endl;
        for (auto &exclude : excludes) {
            std::cout << exclude << std::endl;
        }
    }

    if (vm.count("file-name-masks")) {
        auto masks = vm["file-name-masks"].as<std::vector<std::string>>();
        std::cout << "file-name-masks: " << std::endl;
        for (auto &mask : masks) {
            std::cout << mask << std::endl;
        }
    }

    if (vm.count("depth")) {
        std::cout << "depth: " << vm["depth"].as<std::uint32_t>() << std::endl;
    }

    if (vm.count("min-file-size")) {
        std::cout << "min-file-size: " << vm["min-file-size"].as<std::size_t>() << std::endl;
    }

    if (vm.count("block-size")) {
        std::cout << "block-size: " << vm["block-size"].as<std::size_t>() << std::endl;
    }

    if (vm.count("hash-algorithm")) {
        std::cout << "hash-algorithm: " << vm["hash-algorithm"].as<std::string>() << std::endl;
    }

    return 0;
}
