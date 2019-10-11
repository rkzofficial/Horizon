using System.Threading.Tasks;
using Horizon.Server.Models;

namespace Horizon.Server.Helper
{
    public interface IAPIHelper
    {
        Task<AuthenticatedUser> Authenticate(string username, string password);
    }
}