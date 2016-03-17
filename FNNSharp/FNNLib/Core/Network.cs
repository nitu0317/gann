using FNNLib.Core.Layers;
using FNNLib.Util.Helpers;
using MathNet.Numerics;
using MathNet.Numerics.Interpolation;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;

namespace FNNLib.Core
{
    /// <summary>
    /// Defines a network for a generalized artificial neural network,.
    /// </summary>
    public class Network
    {
        public Network()
        {
            layers = new List<ILayer>();
        }

        /// <summary>
        /// Feeds the network forward with some input
        /// </summary>
        /// <param name="input">The input of the network : A</param>
        /// <returns>The output of the network : B</returns>
        public object FeedForward(object input)
        {
            if (layers.Count() == 0)
                return input;

            if (AType.IsInstanceOfType(input))
            {
                if (layers.Count() == 0)
                    return input;
                else
                    layers[0].FeedForward(input);

                for (int i = 1; i < layers.Count(); i++)
                {
                    layers[i].FeedForward(layers[i - 1].Output);
                }

                return layers.Last().Output;
            }
            else
                throw new InvalidOperationException("Tried to apply the network to input of incorrect codomain.");
        }

        /// <summary>
        /// Runs the error backpropagation algorithm
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public double ErrorBackpropagate(object d, double lr)
        {
            if (!BType.IsInstanceOfType(d))
                throw new InvalidOperationException("The desired output is not compaitable with the neural network");

            if(layers.Count() == 0)
                throw new InvalidOperationException("There are no layers in the network.");

            //Calculate the error
            double error = layers.Last().Error(d);  


            ///Generalized Error Backpropagation
            List<Vector<double>> B = Enumerable.Range(0, L + 1).Select(x => Vector<double>.Build.Dense(1)).ToList();
            Vector<double> BError = Vector<double>.Build.Dense(layers.Last().Z_Y);

            List<Action> updates = new List<Action>();

            for (int n = 1; L-n >= 0; n++)
            {
                int l = L - n; //Agrees with paper definition.

                if (n == 1) //It is important to perform the output layer computation.
                    //Update the coefficients after the error backpropagation algorithm occurs.
                    updates.Add(() => layers[l].UpdateCoefficients(BError = layers[l].CalculateBError(d), lr));
                
                else //n > 1
                {
                    //Ensure that B_l+2,t from (2.3.19) is computed for all t \in Z_X^(l+1)
                    if (l + 2 == L)
                        B[L] = layers[l + 1].K * BError; //Notice that the first of (2.3.19) is the same as BError from (2.3.20) B=∫∑jᵇ[F(γ)-δ]Ψ djL.
                    else
                        B[l + 2] = layers[l + 1].K * B[l + 2];

                    //Then for all x,y Compute B_l+1
                    B[l + 1] = layers[l + 1].CalculateB(layers[l].Z_Y, B[l + 2]);

                    //Update the coefficient by using I outer B_lp1
                    updates.Add(() => layers[l].UpdateCoefficients(B[l + 1], lr));


                }

            }

            //Update all of the coefficients.
            updates.ForEach(x => x());

            return error;
        }

        /// <summary>
        /// Trains the network on an input/desired pair with a given learning rate.
        /// </summary>
        /// <param name="input"></param>
        /// <param name="desired"></param>
        /// <param name="lr"></param>
        /// <returns></returns>
        public double Train(object input, object desired, double lr)
        {
            FeedForward(input);
            return ErrorBackpropagate(desired, lr);
        }

        /// <summary>
        /// Adds a layer to the generalized artificial neural network.
        /// The layer must have B equal to the previously added layer.
        /// </summary>
        /// <param name="layer"></param>
        public void AddLayer(ILayer layer)
        {
            //We need to verify type congruence.
            if (layers.Count() != 0)
            {
                if (!layers.Last().BType.Equals(layer.AType))
                    throw new ArrayTypeMismatchException(
                        "Tried to add a layer to the network whose domain is not equivalent to the last layer's codomain.");
                else
                    this.layers.Add(layer);
            }
            else
            {
                layers.Add(layer);
                this.AType = layer.AType;
            }

            this.BType = layer.BType;
        }

        #region Properties

        /// <summary>
        /// The input type of the neural network
        /// </summary>
        public Type AType { get; protected set; }

        /// <summary>
        /// The output type of the nerual network.
        /// </summary>
        public Type BType { get; protected set; }

        public object Output 
        {
            get
            {
                if (layers.Count() == 0)
                    throw new InvalidOperationException("There are no layers in the network.");
                return layers.Last().Output;
            }
        }


        public int L
        {
            get
            {
                return layers.Count();
            }
        }

        #endregion Properties

        #region Fields

        private List<ILayer> layers;

        #endregion Fields
    }
}