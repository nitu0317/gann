using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Experimentation
{

    public class DataPoint
    {

        public DataPoint(object input, object desired)
        {
            this.Input = input;
            this.Desired = desired;
        }


        /// <summary>
        /// Gets the input componenet of the datapoint
        /// </summary>
        public object Input { get; private set; }

        /// <summary>
        /// Gets the desired component of the data point.
        /// </summary>
        public object Desired { get; private set; }

    }


}
