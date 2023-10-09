#include "soundEffects.h"
#include "soundEffectsException.h"
#include "modes.h"
#include "wavHeader.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            throw argumentsException("ERROR:Wrong amount of arguments!");
        }
        if (argv[1] == modes::help) {
            runModeHelp();
            return 0;
        }
        if (argv[1] == modes::test) {
            if (argc != 3) {
                throw argumentsException("ERROR:Wrong amount of arguments!");
            }
            paramsTest params = { argv[2] };
            runModeTest(params);
            return 0;
        }
		if (argv[1] == modes::hex) {
			if (argc != 4) {
				throw argumentsException("ERROR:Wrong amount of arguments!");
			}
			if (atoi(argv[3]) < 0) {
				throw argumentsException("ERROR:Size can't be less 0!");
			}
			paramsHex params = { argv[2], (size_t)atoi(argv[3]) };
			runModeHex(params);
			return 0;
		}
        if (argv[1] == modes::readheader) {
            if (argc != 4) {
                throw argumentsException("ERROR:Wrong amount of arguments!");
            }
            bool needToPrint;
            if (argv[3][0] == '1') {
                needToPrint = true;
            }
            else {
                needToPrint = false;
            }
            paramsReadHeader params = { argv[2] , needToPrint };
            runModeReadHeader(params);
            return 0;
        }
        throw argumentsException("ERROR:Wrong arguments!");
    }
    catch (argumentsException e) {
        std::cout << e.what() << std::endl;
        runModeHelp();
    }
    catch (fileException e) {
        std::cout << e.what() << std::endl;
    }
    catch (notImplementedException e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
