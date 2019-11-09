using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Horizon.Server.Interfaces;

namespace Horizon.Server.ViewModels
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
            //_server.Start();
        }

    }
}
