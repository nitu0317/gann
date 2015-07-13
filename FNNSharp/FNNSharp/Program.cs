using FNNLib.Core;
using FNNLib.Core.Layers;
using FNNLib.Util;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace FNNSharp
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {


            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            ///Build arbitrary 100 layer functional neural networks.
            //while (true)
            //{
            //    Network fnn = new Network();
            //    for (int i = 0; i < 100; i++ )
            //    {
            //        fnn.AddLayer(new FunctionalLayer(10, 10, Interval.UnitBall));
            //    }


            //    ShowPlot fPlot = new ShowPlot((FuncInterpolation)fnn.FeedForward(
            //        new FuncInterpolation((x) => -x*x + 3*x - 2)), "f functional test");
            //    fPlot.ShowDialog();
            //}



            ///Build arbitrary discrete neural network.
            while(true)
            {
                Network nn = new Network();
                nn.AddLayer(new DiscreteLayer(2, 4));
                nn.AddLayer(new DiscreteLayer(4, 4));
                nn.AddLayer(new DiscreteLayer(4, 1));

                Vector<double> output = (Vector<double>)nn.FeedForward(Vector<double>.Build.Random(2));

                Console.WriteLine("o = " + output);
                Console.ReadKey();
            }

            Console.ReadKey();


        }
    }
}
