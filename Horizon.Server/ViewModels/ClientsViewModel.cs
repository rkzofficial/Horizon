using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Caliburn.Micro;
using Horizon.Server.Interfaces;
using Horizon.Server.Models;

namespace Horizon.Server.ViewModels
{
    public class ClientsViewModel : Screen
    {
        private readonly IWindowManager _windowManager;
        private Client _selected;
        public ObservableCollection<Client> Clients { get; set; }

        public Client SelectedClients
        {
            get => _selected;
            set
            {
                if (_selected == value) return;
                _selected = value;
                NotifyOfPropertyChange();
            }
        }

        public ClientsViewModel(IWindowManager windowManager)
        {
            _windowManager = windowManager;
            Clients = new ObservableCollection<Client>
            {
                new Client("34ms", "127.0.0.1", "DELL-PC", "rkh4c", "User", "Windows 10 Pro", "Google Chrome", "84%", "e229b1ab-3932-436a-b351-05e0472ebf28"),
                new Client("34ms", "127.0.0.1", "LENOVO-PC", "rajlk1317", "Admin", "Windows 10 Home", "", "54%", "e229b1ab-3932-436a-b251-05e0472ebf28"),
                new Client("44ms", "127.5.0.1", "HP-PC", "kirito", "User", "Windows 7 Ultimate", "Explorer", "44%", "e229b1b-3932-436a-b351-05e0472ebf28"),
                new Client("24ms", "127.0.0.1", "RAJ-PC", "kira", "Admin", "Windows 8.1", "Excel", "1%", "e229b1ab-3932-416a-b351-05e0472ebf28")
            };
        }

        public void AddButton()
        {
            Clients.Add(new Client("24ms", "127.0.0.1", "DELL-PC", "rkh4c", "Admin", "Windows 10 Pro", "Google Chrome", "84%", "e229b1ab-3932-436a-b351-05e0472ebf28"));
        }
        public void RemButton()
        {
            Clients.RemoveAt(0);
        }

        public void Delete()
        {
            Clients.Remove(SelectedClients);
        }

        public void Open()
        {
            foreach (Window w in Application.Current.Windows)
            {
                if ((string) w.Tag != SelectedClients.Id) continue;
                w.Focus();
                return;
            }

            dynamic settings = new ExpandoObject();
            settings.Tag = SelectedClients.Id;
            _windowManager.ShowWindow(new RemoteDesktopViewModel(),null, settings);
        }
    }
}
