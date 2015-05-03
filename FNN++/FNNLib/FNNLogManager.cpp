///=================================================================================================
// file:	FNNLogManager.cpp
//
// summary:	Implements the fnn log manager class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNLogManager.h"

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
/// <param name="logger">   The logger. </param>
/// <param name="verbose">  true to verbose. </param>
///-------------------------------------------------------------------------------------------------

void fnn::LogManager::Register(Loggable* logger, bool verbose)
{
    this->loggers.push_back(logger);
    logger->SetVerbose(verbose);
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

    //Collect every logger.
    for (std::vector<fnn::Loggable*>::iterator it = loggers.begin();
        it != loggers.end(); it++)
    {

    }
}

void fnn::LogManager::Print(Loggable* logger, string log, string message)
{
    string out = logger->GetName() + "::" + log + "::" + message;
    
    std::cout << out << std::endl;
    this->verboseLog.push_front(out);
}