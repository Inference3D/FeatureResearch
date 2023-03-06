//--------------------------------------------------
// A helper module for dealing with incoming arguments
//
// @author: Wild Boar
//
// @date: 2023-03-06
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/Parameters/Parameters.h>
#include <NVLib/StringUtils.h>

namespace NVL_Utils 
{
    class ArgReader
    {
    public:

        /**
         * @brief Load parameters from the command line arguments
         * @param argc The number of arguments
         * @param argv The argument values
         * @return The list of parameters found
         */
        inline static NVLib::Parameters * GetParameters(int argc, char ** argv) 
        {
            auto parser = CommandLineParser(argc, argv, GetParamKeys());
            parser.about("TBlock v1.0.0");

            if (parser.has("help")) 
            {
                parser.printMessage();
                return nullptr;
            }

            auto parameters = new NVLib::Parameters();

            parameters->Add("input", parser.get<String>("input"));
            parameters->Add("output", parser.get<String>("output"));
            parameters->Add("filename", parser.get<String>("filename"));
            parameters->Add("count", parser.get<String>("count"));

            return parameters;
        }        

    //--------------------------------------------------
    // Parameter Helpers
    //--------------------------------------------------

    /**
     * @brief Read an integer value from the parameters 
     * @param parameters The parameter collection
     * @param key The key that we are reading
     * @return int The resultant integer
     */
    inline static int ReadInteger(NVLib::Parameters * parameters, const string& key) 
    {
        if (!parameters->Contains(key)) throw runtime_error("Required key not found: " + key);
        auto value = parameters->Get(key);
        return NVLib::StringUtils::String2Int(value);
    }

    /**
     * @brief Read a double value from the parameters
     * @param parameters The parameter collection
     * @param key The key that we are reading
     * @return double The resultant double
     */
    inline static double ReadDouble(NVLib::Parameters * parameters, const string& key) 
    {
        if (!parameters->Contains(key)) throw runtime_error("Required key not found: " + key);
        auto value = parameters->Get(key);
        return NVLib::StringUtils::String2Double(value);
    }

    /**
     * @brief Read a string value from the parameters
     * @param parameters The parameter collection
     * @param key The key that we want
     * @return string The resultant string
     */
    inline static string ReadString(NVLib::Parameters * parameters, const string& key) 
    {
        if (!parameters->Contains(key)) throw runtime_error("Required key not found: " + key);
        return parameters->Get(key);
    }

    /**
     * @brief Add the logic to read a boolean from the input 
     * @param parameters The parameters that I am reading
     * @param key The key of the parameters being read
     * @return The resultant boolean value of the given parameter 
     */
    inline static bool ReadBoolean(NVLib::Parameters * parameters, const string& key) 
    {
        if (!parameters->Contains(key)) throw runtime_error("Required key not found: " + key);
        auto value = parameters->Get(key);
        return NVLib::StringUtils::String2Bool(value);
    }

    private:

        /**
         * Generate the parameter definition
         * @return The parameter definition as a string
         */
        inline static string GetParamKeys() 
        {
            const char * keys = 
                "{ help h usage ? |                       | Show help message                            }"
                "{ input          | Input                 | The folder containing the input files        }"
                "{ output         | Output                | The folder containing the output files       }"
                "{ filename       | card                  | Image template name --> [@fileName]_<id>.png }"
                "{ count          | 3                     | The location of the output folder            }"; 

            return string(keys);
        }
    };
}
