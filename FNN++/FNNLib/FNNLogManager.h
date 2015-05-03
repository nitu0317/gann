///=================================================================================================
// file:	FNNLogManager.h
//
// summary:	Declares the fnn log manager class
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

#include "FNNLoggable.h"

using std::string;


namespace fnn{

    ///=================================================================================================
    /// <summary>   Manager for logs. </summary>
    ///
    /// <remarks>   William, 4/29/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    class LogManager
    {
    public:

        ///=================================================================================================
        /// <summary>   Default constructor. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///-------------------------------------------------------------------------------------------------

        LogManager();

        ///=================================================================================================
        /// <summary>   Registers a log with the LogManager. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="logger">   The logger. </param>
        /// <param name="verbose">  true to verbose. </param>
        ///-------------------------------------------------------------------------------------------------

        void Register(Loggable* logger, bool verbose);

        ///=================================================================================================
        /// <summary>   Saves the set of all loggers under a directory and a sub directory. Consider is
        ///             main logger property. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="directory">    The directory to which to save. </param>
        ///-------------------------------------------------------------------------------------------------

        void Save(string directory);

        ///=================================================================================================
        /// <summary>   TODO: Consider adding loading functionality. </summary>
        ///
        /// <remarks>   William, 5/3/2015. </remarks>
        ///
        /// <param name="logger">   [in,out] If non-null, the logger. </param>
        /// <param name="log">      The log. </param>
        /// <param name="message">  The message. </param>
        ///-------------------------------------------------------------------------------------------------

        void Print(Loggable* logger, string log, string message);

    private:
        std::vector<fnn::Loggable*> loggers;
        std::list<string> verboseLog;
    };
}