namespace FNNLib.Core
{
    using System;

    namespace NeuralLibrary.NeuralNetwork
    {
        /// <summary>
        /// Defines some generic sigmoid activation function and its derivative.
        /// </summary>
        public class Sigmoid : FNNLib.Util.FuncInterpolation
        {
            /// <summary>
            /// Defines the sigmoid activation function by a function and its derivative.
            /// </summary>
            /// <param name="function"></param>
            /// <param name="derivative"></param>
            public Sigmoid(Func<double, double> function, Func<double, double> derivative)
                : base(function, derivative)
            {
            }

            #region Sigmoids

            /// <summary>
            /// The hyperbolic tangent activation function.
            /// </summary>
            public static Sigmoid HyperbolicTangent =
                new Sigmoid(x => Math.Tanh(x), x => 1 - Math.Pow(Math.Tanh(x), 2));

            public static Sigmoid HyperbolicStep =
                new Sigmoid(x => Math.Round(HyperbolicTangent.Interpolate(x)),
                    x => Math.Round(HyperbolicTangent.Differentiate(x)));

            public static Sigmoid Logistic =
                new Sigmoid(x => 1 / (1 + Math.Exp(-x)), x => Math.Exp(x) / Math.Pow(1 + Math.Exp(x), 2));

            public static Sigmoid Linear =
                new Sigmoid(x => x, x => 1);

            public static Sigmoid None =
                new Sigmoid(x => 0, x => 0);

            #endregion Sigmoids
        }
    }
}