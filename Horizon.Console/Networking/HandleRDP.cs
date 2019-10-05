using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebSocketSharp;
using WebSocketSharp.Server;

namespace Horizon.Console.Networking
{
    public class HandleRDP : WebSocketBehavior
    {
        protected override void OnMessage(MessageEventArgs e)
        {
            var frame = e;
            System.Console.WriteLine(frame);
        }
    }
}
