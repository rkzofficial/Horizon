using Networker.Server;
using Networker.Client;
using Networker.DefaultFormatter;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using Horizon.Console.Networking;
using Networker.Client.Abstractions;
using System.IO;
using MessagePack;
using Networker.Extensions.MessagePack;
using ProtoBuf;

namespace Horizon.Console
{
    public class GameClient
    {
        public GameClient()
        {
            var config = new ConfigurationBuilder()
                .AddJsonFile("AppSettings.json", false, true)
                .Build();

            var networkerSettings = config.GetSection("Horizon");

            Client = new ClientBuilder()
                .UseIp(networkerSettings.GetValue<string>("Address"))
                .UseTcp(networkerSettings.GetValue<int>("TcpPort"))
                .ConfigureLogging(loggingBuilder =>
                {
                    loggingBuilder.AddConfiguration(config.GetSection("Logging"));
                    loggingBuilder.AddConsole();
                })
                .UseMessagePack()
                .Build();
        }

        public IClient Client { get; set; }
    }

    internal class Program
    {
        public static void Main()
        {

            IConfiguration config = new ConfigurationBuilder()
                .AddJsonFile("AppSettings.json", false, true)
                .Build();

            var networkerSettings = config.GetSection("Horizon");

            var server = new ServerBuilder()
                .UseTcp(networkerSettings.GetValue<int>("TcpPort"))
                .ConfigureLogging(loggingBuilder =>
                {
                    loggingBuilder.AddConfiguration(config.GetSection("Logging"));
                    loggingBuilder.AddConsole();
                })
                .RegisterPacketHandler<ChatPacket, ChatPacketHandler>()
                .UseMessagePack()
                .Build();

            server.Start();

            //var gameClient = new GameClient();
            //gameClient.Client.Connect();

            //var packet = new ChatPacket
            //{
            //    Age = 18,
            //    Name = "MSGPACK",
            //    Message = "Hello MessagePack",
            //    Designation = "Programmer"
            //};

            while (server.Information.IsRunning)
            {
                Thread.Sleep(1000);
            }
        }
    }
}
