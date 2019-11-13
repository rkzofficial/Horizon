using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Horizon.Server.EventModels;
using Horizon.Server.Interfaces;

namespace Horizon.Server.ViewModels
{
    public class HorizonViewModel : Conductor<Screen>
    {
        private readonly IServer _server;
        private readonly IWindowManager _windowManager;
        private readonly EventAggregator _events;
        private readonly SimpleContainer _container;
        public ClientsViewModel ClientsViewModel { get; set; }
        private readonly ClientsEvent _clientsEvent;

        public HorizonViewModel(IWindowManager windowManager, IServer server, SimpleContainer container, EventAggregator events, ClientsViewModel clientsVM, ClientsEvent clientsEvent)
        {
            _windowManager = windowManager;
            _server = server;
            _events = events;
            _container = container;
            //_clientsVM = clientsVM;
            _clientsEvent = clientsEvent;
        }

        //public void Handle(ClientsEvent message)
        //{
        //    ActivateItem(_clientsVM);
        //}

        public void Clients()
        {
            ActivateItem(_container.GetInstance<ClientsViewModel>());
            //MessageBox.Show("Clicked");
        }

    }
}
