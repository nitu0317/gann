///=================================================================================================
// file:	FNNLoggable.h
//
// summary:	Declares the fnn loggable class
///-------------------------------------------------------------------------------------------------

#pragma once //DONT LOOK AT ME 2 MANY TIMES ;)

#ifdef FNNDLL
#ifdef FNNLIB_EXPORTS
#define FNNLIB  __declspec(dllexport)   // export DLL information
#else
#define FNNLIB  __declspec(dllimport)   // import DLL information
#endif
#else
#define FNNLIB
#endif

#include<string>
#include<vector>
#include<map>
#include<list>

#include "FNNLog.h"

using std::string;

namespace fnn{

    ///=================================================================================================
    /// <summary>   A loggable. </summary>
    ///
    /// <remarks>   William, 4/29/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    class Loggable{
    public:

        ///=================================================================================================
        /// <summary>   Constructs the logger </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="name"> The name. </param>
        ///-------------------------------------------------------------------------------------------------

        Loggable(string name);

        ///=================================================================================================
        /// <summary>   Logs a message to a specific log. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="log">      The log. </param>
        /// <param name="message">  The message. </param>
        ///-------------------------------------------------------------------------------------------------

        void Log(string log, string message, bool verbose=false);

        ///=================================================================================================
        /// <summary>   Adds a log. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="name"> The name. </param>
        ///-------------------------------------------------------------------------------------------------

        void AddLog(string name, bool verbose);

        ///=================================================================================================
        /// <summary>   Sets a verbose. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="verbose">  true to verbose. </param>
        ///-------------------------------------------------------------------------------------------------

        void SetVerbose(bool verbose);

        ///=================================================================================================
        /// <summary>   Query if this object is verbose. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <returns>   true if verbose, false if not. </returns>
        ///-------------------------------------------------------------------------------------------------

        bool IsVerbose();

        ///=================================================================================================
        /// <summary>   Gets the logs. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks> 
        ///
        /// <returns>   null if it fails, else the logs. </returns>
        ///-------------------------------------------------------------------------------------------------

        std::vector<fnn::Log*> GetLogs();

        ///=================================================================================================
        /// <summary>   Gets the name. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <returns>   The name. </returns>
        ///-------------------------------------------------------------------------------------------------

        string GetName();



    private:
        /// <summary>   The logs. </summary>
        std::map<string, fnn::Log> logs;


        /// <summary>   The name. </summary>
        string name;


        /// <summary>   true to verbose. </summary>
        bool verbose;
    };
}