using Caliburn.Micro;
using Horizon.Server.UWP.EventModels;
using Horizon.Server.UWP.Helper;
using Horizon.Server.UWP.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Horizon.Server.UWP.Interfaces;

namespace Horizon.Server.UWP.ViewModels
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
                var output = Username?.Length > 0 && Password?.Length > 0 && _clicked == false;

                return output;
            }
        }

        public async Task Login()
        {
            _clicked = true;
            NotifyOfPropertyChange(() => CanLogin);
            var msg = new MessageDialog("");
            try
            {
                //var result = await _apiHelper.Authenticate(Username, Password);
                //msg.Content = "Login Successfull";
                //await msg.ShowAsync();
                _events.PublishOnUIThread(new LogOnEvent());

            }
            catch (HttpRequestException ex)
            {
                if (ex.InnerException != null) msg.Content = ex.InnerException.Message;
                await msg.ShowAsync();
            }
            _clicked = false;
            NotifyOfPropertyChange(() => CanLogin);
        }
    }
}
