#pragma once

#include <fmt/format.h>
#include <vector>

namespace mujoco_examples
{

struct InputParser {
public:
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }

    const std::string& getCmdOption(const std::string& option) const {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }

    bool cmdOptionExists(const std::string& option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
    }


private:
    std::vector <std::string> tokens;
};

struct MujocoInputParser: InputParser
{

    MujocoInputParser(int& argc, char** argv) : InputParser(argc, argv){
        fmt::print("Loading Parameters:");
        if (cmdOptionExists("--model"))
        {
            parameters.model = getCmdOption("--model");
            fmt::print("\t model specified: {}", parameters.model);
        } else {
            throw std::runtime_error("you must specify a model");
        }
    }

    struct Parameters
    {
        std::string model;
    } parameters;

};
}
