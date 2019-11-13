using System;
using Caliburn.Micro;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Horizon.Server.EventModels;

namespace Horizon.Server.ViewModels
{
    public class ShellViewModel : Conductor<object>, IHandle<LogOnEvent>
    {
        private readonly EventAggregator _events;
        private readonly IWindowManager _windowManager;
        private readonly SimpleContainer _container;
        private readonly HorizonViewModel _horizonVM;
        public ShellViewModel(HorizonViewModel horizonVM, EventAggregator events, SimpleContainer container, IWindowManager windowManager)
        {
            _events = events;
            _container = container;
            _horizonVM = horizonVM;
            _windowManager = windowManager;

            _events.Subscribe(this);

            ActivateItem(_container.GetInstance<LoginViewModel>());
        }

        public void Handle(LogOnEvent message)
        {
            ActivateItem(_horizonVM);
            
        }
    }
}
