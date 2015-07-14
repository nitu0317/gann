using FNNLib.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Experimentation
{ 
    /// <summary>
    /// Holds an abstract dataset.
    /// </summary>
    public abstract class DataSet : List<IDataPoint>
    {
        /// <summary>
        /// Load dataset into the list.
        /// </summary>
        public abstract void Load();

        /// <summary>
        /// Random used for the dataset extension (shuffle)
        /// </summary>
        public static Random r = new Random();

        /// <summary>
        /// An extension for all ILists and dataset which shuffles the order.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="list"></param>
        public DataSet Shuffle()
        {
            int n = this.Count;
            while (n > 1)
            {
                n--;
                int k = r.Next(n + 1);
                IDataPoint value = this[k];
                this[k] = this[n];
                this[n] = value;
            }

            return this;
        }

        /// <summary>
        /// Print the entire dataset
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            //Join all of the data points.
            return string.Join("\n",
                this.Select(x => "["
                + string.Join(",", x.Input)
                + "]---> ["
                + string.Join(",", x.Desired)
                + "]"));
        }
    }

}
