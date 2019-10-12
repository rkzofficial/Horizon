using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking.Sockets;
using Windows.UI.Popups;
using Horizon.Server.UWP.Interfaces;
using Horizon.Server.UWP.Networking;
using Networker.Extensions.MessagePack;
using Networker.Server;

namespace Horizon.Server.UWP.ViewModels
{
    public class HorizonViewModel : Screen
    {
        private readonly IServer _server;

        public HorizonViewModel(IServer server)
        {
            _server = server;
        }
        public void Click()
        {
            _server.Start();
        }
    }
}
