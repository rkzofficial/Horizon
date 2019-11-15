using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Horizon.Server.ViewModels;
using MessagePack;
using Microsoft.Extensions.Logging;
using Networker.Common;
using Networker.Common.Abstractions;

namespace Horizon.Server.HandlePacket
{
    [MessagePackObject]
    public class ClientPacket
    {
        [Key(0)]
        public virtual string Id { get; set; }
        [Key(1)]
        public virtual string Ping { get; set; }
        [Key(2)]
        public virtual string Ip { get; set; }
        [Key(3)]
        public virtual string CompName { get; set; }
        [Key(4)]
        public virtual string UserName { get; set; }
        [Key(5)]
        public virtual string Privilege { get; set; }
        [Key(6)]
        public virtual string Os { get; set; }
        [Key(7)]
        public virtual string Activity { get; set; }
        [Key(8)]
        public virtual string Usage { get; set; }
    }

    public class ClientPacketHandler : PacketHandlerBase<ClientPacket>
    {
        private readonly ILogger<ClientPacketHandler> _logger;
        private readonly ClientsViewModel _clientVm;

        public ClientPacketHandler(ILogger<ClientPacketHandler> logger, ClientsViewModel clientVm)
        {
            _clientVm = clientVm;
            _logger = logger;
        }

        public override async Task Process(ClientPacket packet, IPacketContext context)
        {
            _clientVm.AddClient(packet);
        }
    }
}
