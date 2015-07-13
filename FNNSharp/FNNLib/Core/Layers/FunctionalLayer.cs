﻿using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using FNNLib.Util;
using MathNet.Numerics;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.Integration;
using MathNet.Numerics.Interpolation;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core.Layers
{
    public class FunctionalLayer : Layer<IInterpolation, IInterpolation>
    {
        /// <summary>
        /// Builds a functional layer with a given prior distribution.
        /// </summary>
        /// <param name="Z_X">The number of X priors.</param>
        /// <param name="Z_Y">The number of y priors.</param>
        /// <param name="R">The radius of integration.</param>
        /// <param name="dist">The prior distribution.</param>
        public FunctionalLayer(int Z_X, int Z_Y, Interval R,
            IContinuousDistribution dist, Sigmoid activation)
            : base(Z_X, Z_Y, dist, activation)
        {
            I = Vector<double>.Build.Dense(Z_X);  //As per (2.3.6)
            C = Vector<double>.Build.Dense(Z_Y);   //As per (2.3.7)
            this.R = R;
        }

        /// <summary>
        /// Builds a functional neural layer with unit gaussian priors and a default logistic sigmoid
        /// </summary>
        /// <param name="Z_X">The number of X priors.</param>
        /// <param name="Z_Y">The number of y priors.</param>
        /// <param name="R">The radius of integration.</param>
        public FunctionalLayer(int Z_X, int Z_Y, Interval R)
            : this(Z_X, Z_Y, R,
            new MathNet.Numerics.Distributions.Normal(0, 1),
            Sigmoid.HyperbolicTangent)
        { }

        /// <summary>
        /// Propogates the network forward.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override IInterpolation ForwardAction(IInterpolation input)
        {
            //As per (2.3.6)
            I = Vector<double>.Build.Dense(Z_X, (t) =>
                 Integrate.OnClosedInterval
                    ((j) =>  //int sigmoid * x^t
                        input.Interpolate(j)*Math.Pow(j,t),
                     R.A, R.B, 0.1 //TODO: Find acceptable error.
                    )
            );


            //As per (2.3.7)
            C = K.Transpose() * I;


            //As per (2.3.8)
            return   new FuncInterpolation(
                (j) =>
                {
                    //Construct a j power vector.
                    var J = Vector<double>.Build.Dense(Z_Y, y => Math.Pow(j, y));
                    //Return the dot product.
                    return J * C;
                }
            );

            
        }


        /// <summary>
        /// Back propagates with respect to some error vector on the next layer.
        /// </summary>
        /// <param name="B_lp1">The next error parameter.</param>
        /// <returns></returns>
        public  void UpdateCoefficients(Vector<double> B_lp1, double a)
        {
            K = K - a * I.OuterProduct(B_lp1); //Compute the outer product.
        }

        #region Properties
        /// <summary>
        /// The interval alonmg which the functional layer is disposed.
        /// </summary>
        public Interval R { get; set; }
        
        /// <summary>
        /// Calculates a layers Psi based on an action output.
        /// </summary>
        public IInterpolation Psi
        {
            get
            {
                return new FuncInterpolation(
                    y => Activation.Differentiate(ActionOutput.Interpolate(y))
                );
            }
        }

        #endregion

        #region Fields
        Vector<double> I; //The interpolation from the paper.
        Vector<double> C; //C_s^{(l)}
        #endregion

    }
}
