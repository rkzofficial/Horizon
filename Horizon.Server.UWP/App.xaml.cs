using Caliburn.Micro;
using Horizon.Server.UWP.Helper;
using Horizon.Server.UWP.ViewModels;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace Horizon.Server.UWP
{
    public sealed partial class App
    {
        private WinRTContainer _container;

        public App()
        {
            Initialize();
            InitializeComponent();
        }
        protected override void OnActivated(IActivatedEventArgs args)
        {
            base.OnActivated(args);

            DisplayRootViewFor<ShellViewModel>();
        }
        protected override void Configure()
        {
            _container = new WinRTContainer();

            _container.RegisterWinRTServices();



            _container
                .Singleton<IAPIHelper, APIHelper>();

            _container.PerRequest<ShellViewModel>();
            _container.PerRequest<LoginViewModel>();

            GetType().Assembly.GetTypes()
                .Where(type => type.IsClass)
                .Where(type => type.Name.EndsWith("ViewModel"))
                .ToList()
                .ForEach(viewModelType => _container.RegisterPerRequest(
                    viewModelType, viewModelType.ToString(), viewModelType));
        }

        protected override void PrepareViewFirst(Frame rootFrame)
        {
            _container.RegisterNavigationService(rootFrame);
        }

        protected override void OnLaunched(LaunchActivatedEventArgs args)
        {
            if (args.PreviousExecutionState == ApplicationExecutionState.Running)
                return;

            DisplayRootViewFor<ShellViewModel>();
            ApplicationView.GetForCurrentView().Consolidated += ViewConsolidated;
        }

        private void ViewConsolidated(ApplicationView sender, ApplicationViewConsolidatedEventArgs args)
        {
            App.Current.Exit();
        }

        protected override object GetInstance(Type service, string key)
        {
            return _container.GetInstance(service, key);
        }
        protected override Frame CreateApplicationFrame()
        {
            return base.CreateApplicationFrame();
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
