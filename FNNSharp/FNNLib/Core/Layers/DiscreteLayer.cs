using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Linq;

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
            : this(Z_X, Z_Y, new Normal(0, 1), Sigmoid.HyperbolicTangent)
        {
        }

        /// <summary>
        /// Feeds an input vector forward.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override Vector<double> ForwardAction(Vector<double> input)
        {
            if (input.Count() != K.RowCount)
                throw new InvalidOperationException("Input vector of improper length");
            else
                return K.Transpose() * input; //As per the definition of neural computation.
        }

        /// <summary>
        /// Calculates the error for a discrete layer using the sum squared loss function
        /// </summary>
        /// <param name="desired">The desired output vector.</param>
        /// <returns></returns>
        protected override double CalculateError(Vector<double> desired)
        {
            if(desired.Count() != Output.Count())
                throw new InvalidOperationException("Desired output vector is of different dimensionality than that of the output vector.");


            //We use the 0.5||O - D||^2 loss function.
            return 0.5 * Math.Pow((desired - Output).L2Norm(),2);
        }

        /// <summary>
        /// Updates the coefficients of the weight matrix using a $\delta$.
        /// </summary>
        /// <param name="delta_lp1"></param>
        /// <param name="a">The learning rate.</param>
        public override void UpdateCoefficients(Vector<double> delta_lp1, double a)
        {
            throw new NotImplementedException();
        }
    }
}