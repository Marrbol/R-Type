/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Main
*/

#include "Program.hpp"
#include "ECS.hpp"

Program::Params::Params(const vector<string> args)
{
    for (size_t i = 0; i < args.size(); i++) {

        // Modes

        if (args[i] == "-h" || args[i] == "--help") { // Help mode
            if (runMode != RunMode::NONE)
                throw InvalidParamsException("Cannot run with several modes");
            runMode = RunMode::HELP;
        } else if (args[i] == "-s" || args[i] == "--server") { // Server mode
            if (runMode != RunMode::NONE)
                throw InvalidParamsException("Cannot run with several modes");
            runMode = RunMode::SERVER;
        } else if (args[i] == "-c" || args[i] == "--client") { // Client mode
            if (runMode != RunMode::NONE)
                throw InvalidParamsException("Cannot run with several modes");
            runMode = RunMode::CLIENT;

        // Options

        } else if (args[i] == "-p" || args[i] == "--port") { // Port option
            if (i + 1 >= args.size())
                throw InvalidParamsException(args[i] + " requires an argument");
            try {
                port = stoi(args[i + 1]);
            } catch (const exception &e) {
                throw InvalidParamsException(args[i] + " requires an integer argument");
            }
            if (port < 1024 || port > 65535)
                throw InvalidParamsException(args[i] + " requires an integer argument between 1024 and 65535");
            i += 1;
        } else if (args[i] == "-i" || args[i] == "--ip") { // IP option
            if (i + 1 >= args.size())
                throw InvalidParamsException(args[i] + " requires an argument");
            ip = args[i + 1];
            i += 1;
        } else
            throw InvalidParamsException(args[i] + " not recognized");
    }
    if (runMode == RunMode::NONE)
        runMode = RunMode::CLIENT;
        // throw InvalidParamsException("No mode specified");
}

int main(const int argc, const char *argv[])
{
    try {
        // Parsing parameters, instantiating the ECS and running it
        const Program::Params params(vector<string>(argv + 1, argv + argc));
        if (params.runMode == Program::RunMode::HELP) {
            cout << Program::help << endl;
            return Program::exitSuccess;
        }

        ECS::ECS ecs(params);
        ecs.run();

    // Specifying any error the most precisely possible
    } catch (const Program::InvalidParamsException &e) {
        cerr << "Invalid parameters: \"" << e.what() << "\". Run with -h or --help for more details." << endl;
        return Program::exitError;
    } catch (const ECS::RuntimeException &e) {
        cerr << "Runtime error: \"" << e.what() << "\"." << endl;
        return Program::exitError;
    } catch (const exception &e) {
        cerr << "Error: \"" << e.what() << "\"." << endl;
        return Program::exitError;
    } catch (...) {
        cerr << "Unknown error occured." << endl;
        return Program::exitError;
    }
    return Program::exitSuccess;
}
