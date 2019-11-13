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

namespace Horizon.Server.ViewModels
{
    public class RemoteDesktopViewModel : PropertyChangedBase
    {
        //public string Title { get; set; }
        public RemoteDesktopViewModel()
        {
            //Title = "Remote Desktop View Model";
        }

        public Uri RemoteImage { get; set; }

        public void Capture()
        {
            RemoteImage = new Uri("D:/OneAssist.jpg");            
        }
    }
}
