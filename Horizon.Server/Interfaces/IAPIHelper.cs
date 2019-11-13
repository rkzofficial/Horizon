using Horizon.Server.Models;
using System.Threading.Tasks;

namespace Horizon.Server.Helper
{
    public interface IAPIHelper
    {
        Task<AuthenticatedUser> Authenticate(string username, string password);
    }
}