using Caliburn.Micro;
using Horizon.Server.HandlePacket;
using Horizon.Server.ViewModels;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Networker.Extensions.MessagePack;
using Networker.Server.Abstractions;
using IServer = Horizon.Server.Interfaces.IServer;
using NIServer = Networker.Server.Abstractions.IServer;

namespace Horizon.Server.Networking
{
    public class Server : IServer
    {
        private readonly IServerBuilder _serverBuilder;
        private NIServer _server;
        private readonly ClientsViewModel _clientVm;
        public Server(IServerBuilder server, ClientsViewModel clientVm)
        {
            _clientVm = clientVm;
            _serverBuilder = server;
        }

        public void Start()
        {
            IConfiguration config = new ConfigurationBuilder()
                .AddJsonFile("AppSettings.json", false, true)
                .Build();

            var networkerSettings = config.GetSection("Horizon");

            _server = _serverBuilder
                .UseTcp(networkerSettings.GetValue<int>("TcpPort"))
                .ConfigureLogging(loggingBuilder =>
                {
                    loggingBuilder.AddConfiguration(config.GetSection("Logging"));
                    loggingBuilder.AddConsole();
                })
                .RegisterTypes(serviceCollection =>
                {
                    serviceCollection.AddSingleton(_clientVm);
                })
                .RegisterPacketHandler<ChatPacket, ChatPacketHandler>()
                .RegisterPacketHandler<ClientPacket, ClientPacketHandler>()
                .UseMessagePack()
                .Build();

            _server.Start();
        }

        public void Stop()
        {
            _server.Stop();
        }
    }
}
