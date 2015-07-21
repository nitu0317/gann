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
        public double ErrorBackpropagate(object desired, double lr)
        {
            if (!BType.IsInstanceOfType(desired))
                throw new InvalidOperationException("The desired output is not compaitable with the neural network");

            if(layers.Count() == 0)
                throw new InvalidOperationException("There are no layers in the network.");


            ///Functional Error Backpropagation
            ///TODO: MAKE GENERAL.

            List<Vector<double>> B = Enumerable.Range(0, L + 1).Select(x => Vector<double>.Build.Dense(1)).ToList();
            Vector<double> G = Vector<double>.Build.Dense(layers.Last().Z_Y);
            double error = layers.Last().Error(desired);

            IInterpolation d = (dynamic)desired;
            List<Action> updates = new List<Action>();

            for (int n = 1; L-n >= 0; n++)
            {
                int l = L - n; //Agrees with paper definition.

                FunctionalLayer layer = (dynamic)layers[l];

                if (n == 1) //It is important to perform the output layer computation.
                {

                    //As per (2.3.20)
                    G = Vector<double>.Build.Dense(layer.Z_Y,
                        y => Integrate.OnClosedInterval(
                                j => (layer.Output.Interpolate(j) - d.Interpolate(j))
                                    * layer.Psi.Interpolate(j)
                                    * Math.Pow(j, y),
                            layer.R.A, layer.R.B, 0.01) //0.1 ERROR

                    );

                    //Update the coefficients after the error backpropagation algorithm occurs.
                    updates.Add(() => layer.UpdateCoefficients(G, lr));
                }
                else //n > 1
                {
                    FunctionalLayer lp1 = (dynamic)layers[l + 1];


                    //Ensure that B_l+2,t from (2.3.19) is computed for all t \in Z_X^(l+1)
                    if (l + 2 == L)
                        B[L] = lp1.K * G; //Notice that the first of (2.3.19) is the same as G from (2.3.20) B=∫∑jᵇ[F(γ)-δ]Ψ djL.
                    else
                    {
                        FunctionalLayer lp2 = (dynamic)layers[l + 2];

                        B[l + 2] = lp1.K * (Matrix<double>.Build.Dense(lp2.Z_X, lp1.Z_Y,
                            (a, b) => Integrate.OnClosedInterval(
                                j => Math.Pow(j, a + b)
                                    * lp2.Psi.Interpolate(j),
                                lp2.R.A, lp2.R.B)
                            ) * B[l + 3]);

                        //Then for all x,y Compute B_l+1
                        Vector<double> B_lp1 = Matrix<double>.Build.Dense(lp1.Z_X, layer.Z_Y,
                            (a, y) => Integrate.OnClosedInterval(
                                j => Math.Pow(j, a + y)
                                    * lp1.Psi.Interpolate(j),
                                lp1.R.A, lp1.R.B)
                            ) * B[l + 2];

                        //Update the coefficient by using I outer B_lp1
                        updates.Add(() => layer.UpdateCoefficients(B_lp1, lr));

                    }



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