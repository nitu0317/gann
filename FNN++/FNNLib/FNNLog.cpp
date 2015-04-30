///=================================================================================================
// file:	FNNLog.cpp
//
// summary:	Implements the fnn log class
///-------------------------------------------------------------------------------------------------

///=================================================================================================
/// <summary>   Constructs the log with a name and a vocality. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="name">     The name. </param>
/// <param name="verbose">  true to vocal. </param>
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNLog.h"

///=================================================================================================
/// <summary>   Constructs the log. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="name">     The name. </param>
/// <param name="verbose">  true to verbose. </param>
///-------------------------------------------------------------------------------------------------

fnn::Log::Log(string name, bool verbose)
{
    this->name = name;
    this->verbose = verbose;
    this->content = list<string>();
}

///=================================================================================================
/// <summary>   Gets the content of the log. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   null if it fails, else the content. </returns>
///-------------------------------------------------------------------------------------------------

list<string>* fnn::Log::GetContent(void)
{
    return &this->content;
}

///=================================================================================================
/// <summary>   Pushes an object onto this log. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <param name="message">  The message to push. </param>
///-------------------------------------------------------------------------------------------------

void fnn::Log::Push(string message)
{
    this->content.push_back(message);
}

///=================================================================================================
/// <summary>   Gets the name. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   The name. </returns>
///-------------------------------------------------------------------------------------------------

string fnn::Log::GetName(void)
{
	
    return this->name;
}

///=================================================================================================
/// <summary>   Query if this object is verbose. </summary>
///
/// <remarks>   William, 4/29/2015. </remarks>
///
/// <returns>   true if verbose, false if not. </returns>
///-------------------------------------------------------------------------------------------------

bool fnn::Log::IsVerbose(void)
{
	
    return this->verbose;
}

