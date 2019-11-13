namespace Horizon.Server.Models
{
    public class Client
    {
        public string Id { get; set; }
        public string Ping { get; set; }
        public string Ip { get; set; }
        public string CompName { get; set; }
        public string UserName { get; set; }
        public string Privilege { get; set; }
        public string OS { get; set; }
        public string Activity { get; set; }
        public string Usage { get; set; }

        public Client(string ping, string ip, string comp, string userName, string privilege, string os, string activity, string usage, string id)
        {
            Ping = ping;
            Ip = ip;
            CompName = comp;
            UserName = userName;
            Privilege = privilege;
            OS = os;
            Activity = activity;
            Usage = usage;
            Id = id;
        }
    }

}
