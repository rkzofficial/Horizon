using Caliburn.Micro;
using Horizon.Server.UWP.EventModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Horizon.Server.UWP.ViewModels
{
    public class ShellViewModel : Conductor<object>, IHandle<LogOnEvent>
    {
        private readonly EventAggregator _events;
        private readonly SimpleContainer _container;
        private readonly HorizonViewModel _horizonVM;
        public ShellViewModel(HorizonViewModel horizonVM, EventAggregator events, SimpleContainer container)
        {
            _events = events;
            _container = container;
            _horizonVM = horizonVM;

            _events.Subscribe(this);

            ActivateItem(_container.GetInstance<LoginViewModel>());
        }

        public void Handle(LogOnEvent message)
        {
            ActivateItem(_horizonVM);
        }
    }
}
