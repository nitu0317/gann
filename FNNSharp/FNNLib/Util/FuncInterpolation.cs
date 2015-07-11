using MathNet.Numerics.Integration;
using MathNet.Numerics.Interpolation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Util
{
    public class FuncInterpolation :IInterpolation
    {
        #region Fields
        private Func<double, double> proc;
        private Func<double, double> deriv = null;
        private Func<double, double> integ = null;
        #endregion

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

        #endregion

        #region Operators

        /// <summary>
        /// Constructs a pointwise construction of the addition operator along interpolation.
        /// </summary>
        /// <param name="f"></param>
        /// <param name="g"></param>
        /// <returns></returns>
        public static FuncInterpolation operator +(FuncInterpolation f, FuncInterpolation g)
        {
            Func<double,double> hproc = (x) => f.proc(x) + g.proc(x),
                hderiv = null , hinteg = null;

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
            Func<double, double> hproc = (x) =>  a / f.proc(x),
                hderiv = null, hinteg = null;

            if (f.SupportsDifferentiation)
                hderiv = (x) => - a * Math.Pow(f.proc(x),-2)*f.deriv(x); //by chain rule.

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
            Func<double, double> hproc = (x) => f.proc(x)* g.proc(x),
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
            return NewtonCotesTrapeziumRule.IntegrateAdaptive((this*g).Interpolate,
                region.A, region.B, 0.1);
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

        #endregion

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

        #endregion
    }
}
