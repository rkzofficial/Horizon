using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Horizon.Console.Networking;
using WebSocketSharp.Server;

namespace Horizon.Console
{
    internal class Program
    {
        public static void Main()
        {
            try
            {
                var server = new WebSocketServer(1997);
                server.AddWebSocketService<HandleRDP>("/RDP");
                server.Start();
                System.Console.WriteLine("Server started at : " + server.Address);
                System.Console.ReadKey(true);
                server.Stop();
            }
            catch (Exception e) when (e is NullReferenceException || e is InvalidOperationException)
            {
                System.Console.WriteLine(e);
            }
        }
    }
}
