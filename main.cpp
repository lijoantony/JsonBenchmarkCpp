/*
 * JsonBenchmarkCpp
 * A small program to compare perfomance of different json libs available
 * 
 * Currently supporting following libs,
 *
 * 1. Cajun
 * 2. json_spirit
 * 3. libjson
 * 4. json-parser
 *
 * Copyright Lijo Antony 2011
 * Distributed under Apache License, Version 2.0
 * see accompanying file LICENSE.txt
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>

//Cajun headers
#include <json/reader.h>
#include <json/writer.h>
#include <json/elements.h>

//json_spirit headers
#include <json_spirit.h>

//libjson headers
#include <libjson.h>

//json-parser headers
#define json_string __json_string
#include <json.h>
#undef json_string


/*
 * @brief A function to print time duration
 *
 * @param start starttime
 * @param end   endtime
 * @return none
 */
void printTimeDiff(timespec start, timespec end)
{
    timespec temp;

    if (end.tv_nsec > start.tv_nsec)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    } 
    else 
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    unsigned long long int usecs = (unsigned long long int)(temp.tv_sec) * 1000000 + (unsigned long long int)(temp.tv_nsec / 1000);

    std::cout << std::setw(25) << std::left << usecs;
}

/*
 * @brief function for cajun benchmark
 *
 * @param jsonString test data as a string
 * @return none
 */
void cajunBenchmark(std::string jsonString)
{
    std::istringstream buff(jsonString);
    timespec time1, time2; 
    json::Object obj;

    std::cout << std::setw(25) << "cajun";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    json::Reader::Read(obj, buff);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::ostringstream out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    json::Writer::Write(obj, out);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);
    std::cout << std::endl;
}

/*
 * @brief function for json_spirit benchmark
 *
 * @param jsonString test data as a string
 * @return none
 */
void jsonspiritBenchmark(std::string jsonString)
{
    std::istringstream buff(jsonString);
    timespec time1, time2; 
    json_spirit::mValue value;

    std::cout << std::setw(25) << "json_spirit";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    json_spirit::read( buff, value );
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::ostringstream out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    json_spirit::write(value, out);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);
    std::cout << std::endl;
}
/*
 * @brief function for libjson benchmark
 *
 * @param jsonString test data as a string
 * @return none
 */
void libjsonBenchmark(std::string jsonString)
{
    timespec time1, time2; 

    std::cout << std::setw(25) << "libjson";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    JSONNode n = libjson::parse(jsonString);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::string out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    out = n.write();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);
    std::cout << std::endl;
}

/*
 * @brief function for json-parser benchmark
 *
 * @param jsonString test data as a string
 * @return none
 */
void jsonparserBenchmark(std::string jsonString)
{
    timespec time1, time2; 
    json_value * value;

    std::cout << std::setw(25) << "json_parser";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    value = json_parse(jsonString.c_str());
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    std::cout << std::endl;
}
int main()
{

    std::ifstream ifs("data.json", std::ifstream::in);
    std::string buff = "";

    if(ifs.is_open())
    {
        while(!ifs.eof())
        {
            std::string temp;
            ifs >> temp;
            buff += temp;
        }
    }

    if(buff.empty())
    {
        std::cout << "No data available for test, exiting!" << std::endl;
        exit(1);
    }


    std::cout << std::setw(25) << std::left << "#library" 
              << std::setw(25) << std::left << "parsing"
              << std::setw(25) << std::left << "writing"
              << std::endl;

    cajunBenchmark(buff);
    jsonspiritBenchmark(buff);
    libjsonBenchmark(buff);
    jsonparserBenchmark(buff);

    return 0;
}
