using System.Threading.Tasks;
using Horizon.Server.UWP.Models;

namespace Horizon.Server.UWP.Helper
{
    public interface IAPIHelper
    {
        Task<AuthenticatedUser> Authenticate(string username, string password);
    }
}