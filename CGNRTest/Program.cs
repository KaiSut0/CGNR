using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CGNR;

namespace CGNRTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var csrVal = new double[]
            {
                1.0, 1.0,
                1.0,-1.0,
                     1.0
            };
            var csrColInd = new int[]
            {
                0, 1,
                0, 1,
                   1
            };
            var csrRowPtr = new int[]
            {
                0, 2, 4, 5
            };
            var b = new double[]
            {
                4, 0, 1
            };
            var x = new double[]
            {
                0.0, 0.0
            };
            double threshold = 1e-10;
            int iterationMax = 10;

            var cgnr = new CGNRWrapper();
            var result = cgnr.CGNRForRect(3, 2, csrRowPtr, csrColInd, csrVal, b, x, threshold, iterationMax);

            for(int i = 0; i < 2; i++)
                System.Console.WriteLine(result[i].ToString());

            System.Console.ReadLine();
        }
    }
}
