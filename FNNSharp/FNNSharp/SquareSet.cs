using FNNLib.Experimentation;
using FNNLib.Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FNNSharp
{
    class SquareSet : DataSet
    {
        /// <summary>
        /// Generates a whole suite of operations on squaring functions.
        /// </summary>
        public override void Load()
        {
            //Start with random polynomials.
            IEnumerable<FuncInterpolation> Polynomials =
                Enumerable.Range(0, 20)
                    .Select(
                        i => Enumerable.Range(1, 10)
                            .Select(
                                j => FuncInterpolation.Polynomial(
                                    Enumerable.Range(0,i).Select(
                                        k => new Random().NextDouble()*2-1.0 
                                    ).ToArray()
                                )
                            )
                    ).Aggregate(
                        (c,a) => c.Union(a)
                    );

            //Add a datapoint specifyting the square.
            this.AddRange(Polynomials
                .Select(p => new DataPoint(p, p*p))
                );


        }
    }
}
