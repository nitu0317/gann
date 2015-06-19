// FNN++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FNNNetwork.h"
#include "FNNDataSet.h"
#include "FNNLaplaceDataSet.h"
#include "FNNLogManager.h"
#include "FNNTrainer.h"

#include<iostream>
using namespace fnn;

int _tmain(int argc, _TCHAR* argv[])
{
    LogManager lm = LogManager();
  

    LaplaceDataSet ds = LaplaceDataSet();
    ds.Load();
        
    Network nn = Network();
    lm.Register(&nn, "fnn", true); 
        
    lm.Register(nn.AddLayer(10, 10), "ws1", false);
    lm.Register(nn.AddLayer(10, 10), "ws2", false);
        
    Trainer t = Trainer(nn, ds, ds);
    lm.Register(&t, "trainer", true);
        
        
    //Register the logs
        
        
    t.Train(10000, 0.1, false);
        
        
    lm.Save("LaplaceTrainingSession1.exe");
        
        
        
	return 0;
}

