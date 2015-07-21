using FNNLib.Core;
using FNNLib.Core.Layers;
using FNNLib.Experimentation;
using FNNLib.Util;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Linq;
using System.Threading;
using System.Windows.Forms;

namespace FNNSharp
{
    internal class Program
    {
        [STAThread]
        private static void Main(string[] args)
        {

            Network fnn = new Network();
            fnn.AddLayer(new FunctionalLayer(20, 20, Interval.UnitBall));


            #region Plotting Environment Setup
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            ShowPlot fPlot = new ShowPlot(
                (FuncInterpolation)fnn.FeedForward(
                new FuncInterpolation(x => x)), "f functional test");

            Thread t = new Thread(
                () => Application.Run(fPlot));



            t.Start();

            #endregion


            SquareSet ss = new SquareSet();
            ss.Load();

            Trainer trainer = new Trainer(fnn, ss);

            //trainer.Train(100000, 0.1, 1);

            Console.WriteLine("Mononomial Test");

            double lr = 1;
            while (true)
            {
                //Make 4 test examples.
                double error = Enumerable.Range(0, 4).Aggregate(0.0,
                    (val, i) => 
                        val + fnn.Train(FuncInterpolation.Mononomial(i), FuncInterpolation.Mononomial(i + 1), lr));
                    

                Console.WriteLine(error);
                if (Console.ReadKey().Key == ConsoleKey.A)
                    break;
                fPlot.Replot((FuncInterpolation)fnn.Output, "output");
            }

            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("Input x^" + i);

                fnn.FeedForward(FuncInterpolation.Mononomial(i));

                fPlot.Replot((FuncInterpolation)fnn.Output, "output");
                Console.ReadKey();
            }

            Console.ReadKey();
           






        }
    }
}