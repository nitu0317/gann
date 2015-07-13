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
    /// The abstract type for Layer which allows polymorphic 
    /// IEnumerable representation
    /// </summary>
    public interface ILayer
    {
        /// <summary>
        /// Returns the type of the domain.
        /// </summary>
        Type AType { get; }
        

        /// <summary>
        /// Returns the typer of the codomain.
        /// </summary>
        Type BType { get; }

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

    }



    /// <summary>
    /// Describes the general class of layers, \Sigma_l: A -> B.
    /// Subclasses include n,n1,n2, and f, all of which are described in the white paper.
    /// </summary>
    /// <typeparam name="A">The set from which the layer maps.</typeparam>
    /// <typeparam name="B">The set to which the layer maps.</typeparam>
    public abstract class Layer<A,B> : ILayer
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
		protected abstract B ForwardAction(A input);

        /// <summary>
        /// Calculates the generalized sigma output for a given layer.
        /// Apply g(T_l[σ] + β)
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public B FeedForward(A input)
        {
            //g(T_l[σ] + //β)
            
            return this.Activation.Interpolate((dynamic)ForwardAction(input));
        }


        /// <summary>
        /// Back propagates with respect to some error vector on the next layer.
        /// </summary>
        /// <param name="B_lp1">The next error parameter.</param>
        /// <returns></returns>
        //public abstract Vector<double> BackPropagate(Vector<double> B_lp1);

        /// <summary>
        /// A cached output from the feed forward action.
        /// </summary>
        public B Output { get; protected set; }


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
            get { return typeof(B);  }
        }
        #endregion

        #region Properties

        /// <summary>
        /// The coefficient weight matrix.
        /// </summary>
        public Matrix<double> K { get; protected set; } //The k coefficient matrix.

        /// <summary>
        /// The bias on each layer.
        /// </summary>
       // public B Bias { get; set; }

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
