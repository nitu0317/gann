using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Experimentation
{
    public interface IDataPoint
    {
        object Input { get; } //Gamma as per the paper.
        object Desired { get; } //Delta as per the paper.

        Type AType { get; }
        Type BType { get;  }
    }

    class DataPoint<A,B> :IDataPoint
    {

        public DataPoint(A input, B desired)
        {
            this.Input = input;
            this.Desired = desired;
        }


        /// <summary>
        /// Gets the input componenet of the datapoint
        /// </summary>
        public A Input { get; private set; }

        /// <summary>
        /// Gets the desired component of the data point.
        /// </summary>
        public B Desired { get; private set; }


        #region Properties

        /// <summary>
        /// Returns the type of the input.
        /// </summary>
        public Type AType {
            get
            {
                return typeof(A); 
            }
        }

        /// <summary>
        /// Returns the type of the desired
        /// </summary>
        public Type BType
        { 
            get
            {
                return typeof(B);
            }
        }
        #endregion

        #region Explicit IDataPoint

        /// <summary>
        /// Returns the input as an object
        /// </summary>
        object IDataPoint.Input 
        {
            get
            {
                return Input;
            }
        }

        /// <summary>
        /// Gets the desired comnponenet of the data point.
        /// </summary>
        object IDataPoint.Desired
        {
            get 
            {
                return Desired;
            }
        }

        #endregion
    }
}
