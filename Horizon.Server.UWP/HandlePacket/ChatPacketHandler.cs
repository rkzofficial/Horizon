using System;
using System.Threading.Tasks;
using Windows.UI.Popups;
using MessagePack;
using Microsoft.Extensions.Logging;
using Networker.Common;
using Networker.Common.Abstractions;

namespace Horizon.Server.UWP.HandlePacket
{
    [MessagePackObject]
    public class ChatPacket
    {

        [Key(0)]
        public virtual int Age { get; set; }

        [Key(1)]
        public virtual string Name { get; set; }

        [Key(2)]
        public virtual string Message { get; set; }

        [Key(3)]
        public virtual string Designation { get; set; }
    }

    public class ChatPacketHandler : PacketHandlerBase<ChatPacket>
    {
        private readonly MessageDialog _msg = new MessageDialog("");
        private readonly ILogger<ChatPacketHandler> _logger;

        public ChatPacketHandler(ILogger<ChatPacketHandler> logger)
        {
            _logger = logger;
        }

        public override async Task Process(ChatPacket packet, IPacketContext packetContext)
        {
            _msg.Content = packet.Message;
            await _msg.ShowAsync();
        }
    }
}
