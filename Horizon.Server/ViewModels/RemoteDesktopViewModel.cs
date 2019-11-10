using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Xceed.Wpf.Toolkit;

namespace Horizon.Server.ViewModels
{
    public class RemoteDesktopViewModel : PropertyChangedBase
    {

        public RemoteDesktopViewModel()
        {
            
        }

        public Uri RemoteImage { get; set; }

        public void Capture()
        {
            RemoteImage = new Uri("D:/OneAssist.jpg");            
        }
    }
}
