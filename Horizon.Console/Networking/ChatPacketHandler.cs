using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ProtoBuf;
using Microsoft.Extensions.Logging;
using Networker.Common;
using Networker.Common.Abstractions;

namespace Horizon.Console.Networking
{
    [ProtoContract]
    public class ChatPacket
    {
        //[Key(1)]
        //public virtual string Name { get; set; }

        [ProtoMember(1)]
        public virtual string Message { get; set; }
    }

    public class ChatPacketHandler : PacketHandlerBase<ChatPacket>
    {
        private readonly ILogger<ChatPacketHandler> _logger;

        public ChatPacketHandler(ILogger<ChatPacketHandler> logger)
        {
            _logger = logger;
        }

        public override async Task Process(ChatPacket packet, IPacketContext packetContext)
        {
            _logger.LogDebug("I received the chat message: " + packet.Message);
        }
    }
}
