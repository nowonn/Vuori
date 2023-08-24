#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>

#define STREAM_PANIC(x) \
    do if(!x){\
        std::cerr << "[helper.cpp] "       \
                  << "Panicked on line "   \
                  << __LINE__              \
                  << ": Unable to create " \
                  << #x ;                  \
        std::exit(EXIT_FAILURE);           \
    } while(0)

// NOTE: CTAD (std::array<std::string, n>)
constexpr std::array makefile = {
    // Makefile name
    "Makefile",

    // Start of makefile
    ".SUFFIXES:\n"
    ".SUFFIXES: .c\n"
    "{src}.c{obj}.obj:\n"
    "\t$(CC) $(CPPFLAGS) $(CFLAGS) src/$(*B).c /Foobj/$(*B).obj\n"
    "\n"
    "CC=cl\n"
    // /wd(warning_number) - Disables warning_number warning
    // C4047: 'operator' : 'identifier1' differs in levels of indirection from 'identifier2'
    // C4201: nonstandard extension used : nameless struct/union
    // C4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
    // C4245: 'operator': conversion from 'type1' to 'type2', signed/unsigned mismatch
    // C4996: 'function/variable': This function or variable may be unsafe.
    "CFLAGS=/nologo /c /W4 /O2 /MD /wd4047 /wd4201 /wd4244 /wd4245 /wd4996\n"
    "CPPFLAGS=/Iinclude /Iassets/maps /DSTBI_ONLY_PNG /DMA_NO_ENCODING /DMA_NO_WAV /DMA_NO_FLAC /DMA_NO_GENERATION\n"
    "\n"
    "LD=link\n"
    "LDFLAGS=/NOLOGO /LIBPATH:obj /SUBSYSTEM:windows /INCREMENTAL:no /OPT:ref\n"
    "LDLIBS=user32.lib gdi32.lib\n"
    "\n"
    "RC=rc\n"
    "RCFLAGS=/nologo\n"
    "\n"
    "all: build\\Vuori.exe\n"
    "\n"
    "# Source object files\n",

    // Resource suffix inference rule recipe
    "\t$(RC) $(RCFLAGS) /fo$*.res $*.rc\n"
    "\n",

    // Clean target
    "clean:\n"
    "\t@del /q $(RCFILES)\n"
    "\t@del /q build\\history.log\n"
    "\t@del /q "
};

void generateFiles(const std::string& dirname);
void generateMakefile(const std::string& rootDir, bool shouldRemakeAssets);
bool generateHistoryLog(const std::string& rootDir);
std::set<std::string> openAndScanFiles(const std::string& filepath, const std::string& baseSourcePath);
std::set<std::string> generateSourceDependencies(std::ofstream& makefile);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
        return EXIT_FAILURE;
    }

    std::string rootDir = argv[1];

    bool shouldRemakeAssets = generateHistoryLog(rootDir);
    generateMakefile(rootDir, shouldRemakeAssets);

    return EXIT_SUCCESS;
}

// Function to generate .h and .c files for a sub-directory
void generateFiles(const std::string& baseDir, const std::string& subDirname) {
    // XXX remove this
    if(subDirname == "maps")
        return;
    //

    std::string headerFileName = "include\\" + subDirname + "_files.h";
    std::string sourceFileName = "src\\" + subDirname + "_files.c";

    std::ofstream headerFile(headerFileName);
    STREAM_PANIC(headerFile);

    std::ofstream sourceFile(sourceFileName);
    STREAM_PANIC(sourceFile);

    sourceFile << "#include \"" << subDirname << ".h\"" << std::endl;

    for (const auto& entry : std::filesystem::directory_iterator(baseDir + "\\" + subDirname)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string stem = entry.path().stem().string();

            headerFile << "INCLUDE(" << stem << ")" << std::endl;
            sourceFile << "DEFINE(" << stem << ")" << std::endl;
        }
    }
}

// Function to generate Makefile for all sub-directories
void generateMakefile(const std::string& rootDir, bool shouldRemakeAssets) {
    std::ofstream makefileStream(makefile[0]);
    STREAM_PANIC(makefileStream);

    makefileStream << makefile[1];

    if (!std::filesystem::is_directory("rc") || !std::filesystem::exists("rc"))
        std::filesystem::create_directory("rc");
    if (!std::filesystem::is_directory("rc\\" + rootDir) || !std::filesystem::exists("rc\\" + rootDir))
        std::filesystem::create_directory("rc\\" + rootDir);

    std::set<std::string> all_asset_files, special_files, subDirs;
    for (const auto& entry : std::filesystem::directory_iterator(rootDir)) {
        if (std::filesystem::is_directory(entry)) {
            std::string subdirName = entry.path().filename().string();
            std::string headerFileName = subdirName + "_files.h";
            std::string sourceFileName = subdirName + "_files.c";

            special_files.insert("include\\" + headerFileName);
            special_files.insert("src\\" + sourceFileName);
            subDirs.insert(subdirName);

            if(shouldRemakeAssets)
                generateFiles(rootDir, subdirName);

            makefileStream << "# " << rootDir << "\\" << subdirName << "\\ directory" << std::endl;

            std::set<std::string> asset_files;

            // This generates each target and its dependencies
            for (const auto& subEntry : std::filesystem::directory_iterator(entry.path())) {
                if (std::filesystem::is_regular_file(subEntry)) {
                    std::string fileName = subEntry.path().filename().string();
                    std::string stem = subEntry.path().stem().string();

                    std::string asset = "rc\\" + rootDir + "\\" + subdirName + "\\" + stem + ".res";
                    // XXX remove this
                    if(subdirName != "maps")
                    //
                        asset_files.insert(asset);
                    makefileStream << asset << ": "
                    //               << "rc\\" << rootDir << "\\" << subdirName << "\\" << stem + ".rc "
                                   << rootDir << "\\" << subdirName << "\\" << fileName << std::endl;

                    std::string rcFileName = "rc\\" + rootDir + "\\" + subdirName + "\\" + stem + ".rc";
                    if (!std::filesystem::is_directory("rc\\" + rootDir + "\\" + subdirName) || !std::filesystem::exists("rc\\" + rootDir + "\\" + subdirName))
                        std::filesystem::create_directory("rc\\" + rootDir + "\\" + subdirName);

                    std::ofstream rcFile(rcFileName);
                    STREAM_PANIC(rcFile);

                    rcFile << stem << "." << subdirName << " RCDATA " << "\"" << rootDir << "\\\\" << subdirName << "\\\\" << stem << "." << subdirName << "\"";
                }
            }

            makefileStream << std::endl
            // This creates the main target for this sub-directory
                           << subdirName << ": ";
            for (const auto& asset : asset_files)
                makefileStream << asset << " ";

            makefileStream << std::endl
                           << std::endl
            // Add suffix rule
                           << ".SUFFIXES: ." << subdirName << std::endl
                           << std::endl

            // Generate suffix rule for this sub-directory
                           << "{" << rootDir << "\\" << subdirName << "}."
                           << subdirName << "{rc\\" << rootDir << "\\" << subdirName << "}.res:"
                           << std::endl

                           << makefile[2];

            all_asset_files.insert(asset_files.begin(), asset_files.end());
        }
    }

    std::set<std::string> obj_files = generateSourceDependencies(makefileStream);

    // Put the objs (and other sets of things) into OBJFILES
    // and use it like RCFILES instead of using for range loop

    makefileStream << "RCFILES=";
    for (const auto& asset_file : all_asset_files)
        makefileStream << asset_file << " ";
    makefileStream << std::endl << std::endl

                   << "build\\Vuori.exe: ";
    for (const auto& subDir : subDirs)
        // XXX remove this
        if(subDir != "maps")
        //
            makefileStream << subDir << " ";
    for (const auto& obj_file : obj_files)
        makefileStream << obj_file << " ";
    makefileStream << std::endl
                   << "\t$(LD) $(LDFLAGS) ";
    for (const auto& obj_file : obj_files)
        makefileStream << obj_file << " ";
    makefileStream << "$(LDLIBS) $(RCFILES) /OUT:$@" << std::endl << std::endl

    //// NOTE: hidden dependency (keep this order)
                   << makefile[3];

    for (const auto& obj_file : obj_files)
        makefileStream << obj_file << " ";
    makefileStream << std::endl
                   << "\t@del /q ";
    for (const auto& special_file : special_files)
        makefileStream << special_file << " ";
    makefileStream << std::endl;
    ////
}

// Function to generate or update the history.log file
bool generateHistoryLog(const std::string& rootDir) {
    const std::string logFileName = "history.log";
    const std::string logFilePath = "build\\" + logFileName;

    std::set<std::string> existingFiles;
    if (std::filesystem::exists(logFilePath)) {
        // Read the existing contents of the history.log file to check for missing files later
        std::ifstream logFileRead(logFilePath);
        STREAM_PANIC(logFileRead);

        std::string line;
        while (std::getline(logFileRead, line)) {
            if(line.empty())
                continue;

            std::istringstream iss(line);
            std::string token;

            if (iss >> token && token == "File:" && iss >> token)
                existingFiles.insert(token);
            //else if(token == "Scanned" && iss >> token && token == "directory:" && iss >> token)
            //    std::cerr << "History log scanned directory " << token << std::endl;
            //else if(token == "Sub-directory:" && iss >> token)
            //    std::cerr << "\tsub-directory " << token << std::endl;
        }
    }

    std::ofstream logFile(logFilePath);
    STREAM_PANIC(logFile);

    logFile << "Scanned directory: " << rootDir << std::endl;

    std::vector<std::string> newFiles;

    // Append new sub-directory and file names to the history.log file and store them in newFiles vector
    for (const auto& entry : std::filesystem::directory_iterator(rootDir)) {
        if (std::filesystem::is_directory(entry)) {
            std::string subdirName = entry.path().filename().string();
            logFile << "Sub-directory: " << subdirName << std::endl;

            for (const auto& subEntry : std::filesystem::directory_iterator(entry.path())) {
                if (std::filesystem::is_regular_file(subEntry)) {
                    std::string fileName = subEntry.path().filename().string();
                    logFile << "File: " << fileName << std::endl;

                    // Remove the entry from existingFiles set, if it was already present
                    if (existingFiles.contains(fileName))
                        existingFiles.erase(fileName);
                    else
                        newFiles.push_back(fileName);
                }
            }
        }
    }

    if(existingFiles.empty() && newFiles.empty()){
        std::cerr << "No asset files were added/removed" << std::endl;
        return false;
    }

    // Append the names of missing files (if any) to the history.log file
    for (const std::string& missingFile : existingFiles)
        std::cerr << "Removed file: " << missingFile << std::endl;

    // Print the names of new files to the standard output
    for (const std::string& newFile : newFiles)
        std::cerr << "Added file: " << newFile << std::endl;

    return true;
}

std::set<std::string> openAndScanFiles(const std::string& filepath, const std::string& baseSourcePath) {
    std::set<std::string> openedFiles, includedFiles;

    auto scanFiles = [&](auto&& scanFiles, const std::string& filepath, const std::string& basePath = "include"){
        // Open file
        std::ifstream file(basePath + "\\" + filepath);
        /////// XXX: remove this when maps are fixed
        //if(filepath.substr(filepath.length() - 4, filepath.length() - 1) == ".map")
        //    return;
        //std::cerr << filepath.substr(filepath.length() - 4, filepath.length() - 1) << std::endl;
        ///////
        openedFiles.insert(filepath);
        if (!file){
            std::cerr << "Error: Cannot open file " << filepath << " while traversing " << basePath << std::endl;
            return;
        }

        std::string line;
        // Go through every line
        while (std::getline(file, line)) {
            if(line.empty())
                continue;

            std::istringstream iss(line);
            std::string token;

            // If the first token is not include, this line is skipped
            if (iss >> token && token != "#include")
                continue;

            // The token following the #include must be a quoted string
            if (iss >> token && token[0] == '\"' && token[token.length() - 1] == '\"'){
                ///// XXX: remove this when maps are fixed
                //std::cerr << token.substr(token.length() - 5, 4) << std::endl;
                if(token.length() > 4 && token.substr(token.length() - 5, 4) == ".map"){
                    //std::cerr << token.substr(token.length() - 5, 4) << std::endl;
                    continue;
                }
                /////
                // Remove the quotes from the filename
                includedFiles.insert(token.substr(1, token.length() - 2));
            }
        }

        // Recursively open and scan the included files that weren't opened yet
        for (const auto& includedFile : includedFiles)
            if (!openedFiles.contains(includedFile))
                scanFiles(scanFiles, includedFile);
    };

    // Start at src/ then go through include/
    scanFiles(scanFiles, filepath, baseSourcePath);

    return includedFiles;
}

std::set<std::string> generateSourceDependencies(std::ofstream& mk_stream){
    const std::string baseSourcePath = "src";
    std::set<std::string> obj_files;

    for (const auto& entry : std::filesystem::directory_iterator(baseSourcePath)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string filename = entry.path().filename().string();
            std::string stem = entry.path().stem().string();

            std::set<std::string> tmp = openAndScanFiles(filename, baseSourcePath);

            std::string obj_file = "obj\\" + stem + ".obj";
            obj_files.insert(obj_file);
            mk_stream << obj_file + ": ";
            mk_stream << baseSourcePath << "\\" << filename << " ";
            for (const auto& includeFilename : tmp)
                mk_stream << "include\\" << includeFilename << " ";
            mk_stream << std::endl;
        }

    }

    mk_stream << std::endl;

    return obj_files;
}
