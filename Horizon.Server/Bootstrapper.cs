using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using Caliburn.Micro;
using Horizon.Server.EventModels;
using Horizon.Server.Helper;
using Horizon.Server.Interfaces;
using Horizon.Server.ViewModels;
using MessagePack.Formatters;
using Networker.Server;
using Networker.Server.Abstractions;
using IServer = Horizon.Server.Interfaces.IServer;

namespace Horizon.Server
{
    public class Bootstrapper : BootstrapperBase
    {
        private readonly SimpleContainer _container = new SimpleContainer();
        public Bootstrapper()
        {
            Initialize();
            ConventionManager.AddElementConvention<PasswordBox > (
            PasswordBoxHelper.BoundPasswordProperty,
            "Password",
            "PasswordChanged");
        }

        protected override void Configure()
        {
            _container.Instance(_container);

            _container
                .Singleton<IWindowManager, WindowManager>()
                .Singleton<EventAggregator>()
                .Singleton<IAPIHelper, APIHelper>()
                .Singleton<IServer, Networking.Server>()
                .Singleton<IServerBuilder, ServerBuilder>()
                .Singleton<ClientsEvent>()
                .Singleton<HorizonViewModel>()
                .Singleton<ShellViewModel>()
                .Singleton<ClientsViewModel>()
                .PerRequest<LoginViewModel>()
                .PerRequest<RemoteDesktopViewModel>();

            //GetType().Assembly.GetTypes()
            //    .Where(type => type.IsClass)
            //    .Where(type => type.Name.EndsWith("ViewModel"))
            //    .ToList()
            //    .ForEach(viewModelType => _container.RegisterPerRequest(
            //        viewModelType, viewModelType.ToString(), viewModelType));
        }
        protected override void OnStartup(object sender, StartupEventArgs e)
        {
            DisplayRootViewFor<ShellViewModel>();
        }

        protected override object GetInstance(Type service, string key)
        {
            return _container.GetInstance(service, key);
        }

        protected override IEnumerable<object> GetAllInstances(Type service)
        {
            return _container.GetAllInstances(service);
        }

        protected override void BuildUp(object instance)
        {
            _container.BuildUp(instance);
        }
    }
}
