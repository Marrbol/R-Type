/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Main
*/

#include "Program.hpp"
#include "Core.hpp"

// Parameters parsing ---------------------------------------------------------

Program::Params::Params(const vector<string> args)
{
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == "-h" || args[i] == "--help") {
            if (runMode != RunMode::NONE)
                throw InvalidParamsException("Cannot run with several modes");
            runMode = RunMode::HELP;
        } else
            throw InvalidParamsException(args[i] + " not recognized");
    }
    if (runMode == RunMode::NONE)
        runMode = RunMode::RUN;
        // throw InvalidParamsException("No mode specified");
}

// Program --------------------------------------------------------------------

int main(const int argc, const char *argv[])
{
    try {
        // Parsing parameters, instantiating the ECS and running it
        const Program::Params params(vector<string>(argv + 1, argv + argc));
        if (params.runMode == Program::RunMode::HELP) {
            cout << Program::help << endl;
        } else if (params.runMode == Program::RunMode::RUN) {
            GUI::SfmlGUI gui;
            ECS::Core core(gui);
            ECS::SystemHandler systemHandler(core);

            while (gui.isOpen()) {
                systemHandler.run();
            }
        }

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
