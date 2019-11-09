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
        private readonly IWindowManager _windowManager;

        public HorizonViewModel(IWindowManager windowManager, IServer server)
        {
            _windowManager = windowManager;
            _server = server;
        }
        public void Builder()
        {
            _windowManager.ShowWindow(new RemoteDesktopViewModel());
            //_server.Start();
        }

    }
}
