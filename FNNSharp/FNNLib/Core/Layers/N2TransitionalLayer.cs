﻿using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using FNNLib.Util;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.Interpolation;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core.Layers
{
    /// <summary>
    /// Represents the N2 Transitional layer from the paper
    /// </summary>
    class N2TransitionalLayer : Layer<IInterpolation, Vector<double>>
    {
                /// <summary>
        /// Builds a n2 transitional layer with a given prior distribution.
        /// </summary>
        /// <param name="Z_X">The number of X priors.</param>
        /// <param name="Z_Y">The number of y priors.</param>
        /// <param name="R">The radius of integration.</param>
        /// <param name="dist">The prior distribution.</param>
        public N2TransitionalLayer(int Z_X, int Z_Y, Interval R,
            IContinuousDistribution dist, Sigmoid activation)
            : base(Z_X, Z_Y, dist, activation)
        {
            I = Vector<double>.Build.Dense(Z_X);  //As per (2.3.6)
            C = Vector<double>.Build.Dense(Z_Y);   //As per (2.3.7)
            this.R = R;
        }

        /// <summary>
        /// Builds a n2 transitional layer neural layer with unit gaussian priors and a default logistic sigmoid
        /// </summary>
        /// <param name="Z_X">The number of X priors.</param>
        /// <param name="Z_Y">The number of y priors.</param>
        /// <param name="R">The radius of integration.</param>
        public N2TransitionalLayer(int Z_X, int Z_Y, Interval R)
            : this(Z_X, Z_Y, R,
            new MathNet.Numerics.Distributions.Normal(0, 1),
            Sigmoid.HyperbolicTangent)
        { }

        protected override Vector<double> ForwardAction(IInterpolation input)
        {
            throw new NotImplementedException();
        }

        protected override double CalculateError(Vector<double> desired)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Back propagates with respect to some error vector on the next layer.
        /// </summary>
        /// <param name="B_lp1">The next error parameter.</param>
        /// <returns></returns>
        public override void UpdateCoefficients(Vector<double> B_lp1, double a)
        {
            K = K - a * I.OuterProduct(B_lp1); //Compute the outer product.
        }


        #region Properties

        /// <summary>
        /// The interval alonmg which the functional layer is disposed.
        /// </summary>
        public Interval R { get; set; }

        /// <summary>
        /// Evaluates the layers Psi values.
        /// </summary>
        public override Vector<double> Psi
        {
            get
            {
                return FuncInterpolation.ApplyFuncToVector(
                    x => this.Activation.Differentiate(x),
                    this.ActionOutput);
            }
        }


        #endregion

        #region Fields

        private Vector<double> I; //The interpolation from the paper.
        private Vector<double> C; //C_s^{(l)}

        #endregion


    }
}
