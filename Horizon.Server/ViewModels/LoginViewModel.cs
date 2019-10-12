using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Caliburn.Micro;
using Xceed.Wpf.Toolkit;
using Horizon.Server.Helper;
using PropertyChanged;
using Horizon.Server.EventModels;

namespace Horizon.Server.ViewModels
{
    public class LoginViewModel : Screen
    {
        private string _username;
        private string _password;
        private bool _clicked;
        private readonly IAPIHelper _apiHelper;
        private readonly EventAggregator _events;

        public LoginViewModel(IAPIHelper apiHelper, EventAggregator events)
        {
            _apiHelper = apiHelper;
            _events = events;
            Username = "horizon@horizon.com";
            Password = "Pass123!";
        }
        public string Username
        {
            get 
            { 
                return _username;
            }
            set 
            {
                _username = value;
            }
        }

        public string Password
        {
            get 
            {
                return _password;
            }
            set 
            {
                _password = value;
            }
        }

        public bool CanLogin
        {
            get
            {
                bool output = false;

                if(Username?.Length > 0 && Password?.Length > 0 && _clicked == false)
                {
                    output = true;
                }
                return output;
            }
        }

        public void Login()
        {
            _clicked = true;
            NotifyOfPropertyChange(() => CanLogin);
            try
            {
                //var result = _apiHelper.Authenticate(Username, Password);
                _events.PublishOnUIThread(new LogOnEvent());
            }
            catch (Exception ex)
            {
                Xceed.Wpf.Toolkit.MessageBox.Show(ex.Message);
            }
            _clicked = false;
            NotifyOfPropertyChange(() => CanLogin);
        }

    }
}
