using FNNLib.Core;
using FNNLib.Core.Layers;
using FNNLib.Util;
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

            
            while (true)
            {
                Network fnn = new Network();
                fnn.AddLayer(new FunctionalLayer(100, 100, Interval.AbsoluteUnitBall));
                fnn.AddLayer(new FunctionalLayer(100, 100, Interval.AbsoluteUnitBall));
                ShowPlot fPlot = new ShowPlot((FuncInterpolation)fnn.FeedForward(
                    new FuncInterpolation((x) => x * x)), "f functional test");
                fPlot.ShowDialog();
            }

            Console.ReadKey();


        }
    }
}
