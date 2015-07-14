using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.LinearAlgebra;
using System;

namespace FNNLib.Core
{
    /// <summary>
    /// The abstract type for Layer which allows polymorphic
    /// IEnumerable representation
    /// </summary>
    public interface ILayer
    {
        /// <summary>
        /// Feeds a give layer forward using input as (AType)
        /// </summary>
        /// <param name="input">Feeds the input forward</param>
        /// <returns></returns>
        object FeedForward(object input);

        /// <summary>
        /// Gets the output of a layer.
        /// </summary>
        object Output { get; set; }

        /// <summary>
        /// Back propagates with respect to some error vector on the next layer.
        /// </summary>
        /// <param name="B_lp1">The next error parameter.</param>
        /// <returns></returns>
        void UpdateCoefficients(Vector<double> B_lp1, double a);

        /// <summary>
        /// Calculates the error of an output based on a desired object
        /// </summary>
        /// <param name="desired">The desired output</param>
        /// <returns>The error</returns>
        double Error(object desired);

        #region Properties


        /// <summary>
        /// The coefficient weight matrix.
        /// </summary>
        Matrix<double> K { get;  set; } //The k coefficient matrix.

        /// <summary>
        /// The row size of the K matrix.
        /// </summary>
        int Z_X { get;  }

        /// <summary>
        /// The column size of the K matrix.
        /// </summary>
        int Z_Y { get; }

        #endregion Properties

        #region Generic Type Information

        /// <summary>
        /// Returns the type of the domain.
        /// </summary>
        Type AType { get; }

        /// <summary>
        /// Returns the typer of the codomain.
        /// </summary>
        Type BType { get; }

        #endregion Generic Type Information
    }

    /// <summary>
    /// Describes the general class of layers, \Sigma_l: A -> B.
    /// Subclasses include n,n1,n2, and f, all of which are described in the white paper.
    /// </summary>
    /// <typeparam name="A">The set from which the layer maps.</typeparam>
    /// <typeparam name="B">The set to which the layer maps.</typeparam>
    public abstract class Layer<A, B> : ILayer
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
            this.Activation = activation;

            K = Matrix<double>.Build.Random(Z_X, Z_Y, dist);
        }

        /// <summary>
        /// Calculates the generalized sigma output for a given layer.
        /// Apply g(T_l[σ] + β)
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public B FeedForward(A input)
        {
            //g(T_l[σ] + //β)

            //Set output to g(T_l[σ]) and actionOutput to T_l[σ].
            return Output = this.Activation.Interpolate(
                (dynamic)(ActionOutput = ForwardAction(input)));
        }

        /// <summary>
        /// Calculates the error of an output based on a desired object
        /// </summary>
        /// <param name="desired">The desired output</param>
        /// <returns>The error</returns>
        public double Error(B desired)
        {
            if (Output == null)
                throw new InvalidOperationException("Error cannot be calculated."
                    + " The network may not have been fed forward.");

            return CalculateError(desired);
        }

        /// <summary>
        /// A cached output from the feed forward action.
        /// </summary>
        public B Output { get; private set; }

        protected B ActionOutput { get; private set; }

        #region Abstract Actions

        /// <summary>
        /// Feeds the algorithm forward, yielding an output.
        /// We do not wish to contain anterior layers, and let the network handle propagation
        /// in an interative fashion.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected abstract B ForwardAction(A input);

        /// <summary>
        /// Calculates the error of an output based on a desired object
        /// </summary>
        /// <param name="desired">The desired output</param>
        /// <returns>The error</returns>
        protected abstract double CalculateError(B desired);

        /// <summary>
        /// Back propagates with respect to some error vector on the next layer.
        /// </summary>
        /// <param name="B_lp1">The next error parameter.</param>
        /// <returns></returns>
        public abstract void UpdateCoefficients(Vector<double> B_lp1, double a);

        #endregion Abstract Actions

        #region ILayer

        /// <summary>
        /// Allows FeedForward to be handled in terms of objects.
        /// </summary>
        /// <param name="input">The input object STRICTLY of : A</param>
        /// <returns></returns>
        object ILayer.FeedForward(object input)
        {
            return FeedForward((A)input);
        }

        /// <summary>
        /// Explicitly implements he output yeield of a feed forward action.
        /// </summary>
        object ILayer.Output
        {
            get
            {
                return this.Output;
            }

            set
            {
                this.Output = (B)value;
            }
        }

        /// <summary>
        /// Calculates the error of an output based on a desired object
        /// </summary>
        /// <param name="desired">The desired output</param>
        /// <returns>The error</returns>
        double ILayer.Error(object desired)
        {
            return Error((B)desired);
        }

        /// <summary>
        /// Returns the type A of sets from which the layer maps
        /// </summary>
        public Type AType
        {
            get { return typeof(A); }
        }

        /// <summary>
        /// Returns the type B of sets from which the layer maps.
        /// </summary>
        public Type BType
        {
            get { return typeof(B); }
        }

        #endregion ILayer

        #region Properties

        /// <summary>
        /// The coefficient weight matrix.
        /// </summary>
        public Matrix<double> K { get; set; } //The k coefficient matrix.

        /// <summary>
        /// The bias on each layer.
        /// </summary>
        // public B Bias { get; set; }

        /// <summary>
        /// The row size of the K matrix.
        /// </summary>
        public int Z_X
        {
            get
            {
                return K.RowCount;
            }
        }

        /// <summary>
        /// The column size of the K matrix.
        /// </summary>
        public int Z_Y
        {
            get
            {
                return K.ColumnCount;
            }
        }

        public Sigmoid Activation { get; protected set; }

        #endregion Properties
    }
}