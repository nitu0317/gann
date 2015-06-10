///=================================================================================================
// file:	FNNLog.h
//
// summary:	Declares the fnn log class
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
#include<list>
using std::string;
using std::list;

namespace fnn{
    ///=================================================================================================
    /// <summary>   A log. </summary>
    ///
    /// <remarks>   William, 4/29/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    class Log
    {
    public:

        ///=================================================================================================
        /// <summary>   Default constructor. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///-------------------------------------------------------------------------------------------------

        FNNLIB Log();

        ///=================================================================================================
        /// <summary>   Constructs the log with a name and a vocality. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="name">     The name. </param>
        /// <param name="verbose">  true to vocal. </param>
        ///-------------------------------------------------------------------------------------------------

        FNNLIB Log(string name, bool verbose);

        ///=================================================================================================
        /// <summary>   Pushes an object onto this log. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <param name="message">  The message to push. </param>
        ///-------------------------------------------------------------------------------------------------

        void FNNLIB Push(string message);

        ///=================================================================================================
        /// <summary>   Gets the content of the log. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <returns>   null if it fails, else the content. </returns>
        ///-------------------------------------------------------------------------------------------------

        list<string>* GetContent();


        ///=================================================================================================
        /// <summary>   Gets the name. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <returns>   The name. </returns>
        ///-------------------------------------------------------------------------------------------------

        string FNNLIB GetName();

        ///=================================================================================================
        /// <summary>   Query if this object is verbose. </summary>
        ///
        /// <remarks>   William, 4/29/2015. </remarks>
        ///
        /// <returns>   true if verbose, false if not. </returns>
        ///-------------------------------------------------------------------------------------------------

        bool FNNLIB IsVerbose();

    private:

        /// <summary>   The content of the log by line. </summary>
        list<string> content;

        /// <summary>   The name of the log. </summary>
        string name;

        /// <summary>   true to verbose. </summary>
        bool verbose;
    };
}