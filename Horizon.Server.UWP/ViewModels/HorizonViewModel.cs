using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Popups;

namespace Horizon.Server.UWP.ViewModels
{
    public class HorizonViewModel : Screen
    {
        public async Task Click()
        {
            var message = new MessageDialog("Clicked");
            await message.ShowAsync();
        }
    }
}
