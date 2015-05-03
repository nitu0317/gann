///=================================================================================================
// file:	FNNLogManager.cpp
//
// summary:	Implements the fnn log manager class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNLogManager.h"
#include "FNNLoggable.h"

#include <fstream>
#include <iostream>

///=================================================================================================
/// <summary>   Default constructor. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///-------------------------------------------------------------------------------------------------

fnn::LogManager::LogManager(void)
{
    this->loggers = std::vector<fnn::Loggable*>();
    this->verboseLog = std::list<string>();
}

///=================================================================================================
/// <summary>   Registers a log with the LogManager. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="logger">       [in,out] The logger. </param>
/// <param name="loggerName">   Name of the logger. </param>
/// <param name="verbose">      true to verbose. </param>
///-------------------------------------------------------------------------------------------------

void fnn::LogManager::Register(Loggable* logger, string loggerName, bool verbose)
{
    logger->Initialize(this, loggerName, verbose);
    this->loggers.push_back(logger);
}

///=================================================================================================
/// <summary>   Saves the set of all loggers under a directory and a sub directory. Consider is
///             main logger property. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="dir">  The directory to which to save. </param>
///-------------------------------------------------------------------------------------------------

void fnn::LogManager::Save(string dir)
{
    //Save the maiun log.

    //Collect every logger.
    for (std::vector<fnn::Loggable*>::iterator it = loggers.begin();
        it != loggers.end(); it++)
    {

    }
}

///=================================================================================================
/// <summary>   Prints a message to the verbose log. </summary>
///
/// <remarks>   William, 5/3/2015. </remarks>
///
/// <param name="logger">   [in,out] If non-null, the logger. </param>
/// <param name="log">      The log. </param>
/// <param name="message">  The message. </param>
///-------------------------------------------------------------------------------------------------

void fnn::LogManager::Print(Loggable* logger, string log, string message)
{
    string out = logger->GetName() + "::" + log + "::" + message;
    
    std::cout << out << std::endl;
    this->verboseLog.push_front(out);
}