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

#include <utilities_js.hpp>

//rapidjson headers
#if defined(__SSE4_2__)
#  define RAPIDJSON_SSE42
#elif defined(__SSE2__)
#  define RAPIDJSON_SSE2
#endif
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define ITERATION 10000

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
    timespec time1, time2; 
    json::Object obj;

    std::cout << std::setw(25) << "cajun";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++) {
        std::istringstream buff(jsonString);
        obj.Clear();
        json::Reader::Read(obj, buff);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::ostringstream out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++) {
        json::Writer::Write(obj, out);
        out.str("");
    }
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
    for (int i = 0; i < ITERATION; i++)
        json_spirit::read( buff, value );
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::ostringstream out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++) {
        json_spirit::write(value, out);
        out.str("");
    }
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
    JSONNode n;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++)
        n = libjson::parse(jsonString);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::string out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++)
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
    for (int i = 0; i < ITERATION; i++) {
        value = json_parse(jsonString.c_str());
        json_value_free(value);
    }
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
void jsonAveryBenchmark(std::string jsonString)
{
    std::istringstream buff(jsonString);
    timespec time1, time2; 
    json_spirit::mValue value;

    std::cout << std::setw(25) << "Avery";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    Utilities::JS::Node root;
    for (int i = 0; i < ITERATION; i++)
        Utilities::JS::Node::parse(jsonString.data(), jsonString.data() + jsonString.size(),root);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    std::ostringstream out;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++) {
        out << root;
        out.str("");
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);
    std::cout << std::endl;
}

/*
 * @brief function for RapidJSON benchmark
 *
 * @param jsonString test data as a string
 * @return none
 */
void rapidjsonBenchmark(std::string jsonString)
{
    timespec time1, time2; 
    using namespace rapidjson;
    Document d;

    std::cout << std::setw(25) << "RapidJSON";

    //Parsing the string
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++)
        d.Parse(jsonString.data());
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    printTimeDiff(time1, time2);

    //Serialize to string
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    for (int i = 0; i < ITERATION; i++) {
        sb.Clear();
        d.Accept(writer);
    }
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
    jsonAveryBenchmark(buff);
    jsonparserBenchmark(buff);
    rapidjsonBenchmark(buff);

    return 0;
}
