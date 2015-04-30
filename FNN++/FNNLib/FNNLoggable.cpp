///=================================================================================================
// file:	FNNLoggable.cpp
//
// summary:	Implements the fnn loggable class
///-------------------------------------------------------------------------------------------------

///=================================================================================================
/// <summary>   Constructs the logger. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="name"> The name. </param>
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNLoggable.h"
#include <iostream>

fnn::Loggable::Loggable(string name)
{
    this->name = name;
    this->logs = std::map<string, fnn::Log>();
    this->verbose = false;
}

///=================================================================================================
/// <summary>   Logs a message to a specific log. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="log">      The log. </param>
/// <param name="message">  The message. </param>
/// <param name="verbose">  Whether or not (upon creation of a new log the log is verbose) </param>
///-------------------------------------------------------------------------------------------------

void fnn::Loggable::Log(string log, string message, bool verbose)
{
    if (logs.find(log) == logs.end())
        //if not found
        logs[log] = fnn::Log(log, verbose);
    

    //Add the message to the log.
    logs[log].Push(message);
    
    //Print the log.
    if (this->verbose && logs[log].IsVerbose())
        std::cout << this->name << "::" << log << ":: " << message;
}

///=================================================================================================
/// <summary>   Sets a verbose. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="verbose">  true to verbose. </param>
///-------------------------------------------------------------------------------------------------

void fnn::Loggable::SetVerbose(bool verbose)
{
    this->verbose = verbose;
}

///=================================================================================================
/// <summary>   Query if this object is verbose. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   true if verbose, false if not. </returns>
///-------------------------------------------------------------------------------------------------

bool fnn::Loggable::IsVerbose(void)
{
    return this->verbose;
}

///=================================================================================================
/// <summary>   Gets the logs. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   null if it fails, else the logs. </returns>
///-------------------------------------------------------------------------------------------------

std::vector<fnn::Log*> fnn::Loggable::GetLogs(void)
{
    std::vector<fnn::Log*> retList;
    for (std::map<std::string, fnn::Log>::iterator it = logs.begin();
        it != logs.end(); it++)
        //Send the adress of the value.
        retList.push_back(&(it->second));
    
    return retList;
}

///=================================================================================================
/// <summary>   Gets the name. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   The name. </returns>
///-------------------------------------------------------------------------------------------------

string fnn::Loggable::GetName(void)
{
	
    return this->name;
}

///=================================================================================================
/// <summary>   Adds a log. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="name"> The name. </param>
///-------------------------------------------------------------------------------------------------

void fnn::Loggable::AddLog(string name, bool verbose)
{
    this->logs[name] = fnn::Log(name, verbose);
}
