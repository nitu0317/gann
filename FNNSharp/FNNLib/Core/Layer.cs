using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using FNNLib.Util;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core
{
    /// <summary>
    /// Describes the general class of layers, \Sigma_l: A -> B.
    /// Subclasses include n,n1,n2, and f, all of which are described in the white paper.
    /// </summary>
    /// <typeparam name="A">The set from which the layer maps.</typeparam>
    /// <typeparam name="B">The set to which the layer maps.</typeparam>
    public abstract class Layer<A,B>
    {
        /// <summary>
        /// Constructs a layer wutg a given prior distribution.
        /// </summary>
        /// <param name="Z_X"></param>
        /// <param name="Z_Y"></param>
        /// <param name="dist"></param>
        public Layer(int Z_X, int Z_Y,
            IContinuousDistribution dist, Sigmoid activation)
        {
            this.Z_X = Z_X;
            this.Z_Y = Z_Y;
            this.Activation = activation;

            K = Matrix<double>.Build.Random(Z_X, Z_Y, dist);
        }

        /// <summary>
        /// Feeds the algorithm forward, yielding an output.
        /// We do not wish to contain anterior layers, and let the network handle propagation
        /// in an interative fashion.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public abstract B FeedForward(A input);


        /// <summary>
        /// A cached output from the feed forward action.
        /// </summary>
        public B Output { get; protected set; }




        #region Properties

        /// <summary>
        /// The coefficient weight matrix.
        /// </summary>
        public Matrix<double> K { get; protected set; } //The k coefficient matrix.

        /// <summary>
        /// The row size of the K matrix.
        /// </summary>
        public int Z_X { get; private set; }

        /// <summary>
        /// The column size of the K matrix.
        /// </summary>
        public int Z_Y { get; private set; }

        public Sigmoid Activation { get; protected set; }

        #endregion
    }
}
