using Networker.Server;
using Networker.Client;
using Networker.Extensions.ProtobufNet;
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
                .UseProtobufNet()
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
                .UseProtobufNet()
                .Build();

            server.Start();

            var gameClient = new GameClient();
            gameClient.Client.Connect();

            var packet = new ChatPacket
            {
                Message = "Hello Google Protobuf"
            };

            using (var file = File.Create("chat.bin"))
            {
                Serializer.Serialize(file, packet);
            }

            while (server.Information.IsRunning)
            {
                gameClient.Client.Send(packet);

                Thread.Sleep(1000);
            }
        }
    }
}
