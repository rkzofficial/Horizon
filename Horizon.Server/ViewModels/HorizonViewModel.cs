using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Horizon.Server.ViewModels
{
    public class HorizonViewModel : Screen
    {
        public void Click()
        {
            Xceed.Wpf.Toolkit.MessageBox.Show("Clicked");
        }
    }
}
