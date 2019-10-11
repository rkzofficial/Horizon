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

namespace Horizon.Server.ViewModels
{
    public class LoginViewModel : Screen
    {
        private string _username;
        private string _password;
        private readonly IAPIHelper _apiHelper;
        private IWindowManager _windowManager;

        public LoginViewModel(IWindowManager windowManager, IAPIHelper apiHelper)
        {
            _windowManager = windowManager;
            _apiHelper = apiHelper;
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
                NotifyOfPropertyChange(() => CanLogin);
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
                NotifyOfPropertyChange(() => CanLogin);
            }
        }

        public bool CanLogin
        {
            get
            {
                bool output = false;

                if(Username?.Length > 0 && Password?.Length > 0)
                {
                    output = true;
                }
                return output;
            }
        }

        public async Task Login()
        {
            try
            {
                var result = await _apiHelper.Authenticate(Username, Password);
                _windowManager.ShowWindow(new HorizonViewModel(), null, null);
                TryClose();
                
            }
            catch (Exception ex)
            {
                Xceed.Wpf.Toolkit.MessageBox.Show(ex.Message);
            }
        }

    }
}
