using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using FNNLib.Util;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core.Layers
{
    public class DiscreteLayer : Layer<Vector<double>, Vector<double>>
    {
    
        /// <summary>
        /// Constructs a discrerte neural layer
        /// </summary>
        /// <param name="Z_X">The dimension of input vector</param>
        /// <param name="Z_Y">The dimension of output vectors</param>
        /// <param name="dist">The distribution of priors</param>
        /// <param name="activation">The activation function</param>
        public DiscreteLayer(int Z_X, int Z_Y,
            IContinuousDistribution dist, Sigmoid activation)
            : base(Z_X, Z_Y, dist, activation)
        {
        }

        /// <summary>
        /// Constructs a discrete neural layer with a normal distribtuion
        /// </summary>
        /// <param name="Z_X">The dimension of input vector</param>
        /// <param name="Z_Y">The dimension of output vectors</param>
        public DiscreteLayer(int Z_X, int Z_Y)
            : this(Z_X, Z_Y, new Normal(0,1), Sigmoid.HyperbolicTangent)
        {
        }


        /// <summary>
        /// Feeds an input vector forward.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override Vector<double> ForwardAction(Vector<double> input)
        {
            if(input.Count()!= K.RowCount)
                throw new InvalidOperationException("Input vector of improper length");
            else
                return K.Transpose() *input; //As per the definition of neural computation.

        }
    }
}
