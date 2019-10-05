using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Horizon.Console
{
    internal class Program
    {
        public static void Main()
        {
            try
            {
                throw new NotImplementedException();
            }
            catch (Exception e)
            {
                System.Console.WriteLine(e);
                System.Console.ReadLine();
            }
        }
    }
}
