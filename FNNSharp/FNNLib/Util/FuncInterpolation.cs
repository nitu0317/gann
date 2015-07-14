using MathNet.Numerics.Interpolation;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;

namespace FNNLib.Util
{
    public class FuncInterpolation : IInterpolation
    {
        #region Fields

        private Func<double, double> proc;
        private Func<double, double> deriv = null;
        private Func<double, double> integ = null;

        #endregion Fields

        #region Constructors

        /// <summary>
        /// Defines a functional interepolation with only a procedure ]
        /// and no integratrion/differentiation capabilities.
        /// </summary>
        /// <param name="proc">The function representing the interpolation</param>
        public FuncInterpolation(Func<double, double> proc)
        {
            this.proc = proc;
        }

        /// <summary>
        /// Defines a functional interepolation with only a procedure ]
        /// and no integratrion/differentiation capabilities.
        /// </summary>
        /// <param name="proc">The function representing the interpolation</param>
        /// <param name="deriv">The derivative of the procedure.</param>
        public FuncInterpolation(Func<double, double> proc, Func<double, double> deriv)
        {
            this.proc = proc;
            this.deriv = deriv;
        }

        /// <summary>
        /// Defines a functional interepolation with only a procedure ]
        /// and no integratrion/differentiation capabilities.
        /// </summary>
        /// <param name="proc">The function representing the interpolation</param>
        /// <param name="deriv">The derivative of the procedure.</param>
        /// <param name="integ">The indefinite integral of the procedure.</param>
        public FuncInterpolation(Func<double, double> proc, Func<double, double> deriv,
            Func<double, double> integ)
        {
            this.proc = proc;
            this.deriv = deriv;
            this.integ = integ;
        }

        #endregion Constructors

        #region Operators

        /// <summary>
        /// Constructs a pointwise construction of the addition operator along interpolation.
        /// </summary>
        /// <param name="f"></param>
        /// <param name="g"></param>
        /// <returns></returns>
        public static FuncInterpolation operator +(FuncInterpolation f, FuncInterpolation g)
        {
            Func<double, double> hproc = (x) => f.proc(x) + g.proc(x),
                hderiv = null, hinteg = null;

            if (f.SupportsDifferentiation && g.SupportsDifferentiation)
                hderiv = (x) => f.deriv(x) + g.deriv(x); //by linearity of differentiation.
            if (f.SupportsIntegration && g.SupportsIntegration)
                hinteg = (x) => f.integ(x) + g.integ(x); //by linearity of integration.

            return new FuncInterpolation(hproc, hderiv, hinteg);
        }

        /// <summary>
        /// The pointwise scalar multiplication of function interpolations.
        /// </summary>
        /// <param name="a">A scalar by which to multiply</param>
        /// <param name="f">The function being scaled.</param>
        /// <returns></returns>
        public static FuncInterpolation operator *(double a, FuncInterpolation f)
        {
            Func<double, double> hproc = (x) => f.proc(x) * a,
                hderiv = null, hinteg = null;

            if (f.SupportsDifferentiation)
                hderiv = (x) => f.deriv(x) * a; //by linearity of differentiation.
            if (f.SupportsIntegration)
                hinteg = (x) => f.integ(x) * a; //by linearity of integration.

            return new FuncInterpolation(hproc, hderiv, hinteg);
        }

        /// <summary>
        /// The pointwise scalar multiplication of function interpolations.
        /// </summary>
        /// <param name="a">A scalar by which to multiply</param>
        /// <param name="f">The function being scaled.</param>
        /// <returns></returns>
        public static FuncInterpolation operator *(FuncInterpolation f, double a)
        {
            return a * f;
        }

        /// <summary>
        /// The pointwise addition operator of function interpolations.
        /// Defined using + and *.
        /// </summary>
        /// <param name="f"></param>
        /// <param name="g"></param>
        /// <returns></returns>
        public static FuncInterpolation operator -(FuncInterpolation f, FuncInterpolation g)
        {
            return f + (-1.0 * g);
        }

        /// <summary>
        /// The pointwise scalar division of function interpolations.
        /// </summary>
        /// <param name="a">A scalar by which to multiply</param>
        /// <param name="f">The function being scaled.</param>
        /// <returns></returns>
        public static FuncInterpolation operator /(FuncInterpolation f, double a)
        {
            if (a != 0)
                return (1.0 / a) * f;
            else
                throw new DivideByZeroException();
        }

        /// <summary>
        /// The pointwise scalar division of function interpolations.
        /// Integration cannot be defined in this case.
        /// </summary>
        /// <param name="a">A scalar by which to multiply</param>
        /// <param name="f">The function being scaled.</param>
        /// <returns></returns>
        public static FuncInterpolation operator /(double a, FuncInterpolation f)
        {
            Func<double, double> hproc = (x) => a / f.proc(x),
                hderiv = null, hinteg = null;

            if (f.SupportsDifferentiation)
                hderiv = (x) => -a * Math.Pow(f.proc(x), -2) * f.deriv(x); //by chain rule.

            //Integration cannot be defined.

            return new FuncInterpolation(hproc, hderiv, hinteg);
        }

        /// <summary>
        /// The pointwise functional multiplication of function interpolations.
        /// </summary>
        /// <param name="a">A scalar by which to multiply</param>
        /// <param name="f">The function being scaled.</param>
        /// <returns></returns>
        public static FuncInterpolation operator *(FuncInterpolation f, FuncInterpolation g)
        {
            Func<double, double> hproc = (x) => f.proc(x) * g.proc(x),
                hderiv = null, hinteg = null;

            if (f.SupportsDifferentiation && g.SupportsDifferentiation)
                hderiv = (x) => f.proc(x) * g.deriv(x) + f.deriv(x) * g.proc(x); //by the product rule.

            //Integration is not defined.

            return new FuncInterpolation(hproc, hderiv, hinteg);
        }

        /// <summary>
        /// Calculates the L2InnerProduct of two functions
        /// </summary>
        /// <param name="g"></param>
        /// <param name="region"></param>
        /// <returns></returns>
        public double L2InnerProduct(FuncInterpolation g, Interval region)
        {
            return MathNet.Numerics.Integrate.OnClosedInterval((this * g).Interpolate,
                region.A, region.B, 0.01);
        }

        /// <summary>
        /// Calculates the L2 norm of a function over its region.
        /// </summary>
        /// <param name="f"></param>
        /// <param name="region"></param>
        /// <returns></returns>
        public double L2Norm(Interval region)
        {
            return this.L2InnerProduct(this, region);
        }

        #endregion Operators

        #region Basic Types

        /// <summary>
        /// A easily construct4ed cosntant func interpolation.
        /// </summary>
        /// <param name="b"></param>
        /// <returns></returns>
        public static FuncInterpolation Constant(double b)
        {
            return new FuncInterpolation(
                (x) => b, //f
                (x) => 0, //f'
                (x) => b * x //int f
                    );
        }

        /// <summary>
        /// Creates a linear function
        /// </summary>
        /// <param name="m">The slope</param>
        /// <param name="b">The y intercept</param>
        /// <returns></returns>
        public static FuncInterpolation Linear(double m, double b)
        {
            return m * new FuncInterpolation(
                (x) => x,
                (x) => 1,
                (x) => 0.5 * x * x
                    ) + Constant(b);
        }

        /// <summary>
        /// Constructs a mononomial of degree p.
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        public static FuncInterpolation Mononomial(double p)
        {
            return new FuncInterpolation(
                (x) => Math.Pow(x, p),
                (x) => (p) * Math.Pow(x, p - 1),
                (x) => p == -1 ? //If some crazy ln stuff is occurring here.
                        Math.Log(x) :
                        1.0 / (p + 1) * Math.Pow(x, p + 1)
                    );
        }

        public static FuncInterpolation Polynomial(params double[] args)
        {
            if (args == null || args.Count() == 0)
                return Constant(0);
            else
                return args.Select((k, i) => k * Mononomial(i))
                    .Aggregate((a, b) => a + b);
        }


        /// <summary>
        /// Generates a Power Vector
        /// </summary>
        /// <param name="n">The highest power in the vector</param>
        /// <returns></returns>
        public static IEnumerable<FuncInterpolation> PowerVector(int n, FuncInterpolation multiplier)
        {

            return Enumerable.Range(0, n-1)
                .Select(i => 
                    new FuncInterpolation(
                        j => Math.Pow(j, i)
                    ) * multiplier
                );
          
        }

        /// <summary>
        /// Creates a power vector with no multiplier
        /// </summary>
        /// <param name="n"></param>
        /// <returns></returns>
        public static IEnumerable<FuncInterpolation> PowerVector(int n)
        {
            return Enumerable.Range(0, n - 1)
                .Select(i =>
                    new FuncInterpolation(
                        j => Math.Pow(j, i)
                    )
                );
        }

        

        #endregion Basic Types

        #region IInterpolation Explicit

        /// <summary>
        /// Checks to see if a derivative is specified and returns its evaluation at t.
        /// </summary>
        /// <param name="t">The value at which to evaluate the derivative.</param>
        /// <returns>The derivative evaluated at t.</returns>
        public double Differentiate(double t)
        {
            if (deriv != null)
                return deriv(t);
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// We do not implement second order differentiation explicitly.
        /// </summary>
        /// <param name="t">NA</param>
        /// <returns>NA</returns>
        public double Differentiate2(double t)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the evaluation of integration at a certain interval.
        /// </summary>
        /// <param name="a">The left end point.</param>
        /// <param name="b">The right end point.</param>
        /// <returns></returns>
        public double Integrate(double a, double b)
        {
            if (integ != null)
                return integ(b) - integ(a);
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// Integrates the procedure from 0 to t.
        /// </summary>
        /// <param name="t">The value at which to end the integration.</param>
        /// <returns></returns>
        public double Integrate(double t)
        {
            if (integ != null)
                return integ(t);
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the value of the procedure at some value t.
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public double Interpolate(double t)
        {
            return proc(t);
        }

        /// <summary>
        /// Returns whether or not differentiation is supported.
        /// </summary>
        public bool SupportsDifferentiation
        {
            get { return deriv == null; }
        }

        /// <summary>
        /// Returns whether or not integration is supported.
        /// </summary>
        public bool SupportsIntegration
        {
            get { return integ == null; }
        }

        #endregion IInterpolation Explicit

        #region IInterpolation Extensions

        #region IEnumerable

        /// <summary>
        /// Integrates a given vector over a set of vector ranges.
        /// </summary>
        /// <param name="inv"></param>
        /// <param name="inv"></param>
        /// <returns></returns>
        public IEnumerable<double> Integrate(IEnumerable<double> inv)
        {
            return inv.Select((x) => this.Integrate(x));
        }

        /// <summary>
        /// Interpolates a function applied to a given vector.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public IEnumerable<double> Interpolate(IEnumerable<double> inv)
        {
            return inv.Select(this.Interpolate);
        }

        /// <summary>
        /// Differentiates a function with respect to a given vector.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public IEnumerable<double> Differentiate(IEnumerable<double> inv)
        {
            return inv.Select(this.Differentiate);
        }

        #endregion IEnumerable

        #region Vector<double>

        /// <summary>
        /// Integrates a given vector over a set of vector ranges.
        /// </summary>
        /// <param name="inv"></param>
        /// <param name="inv"></param>
        /// <returns></returns>
        public Vector<double> Integrate(Vector<double> inv)
        {
            return ApplyFuncToVector((x) => this.Integrate(x), inv);
        }

        /// <summary>
        /// Interpolates a function applied to a given vector.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public Vector<double> Interpolate(Vector<double> inv)
        {
            return ApplyFuncToVector(this.Interpolate, inv);
        }

        /// <summary>
        /// Differentiates a function with respect to a given vector.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public Vector<double> Differentiate(Vector<double> inv)
        {
            return ApplyFuncToVector(this.Differentiate, inv);
        }

        #endregion Vector<double>

        #region Functional Composition

        /// <summary>
        /// Integrates a given vector over a set of vector ranges.
        /// </summary>
        /// <param name="inv"></param>
        /// <param name="inv"></param>
        /// <returns></returns>
        public FuncInterpolation Integrate(FuncInterpolation inv)
        {
            return new FuncInterpolation(
                (x) =>
                    this.Integrate(inv.Interpolate(x)));
        }

        /// <summary>
        /// Interpolates a function applied to a given function.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public FuncInterpolation Interpolate(FuncInterpolation inv)
        {
            return new FuncInterpolation(
                (x) =>
                    this.Interpolate(inv.Interpolate(x)));
        }

        /// <summary>
        /// Differentiates a function with respect to a given function.
        /// </summary>
        /// <param name="inv"></param>
        /// <returns></returns>
        public FuncInterpolation Differentiate(FuncInterpolation inv)
        {
            return new FuncInterpolation(
                (x) =>
                    this.Differentiate(inv.Interpolate(x)));
        }

        #endregion Functional Composition

        #endregion IInterpolation Extensions

        #region Helpers

        /// <summary>
        /// Applies funcs of double to vectors
        /// </summary>
        /// <param name="f"></param>
        /// <param name="v"></param>
        /// <returns></returns>
        public static Vector<double> ApplyFuncToVector(Func<double, double> f, Vector<double> v)
        {
            return Vector<double>.Build
                .DenseOfEnumerable(v.Select(f)); //Project the function on to the vector.
        }

        #endregion Helpers
    }
}