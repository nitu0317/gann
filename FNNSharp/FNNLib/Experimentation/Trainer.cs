﻿using FNNLib.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Experimentation
{

    /// <summary>
    /// Trains the a neural network given a DataSet
    /// </summary>
    public class Trainer
    {
        public Trainer(Network network, DataSet trainingSet, bool online = true) :
            this(network, trainingSet, trainingSet, online)
        {
        }

        public Trainer(Network network, DataSet trainingSet, DataSet testingSet, bool online = true)
        {
            this.trainingSet = trainingSet;
            this.network = network;
            this.ErrorHistory = new List<double>();
            this.testingSet = testingSet;
            this.online = online;
        }

        /// <summary>
        /// Treains the neural network over a given number of epochs using backpropagation.
        /// </summary>
        /// <param name="epochs">THe number of iterations to which the neural network will train before failing.</param>
        /// <param name="minimumError">The minimum error which the network must reach to </param>
        /// <param name="learningRate">The learning rate at which the network will begin to learn.</param>
        /// <param name="momentum">The momentum at which the network will begin to learn.</param>
        /// <param name="nudging">Enables nudging of the neural network during training.</param>
        /// <returns>Whether or not the network was successful in learning.</returns>
        public int Train(int epochs, double minimumError, double lr, bool nudging = false)
        {
            ErrorHistory.Clear();
            int epoch = 0;
            double error = 0;

            do
            {
                epoch++;

                //Train online or perform batch training
                if (online)
                    error = trainingSet.Select
                        (
                            dp => network.Train(dp.Input, dp.Desired, lr)
                        ).Sum();

                //else //TODO: Implement batch training.
                //    error = network.Train(trainingSet, lr);

                this.ErrorHistory.Add(error);

                //NUDGING
                //if (nudging && ErrorHistory
                //    .SkipWhile(i => i < ErrorHistory.Count() - 10)
                //    .StdDev() < .0000075)
                //{
                //    network.NudgeWeights(); //Nudge the weights
                //}

#if DEBUG
                Console.WriteLine("Epoch {0}: Error = {1};", epoch, error);
#endif
            }
            while (epoch < epochs && error > minimumError);
            return epoch;
        }

        #region Properties

        /// <summary>
        /// The error history for a given training session (nn);
        /// </summary>
        public List<double> ErrorHistory { private set; get; }

        #endregion Properties

        #region Fields

        private Network network;
        private DataSet trainingSet;
        private DataSet testingSet;
        private bool online;

        #endregion Fields

        #region Helpers

        /// <summary>
        /// Bounds a double to a range.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public double Bound(double val, double min, double max)
        {
            return val > min && val < max ? val : val < min ? min : max;
        }

        #endregion Helpers
    }
}
