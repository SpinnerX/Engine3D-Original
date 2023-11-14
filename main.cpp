#include <Logger/core/Logger.h>


int main(){
    Logger::info("Testing Logger working with formatCpp!\n");
    std::string filename1 = "out.txt";
    std::string filename2 = "logs.txt";
    Logger::saveLog(filename1);
    Logger::debugToFile(filename1, "This is testing and sending output to out.txt");

    Logger::saveLog(filename2);
    Logger::debugToFile(filename2, "This is testing that outputs sent to logs.txt");
    Logger::warnToFile(filename2, "This is a warning message!");
    // Logger::traceToFile(filename2, "This is a tracing message!");


    auto file = Logger::open("file2.txt");
    file.warn("This is opening a log file called file2.txt\n");
    file.debug("Another message being sent here!!!");

    return 0;
}